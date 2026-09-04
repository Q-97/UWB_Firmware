/*****************************************************************************
 *  File: hal_uart.c
 *
 * Descirption: this file contains the functions support systick operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_uart.h"

ERROR_Type hal_uart_init(hal_uart_t *uart_config)
{
    UART_ConfigType config         = {0};
    ACTION_Type tx_int_en          = DISABLE;
    ACTION_Type rx_int_en          = DISABLE;
    int8_t      uart_irq_id        = UART0_IRQn;
    uint8_t     uart_clk_icg_shift = 0;
    uint32_t    gp_sel             = 0;
    uint32_t    init_count         = 0;
    int32_t     ret                = UART_SUCCESS; 
    
    if(NULL == uart_config)
    {
        return ERROR;
    }

    ZN_UartType *UARTx = UART_BASE(uart_config->uart_id);
    sys_clear_bit(CLK_ICG_REG,CLK_ICG_REG_UART_PCLK_ICG_SHIFT);   /*UART PCLK normal*/
    uart_clk_icg_shift = (0 == uart_config->uart_id) ? CLK_ICG_REG_UART_CLK_ICG_SHIFT : CLK_ICG_REG_UART1_CLK_ICG_SHIFT;
    sys_clear_bit(CLK_ICG_REG,uart_clk_icg_shift);    /*UART CLK normal*/

    tx_int_en = uart_config->is_tx_int_en ? ENABLE : DISABLE;
    rx_int_en = uart_config->is_rx_int_en ? ENABLE : DISABLE;

  
    if(0 == uart_config->uart_id)
    {
        pad_reg_write(UART0_TXD_PREG, 0x178);
        pad_reg_write(UART0_RXD_PREG, 0x178);
        uart_irq_id = UART0_IRQn;
    }
    else
    {
        gp_sel = (uart_config->group_sel << SEL_GROUP_SELGP_UART1_SHIFT) & SEL_GROUP_SELGP_UART1_MASK;
        gp_sel |= (pad_reg_read(SEL_GROUP) & (~SEL_GROUP_SELGP_UART1_MASK));
        pad_reg_write(SEL_GROUP, gp_sel);
        
        if(0 == uart_config->group_sel)
        {
            pad_reg_write(SWDIO_PREG,0x178 | GPIOA5_AF_UART1_RXD);
            pad_reg_write(SWCLK_PREG,0x178 | GPIOA6_AF_UART1_TXD);
        }
        else if(1 == uart_config->group_sel)
        {
            pad_reg_write(I2C0_SCL_PREG, 0x178 | GPIOA7_AF_UART1_RXD);
            pad_reg_write(I2C0_SDA_PREG, 0x178 | GPIOA8_AF_UART1_TXD);
        }
        else if(2 == uart_config->group_sel)
        {
            pad_reg_write(SPI0_CLK_PREG,0x178 | GPIOA9_AF_UART1_RXD);
            pad_reg_write(SPI0_MISO_PREG,0x178 | GPIOA10_AF_UART1_TXD);
        }
        uart_irq_id = UART1_IRQn;
    }
 
    uart_deinit(UARTx);
    config.uartClk = 38400000; /*uart clk 38.4M*/
    config.baudRate = uart_config->baurdrate;
    config.wordSize = WORD_SIZE_8;
    config.stopBits = LCR_STOP_BIT_1;
    config.parity = NONE;
    config.fifoEn = uart_config->is_block_mode ? FALSE : TRUE;
    config.callBack = uart_config->func;
    
    do
    {
        init_count++;
        sys_clear_bit(BLK_SW_RSTN0,(uart_config->uart_id ? BLK_SW_RSTN0_UART1_SW_RSTN_SHIFT : BLK_SW_RSTN0_UART_SW_RSTN_SHIFT)); /*UART_SW_RSTN reset*/
        sys_set_bit(BLK_SW_RSTN0,(uart_config->uart_id ? BLK_SW_RSTN0_UART1_SW_RSTN_SHIFT : BLK_SW_RSTN0_UART_SW_RSTN_SHIFT));   /*UART_SW_RSTN set*/
        if(init_count > 10)
        {
            return ERROR;
        }
        
        ret = uart_init(UARTx, &config);
    }while(ret);

    uart_set_rx_irq_available(UARTx,rx_int_en);
    uart_set_tx_irq_empty(UARTx,tx_int_en);

    if(uart_config->is_rx_int_en | uart_config->is_tx_int_en)
    {
        NVIC_EnableIRQ(uart_irq_id);
    }
    else
    {
        NVIC_DisableIRQ(uart_irq_id);
    }  
    return SUCCESS;
}

uint8_t hal_uart_get_rx_data(uint8_t id)
{
    ZN_UartType *uartx = UART_BASE(id);

    return uart_get_rx_data(uartx);
}

uint8_t hal_uart_get_int_state(uint8_t id)
{
    ZN_UartType *uartx = UART_BASE(id);

    return get_uart_interrupt_state(uartx);
}

uint8_t hal_uart_tx_buff_is_empty(uint8_t id)
{
    ZN_UartType *uartx = UART_BASE(id);

    return (get_uart_interrupt_state(uartx) & IIR_ISQ_THR_EMPTY);
}

uint8_t hal_uart_rx_buff_is_not_empty(uint8_t id)
{
    ZN_UartType *uartx = UART_BASE(id);

    return (get_uart_interrupt_state(uartx) & IIR_ISQ_RX_DATA);
}

uint8_t hal_uart_get_char(uint8_t id)
{
    uint8_t data = 0;
    ZN_UartType *uartx = UART_BASE(id);

    uart_getchar(uartx, &data);

    return data;
}

void hal_uart_put_char(uint8_t id, uint8_t data)
{
    ZN_UartType *uartx = UART_BASE(id);

    uart_putchar(uartx, data);
}

uint32_t hal_uart_send_data(uint8_t id, uint8_t *buf, uint32_t len)
{
    ZN_UartType *uartx = UART_BASE(id);
    
    for(uint16_t index = 0; index < len; index++)
    {
        uart_putchar(uartx, *(buf + index));
    }

    return len;
}

uint32_t hal_uart_get_rx_addr(uint8_t id)
{
    ZN_UartType *uartx = UART_BASE(id);
    
    return (uint32_t)(&uartx->RBR);
}

uint32_t hal_uart_get_tx_addr(uint8_t id)
{
    ZN_UartType *uartx = UART_BASE(id);
    
    return (uint32_t)(&uartx->THR);
}

