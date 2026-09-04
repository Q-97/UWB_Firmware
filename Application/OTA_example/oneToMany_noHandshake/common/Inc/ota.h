/*****************************************************************************
* File: ota.h
* Descirption: this file contains the functions support ota test.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team zgc
* Mail:   ultraception@ultraception.com
* Date:   2025 - 8
*****************************************************************************/
#ifndef _OTA_H_
#define _OTA_H_

#include <stdint.h>
#include "hal_flash.h"

extern uint8_t ota_start_flag;
extern uint8_t ota_role;

extern uint8_t g_ota_req_msg_head[5];
extern uint8_t g_ota_data_msg_head[5];

//role
#define     OTA_ROLE_MASTER         (0)
#define     OTA_ROLE_SLAVE          (1)

//dir
#define     UPDATE_DIR_OTA          (0x00)
#define     UPDATE_DIR_LOCAL        (0x10)

#define     APP1_FLASH_ADDR         (0x8000)
#define     APP2_UP_FLAG            (0x5AA55AA5)
#define     APP2_FLASH_ADDR         (0x38000)
#define     UPDATE_VER_FLASH_ADDR   (0x70000)
#define     CAN_UPGRADE_ID          0x151

//#define OTA_UWB_BUF_SIZE 1023
#define OTA_UART_DATSIZE 270
typedef enum up_cmd
{
    SEND_START_UPGRADE_CMD = 0,
    SEND_STOP_UPGRADE_CMD,
    SEND_TOTAL_PACKET_CMD,
    SEND_DATA_CMD,
    SEND_INQU_VER_CMD,
    SEND_FINAL
}up_cmd_t;
typedef struct
{
	uint8_t pack_flag;
	uint8_t buf[OTA_UART_DATSIZE];
	uint16_t len;
	
	uint16_t pack_num;//total pack num
	uint16_t pack_idx;//current pack idx      //uwb(ota) total pack num
}OTA_Uart_Deal;
extern OTA_Uart_Deal ota_uart;


typedef enum up_status
{
    UP_STATUS_NO = 0,
	
	UP_STATUS_UART_RECV,
	
    UP_STATUS_SLAVE_RECV_INIT,
    UP_STATUS_SLAVE_RECV_PKG,
    UP_STATUS_SLAVE_RECV_CONTINUE,
	
	UP_STATUS_MASTER_REQ_RING,
	UP_STATUS_MASTER_RECV_RING,
	UP_STATUS_MASTER_SEND,
	
    UP_STATUS_MASTER_UP_REMOTE,
    UP_STATUS_MASTER_UP_LOCAL,
    UP_STATUS_FINISH
}up_status_t;

#define OTA_DATA_PACK_SIZE  768  //256*3
#define OTA_RX_TIMEOUT      5000 //us

typedef struct _ota_info
{
	uint8_t dir;
	uint8_t status;
	
	uint16_t total_packet_flash;     //uart total pack
	uint16_t total_packet_air;       //uwb(ota) total pack
	uint32_t total_byte;
	uint32_t version;
}OTA_INFO;
extern OTA_INFO ota_info;


typedef struct ota_req_msg
{
    uint8_t  head[4];
    uint32_t version;
    uint32_t total_byte;
    uint32_t total_packet_air;      //uwb(ota) total pack num
}OTA_REQ_MSG;

typedef struct ota_data_msg
{
    uint8_t  head[4];
    uint16_t seq_num;//pack idx
    uint16_t len;
    uint8_t  data[1023];
}OTA_DATA_MSG;


uint32_t OTA_Get_Version(void);
void OTA_Uart_Recv_Deal(uint8_t dat);
void OTA_Update_to_APP2(uint16_t cmd_len, uint8_t* cmd_buf);
void OTA_Slave_Req_Proc(const uint8_t *data);
void OTA_Loop(void);

void OTA_Master_Send_Up_Data();

#endif //_OTA_H_
