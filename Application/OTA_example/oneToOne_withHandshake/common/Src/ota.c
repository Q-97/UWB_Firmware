/*****************************************************************************
* File: ota.c
* Descirption: this file contains the functions support ota test.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team zyc
* Mail:   ultraception@ultraception.com
* Date:   2025 - 12
*****************************************************************************/
#include "ota.h"
#include "hal_uart.h"
#include "hal_delay.h"
#include "hal_uwb.h"
#include "hal_gp_timer.h"

OTA_Uart_Deal   ota_uart = {0};
OTA_INFO        ota_info = {0};
OTA_REQ_MSG     packet_up_req = {0};
//OTA_DATA_MSG    packet_up_data = {0};

volatile uint8_t g_ota_rsp_flag = 0;
volatile uint8_t g_ota_data_rsp = 0;
volatile uint16_t g_ota_data_seq = 0;
uint8_t ota_start_flag = 0;
uint8_t ota_role = OTA_ROLE_MASTER;
uint8_t ota_rx_ok_flag = 0;
uint8_t ota_rx_error_flag = 0;
uint8_t ota_rx_timeout_flag = 0;
uint8_t ota_rx_cp_error_flag = 0;
uint8_t ota_rx_phr_error_flag = 0;
uint8_t ota_tx_done_flag = 0;

uint8_t g_ota_req_msg_head[5]  = {0xe0, 0xe1, 0xe2};
uint8_t g_ota_rsp_msg_head[5]  = {0xe3, 0xe4, 0xe5};
uint8_t g_ota_data_msg_head[5] = {0xe4, 0xe5, 0xe6};
uint8_t g_ota_data_rsp_head[5] = {0xe5, 0xe6, 0xe7};
static const uint16_t crc16tab[256] =
{
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};
volatile uint16_t recv_num = 0;
volatile uint32_t recv_total_byte = 0;
extern volatile uint8_t slave_tx_done_flag;

uint16_t om_crc16_ccitt(uint16_t crcinit, const void *buf, unsigned len)
{
    register unsigned counter;
    register uint16_t crc = crcinit;
    const uint8_t *crc_buf = (uint8_t *)buf;

    for( counter = 0; counter < len; counter++)
        crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(uint8_t *)crc_buf++) & 0x00FF];

    return crc;
}

void ota_soft_reset(void)
{
    sys_ctrl_write(0x08, 0x08000001);
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}

static void ota_save_data_to_flash(uint8_t *buff, uint32_t write_flash_addr, uint32_t data_size)
{
	uint16_t i,num;
	num = data_size / QSPI_PAGE_SIZE;
	
	for(i=0; i < num; i++)
	{
		__disable_irq();
		qspi_write_buffer(buff + i*QSPI_PAGE_SIZE, write_flash_addr + i*QSPI_PAGE_SIZE, QSPI_PAGE_SIZE, QSPI_DATASIZE_BYTE);
		__enable_irq();
	}
	if(data_size % QSPI_PAGE_SIZE)
	{
		__disable_irq();
		qspi_write_buffer(buff + i*QSPI_PAGE_SIZE, write_flash_addr + i*QSPI_PAGE_SIZE, data_size % QSPI_PAGE_SIZE, QSPI_DATASIZE_BYTE);
		__enable_irq();
	}
}
ERROR_Type hal_flash_erase(uint32_t address,uint32_t dat_size)
{
	uint16_t num = 0;
	uint16_t i = 0;
	
	if((address % QSPI_SECTOR_SIZE) != 0)
	{
		LOG_ERROR("error address, is not 4k-aligned");
		return ERROR;
	}
	
	num = (dat_size / QSPI_SECTOR_SIZE) + ((dat_size % QSPI_SECTOR_SIZE) > 0 ? 1 : 0);
	
	for(i = 0; i < num; i++)
	{
		qspi_erase_sector(address + i * QSPI_SECTOR_SIZE);
	}
    
    return SUCCESS;
}


/*************************************UART Deal Function start***************************************/

void OTA_Uart_Recv_Deal(uint8_t dat)
{
	static uint32_t last_tick=0;
    static uint32_t cur_tick=0;

    cur_tick = hal_get_cur_sys_time();
    if(cur_tick >= last_tick)
    {
        if((((cur_tick - last_tick) << 2) / 1000000) > 300) //msg timeout 200ms
        {
            ota_uart.len = 0;
        }
    }
    else
    {
        if((((0xffffffffUL - last_tick + cur_tick) << 2) / 1000000) > 300) //msg timeout 200ms
        {
            ota_uart.len = 0;
        }
    }
    last_tick = cur_tick;
	
	ota_uart.buf[ota_uart.len++] = dat;
	if(ota_uart.len > 4 && (ota_uart.len == (ota_uart.buf[2]*256 + ota_uart.buf[3] + 4)) &&
			ota_uart.buf[0]==0xa5 && ota_uart.buf[1]==0x5a)
	{
        if((ota_uart.buf[4] & 0xF0) == 0x30)
        {
            ota_start_flag = 1;
            ota_info.status = UP_STATUS_MASTER_UP_REMOTE;
        }else{
            ota_uart.pack_flag = 1;
        }
	}
}

static uint8_t is_checksum(uint8_t *pdata,uint32_t len)
{
	uint16_t i = 0;
	uint8_t sum = 0;
	for (i=0;i<len;i++)sum+= pdata[i];
	return sum;
}
/**************************************
software data from uart format
| byte0 | byte1 | byte2 | byte3 | byte4                 | 
| 0xA5  | 0x5A  | len_H | len_L | local flag & msg type |

UCI_MSG_HEAD:
|byte5 | byte6 | byte7 | byte8| byte9 | byte10 |
|total_packet  | total_byte                    |

UCI_MSG_DATA:
|byte5 | byte6 | byte7 .. byte len - 2| byte len - 1 |
| seq          | data                 | checksum     |

A5	5A	LEN_H	LEN_L	Local&msg_type	seq_H	seq_L
***************************************/
void OTA_Update_to_APP2(uint16_t cmd_len, uint8_t* cmd_buf)
{
	uint8_t update_dir		= 0;
	uint8_t msg_type		= 0;
	uint8_t resp[6]			= {0x5a, 0xa5, 0x00, 0x02, 0x00, 0x00};
	uint16_t seq			= 0;
	uint32_t ttt = 0;
	if(cmd_buf==NULL || cmd_len >= OTA_UART_DATSIZE || cmd_len==0)return;
	if((cmd_buf[0] != 0xA5) || (cmd_buf[1] != 0x5A))return;
	if(cmd_len <= 4 || (cmd_len != (cmd_buf[2]*256 + cmd_buf[3] + 4)))return;
	
	update_dir = cmd_buf[4]&0xf0;
	msg_type = cmd_buf[4]&0x0f;
	resp[4] = cmd_buf[4];
	
	if(msg_type == OTA_UCI_MSG_HEAD)
	{
		ota_info.total_packet_flash = ((uint16_t)cmd_buf[5]<<8) | cmd_buf[6];
		ota_info.total_byte = ((uint32_t)cmd_buf[7]<<24) | ((uint32_t)cmd_buf[8]<<16) | ((uint32_t) cmd_buf[9]<<8) | cmd_buf[10];
		ota_info.crc16 = ((uint16_t)cmd_buf[11] << 8) | cmd_buf[12];
		
		recv_num=0;
		ota_start_flag=1;
		ota_info.status = UP_STATUS_UART_RECV;
		NVIC_DisableIRQ(UWB_IRQn);

		__disable_irq();
		hal_flash_erase(APP2_FLASH_ADDR,ota_info.total_byte);
        hal_flash_erase(OTA_TOTAL_BYTES,6);
        ota_save_data_to_flash((uint8_t*)(&ota_info.total_byte), OTA_TOTAL_BYTES, 4);
        ota_save_data_to_flash((uint8_t*)(&ota_info.crc16), OTA_TOTAL_BYTES + 4, 2);
		__enable_irq();
	}
	else if(msg_type == OTA_UCI_MSG_DATA)
	{
		if(is_checksum(cmd_buf,cmd_len-1) != cmd_buf[cmd_len-1])return;
		
		seq = ((uint16_t)cmd_buf[5]<<8) | cmd_buf[6];
		recv_num++;
		
		ota_save_data_to_flash(&cmd_buf[7], (APP2_FLASH_ADDR + (seq * QSPI_PAGE_SIZE)), cmd_len-8);
		
		if((recv_num == ota_info.total_packet_flash) && (seq == (ota_info.total_packet_flash - 1)))
		{
			NVIC_EnableIRQ(UWB_IRQn);
			ota_role = OTA_ROLE_MASTER;
			if(update_dir == UPDATE_DIR_LOCAL){
				ota_info.status = UP_STATUS_MASTER_UP_LOCAL;
            }else if(update_dir == UPDATE_DIR_OTA){
				ota_info.status = UP_STATUS_MASTER_UP_REMOTE;
            }else if(update_dir == UPDATE_DIR_APP2){
                hal_uart_send_data(0, resp, 6);
                hal_delay_ms(5);
                ota_soft_reset();
            }
		}
	}
	hal_uart_send_data(0, resp, 6);
}
/*************************************UART Deal Function end***************************************/


/*************************************UWB Callback Function start***************************************/
static void tx_done_proc(const zn_cb_data_t* rx_data)
{
	ota_tx_done_flag = 1;
}
static void rx_ok_proc(const zn_cb_data_t* rx_data)
{
	uint16_t len = rx_data->data_length - 2;
	uint32_t dat;
    uint16_t crc16 = 0;
    uint8_t data_crc = 0;
    uint32_t data_num = 0;
	printf("rx ok\n");
	OTA_DATA_MSG *data_pkt = NULL;

	if((rx_data->data_length >= RX_BUFFER_MAX_LEN) || (rx_data->data_length == 0))
	{
		printf("error rx data len %d\r\n", rx_data->data_length);
		hal_force_uwb_off();
		hal_uwb_immediate_rx();
		return;
	}
	ota_rx_ok_flag = 1;
	hal_uwb_read_rx_buffer((uint8_t *)rx_data->data, len);	
	//hal_gp_timer_reset_cnt(TIMER2);
    if(ota_info.status == UP_STATUS_MASTER_SEND_AND_RECV)
    {
        data_pkt = (OTA_DATA_MSG*)rx_data->data;        
        if(!memcmp(data_pkt, g_ota_rsp_msg_head, 3))
        {
            g_ota_rsp_flag = 1;
            printf("g_ota_rsp_flag = 1\n");
            ota_info.status = UP_STATUS_MASTER_REQ_RING;
            return;
        }
    }
    else if(ota_info.status == UP_STATUS_MASTER_REQ_RING)
    {
        printf("data rsp, \n");
        data_pkt = (OTA_DATA_MSG*)rx_data->data;   
        if(!memcmp(data_pkt, g_ota_data_rsp_head, 3))
        {
            g_ota_data_seq = data_pkt->seq_num;
            g_ota_data_rsp = 1;
            printf("g_ota_data_rsp ok\n");
            return;
        }
    }
	else if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		data_pkt = (OTA_DATA_MSG*)rx_data->data;
        OTA_DATA_MSG packet_data_rsp = {0};
		if(!memcmp(data_pkt, g_ota_data_msg_head, 3))
		{
			if(data_pkt->seq_num >= ota_info.total_packet_air)
			{
				printf("ota slave recv packnum error:%d,total_packet_air:%d\r\n",data_pkt->seq_num, ota_info.total_packet_air);
				hal_force_uwb_off();
				hal_uwb_immediate_rx();
				return;
			}
            __disable_irq();
			dat = 0;
			if(recv_num == data_pkt->seq_num)
			{
				ota_save_data_to_flash(data_pkt->data, (APP2_FLASH_ADDR + (data_pkt->seq_num * OTA_DATA_PACK_SIZE)), data_pkt->len);
				recv_num += 1;
				recv_total_byte += data_pkt->len;
			}
			if((recv_num == ota_info.total_packet_air) && (recv_total_byte == ota_info.total_byte))
			{
                //flash data crc check
                data_num = (recv_total_byte % 4) ? (recv_total_byte / 4 + 1) : (recv_total_byte / 4);
                for(uint32_t i = 0; i < data_num; i++)
                {
                    qspi_memory_mapped_read(&dat, (APP2_FLASH_ADDR + (i << 2)), 1);
                    data_crc = (dat) & 0xFF;
                    if((i<<2) + 1 == recv_total_byte)
                    {
                        crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                        break;
                    }
                    crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                    data_crc = (dat >> 8) & 0xFF;
                    if((i<<2) + 2 == recv_total_byte)
                    {
                        crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                        break;
                    }
                    crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                    data_crc = (dat >> 16) & 0xFF;
                    if((i<<2) + 3 == recv_total_byte)
                    {
                        crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                        break;
                    }
                    crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                    data_crc = (dat >> 24) & 0xFF;
                    if((i<<2) + 4 == recv_total_byte)
                    {
                        crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                        break;
                    }
                    crc16 = om_crc16_ccitt(crc16, &data_crc, 1);
                }
                if(crc16 != ota_info.crc16)
                {
                    printf("crc err: flash crc is 0x%x, ota crc is 0x%x\n", crc16, ota_info.crc16);
                    return;
                }                
                memcpy(packet_data_rsp.head, g_ota_data_rsp_head, 3);
                packet_data_rsp.seq_num = data_pkt->seq_num;
                hal_uwb_write_tx_buffer((uint8_t *)&packet_data_rsp, 6);
                hal_uwb_immediate_tx();
                hal_delay_us(300);
                hal_uwb_write_tx_buffer((uint8_t *)&packet_data_rsp, 6);
                hal_uwb_immediate_tx();
                hal_delay_us(300);
				ota_info.status = UP_STATUS_FINISH;
                __enable_irq();
                return;
			}else{
                printf("%d:%d %d %d %d\r\n",data_pkt->seq_num, recv_num, ota_info.total_packet_air, recv_total_byte, ota_info.total_byte);
            }
            memcpy(packet_data_rsp.head, g_ota_data_rsp_head, 3);
            packet_data_rsp.seq_num = data_pkt->seq_num;
            hal_uwb_write_tx_buffer((uint8_t *)&packet_data_rsp, 6);
            hal_uwb_immediate_tx();
            hal_delay_us(200);
            __enable_irq();
		}else { printf("ota slave recv data error:0x%x,0x%x,0x%x\r\n",data_pkt->head[0],data_pkt->head[1],data_pkt->head[2]); }
	}
	ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
}
static void rx_error_proc(const zn_cb_data_t* rx_data)
{
    ota_rx_error_flag = 1;
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx err\n");
	}
}
static void rx_timeout_proc(const zn_cb_data_t* rx_data)
{
    ota_rx_timeout_flag = 1;
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
        ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx timeout\n");
	}
}
static void rx_cp_error_proc(const zn_cb_data_t* rx_data)
{
    ota_rx_cp_error_flag = 1;
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx cp err\n");
	}
}

static void rx_phr_err_proc(const zn_cb_data_t* rx_data)
{
    ota_rx_phr_error_flag = 1;
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx phr err\n");
	}
}
static void ota_update_failure_proc(void)
{
    zn_force_trx_off();
    printf("update version failure!\r\n");
    ota_soft_reset();
}
/*************************************UWB Callback Function end***************************************/


void OTA_Slave_Req_Proc(const uint8_t *data)
{
	OTA_REQ_MSG *req_pkt = NULL;
	
	req_pkt = (OTA_REQ_MSG*)data;
	if(!memcmp(req_pkt, g_ota_req_msg_head, 3))
	{
		ota_info.crc16 = req_pkt->crc16;
		ota_info.total_byte = req_pkt->total_byte;
		//ota_info.total_packet_air = req_pkt->total_packet_air;
		ota_info.total_packet_air = req_pkt->total_byte / OTA_DATA_PACK_SIZE + ((req_pkt->total_byte % OTA_DATA_PACK_SIZE) > 0 ? 1 : 0);

		__disable_irq();
		hal_flash_erase(APP2_FLASH_ADDR,ota_info.total_byte);
		__enable_irq();

		ota_start_flag = 1;
		ota_role = OTA_ROLE_SLAVE;
		printf("\r\nota recv req, total_byte: 0x%x!\r\n", req_pkt->total_byte);
	}
}


/************************************************************************/
void ota_init(void )
{
	uint32_t reg;
	zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
	
	hal_force_uwb_off();
	zn_set_rx_timeout(5000);
	
	//close aoa
	reg = zn_read_32bit_reg(SYS_CFG_ID);
    reg &= (~SYS_CFG_PDOA_EN_BIT_MASK);
    zn_write_32bit_reg(SYS_CFG_ID, reg);

	
	__disable_irq();
	driver_config->zn_interrupt_callback.cb_tx_done = &tx_done_proc;
	driver_config->zn_interrupt_callback.cb_rx_ok = &rx_ok_proc;
	driver_config->zn_interrupt_callback.cb_rx_err = &rx_error_proc;
	driver_config->zn_interrupt_callback.cb_rx_timeout = &rx_timeout_proc;
    driver_config->zn_interrupt_callback.cb_rx_phr_err = &rx_phr_err_proc;
	__enable_irq();
}

void OTA_Update_Local(void)
{
	uint32_t up_flag=APP2_UP_FLAG;
	
	hal_delay_ms(2);
	printf("begin to reset the device...\r\n");
	__disable_irq();
	hal_flash_sector_erase(UPDATE_VER_FLASH_ADDR);
	ota_save_data_to_flash((uint8_t*)(&up_flag), UPDATE_VER_FLASH_ADDR, 4);
	ota_save_data_to_flash((uint8_t*)(&ota_info.total_byte), UPDATE_VER_FLASH_ADDR + 8, 4);
	__enable_irq();
	printf("reset\r\n");
	ota_soft_reset();
}

void OTA_Master_Send_Up_Req()
{
    uint32_t crc16 = 0;
    qspi_memory_mapped_read(&ota_info.total_byte, OTA_TOTAL_BYTES, 1);
    qspi_memory_mapped_read(&crc16, OTA_TOTAL_BYTES + 4, 1);
    ota_info.crc16 = (crc16) & 0xFFFF;
    printf("---crc16: 0x%x\n", ota_info.crc16);
	ota_info.total_packet_air  = (ota_info.total_byte / OTA_DATA_PACK_SIZE) + ((ota_info.total_byte % OTA_DATA_PACK_SIZE) > 0 ? 1 : 0);
	memcpy(packet_up_req.head, g_ota_req_msg_head, 3);
    packet_up_req.crc16 = ota_info.crc16;
    packet_up_req.total_byte = ota_info.total_byte;
    packet_up_req.total_packet_air = ota_info.total_packet_air;

	while(1)//!g_ota_rsp_flag)
    {
        zn_set_rx_timeout(4900);
        hal_uwb_write_tx_buffer((uint8_t*)&packet_up_req, sizeof(OTA_REQ_MSG));
        hal_uwb_rx_after_tx(0);
        //while((!rx_cp_error_flag) && (!rx_error_flag) && (!rx_ok_flag) && (!rx_timeout_flag));
        hal_delay_ms(6);
        hal_force_uwb_off();
        if(g_ota_rsp_flag)
        {
            break;
        }
    }
}
void OTA_Master_Send_Up_Data()
{
//    uint8_t progress[4] = {0x5A,0xA5,0xCC,0x00};
    uint16_t i = 0;
    uint16_t content_len = 0;
    OTA_DATA_MSG packet_up_data = {0};

    ota_info.total_packet_air  = (ota_info.total_byte / OTA_DATA_PACK_SIZE) + ((ota_info.total_byte % OTA_DATA_PACK_SIZE) > 0 ? 1 : 0);
    printf("0x%x,0x%x\n",ota_info.total_byte,ota_info.total_packet_air);
    for(i = 0; i < ota_info.total_packet_air; i++)
    {
        while(1)
        {
            if(g_ota_data_rsp)
            {
//                progress[3] = (i+1)*100/ota_info.total_packet_air;
//                hal_uart_send_data(progress, 4);
                printf("---%d---%d%%\n", (i+1), (i+1)*100/ota_info.total_packet_air);                
                g_ota_data_rsp = 0;
                if(g_ota_data_seq == i)
                {
                    printf("break\n");
                    break;
                }
            }
            
            if(i == ota_info.total_packet_air - 1)
            {
                content_len = ota_info.total_byte % OTA_DATA_PACK_SIZE;
            }
            else
            {
                content_len = OTA_DATA_PACK_SIZE;
            }
            memcpy(packet_up_data.head, g_ota_data_msg_head, 3);
            packet_up_data.seq_num = i;
            packet_up_data.len = content_len;
            qspi_memory_mapped_read((uint32_t*)packet_up_data.data, (APP2_FLASH_ADDR + i * OTA_DATA_PACK_SIZE), OTA_DATA_PACK_SIZE/4);
            
            ota_tx_done_flag = 0;
            hal_uwb_write_tx_buffer((uint8_t *)&packet_up_data, 8 + content_len);
            hal_uwb_immediate_tx();
            while(!ota_tx_done_flag);
            ota_rx_ok_flag = 0;
            ota_rx_error_flag = 0;
            ota_rx_timeout_flag = 0;
            ota_rx_phr_error_flag = 0;
            hal_uwb_immediate_rx();
            while((!ota_rx_ok_flag)&&(!ota_rx_error_flag)&&(!ota_rx_timeout_flag)&&(!ota_rx_phr_error_flag));
        }
    }
    return;
}
void OTA_Master_Update_Remote(void)
{
    uint8_t ret[5] = {0x4A,0xA4,0x00,0x01,0x00};//remote update done response
    uint32_t reg = 0;
	printf("ota send start\n");     
    OTA_Master_Send_Up_Req();
	printf("ota req send and recv ok\n");
	mdelay(10);
    zn_modify_psdu_data_rate(PSDU_RATE_681);
    reg = zn_read_32bit_reg(SYS_CFG_ID);
    reg |= SYS_CFG_PHR_MODE_BIT_MASK;//using the enhance PHR length
    zn_write_32bit_reg(SYS_CFG_ID, reg);

    OTA_Master_Send_Up_Data();

	printf("ota send end\n");
	hal_uart_send_data(0, ret, 5);    
    mdelay(20);
	ota_soft_reset();
}

void OTA_Loop(void)
{
	if(ota_info.status == UP_STATUS_UART_RECV)
	{
		//uart recv timeout deal
		
	}
	if(ota_role == OTA_ROLE_MASTER)
    {
		if(ota_info.status == UP_STATUS_MASTER_UP_LOCAL)
		{
			OTA_Update_Local();
			ota_info.status = UP_STATUS_FINISH;
		}
		else if(ota_info.status == UP_STATUS_MASTER_UP_REMOTE)
		{
			ota_init();
			ota_info.status = UP_STATUS_MASTER_SEND_AND_RECV;
			recv_num = 0;
			OTA_Master_Update_Remote();
		}
    }
    else if(ota_role == OTA_ROLE_SLAVE)
    {
        if(ota_info.status == UP_STATUS_SLAVE_OTA_RSP)
        {
            for(uint8_t i = 0; i < 2; i++)//send 2 times makes good success rate
            {
                hal_uwb_write_tx_buffer(g_ota_rsp_msg_head, sizeof(g_ota_rsp_msg_head));
                hal_uwb_immediate_tx();
                while(!slave_tx_done_flag);
                hal_delay_ms(1);
            }            
            ota_info.status = UP_STATUS_SLAVE_RECV_INIT;
        }
		else if(ota_info.status == UP_STATUS_SLAVE_RECV_INIT)
		{
            //hal_gp_timer_close(gp_timer.timer_id);
			ota_init();
			recv_num = 0;
			ota_info.status = UP_STATUS_SLAVE_RECV_PKG;
			
			
			uint32_t reg = 0;
			zn_modify_psdu_data_rate(PSDU_RATE_681);
            reg = zn_read_32bit_reg(SYS_CFG_ID);
            reg |= SYS_CFG_PHR_MODE_BIT_MASK;    //using the enhance PHR length
            zn_write_32bit_reg(SYS_CFG_ID, reg);
			
			
//			hal_gp_timer_t timer_cfg = {0};
//			timer_cfg.timer_id = TIMER2;
//			timer_cfg.clk_src = PLL_CLK;//124.8MHz
//			timer_cfg.clk_div = 0;
//			timer_cfg.mode = TIMER_USER_DEFINE;
//			timer_cfg.interrupt_en = 1;
//			timer_cfg.time1 = (uint32_t)(30*1000*1000);//us
//			timer_cfg.func = (TIMER_CallbackType)&ota_update_failure_proc;
//			hal_gp_timer_init(&timer_cfg);
//			hal_gp_timer_start(timer_cfg.timer_id);
			
			hal_uwb_immediate_rx();
		}
        else if(ota_info.status == UP_STATUS_SLAVE_RECV_CONTINUE)
        {
            hal_force_uwb_off();
            hal_uwb_immediate_rx();
            ota_info.status = UP_STATUS_SLAVE_RECV_PKG;
        }
		else if(ota_info.status == UP_STATUS_FINISH)
		{
			//printf("sucess\r\n");
			OTA_Update_Local();
		}
    }
}

