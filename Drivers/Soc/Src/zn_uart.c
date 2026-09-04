/*****************************************************************************
 *  File: zn_uart.c
 *
 * Descirption: this file contains the functions support uart operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:
 *  Date:   2023-4-27
 *
 *****************************************************************************/

#include "zn_uart.h"
#include "stdio.h"


DeviceCallback_Type s_uartCallback[2] = {NULL,NULL};

/**
* uart_init
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  config: Pointer to UART configuration structure
* @return     Returns 0 if initialization is successful, otherwise returns error code
*
* @brief      Initializes UART module with the given configuration
*/
int32_t uart_init(ZN_UartType *UARTx, const UART_ConfigType *config)
{
    int32_t ret = UART_SUCCESS;    
    
    ret = uart_set_baudrate(UARTx,config->baudRate,config->uartClk);
    if(ret)
    {
        return ret;
    }
    ret = uart_set_parity(UARTx,config->parity);
    if(ret)
    {
        return ret;
    }
    ret = uart_set_wordsize(UARTx,config->wordSize);
    if(ret)
    {
        return ret;
    }
    ret = uart_set_stopbit(UARTx,config->stopBits);
    if(ret)
    {
        return ret;
    }
    if (config->fifoEn)
    {
        ret = uart_enable_fifo(UARTx);
    }
    else
    {
       ret = uart_disable_fifo(UARTx);
    }
    
    if(config->callBack)
    {
        if(UARTx == UART0)
        {
            s_uartCallback[0] = config->callBack;
        }
        else
        {
            s_uartCallback[1] = config->callBack;
        }
    }
    return ret;
}


/**
* uart_deinit
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if deinitialization is successful, otherwise returns error code
*
* @brief      Deinitializes UART module
*/
int32_t uart_deinit(ZN_UartType *UARTx)
{
    UARTx->LCR = 0x83;
    UARTx->DLL = 0;
    UARTx->DLH = 0;
    UARTx->DLF = 0;
    UARTx->SRR = SRR_XMIT_RIFO_RESET | SRR_RCVR_RIFO_RESET | SRR_YART_RESET;
    return UART_SUCCESS;
}


/**
* uart_set_baudrate
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  baudRate: Baud rate to be set
* @param[in]  uartClk: UART clock frequency
* @return     Returns 0 if setting baud rate is successful, otherwise returns error code
*
* @brief      Sets the baud rate for the UART module
*/
int32_t uart_set_baudrate(ZN_UartType *UARTx, UART_Baudrate baudRate, uint32_t uartClk)
{
     uint32_t timeCnt = 0;    
     float floatDiv  = 0.0f;    
     uint32_t intDiv = 0;
    /*the baudrates that uart surported as follows:*/
    if((baudRate == B4800) || (baudRate == B9600) ||(baudRate == B14400) ||
       (baudRate == B19200) || (baudRate == B38400) || (baudRate == B56000) ||
       (baudRate == B57600) || (baudRate == B115200) || (baudRate == B128000)||
       (baudRate == B230400) || (baudRate == B256000)|| (baudRate == B460800)|| 
       (baudRate == B500000)||(baudRate == B512000) || (baudRate == B600000) ||  
       (baudRate == B750000) || (baudRate == B921600) || (baudRate == B1000000)|| 
       (baudRate == B1500000)||(baudRate == B2000000))
    {

        /* DLH and DLL may be accessed when the UART is not busy(USR[0]=0) and the DLAB bit(LCR[7]) is set.*/
        while(UARTx->USR & USR_UART_BUSY)
        {
            timeCnt++;
            if (timeCnt >= UART_BUSY_TIMEOUT)
            {
                return UART_BUSY;    
            }
            if(UARTx->LSR & LSR_DATA_READY)
            {
                uint32_t data = (UARTx->RBR);
            }
        }
        floatDiv = 1.0f*(uartClk>>4)/baudRate;
        UARTx->LCR |= LCR_SET_DLAB;
        intDiv = (uint32_t)floatDiv;
        /* DLL and DLH is lower 8-bits and higher 8-bits of Integer part (floatDiv).*/
        UARTx->DLH = (intDiv >> 8) & 0xFF;
        UARTx->DLL = intDiv & 0xFF;
        /*DLF = roundoff(Fractional part floatDiv *2^ DLF_SIZE) */
        UARTx->DLF = (uint32_t)((floatDiv - intDiv) * 64+0.5f); 
        
        UARTx->LCR &= ~LCR_SET_DLAB;
    }
    else
    {
        return UART_OTHER;
    }
    return UART_SUCCESS;
}

/**
* uart_set_parity
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  parity: Parity to be set (NONE, ODD, EVEN)
* @return     Returns 0 if setting parity is successful, otherwise returns error code
*
* @brief      Sets the parity for the UART module
*/
int32_t uart_set_parity(ZN_UartType *UARTx, UART_Parity parity)
{
    uint32_t timeCnt = 0;

      /* PEN bit(LCR[3]) is writeable when the UART is not busy(USR[0]=0).*/
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TIMEOUT)
        {
            return UART_BUSY;    
        }
        if(UARTx->LSR & LSR_DATA_READY)
        {
            uint32_t data = (UARTx->RBR);
        }
    }
    switch(parity)
    {
        case NONE:
            /*CLear the PEN bit(LCR[3]) to disable parity.*/
            UARTx->LCR &= (~LCR_PARITY_ENABLE);
            break;

        case ODD:
            /* Set PEN and clear EPS(LCR[4]) to set the ODD parity. */
            UARTx->LCR |= LCR_PARITY_ENABLE;
            UARTx->LCR &= LCR_PARITY_ODD;
            break;

        case EVEN:
            /* Set PEN and EPS(LCR[4]) to set the EVEN parity.*/
            UARTx->LCR |= LCR_PARITY_ENABLE;
            UARTx->LCR |= LCR_PARITY_EVEN;
            break;

        default:
            return UART_OTHER;
            break;
    }
    return UART_SUCCESS;
}

/**
* uart_set_wordsize
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  wordsize: Word size to be set (WORD_SIZE_5, WORD_SIZE_6, WORD_SIZE_7, WORD_SIZE_8)
* @return     Returns 0 if setting word size is successful, otherwise returns error code
*
* @brief      Sets the word size for the UART module
*/
int32_t uart_set_wordsize(ZN_UartType *UARTx, UART_WordSize wordsize)
{
    uint32_t timeCnt = 0;
    
    /*  set wordsize when the UART is not busy(USR[0]=0).*/
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TIMEOUT)
        {
            return UART_BUSY;    
        }
        if(UARTx->LSR & LSR_DATA_READY)
        {
            uint32_t data = (UARTx->RBR);
        }
    }
    switch(wordsize)
    {
        case WORD_SIZE_5:
            UARTx->LCR &= LCR_WORD_SIZE_5;
            break;

        case WORD_SIZE_6:
            UARTx->LCR &= 0xfd;
            UARTx->LCR |= LCR_WORD_SIZE_6;
            break;

        case WORD_SIZE_7:
            UARTx->LCR &= 0xfe;
            UARTx->LCR |= LCR_WORD_SIZE_7;
            break;

        case WORD_SIZE_8:
            UARTx->LCR |= LCR_WORD_SIZE_8;
            break;

        default:
            return UART_OTHER;
            break;
    }
  
    return UART_SUCCESS;
}

/**
* uart_set_stopbit
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  stopbit: Stop bit to be set (LCR_STOP_BIT_1, LCR_STOP_BIT_2)
* @return     Returns 0 if setting stop bit is successful, otherwise returns error code
*
* @brief      Sets the stop bit for the UART module
*/
int32_t uart_set_stopbit(ZN_UartType *UARTx, UART_StopBit stopbit)
{
    uint32_t timeCnt = 0;
    
    /*  STOP(LCR[2]) is writeable when the UART is not busy(USR[0]=0).*/
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TIMEOUT)
        {
            return UART_BUSY;    
        }
        if(UARTx->LSR & LSR_DATA_READY)
        {
            uint32_t data = (UARTx->RBR);
        }
    }
    
    switch(stopbit)
    {
        case LCR_STOP_BIT_1:
            /* Clear the STOP bit to set 1 stop bit*/
           UARTx->LCR &= LCR_STOP_BIT1;
            break;

        case LCR_STOP_BIT_2:
            /*
             * If the STOP bit is set "1",we'd gotten 1.5 stop
             * bits when DLS(LCR[1:0]) is zero, else 2 stop bits.
             */
            UARTx->LCR |= LCR_STOP_BIT2;
            break;

        default:
            return UART_OTHER;
            break;

    }
    return UART_SUCCESS;
}

/**
* uart_enable_fifo
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if enabling FIFO is successful, otherwise returns error code
*
* @brief      Enables FIFO for the UART module
*/
int32_t uart_enable_fifo(ZN_UartType *UARTx)
{
    uint32_t timeCnt = 0;
    
    /*  STOP(LCR[2:0]) is writeable when the UART is not busy(USR[0]=0).*/
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TIMEOUT)
        {
            return UART_BUSY;    
        }
        if(UARTx->LSR & LSR_DATA_READY)
        {
            uint32_t data = (UARTx->RBR);
        }
    }
    /*enable both tx&rx fifo*/
    UARTx->FCR |= FCR_TXSR | FCR_RXSR | FCR_FIFO_EN;
    return UART_SUCCESS;
}

/**
* uart_disable_fifo
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if disabling FIFO is successful, otherwise returns error code
*
* @brief      Disables FIFO for the UART module
*/
int32_t uart_disable_fifo(ZN_UartType *UARTx)
{
    uint32_t timeCnt = 0;
    
    /*  STOP(LCR[2:0]) is writeable when the UART is not busy(USR[0]=0).*/
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TIMEOUT)
        {
            return UART_BUSY;    
        }
        if(UARTx->LSR & LSR_DATA_READY)
        {
            uint32_t data = (UARTx->RBR);
        }
    }
    /*disable both tx&rx fifo*/
    UARTx->FCR &= ~(FCR_TXSR | FCR_RXSR | FCR_FIFO_EN);
    return UART_SUCCESS;
}

/**
* uart_set_dma_mode
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  mode: DMA mode to be set (0 or 1)
* @return     Returns 0 if setting DMA mode is successful, otherwise returns error code
*
* @brief      Sets the DMA mode for the UART module
*/
int32_t uart_set_dma_mode(ZN_UartType *UARTx, uint8_t mode)
{
    /*Only DMA mode 0 is available when FIFOs are not implemented or disabled.*/
    if ( 0 == mode)
    {
        UARTx->FCR &= ~FCR_DMA_MODE1;
    }
    else if (1 == mode)
    {
        UARTx->FCR |= FCR_DMA_MODE1;
    }
    else
    {
        return UART_OTHER;
    }
    return UART_SUCCESS;
}

/**
* uart_set_loopback
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if setting loopback is successful
*
* @brief      Sets the loopback mode for the UART module
*/
int32_t uart_set_loopback(ZN_UartType *UARTx)
{
    UARTx->MCR |= MCR_LOOPBACK;
    return UART_SUCCESS;
}

/**
* uart_reset_loopback
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if resetting loopback is successful
*
* @brief      Resets the loopback mode for the UART module
*/
int32_t uart_reset_loopback(ZN_UartType *UARTx)
{
    UARTx->MCR &= ~MCR_LOOPBACK;
    return UART_SUCCESS;
}

/**
* uart_set_fifo_acess_mode
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if setting FIFO access mode is successful
*
* @brief      Sets the FIFO access mode for the UART module
*/
int32_t uart_set_fifo_acess_mode(ZN_UartType *UARTx)
{
    UARTx->FAR |= FAR_FIFO_ACCESS;
    return UART_SUCCESS;
}

/**
* uart_reset_fifo_acess_mode
*
* @param[in]  UARTx: Pointer to UART instance
* @return     Returns 0 if resetting FIFO access mode is successful
*
* @brief      Resets the FIFO access mode for the UART module
*/
int32_t uart_reset_fifo_acess_mode(ZN_UartType *UARTx)
{
    UARTx->FAR &= ~FAR_FIFO_ACCESS;
    return UART_SUCCESS;
}

/**
* uart_set_fifo_trigger
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  rxTriggerLevel: RX trigger level (0 to 3)
* @param[in]  txTriggerLevel: TX trigger level (0 to 3)
* @return     Returns 0 if setting FIFO trigger is successful, otherwise returns error code
*
* @brief      Sets the FIFO trigger levels for the UART module
*/
int32_t uart_set_fifo_trigger(ZN_UartType *UARTx,uint8_t rxTriggerLevel,uint8_t txTriggerLevel)
{
    if (rxTriggerLevel>3 || txTriggerLevel>3)
    {
        return UART_OTHER;
    }
    /*rxTriggerLevel
    00 - 1 character in the FIFO
    01 - FIFO 1/4 full
    10 - FIFO 1/2 full
    11 - FIFO 2 less than full
    */
    /*txTriggerLevel
     00 - FIFO empty
     01 - 2 characters in the FIFO
     10 - FIFO 1/4 full
     11 - FIFO 1/2 full
    */
    UARTx->FCR |= (rxTriggerLevel<<6) | (txTriggerLevel<<4)|FCR_FIFO_EN;
    return UART_SUCCESS;
}

/**
* uart_set_tx_irq_empty
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  isEnable: ENABLE or DISABLE
* @return     Returns 0 if setting TX IRQ empty is successful, otherwise returns error code
*
* @brief      Sets the TX IRQ empty for the UART module
*/
int32_t uart_set_tx_irq_empty(ZN_UartType *UARTx, ACTION_Type isEnable)
{
    uint32_t timeCnt = 0;
    
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TR_TIMEOUT)
        {
            return UART_BUSY;    
        }
    }
    /*Enable or Disable Transmit Holding Register Empty Interrupt.*/
    if (ENABLE == isEnable)
    {
        UARTx->IER |= IER_THRE_INT_ENABLE;
    }
    else
    {
        UARTx->IER &= ~IER_THRE_INT_ENABLE;
    }
    return UART_SUCCESS;
}

/**
* uart_set_rx_irq_available
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  isEnable: ENABLE or DISABLE
* @return     Returns 0 if setting RX IRQ available is successful, otherwise returns error code
*
* @brief      Sets the RX IRQ available for the UART module
*/
int32_t uart_set_rx_irq_available(ZN_UartType *UARTx, ACTION_Type isEnable)
{
    uint32_t timeCnt = 0;
    
    while(UARTx->USR & USR_UART_BUSY)
    {
        timeCnt++;
        if (timeCnt >= UART_BUSY_TR_TIMEOUT)
        {
            return UART_BUSY;    
        }
    }
    /*Enable or Disable Received Data Available Interrupt.*/
    if (ENABLE == isEnable)
    {
        UARTx->IER |= IER_RDA_INT_ENABLE;
    }
    else
    {
        UARTx->IER &= ~IER_RDA_INT_ENABLE;
    }
    return UART_SUCCESS;
}

/**
* uart_getchar
*
* @param[in]  UARTx: Pointer to UART instance
* @param[out] ch: Pointer to store received character
* @return     Returns 0 if getting character is successful
*
* @brief      Gets a character from the UART module
*/
int32_t uart_getchar(ZN_UartType *UARTx,uint8_t *ch)
{
     /*recevie uart  data when disable rx interrupt*/    
    while (!(UARTx->LSR & LSR_DATA_READY)){};
    *ch = UARTx->RBR;
    return UART_SUCCESS;
}

/**
* uart_putchar
*
* @param[in]  UARTx: Pointer to UART instance
* @param[in]  ch: Character to be sent
* @return     Returns 0 if putting character is successful
*
* @brief      Puts a character to the UART module
*/
int32_t uart_putchar(ZN_UartType *UARTx,uint8_t ch)
{
    /*send uart  data when disable tx interrupt*/    
     while (!(UARTx->LSR & LSR_THR_EMPTY)){};
     UARTx->THR = ch;
    return UART_SUCCESS;
}

uint8_t uart_get_rx_data(ZN_UartType *UARTx)
{
    return UARTx->RBR;
}

uint8_t get_uart_interrupt_state(ZN_UartType *UARTx)
{
    return UARTx->IIR & 0x0f;
}

/**
* UART0_IRQHandler
*
* @brief      UART0 Interrupt Handler
*/
void UART0_IRQHandler(void)
{
    uint32_t wpara;
    uint32_t lpara;
    if (s_uartCallback[0])
    {
        s_uartCallback[0](UART0, wpara, lpara);
    }
    return;
}


/**
* UART1_IRQHandler
*
* @brief      UART1 Interrupt Handler
*/
void UART1_IRQHandler(void)
{
    uint32_t wpara;
    uint32_t lpara;
    if (s_uartCallback[1])
    {
        s_uartCallback[1](UART1, wpara, lpara);
    }
    return;
}
#ifdef __MICROLIB
int fputc(int ch, FILE *f)
{
    uart_putchar(UART0,ch);  /*if use uart1, need uart_putchar(UART1,ch)*/
    
    return ch;
}



/*
 * print the result after translated according to the format
 */
#else
int printf ( const char *fmt, ... )
{
  const char *s;
  int        value;
  CK_UINT32        ptr;
  char       ch, buf[64], *pbuf;
  va_list    ap;
  double f;
  va_start(ap, fmt);
  while (*fmt) 
  {
    if (*fmt != '%')
    {
      con_putchar(*fmt++);
      continue;
    }

    switch (*++fmt)
    {
      case 's':
        s = va_arg(ap, const char *);
         puts_without_enter(s);
         break;
      case 'd':
         value = va_arg(ap, int);
         if (value < 0)
         {
            con_putchar('-');
            value = 0 - value;
         }
         pbuf = numtostring((unsigned int)value, 10, buf);
         puts_without_enter(pbuf);
         break;
       case 'x':
       case 'X':
         value = va_arg(ap,int);
         pbuf = numtostring((unsigned int)value, 16, buf);
         puts_without_enter(pbuf);
         break;
       case 'c':
          ch = (unsigned char)va_arg(ap, int);
          pbuf = &ch;     
          con_putchar(*pbuf);                         
          break;  
        case 'u':
            value = va_arg(ap,int);
            snprintf(buf, sizeof(buf),"%u\0", value); 
            for (s = buf; *s; s ++)
            {     
                con_putchar(*s);                              
            }
            break; 
        case 'f':
            f = va_arg(ap, double);
            snprintf(buf, sizeof(buf),"%.6f\0", f);      
            for (s = buf; *s; s ++)
            {     
                con_putchar(*s);                              
            }
            break;        
       case 'p':
         ptr = (unsigned) va_arg(ap, void *); 
         pbuf = numtostring(ptr, 16, buf);
         puts_without_enter(pbuf);
         break;  
       default:  
         con_putchar(*fmt);
         break;
    }
    fmt ++;
  }
  va_end(ap);
  return 0x01;   
}
#endif
