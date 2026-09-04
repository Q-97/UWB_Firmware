/*****************************************************************************
 *  File: zn_qspi_gd25q40.h
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

#ifndef __QSPI_GD25Q40_H__
#define __QSPI_GD25Q40_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"
#include "zn_qspi.h"
extern uint32_t g_jedecID;

/* gd15 base info*/
#define QSPI_FLASH_SIZE     (g_jedecID &0xFF)                         
#define QSPI_SECTOR_SIZE    (4 * 1024)              /* sector size,4KB */
#define QSPI_PAGE_SIZE      256                     /* page size,256 bytes*/
#define QSPI_END_ADDR       (1 << QSPI_FLASH_SIZE)  /* Flash end address */
#define QSPI_FLASH_SIZES    (1 << QSPI_FLASH_SIZE )        /* Flash sizes, eg QSPI_FLASH_SIZE=20,2^20 = 1M bytes*/


/* GD25Q40 refer cmd*/
#define READ_JEDEC_ID_CMD                       0x9F
#define WRITE_STATUS_CMD                        0x01
#define WRITE_ENABLE_CMD                        0x06
#define READ_STATUS_REG1_CMD                    0x05
#define READ_STATUS_REG2_CMD                    0x35 
#define READ_STATUS_REG3_CMD                    0x15 
#define PAGE_PROG_CMD                           0x02  
#define READ_DATA_CMD                           0x03  
#define SECTOR_ERASE_4KB_CMD                    0x20  
#define QUAD_IN_PAGE_PROG_CMD                   0x32
#define CHIP_ERASE_CMD                          0xC7
#define FAST_READ_QUAD_OUT_CMD                  0x6B
#define FAST_READ_QUAD_CMD                      0xEB
#define BLOCK_ERASE_32KB_CMD                    0x52
#define BLOCK_ERASE_64KB_CMD                    0xD8
#define RESET_ENABLE_CMD                        0x66
#define RESET_CMD                               0x99
/*Status Registers*/
#define ERASE_OR_WRITE_BUSY                     0x01
/*Status2 Registers*/
#define QUAD_ENABLE                             0x02
/*Back up the following commands ,for later use by the extension API*/
/* Reset Operations */
#define RESET_ENABLE_CMD                        0x66
#define RESET_MEMORY_CMD                        0x99
/* Identification Operations */
#define READ_RELEASE_POWER_DOWN_OR_ID_CMD       0xAB
#define READ_DEVICE_ID_CMD                      0x90
#define READ_JEDEC_ID_CMD                       0x9F
/* Read Operations */
#define READ_DATA_CMD                           0x03  
#define FAST_READ_CMD                           0x0B
/* Program Operations */
#define PAGE_PROGRAM  0x02
/* Erase Operations */
#define SECTOR_ERASE_4KB_CMD                    0x20  
#define BLOCK_ERASE_32KB_CMD                    0x52
#define BLOCK_ERASE_64KB_CMD                    0xD8
#define CHIP_ERASE_CMD                          0xC7
#define CHIP_ERASE_CMD2                         0x60
/* Register Operations Status*/
#define READ_STATUS_REG1_CMD                    0x05 
#define WRITE_STATUS_REG1_CMD                   0x01
#define READ_STATUS_REG2_CMD                    0x35 
#define WRITE_STATUS_REG2_CMD                   0x31 
#define READ_STATUS_REG3_CMD                    0x15  
#define WRITE_STATUS_REG3_CMD                   0x11 

/*when wrtie data to flash*/
#define QSPI_DATASIZE_BYTE                      0
#define QSPI_DATASIZE_SHORT                     1
#define QSPI_DATASIZE_WORD                      3

uint32_t qspi_read_id(void);
int qspi_read_status(void);
int qspi_read_status2(void);
int qspi_write_status(uint8_t buf[2]);
int qspi_erase_sector(uint32_t address);
int qspi_erase_chip(void);
int qspi_write_buffer(uint8_t *pBuf, uint32_t uiWriteAddr, uint16_t usWriteSize,uint8_t ucDataSize);
int qspi_memory_mapped(void);
int qspi_memory_mapped_read(uint32_t *pBuf, uint32_t uiReadAddr, uint32_t uiSize);
void qspi_flash_init(void);
void qspi_read_flash_info(uint8_t* buf);
void qspi_config_sck_scaler(uint8_t div);

#ifdef __cplusplus
}
#endif

#endif
