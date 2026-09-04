/*****************************************************************************
* File: iap_boot.c
* Descirption: this file contains the functions support iap test.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 8
*****************************************************************************/
#include "iap_boot.h"


#define     APP1_FLASH_ADDR     (0x8000) 
#define     APP2_FLASH_ADDR     (0x38000)
#define     APP2_UP_FLAG        (0x5AA55AA5)
#define     BACK_VER_FLASH_ADDR (0x70000) 

#define  PAGE_SIZE                   256

typedef  void (*pfunction)(void);
pfunction jump_to_application;
uint32_t jump_address;

uint32_t flash_sectors_mask(uint32_t Size)
{
    uint32_t sectornumber = 0x0;
    uint32_t size = Size;

    if ((size % QSPI_SECTOR_SIZE) != 0)
    {
        sectornumber = (size / QSPI_SECTOR_SIZE) + 1;
    }
    else
    {
        sectornumber = size / QSPI_SECTOR_SIZE;
    }
    return sectornumber;

}

uint32_t flash_pages_mask(uint32_t Size)
{
    uint32_t page_number = 0x0;
    uint32_t size = Size;

    if ((size % PAGE_SIZE) != 0)
    {
        page_number = (size / PAGE_SIZE) + 1;
    }
    else
    {
        page_number = size / PAGE_SIZE;
    }
    return page_number;

}

void jump_to_app(uint32_t app_address)
{
	
	jump_address = *(__IO uint32_t*) (app_address + 4);
	__disable_irq();
	/* Jump to user application */
	jump_to_application = (pfunction) jump_address;
	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*) app_address);
	jump_to_application();
		
	
}

int iap_load_app(uint32_t dest_addr,uint32_t src_addr,uint32_t size)
{
    uint32_t sector_number          = 0;
    uint32_t page_number            = 0;
    int erase_counter               = 0;
    int ret                         = 0;
    uint32_t content[PAGE_SIZE+10]  = {0};
    int page_counter                = 0;
    
    sector_number = flash_sectors_mask(size);
    page_number   = flash_pages_mask(size); 
	for ( erase_counter = 0; erase_counter < sector_number ; erase_counter++)
	{
		ret = qspi_erase_sector(dest_addr+QSPI_SECTOR_SIZE * erase_counter);
        if(ret !=0)
        {
            return ret;
        }
	}
    __disable_irq();
    for(int page_counter=0; page_counter<page_number ;page_counter++)
    {
        hal_flash_read_data(content,src_addr+page_counter*PAGE_SIZE,PAGE_SIZE);
        if (page_counter*PAGE_SIZE+PAGE_SIZE <= size) //write file content
        {
            ret = qspi_write_buffer((uint8_t*)content, dest_addr +page_counter*PAGE_SIZE, PAGE_SIZE, QSPI_DATASIZE_BYTE);
        }
        else
        {
            if(0 != (size%PAGE_SIZE))
            {
                ret = qspi_write_buffer((uint8_t*)content, dest_addr +page_counter*PAGE_SIZE, PAGE_SIZE, QSPI_DATASIZE_BYTE);
            }
        }
    
    }
    __enable_irq();
    return ret;
    
}
void iap_update_version(uint32_t flash_addr, uint32_t version)
{
    qspi_erase_sector(flash_addr);
    qspi_write_buffer((uint8_t *)&version, flash_addr, 4, QSPI_DATASIZE_BYTE);
}
void print_flash_data( uint32_t addr)
{
    uint8_t data[257]= {0};
    uint16_t pack_num = 0;
    uint16_t print_count = 0;
    uint32_t total_byte = 0x11438;

    hal_flash_read_data(&total_byte, BACK_VER_FLASH_ADDR + 8, 1);


    pack_num = total_byte /256 + 1;
    
    for(uint16_t i = 0; i < pack_num; i++)
    {
        hal_flash_read_data((uint32_t*)data, addr + i*256, 64);
        if(i == (pack_num - 1))
        {
            print_count = total_byte%256;
        }
        else
        {
            print_count = 256;
        }
        for(uint16_t j = 0; j <print_count; j++)
        {
            printf("%02x ",data[j]);
        }
    }
}
uint8_t iap_boot_proc(void)
{
    uint32_t iap_upgrade_flag[3] = {0};
    uint32_t jump_address = FLASH_BASE_ADDR + APP1_FLASH_ADDR;
    uint32_t dest_addr = APP1_FLASH_ADDR;
    uint32_t src_addr  = APP2_FLASH_ADDR;

    hal_flash_read_data(iap_upgrade_flag, BACK_VER_FLASH_ADDR, 3);
    if(iap_upgrade_flag[0] == APP2_UP_FLAG)
    {
        iap_load_app(dest_addr, src_addr, iap_upgrade_flag[2]);
        qspi_erase_sector(BACK_VER_FLASH_ADDR);
        jump_to_app(jump_address);
    }  
    else
    {
        jump_to_app(jump_address);
    } 
    
    return 0;    
}
