/*****************************************************************************
 *  File: zn_uart.h
 *
 *  Descirption: contains the functions support uart.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-26
 *
 *****************************************************************************/
#ifndef __ZN_UART_H__
#define __ZN_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_uart_reg.h"

#define __DEBUG__
 
#ifdef __DEBUG__
#define DPRINTF(...)  printf(__VA_ARGS__)  
#else
#define DPRINTF(...)
#endif

#define UART_SUCCESS  (0)
#define UART_BUSY     (-1)
#define UART_OTHER    (-2)

typedef enum{
    B4800=4800U,
    B9600=9600U,
    B14400=14400U,
    B19200=19200U,
    B38400=38400U,
    B56000=56000U,
    B57600=57600U,
    B115200=115200U,
    B128000=128000U,
    B230400=230400U,
    B256000=256000U,
    B460800=460800U,
    B500000=500000U,
    B512000=512000U,
    B600000=600000U,
    B750000=750000U,
    B921600=921600U,
    B1000000=1000000U,
    B1500000=1500000U,
    B2000000=2000000U,
}UART_Baudrate;

typedef enum{
    WORD_SIZE_5,
    WORD_SIZE_6,
    WORD_SIZE_7,
    WORD_SIZE_8
}UART_WordSize;

typedef enum{
    ODD,
    EVEN,
    NONE
}UART_Parity;

typedef enum{
    LCR_STOP_BIT_1,
    LCR_STOP_BIT_2
}UART_StopBit;



typedef struct {
    uint32_t uartClk;               /*UART clock*/
    UART_Baudrate baudRate;         /*uart baudrate */
    UART_WordSize wordSize;         /*5~9: select word length, 5~9 bits */
    UART_StopBit stopBits;          /*1: 1bit stop; 2: 2bits stop */
    UART_Parity  parity;            /*0: no parity; 1: odd; 2: even */
    uint8_t fifoEn;                 /*0: Disable; 1: Enable */
    //uint8_t dmaEn;                    /*0: disable DMA;  1: DMA_RX Enable; 2: DMA_TX enable; 3: DMATX & DMARX enable */
    DeviceCallback_Type callBack;   /*IRQ Callback pointer */
}UART_ConfigType;

int32_t uart_init(ZN_UartType *UARTx, const UART_ConfigType *config);
int32_t uart_deinit(ZN_UartType *UARTx);
int32_t uart_set_baudrate(ZN_UartType *UARTx, UART_Baudrate baudRate, uint32_t uartClk);
int32_t uart_set_parity(ZN_UartType *UARTx, UART_Parity parity);
int32_t uart_set_wordsize(ZN_UartType *UARTx, UART_WordSize wordsize);
int32_t uart_set_stopbit(ZN_UartType *UARTx, UART_StopBit stopbit);
int32_t uart_enable_fifo(ZN_UartType *UARTx);
int32_t uart_disable_fifo(ZN_UartType *UARTx);
int32_t uart_set_dma_mode(ZN_UartType *UARTx, uint8_t mode);
int32_t uart_set_loopback(ZN_UartType *UARTx);
int32_t uart_reset_loopback(ZN_UartType *UARTx);
int32_t uart_set_fifo_acess_mode(ZN_UartType *UARTx);
int32_t uart_reset_fifo_acess_mode(ZN_UartType *UARTx);
int32_t uart_set_fifo_trigger(ZN_UartType *UARTx,uint8_t rxTriggerLevel,uint8_t txTriggerLevel);
int32_t uart_set_tx_irq_empty(ZN_UartType *UARTx, ACTION_Type isEnable);
int32_t uart_set_rx_irq_available(ZN_UartType *UARTx, ACTION_Type isEnable);
int32_t uart_getchar(ZN_UartType *UARTx,uint8_t *ch);
int32_t uart_putchar(ZN_UartType *UARTx,uint8_t ch);
uint8_t uart_get_rx_data(ZN_UartType *UARTx);
uint8_t get_uart_interrupt_state(ZN_UartType *UARTx);

#ifdef __cplusplus
}
#endif

#endif
