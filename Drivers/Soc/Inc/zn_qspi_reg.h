/*****************************************************************************
 *  File: zn_qspi_reg.h
 *
 *  Descirption: this file contains the functions support qspi operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2022-3-22
 *
 *****************************************************************************/
#ifndef __ZN_QSPI_REG_H__
#define __ZN_QSPI_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"


// star se
#define QSPI_BASE_ADDR            0xE0044000
#define QSPI_CR_ADDR              (QSPI_BASE_ADDR + 0X0)  // control register
#define QSPI_SR_ADDR              (QSPI_BASE_ADDR + 0X4)  // status 
#define QSPI_RMCR_ADDR            (QSPI_BASE_ADDR + 0X8)  // direct read access mode
#define QSPI_OMCR_ADDR            (QSPI_BASE_ADDR + 0Xc)  // inderect mode 
#define QSPI_RABR_ADDR            (QSPI_BASE_ADDR + 0X10) // direct alternate byte
#define QSPI_OABR_ADDR            (QSPI_BASE_ADDR + 0X14) // inderect alternate bytes
#define QSPI_IMAR_ADDR            (QSPI_BASE_ADDR + 0X18) // inderect mode address
#define QSPI_FDR_ADDR             (QSPI_BASE_ADDR + 0X1c) // fifo data
#define QSPI_DLR_ADDR             (QSPI_BASE_ADDR + 0X20) // inderect mode data length_
#define QSPI_WCNT_ADDR            (QSPI_BASE_ADDR + 0X24) // wait counter

#define QSPI_SCKSCALER(x)         ( (x) << 24 )           // scaler factor Fsck = F/(2*(x+1)),x between 0 and 63
#define QSPI_CSRHT(x)             ( (x) << 16 )           //  CSn remain high : x + 2,x between 0 and 63
#define QSPI_FMSIZE(x)            ( (x) <<  8 )           // flash memory size,
#define QSPI_XIPMODE(x)           ( (x) <<  5 )           // xip mode: 0: exit,1 entry
#define QSPI_SCKMODE(x)           ( (x) <<  4 )           // 0: mode0, 1: mode3
#define QSPI_OPMODE(x)            ( (x) <<  0 )           // 00: Direct mode,10: Indirect mode,11 inactive mode

#define QSPI_DDRMODE(x)           ( (x) << 31 )           // 1: DDR MODE
#define QSPI_NOWRAP(x)            ( (x) << 30 )           // 0: follow AHB, critical word first
#define QSPI_IDMODE(x)            ( (x) << 30 )           // 0:rx fifo, 1: txfifo 
#define QSPI_WRAPMODE(x)          ( (x) << 29 )           // 32 byte address boundaries, 0 : not in wrap mode
#define QSPI_NUMDC(x)             ( (x) << 24 )           // dummy cycle
#define QSPI_RXDLY(x)             ( (x) << 22 )           // rx delay
#define QSPI_DSIZE(x)             ( (x) << 20 )           // 11: 4 byte 
#define QSPI_DMODE(x)             ( (x) << 18 )           // data mode 00: RES, 01: single, 10: dual, 11: quad
#define QSPI_ABSIZE(x)            ( (x) << 16 )           // alternate byte size : x  alternate bytes 
#define QSPI_ABMODE(x)            ( (x) << 14 )           // alternate bytes mode 00: 0, 01: single, 10: dual, 11: quad
#define QSPI_ADSIZE(x)            ( (x) << 12 )           // 10: 24 bits, 11: 32 bits 
#define QSPI_ADMODE(x)            ( (x) << 10 )           // data mode 00: no address, 01: single, 10: dual, 11: quad
#define QSPI_IMODE(x)             ( (x) <<  8 )           // inst mode 00: no inst, 01: single, 10: dual, 11: quad
#define QSPI_INSTRUCTION(x)       ( (x) <<  0 )           // inst mode 00: no inst, 01: single, 10: dual, 11: quad




/*QSPI_RMCR(QSPI Direct Read Access Mode Control Register) only*/
#define QSPI_NOWRAP(x)            ( (x) << 30 )           // 0: follow AHB, critical word first
#define QSPI_WRAPMODE(x)          ( (x) << 29 )           // 32 byte address boundaries, 0 : not in wrap mode
/*QSPI_OMCR(QSPI Indirect Mode Control Register) only*/
#define QSPI_IDMODE(x)            ( (x) << 30 )           // 0:rx fifo, 1: txfifo 
#define QSPI_XIPIMMENTER(x)       ( (x) << 29 )           //This bit indicates that when QSPI's FSM comes back from indirect access
/*QSPI_RMCR and QSPI_OMCR share*/
#define QSPI_DDRMODE(x)           ( (x) << 31 )           // 1: DDR MODE
#define QSPI_NUMDC(x)             ( (x) << 24 )           // dummy cycle
#define QSPI_RXDLY(x)             ( (x) << 22 )           // rx delay
#define QSPI_DSIZE(x)             ( (x) << 20 )           // 11: 4 byte 
#define QSPI_DMODE(x)             ( (x) << 18 )           // data mode 00: RES, 01: single, 10: dual, 11: quad
#define QSPI_ABSIZE(x)            ( (x) << 16 )           // alternate byte size : x  alternate bytes 
#define QSPI_ABMODE(x)            ( (x) << 14 )           // alternate bytes mode 00: 0, 01: single, 10: dual, 11: quad
#define QSPI_ADSIZE(x)            ( (x) << 12 )           // 10: 24 bits, 11: 32 bits 
#define QSPI_ADMODE(x)            ( (x) << 10 )           // data mode 00: no address, 01: single, 10: dual, 11: quad
#define QSPI_IMODE(x)             ( (x) <<  8 )           // inst mode 00: no inst, 01: single, 10: dual, 11: quad
#define QSPI_INSTRUCTION(x)       ( (x) <<  0 )           // inst mode 00: no inst, 01: single, 10: dual, 11: quad

/*QSPI Status Register*/
#define QSPI_OPCRCF                (1<<2)                 /*Operation mode change request complete flag.*/
#define QSPI_TCF                   (1<<4)                 /*Transfer complete flag.*/
#define QSPI_BUSY                  (1<<5)                 /*This bit is set when an operation on QSPI-Bus is ongoing.It means that the SCK wire is toggled in the QSPI bus.*/
#define QSPI_FIFOEMPTY             (1<<8)                 /*This bit is set when the FIFO is empty. This bit is usually used in indirect mode.*/
#define QSPI_FIFOFULL              (1<<9)                 /*This bit is set when the FIFO is full. This bit is usually used in indirect mode.*/


#define QSPI_DSIZE_Pos            (20U)
#define QSPI_DSIZE_Msk            (0x3UL << QSPI_DSIZE_Pos)        /*!< 0x00300000 */

#define QSPI_OPERATION_MODE_DIRECT_ACCESS   (0x00000000UL)                     /*!<Direct read access mode*/
#define QSPI_OPERATION_MODE_INDIRECT        (0x00000002UL)                     /*!<Indirect mode.*/
#define QSPI_OPERATION_MODE_INACTIVE        (0x00000003UL)                     /*!<Inactive mode*/

/** @defgroup QSPI_DdrMode QSPI DDR Mode
  * @{
  */
#define QSPI_DDR_MODE_DISABLE          (QSPI_DDRMODE(0))                 /*!<Double data rate mode disabled*/
#define QSPI_DDR_MODE_ENABLE           (QSPI_DDRMODE(1)) /*!<Double data rate mode enabled*/

/** @defgroup QSPI_IndirectAcessMode Indirect access mode data phase direction.
  * @{
  */
#define QSPI_INDIRECT_ACCESS_READ                (QSPI_IDMODE(0))   /*Read data, RX FIFO enabled.Indirect access mode data phase direction.*/
#define QSPI_INDIRECT_ACCESS_WRITE               (QSPI_IDMODE(1))   /*Write data, TX FIFO enabled.Indirect access mode data phase direction.*/


/*DataSize This field defines the data size*/
#define QSPI_DATASIZE_8_BITS                      (QSPI_DSIZE(0))  /* 0b00  8 bits data.*/
#define QSPI_DATASIZE_16_BITS                     (QSPI_DSIZE(1))  /* 0b01  16 bits data*/
#define QSPI_DATASIZE_32_BITS                     (QSPI_DSIZE(3))  /* 0b11  32 bits data*/


/** @defgroup QSPI_DataMode QSPI Data Mode
  * @{
  */
#define QSPI_DATA_NONE                             (QSPI_DMODE(0))   /*!Reserved.*/
#define QSPI_DATA_1_LINE                           (QSPI_DMODE(1))   /*!<Data on a single line*/
#define QSPI_DATA_2_LINES                          (QSPI_DMODE(2))   /*!<Data on two lines*/
#define QSPI_DATA_4_LINES                          (QSPI_DMODE(3))   /*!<Data on four lines*/


/** @defgroup QSPI_AlternateBytesSize QSPI Alternate bytes size
* @{
*/
#define QSPI_ALTERNATE_BYTESSIZE_8_BITS       (QSPI_ABSIZE(0))                      /*!<8-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTESSIZE_16_BITS      (QSPI_ABSIZE(1))                      /*!<16-bit alternate bytes.*/
#define QSPI_ALTERNATE_BYTESSIZE_24_BITS      (QSPI_ABSIZE(2))                      /*!<24-bit alternate bytes.*/
#define QSPI_ALTERNATE_BYTESSIZE_32_BITS      (QSPI_ABSIZE(3))                      /*!<32-bit alternate bytes.*/


/** @defgroup QSPI_AlternateBytesMode QSPI Alternate bytes mode
* @{
*/
#define QSPI_ALTERNATE_BYTESMODE_NONE         (QSPI_ABMODE(0))                      /*!<No alternate bytes.*/
#define QSPI_ALTERNATE_BYTESMODE_1_LINE       (QSPI_ABMODE(1))                      /*!<Alternate bytes on a single line.*/
#define QSPI_ALTERNATE_BYTESMODE_2_LINES      (QSPI_ABMODE(2))                      /*!<Alternate bytes on two lines.*/
#define QSPI_ALTERNATE_BYTESMODE_4_LINES      (QSPI_ABMODE(3))                      /*!<Alternate bytes on quad lines.*/

/** @defgroup QSPI_AddressSize QSPI Address size
* @{
*/
#define QSPI_ADDRESS_BYTESSIZE_RES0           (QSPI_ADSIZE(0))                      /*!<Reserved*/
#define QSPI_ADDRESS_BYTESSIZE_RES1           (QSPI_ADSIZE(1))                      /*!<Reserved.*/
#define QSPI_ADDRESS_BYTESSIZE_24_BITS        (QSPI_ADSIZE(2))                      /*!<24-bit address.*/
#define QSPI_ADDRESS_BYTESSIZE_32_BITS        (QSPI_ADSIZE(3))                      /*!<32-bit address.*/


/** @defgroup QSPI_AddressMode QSPI Address mode.
* @{
*/
#define QSPI_ADDRESS_MODE_NONE                 (QSPI_ADMODE(0))                      /*!<No address bytes.*/
#define QSPI_ADDRESS_MODE_1_LINE               (QSPI_ADMODE(1))                      /*!<Address on a single line.*/
#define QSPI_ADDRESS_MODE_2_LINES              (QSPI_ADMODE(2))                      /*!<Address on two lines.*/
#define QSPI_ADDRESS_MODE_4_LINES              (QSPI_ADMODE(3))                      /*!<Address on quad lines.*/

/** @defgroup QSPI_InstructionMode QSPI Instruction mode.
* @{
*/
#define QSPI_INSTRUCTION_MODE_NONE              (QSPI_IMODE(0))                       /*!<No instruction*/
#define QSPI_INSTRUCTION_MODE_1_LINE            (QSPI_IMODE(1))                       /*!<Instruction on a single line*/
#define QSPI_INSTRUCTION_MODE_2_LINES           (QSPI_IMODE(2))                       /*!<Instruction on two lines*/
#define QSPI_INSTRUCTION_MODE_4_LINES           (QSPI_IMODE(3))                       /*!<Instruction on four lines*/

#ifdef __cplusplus
}
#endif

#endif
