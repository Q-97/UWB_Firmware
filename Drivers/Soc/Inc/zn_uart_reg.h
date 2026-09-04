/*
 * File : zn_uart_reg.h
 * Description: this file contains the macros support uart operations
 * Copyright (C):  2022 ultraception.com.
 * Author(s):   wjy
 * Date:  2023-4-26
 */


#ifndef __ZN_UART_REG_H__
#define __ZN_UART_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"


typedef struct 
{
    union
    {
        __I  uint32_t RBR; /*Receive Buffer Register.Dependencies: LCR[7] bit = 0*/                    
        __O  uint32_t THR; /*Transmit Holding Register.Dependencies: LCR[7] bit = 0*/                   
        __IO uint32_t DLL; /*Divisor Latch (Low).Dependencies: LCR[7] bit = 1*/                   
    }; /*UART Address Offset 0x00*/ 
    union
    {
        __IO uint32_t DLH; /* Divisor Latch (High).Dependencies: LCR[7] bit = 1*/                  
        __IO uint32_t IER;  /* Interrupt Enable Register. ependencies: LCR[7] bit = 0*/                    
    };    /*UART Address Offset 0x04*/     
    union
    {
        __I uint32_t IIR;     /* Interrupt Identification Register.*/                
        __O uint32_t FCR;    /*FIFO Control Register.*/                 
        
    }; /*UART Address Offset 0x08*/
    __IO uint32_t LCR;/*UART Address Offset 0x0c.Line Control Register.*/ 
    __IO uint32_t MCR;  /*UART Address Offset 0x10.Modem Control Register.*/         
    __I uint32_t LSR;/*UART Address Offset 0x14.Line Status Register.*/                     
    __I uint32_t MSR;/*UART Address Offset 0x18.Modem Status Register.*/                    
    __IO uint32_t SCR;/*UART Address Offset 0x1c.Scratchpad Register */                    
    __IO uint32_t LPDLL;/*UART Address Offset 0x20 */                  
    __IO uint32_t LPDLH; /*UART Address Offset 0x24*/
    __I uint32_t Rev0[2];/*UART Address Offset 0x28-0x2C*/
    union
    {
        __I uint32_t SRBR[16];  /*Shadow Receive Buffer Register.Dependencies: LCR[7] bit = 0*/                   
        __O uint32_t STHR[16];   /*Shadow Transmit Holding Register.Dependencies: LCR[7] bit = 0 */                 
    };/*UART Address Offset 0x30-0x6C*/
    __IO uint32_t FAR;/*UART Address Offset 0x70. FIFO Access Register*/                     
    __I  uint32_t TFR;/*UART Address Offset 0x74. Transmit FIFO Read*/                      
    __O  uint32_t RFW;/*UART Address Offset 0x78. Receive FIFO Write*/                     
    __I  uint32_t USR;/*UART Address Offset 0x7c. UART Status Register */                  
    __I  uint32_t TFL; /*UART Address Offset 0x80.  Transmit FIFO Level */                    
    __I  uint32_t RFL; /*UART Address Offset 0x84. Receive FIFO Level */                    
    __O  uint32_t SRR; /*UART Address Offset 0x88. Software Reset Register */ 
    __IO uint32_t SRTS; /*UART Address Offset 0x8c. Shadow Request to Send */                     
    __IO uint32_t SBCR; /*UART Address Offset 0x90. Shadow Break Control Register */                     
    __IO uint32_t SDMAM;/*UART Address Offset 0x94. Shadow DMA Mode */                      
    __IO uint32_t SFE; /*UART Address Offset 0x98. Shadow FIFO Enable */                     
    __IO uint32_t SRT; /*UART Address Offset 0x9C.  Shadow RCVR Trigger */                     
    __IO uint32_t STET; /*UART Address Offset 0xA0.  Shadow TX Empty Triggerr */                     
    __IO uint32_t HTX; /*UART Address Offset 0xA4.  Halt TX */ 
    __O  uint32_t DMASA;/*UART Address Offset 0xA8.  DMA Software Acknowledge*/  
    __IO uint32_t TCR; /*UART Address Offset 0xAC.  Transceiver Control Register.Dependencies: UART_RS485_INTERFACE_EN=1 */ 
    __IO uint32_t DE_EN;/*UART Address Offset 0xB0.   Driver Output Enable Register. Dependencies: UART_RS485_INTERFACE_EN=1 */ 
    __IO uint32_t RE_EN; /*UART Address Offset 0xB4.   Receiver Output Enable Register. Dependencies: UART_RS485_INTERFACE_EN=1 */ 
    __IO uint32_t DET; /*UART Address Offset 0xB8.   Driver Output Enable Timing Register. Dependencies: UART_RS485_INTERFACE_EN=1 */ 
    __IO uint32_t TAT; /*UART Address Offset 0xBC. TurnAround Timing Register.Dependencies: UART_RS485_INTERFACE_EN=1*/ 
    __IO uint32_t DLF;/* UART Address Offset 0xC0.Divisor Latch Fractional Value.*/ 
    __IO uint32_t RAR; /*UART Address Offset 0xC4.Receive Address Register.*/
    __IO uint32_t TAR; /*UART Address Offset 0xC8. Transmit Address Register*/
    __IO uint32_t LCR_EXT;/*UART Address Offset 0xCC. Line Extended Control Register*/ 
}ZN_UartType;

#define UART0    (ZN_UartType*)UART0_BASE_ADDR
#define UART1    (ZN_UartType*)UART1_BASE_ADDR

#define UART_BUSY_TIMEOUT      1000
#define UART_BUSY_TR_TIMEOUT   10000000
#define UART_RECEIVE_TIMEOUT   1000
#define UART_TRANSMIT_TIMEOUT  1000



/* UART register bit definitions */

/*UART Status Register*/
#define USR_UART_BUSY           0x01
#define USR_UART_TFNF           0x02
#define USR_UART_TFE            0x04
#define USR_UART_RFNE           0x08
#define USR_UART_RFF            0x10


/*Interrupt Enable Register*/
#define IER_THRE_INT_ENABLE     0x02
#define IER_RDA_INT_ENABLE      0x01

/*Interrupt Identity Register*/
/*IIR bits[3:0]*/
#define IIR_ISQ_MODEM_STATUS      0x00 
#define IIR_NO_ISQ_PEND           0x01
#define IIR_ISQ_THR_EMPTY         0x02
#define IIR_ISQ_RX_DATA           0x04
#define IIR_ISQ_RX_LINE_STATUS    0x06
#define IIR_ISQ_BUSY_DETECT       0x07
#define IIR_ISQ_CHAR_TIMEOUT      0x0C

/*Line Control Register*/
#define LCR_SET_DLAB            0x80U   /* enable r/w DLR to set the baud rate.This bit must be cleared after initial baud rate setup in order to access other registers. */
/*LCR bits[4], Even Parity Select.*/
#define LCR_PARITY_EVEN         0x10U   /* Even parity enabled */
#define LCR_PARITY_ODD          0xefU   /* Odd parity enabled */
/*LCR bits[3],   Parity Enable.*/
#define LCR_PARITY_ENABLE       0x08U   /* parity enabled */
/*LCR bits[2], Number of stop bits.*/
/*0b0-1 stop bit, 0b1-1.5 stop bits when DLS (LCR[1:0]) is 0, else 2 stop bit*/
#define LCR_STOP_BIT1           0xfbU   /* 1 stop bit */
#define LCR_STOP_BIT2           0x04U   /* 1.5 stop bit */
/*LCR bits[1:0], data length*/
/*0b00 - 5 bits;0b01 - 6 bits;0b10 - 7 bits;0b11 - 8 bits*/
#define LCR_WORD_SIZE_5         0xfcU   /* the data length is 5 bits */
#define LCR_WORD_SIZE_6         0x01U   /* the data length is 6 bits */
#define LCR_WORD_SIZE_7         0x02U   /* the data length is 7 bits */
#define LCR_WORD_SIZE_8         0x03U   /* the data length is 8 bits */

/* e: Modem Control Register.bitfields of MCR*/
#define MCR_SIRE                0x40   /* SIR Mode Enable */
#define MCR_AFCE                0x20   /* Auto Flow Control Enable */
#define MCR_LOOPBACK            0x10   /* Loopback */
#define MCR_RTS                 0x02   /* Request to Send */


/* Line Status Register.bitfields of LSR*/
#define LSR_PFE              0x80 /*Receiver FIFO Error bit*/
/* If in FIFO mode (FIFO_MODE != NONE) and FIFOs enabled (FCR[0] set to 1), 
 this bit is set whenever the Transmitter Shift Register and the FIFO are both empty.*/
#define     LSR_TEMT             0x40 
#define     LSR_THR_EMPTY        0x20  /*the THR or TX FIFO is empty*/
#define     LSR_BREAK_INT        0x10
#define     LSR_FRAM_ERR         0x08
#define     LSR_PARITY_ERR       0x04
#define     LSR_OVERRUN          0x02
#define     LSR_DATA_READY       0x01

/* bitfields of FCR*/
/* FCR[7:6]--RCVR Trigger*/
#define FCR_RT_00               (0 << 6)
#define FCR_RT_01               (1 << 6)
#define FCR_RT_10               (2 << 6)
#define FCR_RT_11               (3 << 6)
/* FCR[5:4]--RCVR Trigger*/       
#define FCR_TET_00              (0 << 4)
#define FCR_TET_01              (1 << 4)
#define FCR_TET_10              (2 << 4)
#define FCR_TET_11              (3 << 4)
/* FCR[3]--DMA MOde*/            
#define FCR_DMA_MODE0           (0 << 3)
#define FCR_DMA_MODE1           (1 << 3)
#define FCR_TXSR                (1<<2) /* Transmitter soft reset */
#define FCR_RXSR                (1<<1) /* Receiver soft reset */

/*
UART FIFO depth max  is 16
*/
/* FCR[0]-- FIFO Enable, FIFO_MODE = 128*/ 
#define FCR_FIFO_EN              (1 << 0) /* Fifo enable */    

// bitfields of FAR
#define FAR_FIFO_ACCESS         (1UL << 0)

/* Software Reset Register.bitfields of SRR*/
#define    SRR_XMIT_RIFO_RESET       0x04
#define    SRR_RCVR_RIFO_RESET       0x02
#define    SRR_YART_RESET            0x01
#ifdef __cplusplus
}
#endif

#endif
