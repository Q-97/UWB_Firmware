/*****************************************************************************
 *  File: zn_qspi.c
 *
 *  Descirption: this file contains the functions support qspi operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-29
 *
 *****************************************************************************/
#include "zn_qspi.h"

/**
* qspi_wait_flag_state
*
* @param[in]  flag: Specified flag
* @return 0 on success
*
* @brief Waits for the specified flag state in the QSPI_SR_ADDR register
*/
int qspi_wait_flag_state(uint32_t flag)
{
    uint32_t val = 0;
    while(1)
    {
        val = read_mreg32(QSPI_SR_ADDR);
        if(flag==(val&flag))
        {
            break;
        }
    }
    return 0;
}
/**
* qspi_receive_by_word
*
* @param[out] pData: Pointer to the data buffer to store received data
* @return 0 on success
*
* @brief Receives data from the QSPI interface in word (32-bit) format
*/
int qspi_receive_by_word(uint32_t *pData)
{
    uint32_t dataLen = 0;
    uint32_t i=0;
    dataLen = read_mreg32(QSPI_DLR_ADDR)+1;

    dataLen=dataLen/4;
    
    for(i=0;i<dataLen;)
    {
        while(!(read_mreg32(QSPI_SR_ADDR)&QSPI_FIFOEMPTY))
        {
            *(pData+i)=read_mreg32(QSPI_FDR_ADDR);
            i++;
        }
    }
    return 0;
}
/**
* qspi_receive_by_short
*
* @param[out] pData: Pointer to the data buffer to store received data
* @return 0 on success
*
* @brief Receives data from the QSPI interface in short (16-bit) format
*/
int qspi_receive_by_short(uint16_t *pData)
{
    uint32_t dataLen = 0;
    uint32_t i=0;
    dataLen = read_mreg32(QSPI_DLR_ADDR)+1;

    dataLen=dataLen/2;
    
    for(i=0;i<dataLen;)
    {
        while(!(read_mreg32(QSPI_SR_ADDR)&QSPI_FIFOEMPTY))
        {
            *(pData+i)=read_mreg32(QSPI_FDR_ADDR);
            i++;
        }
    }
    return 0;
}
/**
* qspi_receive_by_byte
*
* @param[out] pData: Pointer to the data buffer to store received data
* @return 0 on success
*
* @brief Receives data from the QSPI interface in byte (8-bit) format
*/
int qspi_receive_by_byte(uint8_t *pData)
{
    uint32_t dataLen = 0;
    uint32_t i=0;
    dataLen = read_mreg32(QSPI_DLR_ADDR)+1;
    
    for(i=0;i<dataLen;)
    {
        while(!(read_mreg32(QSPI_SR_ADDR)&QSPI_FIFOEMPTY))
        {
            *(pData+i)=read_mreg32(QSPI_FDR_ADDR);
            i++;
        }
    }
    return 0;
}
/**
* qspi_command
*
* @param[in]  cmd: Pointer to the QSPI_CommandTypeDef structure
* @param[in]  operationMode: Operation mode (Direct access or Indirect access mode)
* @param[in]  flashsize: Flash size
* @return 0 on success, -1 on failure
*
* @brief Sets up QSPI command parameters and configures the QSPI interface
*/
int qspi_command(QSPI_CommandTypeDef *cmd, uint32_t operationMode,uint8_t flashsize)
{
    uint32_t modeVal=0;
    uint32_t controlVal=0;
    modeVal = (cmd->DdrMode|QSPI_IDMODE(0)|cmd->DummyCycles|cmd->DataSize|
                cmd->DataMode|cmd->AlternateBytesSize|
                cmd->AlternateBytesMode|cmd->AddressSize|
                cmd->AddressMode|cmd->InstructionMode|cmd->Instruction);
    
    controlVal=QSPI_SCKSCALER(0)|QSPI_CSRHT(0)|QSPI_FMSIZE(flashsize-1)|
                QSPI_XIPMODE(0)|QSPI_SCKMODE(0)|QSPI_OPMODE(operationMode);
    
    if(QSPI_OPERATION_MODE_DIRECT_ACCESS == operationMode)
    {
        /*QSPI_RMCR QSPI Direct Read Access Mode Control Register*/
        modeVal |= cmd->IndirectOrDirectMode.DirectNowrap;
        modeVal |= cmd->IndirectXipOrDirectWrapMode.WrapMode;
        write_mreg32(QSPI_RMCR_ADDR,modeVal);    
        /*---- Command with only alternate phase ----*/
        if (cmd->AlternateBytesMode != QSPI_ALTERNATE_BYTESMODE_NONE)
        {
            write_mreg32(QSPI_RABR_ADDR,cmd->AlternateBytes);
        }
        
    }
    else if (QSPI_OPERATION_MODE_INDIRECT == operationMode)
    {
        /*QSPI_OMCR, QSPI Indirect Mode Control Register*/
        modeVal |= cmd->IndirectOrDirectMode.DirectNowrap;
        modeVal |= cmd->IndirectXipOrDirectWrapMode.Xipimmenter;
        write_mreg32(QSPI_OMCR_ADDR,modeVal);
        /*---- Command with only alternate phase ----*/
        if (cmd->AlternateBytesMode != QSPI_ALTERNATE_BYTESMODE_NONE)
        {
            write_mreg32(QSPI_OABR_ADDR,cmd->AlternateBytes);
        }
        
        /*---- Command with only Address phase ----*/
        if (cmd->AddressMode != QSPI_ADDRESS_MODE_NONE)
        {
            write_mreg32(QSPI_IMAR_ADDR,cmd->Address);
        }
        
        /*---- Command with only data phase ----*/
        if (cmd->DataMode != QSPI_DATA_NONE)
        {
            write_mreg32(QSPI_DLR_ADDR,cmd->NbData-1);
        }
    }
    else
    {
        return -1;
    }
    
    
    write_mreg32(QSPI_CR_ADDR,controlVal);
    return 0;
}

/**
* qspi_command_with_txdata
*
* @param[in]  cmd: Pointer to the QSPI_CommandTypeDef structure
* @param[in]  operationMode: Operation mode (Direct access or Indirect access mode)
* @param[in]  flashsize: Flash size
* @param[in]  pBuf: Pointer to the data buffer to be transmitted
* @return 0 on success, negative value on failure
*
* @brief Sets up QSPI command parameters and sends data through the QSPI interface
*/
int qspi_command_with_txdata(QSPI_CommandTypeDef *cmd, uint32_t operationMode,uint8_t flashsize,uint8_t *pBuf)
{
    uint32_t modeVal=0;
    uint32_t controlVal=0;
    uint32_t i=0;
    uint32_t dataNum=0;

    if (QSPI_OPERATION_MODE_INDIRECT != operationMode 
        && cmd->IndirectOrDirectMode.IndirectAcessMode != QSPI_INDIRECT_ACCESS_WRITE)
    {
        return -1;
    }
    
    if (cmd->DataSize != QSPI_DATASIZE_8_BITS && cmd->DataSize != QSPI_DATASIZE_16_BITS && cmd->DataSize != QSPI_DATASIZE_32_BITS)
    {
        return -2;
    }

    modeVal = (cmd->DdrMode|QSPI_IDMODE(1)|cmd->DummyCycles|cmd->DataSize|
                cmd->DataMode|cmd->AlternateBytesSize|
                cmd->AlternateBytesMode|cmd->AddressSize|
                cmd->AddressMode|cmd->InstructionMode|cmd->Instruction);
    
    controlVal=QSPI_SCKSCALER(0)|QSPI_CSRHT(0)|QSPI_FMSIZE(flashsize-1)|
                QSPI_XIPMODE(0)|QSPI_SCKMODE(0)|QSPI_OPMODE(operationMode);
        
    
    /*QSPI_OMCR, QSPI Indirect Mode Control Register*/
    modeVal |= cmd->IndirectOrDirectMode.DirectNowrap;
    modeVal |= cmd->IndirectXipOrDirectWrapMode.Xipimmenter;
    write_mreg32(QSPI_OMCR_ADDR,modeVal);
    /*---- Command with only alternate phase ----*/
    if (cmd->AlternateBytesMode != QSPI_ALTERNATE_BYTESMODE_NONE)
    {
        write_mreg32(QSPI_RABR_ADDR,cmd->AlternateBytes);
    }
    
    /*---- Command with only Address phase ----*/
    if (cmd->AddressMode != QSPI_ADDRESS_MODE_NONE)
    {
        write_mreg32(QSPI_IMAR_ADDR,cmd->Address);
    }
        
    
    if (cmd->DataMode != QSPI_DATA_NONE)
    {
        write_mreg32(QSPI_DLR_ADDR,cmd->NbData-1);
    }

    /*---- Command with only data phase ----*/
    write_mreg32(QSPI_CR_ADDR,controlVal);
    if (cmd->DataSize == QSPI_DATASIZE_8_BITS)
    {
        uint8_t *pTmpBuf = (uint8_t *)pBuf;
        for(i=0;i<cmd->NbData;i++)
        {
            while(read_mreg32(QSPI_SR_ADDR)&QSPI_FIFOFULL){};
            write_mreg32(QSPI_FDR_ADDR,*pTmpBuf++);
        }
    }
    else if (cmd->DataSize == QSPI_DATASIZE_16_BITS)
    {
        uint16_t *pTmpBuf = (uint16_t *)pBuf;
        for(i=0;i<cmd->NbData;i=i+2)
        {
            while(read_mreg32(QSPI_SR_ADDR)&QSPI_FIFOFULL){};
            write_mreg32(QSPI_FDR_ADDR,*pTmpBuf++);
        }
    }
    else if (cmd->DataSize == QSPI_DATASIZE_32_BITS)
    {
        uint32_t *pTmpBuf = (uint32_t *)pBuf;
        for(i=0;i<cmd->NbData;i=i+4)
        {
            while(read_mreg32(QSPI_SR_ADDR)&QSPI_FIFOFULL){};
            write_mreg32(QSPI_FDR_ADDR,*pTmpBuf++);
        }
    }
    else
    {
        return -2;
    }
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
    return 0;
}
/**
* qspi_flash_switch
*
* @param[in]  type: Flash type (1 = off-chip, 0 = on-chip)
*
* @brief Switches between off-chip and on-chip flash memory for the QSPI interface
*/
void qspi_flash_switch(uint8_t type)
{
    if (1 == type) /*flash offchip*/
    {        
        /*start from ext flash ,set 6 original QSPI pin to GPIO */
        write_mreg32(PADREG_BASE_ADDR+QSPI_CLK_PREG,0x1);     /*QSPI_CLK_PREG PIN->GPIO*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_CSN_PREG,0x1);      /*QSPI_CSN_PREG PIN->GPIO*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_SIO_IO0_PREG,0x1);  /*QSPI_SIO_IO0_PREG PIN->GPIO*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_SOI_IO1_PREG,0x1);  /*QSPI_SIO_IO1_PREG PIN->GPIO*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_WP_IO2_PREG,0x1);   /*QSPI_SIO_IO2_PREG PIN->GPIO*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_HOLD_IO3_PREG,0x1); /*QSPI_SIO_IO3_PREG PIN->GPIO*/
        
        
        write_mreg32(PADREG_BASE_ADDR+SPI0_CLK_PREG,0x7F);     /*SPI0_CLK PIN->QSPI_CLK*/
        write_mreg32(PADREG_BASE_ADDR+SPI0_MISO_PREG,0x7F);    /*SPI0_MISO PIN->QSPI_CSN*/
        write_mreg32(PADREG_BASE_ADDR+SPI0_MOSI_PREG,0x7F);    /*SPI0_MOSI PIN->QSPI_SIO_IO0*/
        write_mreg32(PADREG_BASE_ADDR+SPI1_CLK_PREG,0x7F);     /*SPI1_CLK PIN->QSPI_SOI_IO1*/
        write_mreg32(PADREG_BASE_ADDR+SPI1_MISO_PREG,0x7F);    /*SPI1_MISO PIN->QSPI_WP_IO2*/
        write_mreg32(PADREG_BASE_ADDR+ SPI1_MOSI_PREG ,0x7F);  /*SPI1_MOSI PIN->QSPI_HOLD_IO3*/        
        /*
        SEL_GROUP Group select reg.  32 [31:2] -- NA 30'b0 Reserved 
                                        [1] selgp_qspi RW 1'h1 qspi group sel 
                                        [0] selgp_sync RW 1'b0 sync group sel 
        */
        write_mreg32(PADREG_BASE_ADDR+SEL_GROUP,read_mreg32(PADREG_BASE_ADDR+SEL_GROUP)&0x05);                 
    }
    else /*flash onchip*/
    {
        /*ext flash 6 pin Restore to default configuration*/
        write_mreg32(PADREG_BASE_ADDR+SPI0_CLK_PREG,0x01);    /*SPI0_CLK PIN->GPIOA9*/
        write_mreg32(PADREG_BASE_ADDR+SPI0_MISO_PREG,0x01);   /*SPI0_MISO PIN->GPIOA10*/
        write_mreg32(PADREG_BASE_ADDR+SPI0_MOSI_PREG,0x01);   /*SPI0_MOSI PIN ->GPIOA11*/
        write_mreg32(PADREG_BASE_ADDR+SPI1_CLK_PREG,0x01);    /*SPI1_CLK PIN->GPIOA12 */
        write_mreg32(PADREG_BASE_ADDR+SPI1_MISO_PREG,0x01);   /*SPI1_MISO PIN->GPIOA13*/
        write_mreg32(PADREG_BASE_ADDR+ SPI1_MOSI_PREG ,0x01); /*SPI1_MISO PIN->GPIOA14*/            
        
        
        /*start from sip flash ,set 6 original QSPI pin to QSPI */
        write_mreg32(PADREG_BASE_ADDR+QSPI_CLK_PREG,0x10);     ; /*QSPI_CLK_PREG PIN ->QSPI_CLK*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_CSN_PREG,0x10);     ; /*QSPI_CSN_PREG PIN->QSPI_CSN*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_SIO_IO0_PREG,0x10); ; /*QSPI_SIO_IO0_PREG PIN->QSPI_SIO_IO0*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_SOI_IO1_PREG,0x10); ; /*QSPI_SIO_IO1_PREG PIN->QSPI_SOI_IO1*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_WP_IO2_PREG,0x10);  ; /*QSPI_SIO_IO2_PREG PIN->QSPI_SOI_IO2*/
        write_mreg32(PADREG_BASE_ADDR+QSPI_HOLD_IO3_PREG,0x10);; /*QSPI_SIO_IO3_PREG PIN->QSPI_SOI_IO3*/
        
        /*
        SEL_GROUP Group select reg.  32 [31:2] -- NA 30'b0 Reserved 
                                        [1] selgp_qspi RW 1'h1 qspi group sel 
                                        [0] selgp_sync RW 1'b0 sync group sel 

        */
        write_mreg32(PADREG_BASE_ADDR+SEL_GROUP,read_mreg32(PADREG_BASE_ADDR+SEL_GROUP)|0x02); 
    }
}


