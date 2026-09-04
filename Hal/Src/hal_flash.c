/*****************************************************************************
 *  File: hal_flash.c
 *
 * Descirption: this file contains the functions support flash operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_flash.h"

void hal_flash_init(void)
{
    qspi_flash_init();
}

void hal_flash_chip_erase(void)
{
    qspi_erase_chip();
}

ERROR_Type hal_flash_sector_erase(uint32_t address)
{
    if((address % QSPI_SECTOR_SIZE) != 0)
    {
        LOG_ERROR("error address, is not 4k-aligned");
        return ERROR;
    }
    qspi_erase_sector(address);
    
    return SUCCESS;
}


ERROR_Type hal_flash_read_data(uint32_t* data, uint32_t addr, uint32_t len)
{
    int ret = 0;
    
    ret = qspi_memory_mapped_read(data, addr, len);
    
    if(ret)
    {
        LOG_ERROR("error len is larger than max flash size");
        return ERROR;
    }
    
    return SUCCESS;
}

ERROR_Type hal_flash_write_data_bytes(uint8_t* data, uint32_t addr, uint32_t len)
{
    uint16_t idx          = 0;
    uint16_t page_num     = 1;
    uint32_t end_addr     = addr + len;
    uint32_t sector_num   = 0;
    
    if((addr % QSPI_SECTOR_SIZE) != 0)
    {
        LOG_ERROR("error addr, is not a start addr of a sector");
        return ERROR;
    }
    
    if(end_addr > QSPI_FLASH_SIZES)
    {
        LOG_ERROR("error len is lager than max flash size");
        return ERROR;
    }
    if((len % QSPI_PAGE_SIZE) != 0)
    {
        LOG_ERROR("error len is not an integer multiple of page size ");
        return ERROR;
    }
    sector_num  = (len / QSPI_SECTOR_SIZE) + ((len % QSPI_SECTOR_SIZE) > 0 ? 1 : 0);
    
    for(idx = 0; idx < sector_num; idx++)
    {
        qspi_erase_sector(addr + idx * QSPI_SECTOR_SIZE);
    }
    
    if(len > QSPI_PAGE_SIZE)
    {
        page_num = len / QSPI_PAGE_SIZE;  
    }
    
    for(idx = 0; idx < page_num; idx++)
    {
        qspi_write_buffer(data + idx * QSPI_PAGE_SIZE, addr + idx * QSPI_PAGE_SIZE, QSPI_PAGE_SIZE, QSPI_DATASIZE_BYTE);
    }
    
    return SUCCESS;
}

ERROR_Type hal_flash_write_data_short(uint8_t* data, uint32_t addr, uint32_t len)
{
    uint16_t idx           = 0;
    uint16_t page_num      = 1;
    uint32_t end_addr      = addr + len;
    uint32_t sector_num    = 0;
    
    if((addr % QSPI_SECTOR_SIZE) != 0)
    {
        LOG_ERROR("error addr, is not a start addr of a sector");
        return ERROR;
    }
    
    if((end_addr > QSPI_FLASH_SIZES) || (len & 0x01))
    {
        LOG_ERROR("error len is lager than max flash size or len is not multiple of 2");
        return ERROR;
    }
    
    if((len % QSPI_PAGE_SIZE) != 0)
    {
        LOG_ERROR("error len is not an integer multiple of page size ");
        return ERROR;
    }
    
    sector_num  = (len / QSPI_SECTOR_SIZE) + ((len % QSPI_SECTOR_SIZE) > 0 ? 1 : 0);
    
    for(idx = 0; idx < sector_num; idx++)
    {
        qspi_erase_sector(addr + idx * QSPI_SECTOR_SIZE);
    }
    
    if(len > QSPI_PAGE_SIZE)
    {
        page_num = len / QSPI_PAGE_SIZE;  
    }
    
    for(idx = 0; idx < page_num; idx++)
    {
        qspi_write_buffer(data + idx * QSPI_PAGE_SIZE, addr + idx * QSPI_PAGE_SIZE, QSPI_PAGE_SIZE, QSPI_DATASIZE_SHORT);
    }
    
    return SUCCESS;
}

ERROR_Type hal_flash_write_data_words(uint8_t* data, uint32_t addr, uint32_t len)
{
    uint16_t idx          = 0;
    uint16_t page_num     = 1;
    uint32_t end_addr     = addr + len;
    uint32_t remain_words = 0;
    uint32_t sector_num   = 0;
    
    if((addr % QSPI_SECTOR_SIZE) != 0)
    {
        LOG_ERROR("error addr, is not a start addr of a sector");
        return ERROR;
    }
    
    if((end_addr > QSPI_FLASH_SIZES) || (len & 0x03))
    {
        LOG_ERROR("error len is lager than max flash size or len is not multiple of 4");
        return ERROR;
    }
    
    if((len % QSPI_PAGE_SIZE) != 0)
    {
        LOG_ERROR("error len is not an integer multiple of page size ");
        return ERROR;
    }
    
    sector_num  = (len / QSPI_SECTOR_SIZE) + ((len % QSPI_SECTOR_SIZE) > 0 ? 1 : 0);
    
    for(idx = 0; idx < sector_num; idx++)
    {
        qspi_erase_sector(addr + idx * QSPI_SECTOR_SIZE);
    }
    
    if(len > QSPI_PAGE_SIZE)
    {
        page_num = len / QSPI_PAGE_SIZE;  
    }
    
    for(idx = 0; idx < page_num; idx++)
    {
        qspi_write_buffer(data + idx * QSPI_PAGE_SIZE, addr + idx * QSPI_PAGE_SIZE, QSPI_PAGE_SIZE, QSPI_DATASIZE_WORD);
    }
    
    return SUCCESS;
}


