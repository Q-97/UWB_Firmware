/*****************************************************************************
 *  File: zn_qspi.h
 *
 *  Descirption: this file contains the functions support qspi operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2022-3-22
 *
 *****************************************************************************/
#ifndef __ZN_QSPI_H__
#define __ZN_QSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_qspi_reg.h"



/**
  * @brief  QSPI Command structure definition
  */
typedef struct
{
    uint32_t DdrMode;            /* Specifies the double data rate mode for address, alternate byte and data phase
                                  This parameter can be a value of @ref QSPI_DdrMode */
    union 
    {
        uint32_t DirectNowrap;             /*QSPI does not support WRAP in direct read mode..*/
        uint32_t IndirectAcessMode;        /*Indirect access mode data phase direction.*/
    }IndirectOrDirectMode;
    
    union 
    {
        uint32_t WrapMode;             /*Indirect access mode data phase direction.*/
        uint32_t Xipimmenter;          /*This bit indicates that when QSPI's FSM comes back from indirect access,.*/
    }IndirectXipOrDirectWrapMode;
    uint32_t DummyCycles;        /* Specifies the Number of Dummy Cycles.
                                  This parameter can be a number between 0 and 31 */
    uint32_t DataSize;           /*Data size.*/
    uint32_t DataMode;           /* Data mode*/
    uint32_t AlternateBytesSize; /* Specifies the Alternate Bytes Size
                                  This parameter can be a value of @ref QSPI_AlternateBytesSize */
    uint32_t AlternateBytesMode;  /* Specifies the Alternate Bytes Mode
                                  This parameter can be a value of @ref QSPI_AlternateBytesMode */
    uint32_t AddressSize;        /* Specifies the Address Size
                                  This parameter can be a value of @ref QSPI_AddressSize */
    uint32_t AddressMode;        /* Specifies the Address Mode
                                  This parameter can be a value of @ref QSPI_AddressMode */
    uint32_t InstructionMode;    /* Specifies the Instruction Mode
                                  This parameter can be a value of @ref QSPI_InstructionMode */
    uint32_t Instruction;        /* Specifies the Instruction to be sent
                                  This parameter can be a value (8-bit) between 0x00 and 0xFF */
    uint32_t Address;            /* Specifies the Address to be sent (Size from 1 to 4 bytes according AddressSize)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
    uint32_t AlternateBytes;     /* Specifies the Alternate Bytes to be sent (Size from 1 to 4 bytes according AlternateBytesSize)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
    uint32_t NbData;             /* Specifies the number of data to transfer. (This is the number of bytes)
                                  This parameter can be any value between 0 and 0xFFFFFFFF (0 means undefined length
                                  until end of memory)*/

}QSPI_CommandTypeDef;

int qspi_wait_flag_state(uint32_t flag);
int qspi_command(QSPI_CommandTypeDef *cmd, uint32_t operationMode,uint8_t flashsize);
int qspi_command_with_txdata(QSPI_CommandTypeDef *cmd, uint32_t operationMode,uint8_t flashsize,uint8_t *pBuf);
int qspi_receive_by_byte(uint8_t *pData);
void qspi_flash_switch(uint8_t type);

#ifdef __cplusplus
}
#endif

#endif
