/*****************************************************************************
 *  File: zn_qspi_w25q64.c
 *
 *  Descirption: this file contains the qspi w25q64 Flash driver.
 *
 *  Copyright (C) : 2022 ultraception.com.
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2022-3-22
 *
 *****************************************************************************/

#include "zn_qspi_gd25q40.h"
#include "zn_qspi.h"

#define QSPI_TIME_OUT 0x50000

uint32_t g_jedecID=0x13;

/**
* qspi_read_id
*
* @param none
* @return uiID: 32-bit device ID
*
* @brief Read the device ID from the QSPI flash.
*/
uint32_t qspi_read_id(void)
{
    uint32_t uiID = 0 ;
    QSPI_CommandTypeDef s_command;
    uint8_t buf[3] = {0};

    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_1_LINE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(READ_JEDEC_ID_CMD);  
    s_command.Address =  0;                               
    s_command.AlternateBytes =0;       
    s_command.NbData = 3;  
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);    
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);    
    qspi_receive_by_byte(buf);
    uiID = (buf[0] << 16) | (buf[1] << 8) | buf[2];
    return uiID;
}

/**
* qspi_write_enable
*
* @param none 
* @return none
*
* @brief Enable writing operations on the QSPI flash.
*/
static int qspi_write_enable(void)
{
    QSPI_CommandTypeDef s_command;
    uint32_t cnt = 0;
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_NONE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(WRITE_ENABLE_CMD);  
    s_command.Address =  0;                               
    s_command.AlternateBytes =0;       
    s_command.NbData = 0;  
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);    
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
    
    while(1)
    {        
        if(!(qspi_read_status()&ERASE_OR_WRITE_BUSY))
        {
            break;
        }
        if(cnt++>QSPI_TIME_OUT)
        {
            return -1;
        }
    }

    return 0;      
}



/**
* qspi_read_status
*
* @param none
* @return buf[0]: the status register value
*
* @brief Read the status register 1 from the QSPI flash.
*/
int qspi_read_status(void)
{
    QSPI_CommandTypeDef s_command;
    uint8_t buf[2] = {0};
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_1_LINE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(READ_STATUS_REG1_CMD);  
    s_command.Address =  0;                               
    s_command.AlternateBytes =0;       
    s_command.NbData = 1;  
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);

    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
    qspi_receive_by_byte(buf);
    return buf[0];
}

/**
* qspi_read_status2
*
* @param none
* @return buf[0]: the status register value
*
* @brief Read the status register 2 from the QSPI flash.
*/
int qspi_read_status2(void)
{
    QSPI_CommandTypeDef s_command;
    uint8_t buf[2] = {0};
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_1_LINE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(READ_STATUS_REG2_CMD);  
    s_command.Address =  0;                               
    s_command.AlternateBytes = 0;       
    s_command.NbData = 1;  
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);    
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
    qspi_receive_by_byte(buf);
    return buf[0];
}
/**
* qspi_read_flash_info
*
* @param buf
* @return none
*
* @brief Read the flash info.
*/
void qspi_read_flash_info(uint8_t* buf)
{
    QSPI_CommandTypeDef s_command;
  
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(8);   
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;        
    s_command.DataMode = QSPI_DATA_1_LINE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;
    s_command.Instruction = QSPI_INSTRUCTION(0x4B);  
    s_command.Address =  0;
    s_command.AlternateBytes =0;       
    s_command.NbData = 16;  
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);  
    qspi_receive_by_byte(buf);

    return;
}

/**
* qspi_write_status
*
* @param[in] buf: pointer to a buffer containing the new status register values
* @return 0: success, non-zero: error
*
* @brief Write the status registers in the QSPI flash.
*/
int qspi_write_status(uint8_t buf[2])
{    
    QSPI_CommandTypeDef s_command;
    qspi_write_enable();

    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_1_LINE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(WRITE_STATUS_CMD);  
    s_command.Address =  0;                               
    s_command.AlternateBytes =0;       
    s_command.NbData = 2;  
    
    qspi_command_with_txdata(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE,buf);    
    
    while(1)
    {    
        qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
        if(!(qspi_read_status()&ERASE_OR_WRITE_BUSY))
        {            
            break;
        }
    }    
    

    return 0;
}

/**
* qspi_eraseChip
*
* @param none
* @return 0: success, non-zero: error
*
* @brief Erase the entire QSPI flash.
*/
int qspi_erase_chip(void)
{
    QSPI_CommandTypeDef s_command;
    
    qspi_write_enable();

    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_NONE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_NONE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(CHIP_ERASE_CMD);  
    s_command.Address =  0;                               
    s_command.AlternateBytes =0;       
    s_command.NbData = 0;  
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);    
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
    while(1)
    {
        if(!(qspi_read_status()&ERASE_OR_WRITE_BUSY))
        {
            break;
        }
    }

    return 0;
}
/**
* qspi_write_buffer
*
* @param[in] pBuf: pointer to the data buffer to write
* @param[in] uiWriteAddr: the starting address to write to
* @param[in] usWriteSize: the number of bytes to write
* @param[in] ucDataSize: the size of each data element (0, 1, or 3 bytes)
* @return 0: success, negative value: error
*
* @brief Write a buffer to the QSPI flash.
*/
int qspi_write_buffer(uint8_t *pBuf, uint32_t uiWriteAddr, uint16_t usWriteSize,uint8_t ucDataSize)
{
    QSPI_CommandTypeDef s_command;
    uint16_t i =0;
    int ret = 0;
    uint8_t status=0;
    
    /*The data written is not within one page*/
    if ((uiWriteAddr+usWriteSize) > (uiWriteAddr/QSPI_PAGE_SIZE)*QSPI_PAGE_SIZE+QSPI_PAGE_SIZE)
    {
        return -1;
    }
    
    if (!(0==ucDataSize || 1==ucDataSize || 3==ucDataSize)) /*ucDataSize is not 0,1,3*/
    {
        return -2;
    }
    qspi_write_enable();

  // printf("status =0x%02x%02x\r\n",QSPI_ReadStatus2(),QSPI_ReadStatus());
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_WRITE;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DSIZE(ucDataSize);  /*QSPI_DATASIZE_8_BITS,QSPI_DATASIZE_16_BITS,QSPI_DATASIZE_32_BITS*/            
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_1_LINE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;  
    s_command.DataMode = QSPI_DATA_4_LINES;    
    s_command.Instruction = QSPI_INSTRUCTION(QUAD_IN_PAGE_PROG_CMD); /*note ,when address >16M， command word is different*/

    s_command.Address =  uiWriteAddr;                               
    s_command.AlternateBytes =0;       
    s_command.NbData = usWriteSize;  
    
    ret = qspi_command_with_txdata(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE,pBuf);
    
    if (0 != ret )
    {
        return ret;
    }
    
    while(1)
    {
        qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
        if(!(qspi_read_status()&ERASE_OR_WRITE_BUSY))
        {
            break;
        }
    }
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);

    return 0;
}
/**
* qspi_erase_sector
*
* @param[in] address: the sector address to erase
* @return 0: success, non-zero: error
*
* @brief Erase a sector in the QSPI flash.
*/
int qspi_erase_sector(uint32_t address)
{
    QSPI_CommandTypeDef s_command;
    
    qspi_write_enable();
    qspi_read_status();
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;                                   
    s_command.IndirectOrDirectMode.IndirectAcessMode = QSPI_INDIRECT_ACCESS_READ;
    s_command.IndirectXipOrDirectWrapMode.Xipimmenter = QSPI_XIPIMMENTER(0);
    s_command.DummyCycles = QSPI_NUMDC(0);                               
    s_command.DataSize =  QSPI_DATASIZE_8_BITS;         
    s_command.DataMode = QSPI_DATA_NONE;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_NONE;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_1_LINE;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(SECTOR_ERASE_4KB_CMD);  
    s_command.Address =  address;   /* need n*4KB(0x1000)*/                             
    s_command.AlternateBytes =0;       
    s_command.NbData = 0;  
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_INDIRECT,QSPI_FLASH_SIZE);
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
        
    while(1)
    {
        if(!(qspi_read_status()&ERASE_OR_WRITE_BUSY))
        {
            break;
        }
    }

    return 0;
}

/**
* qspi_memory_mapped
*
* @param none
* @return 0: success, non-zero: error
*
* @brief Configure the QSPI controller to use memory-mapped mode.
*/
int qspi_memory_mapped(void)
{
    QSPI_CommandTypeDef s_command;
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;    /* W25Q64 not support DDR */                                
    s_command.IndirectOrDirectMode.DirectNowrap = QSPI_NOWRAP(0); /**/
    s_command.IndirectXipOrDirectWrapMode.WrapMode = QSPI_WRAPMODE(0);
    s_command.DummyCycles = QSPI_NUMDC(4);  //DCbits is 0, dummy is 4                           
    s_command.DataSize =  QSPI_DATASIZE_32_BITS;  /*only supports 32 bits data*/       
    s_command.DataMode = QSPI_DATA_4_LINES;          
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTESSIZE_8_BITS;                        
    s_command.AlternateBytesMode = QSPI_ALTERNATE_BYTESMODE_4_LINES;    
    s_command.AddressSize = QSPI_ADDRESS_BYTESSIZE_24_BITS;                               
    s_command.AddressMode = QSPI_ADDRESS_MODE_4_LINES;                               
    s_command.InstructionMode = QSPI_INSTRUCTION_MODE_1_LINE;                           
    s_command.Instruction = QSPI_INSTRUCTION(FAST_READ_QUAD_CMD); /*note ,whne address >16M， command word is different*/
    s_command.Address =  0;                               
    s_command.AlternateBytes =0x00;       
    s_command.NbData = 0;   
    
    qspi_command(&s_command, QSPI_OPERATION_MODE_DIRECT_ACCESS,QSPI_FLASH_SIZE);    
    qspi_wait_flag_state(QSPI_TCF|QSPI_OPCRCF);
    return 0;
}

/**
* qspi_memory_mapped_read
*
* @param[out] pBuf: pointer to the buffer to store the read data
* @param[in] uiReadAddr: the starting address to read from
* @param[in] uiSize: the number of data elements to read
* @return 0: success, non-zero: error
*
* @brief Read data from the QSPI flash in memory-mapped mode.
*/
int qspi_memory_mapped_read(uint32_t *pBuf, uint32_t uiReadAddr, uint32_t uiSize)
{
    if (uiReadAddr+uiSize>QSPI_FLASH_SIZES)
    {
        return 1;
    }

    for(int i=0;i<uiSize;i++)
    {
        pBuf[i]=read_mreg32(FLASH_BASE_ADDR+uiReadAddr+i*4);

    }
    
    return 0;
}

/**
* qspi_flash_init
*
* @param none
* @return none
*
* @brief Initialize the QSPI flash and enable Quad SPI mode.
*/
void qspi_flash_init(void)
{
    uint8_t status[2];
    g_jedecID = qspi_read_id();
    status[1] = qspi_read_status2();
    /*enable QE*/
    if (QUAD_ENABLE != (status[1]&QUAD_ENABLE))
    {
        status[0] = qspi_read_status();
        status[1] |= QUAD_ENABLE;
        qspi_write_status(status);
    }

}

/**
* qspi_config_sck_scaler
*
* @param div caler factor Fsck = F/(2*(div+1)),div between 0 and 63
* @return none
*
* @brief config the scaler factor.
*/
void qspi_config_sck_scaler(uint8_t div)
{
    if(div > 63)
    {
        return;
    }
    write_mreg32(QSPI_CR_ADDR, QSPI_SCKSCALER(div) | QSPI_CSRHT(0) | QSPI_FMSIZE(0x14));
}