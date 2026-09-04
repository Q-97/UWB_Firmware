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
#include "range.h"
#include "hal_delay.h"
#include "hal_can.h"

#define CAN_MAX_LEN   (64)
OTA_Uart_Deal   ota_uart = {0};
OTA_INFO        ota_info = {0};
OTA_REQ_MSG     packet_up_req = {0};
//OTA_DATA_MSG    packet_up_data = {0};

extern uint8_t g_soft_ver[4];
extern uint16_t g_packet_size;
uint8_t ota_start_flag = 0;
uint8_t ota_role = OTA_ROLE_MASTER;
hal_can_msg_info_t g_can_send_msg = {0};

uint8_t g_ota_req_msg_head[5]  = {0xe0, 0xe1, 0xe2};
uint8_t g_ota_data_msg_head[5] = {0xe4, 0xe5, 0xe6};

volatile uint16_t recv_num = 0;
volatile uint32_t recv_total_byte = 0;
static uint8_t tx_done_flag = 0;

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
        if((SYS_TO_US(cur_tick - last_tick) / 1000) > 200) //msg timeout 200ms
        {
            ota_uart.len = 0;
        }
    }
    else
    {
        if((SYS_TO_US(0xffffffffUL - last_tick + cur_tick) / 1000) > 200) //msg timeout 200ms
        {
            ota_uart.len = 0;
        }
    }
    last_tick = cur_tick;
	
	ota_uart.buf[ota_uart.len++] = dat;
	if(ota_uart.len > 4 && (ota_uart.len == (ota_uart.buf[2]*256 + ota_uart.buf[3] + 4)) &&
			ota_uart.buf[0]==0xa5 && ota_uart.buf[1]==0x5a)
	{
		ota_uart.pack_flag = 1;
	}
}

static uint8_t is_checksum(uint8_t *pdata,uint32_t len)
{
	uint16_t i = 0;
	uint8_t sum = 0;
	for (i=0;i<len;i++)sum+= pdata[i];
	return sum;
}
uint16_t send_data_to_canfd(uint8_t *buff, uint16_t len,uint32_t can_id)
{
    CAN_MSG_INFO msg   = {0};
	uint32_t     cnt   = 0;
	uint8_t      tmp   = 0;
	uint8_t      index = 0;
    uint8_t      isFDF =1;
    uint8_t      frame_num = 0;

    CAN_MSG_INFO TxMessage = {0};
	 
	TxMessage.RTR = 0;
    TxMessage.ID = can_id;
	TxMessage.FDF = isFDF;
    TxMessage.BRS = 1;
	if (isFDF)
	{				
        TxMessage.DLC = 0x0F;
//        memset(TxMessage.Data,0xAA,64);
        if(len>=CAN_MAX_LEN)
        {
            cnt = len/CAN_MAX_LEN; 
            if(len % CAN_MAX_LEN == 0)
            {
                memset(TxMessage.Data,0xAA,64);
                for(index = 0; index < cnt; index++ )
                {
                    memset(TxMessage.Data,0xAA,64);
                    memcpy(TxMessage.Data,(buff + index *64),CAN_MAX_LEN);
                    can_msg_send(CAN0, &TxMessage, TRANSMIT_SECONDARY); 
                }
            }
            else
            {
                for(index = 0; index <= cnt; index++ )
                {
                    memset(TxMessage.Data,0xAA,64);
                    memcpy(TxMessage.Data,(buff + index *64),(cnt>frame_num)?CAN_MAX_LEN:(len%CAN_MAX_LEN)); 
                    can_msg_send(CAN0, &TxMessage, TRANSMIT_SECONDARY); 
                    frame_num++;
                }
            }            
        }
        else
        {
            memset(TxMessage.Data,0xAA,64);
            memcpy(TxMessage.Data,buff,len);
            TxMessage.DLC = len;
            can_msg_send(CAN0, &TxMessage, TRANSMIT_SECONDARY);             
        }		
	}	
	else	
	{
		TxMessage.DLC = CAN_MAX_LEN;
		memset(TxMessage.Data,0xAA,CAN_MAX_LEN);
        if(len>CAN_MAX_LEN)
        {
            if(len%CAN_MAX_LEN !=0)
            {
               cnt = len/CAN_MAX_LEN; 
            }
            else
            {
                cnt = len /CAN_MAX_LEN - 1;
            }

        }
        for(index = 0; index <= cnt; index++ )
        {
            memcpy(TxMessage.Data,(buff + index *CAN_MAX_LEN),(len>CAN_MAX_LEN)?CAN_MAX_LEN:len);
            can_msg_send(CAN0, &TxMessage, TRANSMIT_SECONDARY); 
        }
	}	
	return len;
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
	uint8_t update_dir = 0;
	uint8_t msg_type   = 0;
    uint8_t resp[6]    = {0x5a,0xa5,0x00,0x02,0x00,0x00};
    uint8_t ver_rsp[9] = {0x5a,0xa5,0x00,0x05,0x00,0x00,0x00,0x00,0x00};
	uint16_t seq	   = 0;
	
	if(cmd_buf==NULL || cmd_len >= OTA_UART_DATSIZE || cmd_len==0)return;
	if((cmd_buf[0] != 0xA5) || (cmd_buf[1] != 0x5A))return;
	if(cmd_len <= 4 || (cmd_len != (cmd_buf[2]*256 + cmd_buf[3] + 4)))return;
	
	update_dir = cmd_buf[4]&0xf0;
	msg_type = cmd_buf[4]&0x0f;
	
	if(msg_type == SEND_START_UPGRADE_CMD)
    {
        resp[4] = cmd_buf[4];
    }
	else if(msg_type == SEND_TOTAL_PACKET_CMD)
	{
        resp[4] = cmd_buf[4];
		ota_info.total_packet_flash = ((uint16_t)cmd_buf[5]<<8) | cmd_buf[6];
		ota_info.total_byte = ((uint32_t)cmd_buf[7]<<24) | ((uint32_t)cmd_buf[8]<<16) | ((uint32_t) cmd_buf[9]<<8) | cmd_buf[10];
		//ota_info.version = ((uint32_t)cmd_buf[11]<<24) | ((uint32_t)cmd_buf[12]<<16) | ((uint32_t) cmd_buf[13]<<8) | cmd_buf[14];
		
		recv_num=0;
		ota_start_flag=1;
		ota_info.status = UP_STATUS_UART_RECV;
		NVIC_DisableIRQ(UWB_IRQn);
		
		__disable_irq();
		hal_flash_erase(APP2_FLASH_ADDR,ota_info.total_byte);
		__enable_irq();
	}
	else if(msg_type == SEND_DATA_CMD)
	{
		if(is_checksum(cmd_buf,cmd_len-1) != cmd_buf[cmd_len-1])
        {
            for(uint16_t i = 0; i < cmd_len; i++)
            {
                printf("cmd_buf[i]: 0x%x\n", cmd_buf[i]);
            }
            printf("crc err, is_checksum: 0x%x, cmd_buf: 0x%x\n", is_checksum(cmd_buf,cmd_len-1), cmd_buf[cmd_len-1]);
            return;
        }
		resp[4] = cmd_buf[4];
		seq = ((uint16_t)cmd_buf[5]<<8) | cmd_buf[6];
		recv_num++;
		
		ota_save_data_to_flash(&cmd_buf[7], (APP2_FLASH_ADDR + (seq * g_packet_size)), cmd_len-8);
		
		if((recv_num >= ota_info.total_packet_flash) && (seq == (ota_info.total_packet_flash - 1)))
		{
			NVIC_EnableIRQ(UWB_IRQn);
			ota_role = OTA_ROLE_MASTER;
			if(update_dir == UPDATE_DIR_LOCAL)
				ota_info.status = UP_STATUS_MASTER_UP_LOCAL;
			else
				ota_info.status = UP_STATUS_MASTER_UP_REMOTE;
		}
	}
    else if(msg_type == SEND_INQU_VER_CMD)
    {
        ver_rsp[4] = SEND_INQU_VER_CMD;
        __disable_irq();
        ver_rsp[5] = g_soft_ver[0];
        ver_rsp[6] = g_soft_ver[1];
        ver_rsp[7] = g_soft_ver[2];
        ver_rsp[8] = g_soft_ver[3];
        __enable_irq();
        send_data_to_canfd(ver_rsp, 9, CAN_UPGRADE_ID);
        hal_uart_send_data(0, ver_rsp, 9);        
        return;
    }
    send_data_to_canfd(resp, 6, CAN_UPGRADE_ID);
	hal_uart_send_data(0, resp, 6);    
}
/*************************************UART Deal Function end***************************************/


/*************************************UWB Callback Function start***************************************/
static void tx_done_proc(const zn_cb_data_t* rx_data)
{
	tx_done_flag = 1;
}
static void rx_ok_proc(const zn_cb_data_t* rx_data)
{
	uint16_t len = rx_data->data_length - 2;
	uint32_t dat;
	
	OTA_DATA_MSG *data_pkt = NULL;
	
	if((rx_data->data_length >= RX_BUFFER_MAX_LEN) || (rx_data->data_length == 0))
	{
		printf("error rx data len %d\r\n", rx_data->data_length);
		hal_force_uwb_off();
		hal_uwb_immediate_rx();
		return;
	}
	
	hal_uwb_read_rx_buffer((uint8_t *)rx_data->data, len);
	
	hal_gp_timer_reset_cnt(TIMER2);
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		
		data_pkt = (OTA_DATA_MSG*)rx_data->data;
		if(!memcmp(data_pkt, g_ota_data_msg_head, 3))
		{
			if(data_pkt->seq_num >= ota_info.total_packet_air)
			{
				printf("ota slave recv packnum error:%d\r\n",data_pkt->seq_num);
				hal_force_uwb_off();
				hal_uwb_immediate_rx();
				return;
			}
			
			
			dat = 0;
			qspi_memory_mapped_read(&dat, (APP2_FLASH_ADDR + (data_pkt->seq_num * OTA_DATA_PACK_SIZE)), 1);
			if(dat == 0xffffffff)
			{
				printf("%d : %d  %d\r\n",data_pkt->seq_num, data_pkt->len, len);
				
				ota_save_data_to_flash(data_pkt->data, (APP2_FLASH_ADDR + (data_pkt->seq_num * OTA_DATA_PACK_SIZE)), data_pkt->len);
				
				recv_num++;
				recv_total_byte += data_pkt->len;
			}
			
			
			if((recv_num == ota_info.total_packet_air)&& (recv_total_byte == ota_info.total_byte))
			{
				ota_info.status = UP_STATUS_FINISH;
                return;
			}
			
		}else { printf("ota slave recv data error:%d\r\n",len); }
	}
	ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
}
static void rx_error_proc(const zn_cb_data_t* rx_data)
{
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx err\n");
	}
}
static void rx_timeout_proc(const zn_cb_data_t* rx_data)
{
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
        ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx timeout\n");
	}
}
static void rx_cp_error_proc(const zn_cb_data_t* rx_data)
{
	if(ota_info.status == UP_STATUS_SLAVE_RECV_PKG)
	{
		ota_info.status = UP_STATUS_SLAVE_RECV_CONTINUE;
        printf("rx cp err\n");
	}
}

static void rx_phr_err_proc(const zn_cb_data_t* rx_data)
{
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
		ota_info.version = req_pkt->version;
		ota_info.total_byte = req_pkt->total_byte;
		//ota_info.total_packet_air = req_pkt->total_packet_air;
		ota_info.total_packet_air = req_pkt->total_byte / OTA_DATA_PACK_SIZE + ((req_pkt->total_byte % OTA_DATA_PACK_SIZE) > 0 ? 1 : 0);
		
		__disable_irq();
		hal_flash_erase(APP2_FLASH_ADDR,ota_info.total_byte);
		__enable_irq();
		
		ota_start_flag = 1;
		ota_role = OTA_ROLE_SLAVE;
		ota_info.status = UP_STATUS_SLAVE_RECV_INIT;
		printf("\r\nota recv req!\r\n");
	}
}


/************************************************************************/
void ota_init(void )
{
	uint32_t reg;
	zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
	
	hal_force_uwb_off();
	zn_set_rx_timeout(1000000);
	
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
	
	hal_delay_ms(20);
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
	ota_info.total_packet_air  = (ota_info.total_byte / OTA_DATA_PACK_SIZE) + ((ota_info.total_byte % OTA_DATA_PACK_SIZE) > 0 ? 1 : 0);
	
	memcpy(packet_up_req.head, g_ota_req_msg_head, 3);
    packet_up_req.version = ota_info.version;
    packet_up_req.total_byte = ota_info.total_byte;
    packet_up_req.total_packet_air = ota_info.total_packet_air;
	
	ota_info.status = UP_STATUS_MASTER_REQ_RING;

	tx_done_flag = 0;
	hal_uwb_write_tx_buffer((uint8_t*)&packet_up_req, sizeof(OTA_REQ_MSG));
	hal_uwb_immediate_tx();
	while(!tx_done_flag);
	tx_done_flag = 0;
}
void OTA_Master_Send_Up_Data()
{
    uint16_t    i = 0;
    uint16_t    content_len = 0;
    OTA_DATA_MSG packet_up_data = {0};

    for(i = 0; i < ota_info.total_packet_air; i++)
    {        
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
        
		tx_done_flag = 0;
        hal_uwb_write_tx_buffer((uint8_t *)&packet_up_data, 8 + content_len);
		hal_uwb_immediate_tx();
		while(!tx_done_flag);
		tx_done_flag = 0;
        mdelay(20);
    }
    
    return;
}
void OTA_Master_Update_Remote(void)
{
    uint8_t ret[4] = {0x5A,0xA5,0x3a,0xa3};//remote update done response
	uint16_t send_req_times = 1000;
    uint16_t send_data_times = 8;
    uint16_t index = 0;
    uint32_t reg = 0;
	
	for(index = 0; index < send_req_times; index++)
    {
        OTA_Master_Send_Up_Req();
        mdelay(1);
    }	
	
	mdelay(100);
    zn_modify_psdu_data_rate(PSDU_RATE_681);
    reg = zn_read_32bit_reg(SYS_CFG_ID);
    reg |= SYS_CFG_PHR_MODE_BIT_MASK;    //using the enhance PHR length
    zn_write_32bit_reg(SYS_CFG_ID, reg);
    
    for(index = 0; index < send_data_times; index++)
    {
        OTA_Master_Send_Up_Data();
        mdelay(20);
    }
	
	hal_uart_send_data(0, ret, 4);
    mdelay(10);
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
			ota_info.status = UP_STATUS_MASTER_SEND;
			recv_num = 0;
			OTA_Master_Update_Remote();
		}
    }
    else if(ota_role == OTA_ROLE_SLAVE)
    {
		if(ota_info.status == UP_STATUS_SLAVE_RECV_INIT)
		{
            hal_gp_timer_close(gp_timer.timer_id);
			ota_init();
			recv_num = 0;
			ota_info.status = UP_STATUS_SLAVE_RECV_PKG;
			
			
			uint32_t reg = 0;
			zn_modify_psdu_data_rate(PSDU_RATE_681);
            reg = zn_read_32bit_reg(SYS_CFG_ID);
            reg |= SYS_CFG_PHR_MODE_BIT_MASK;    //using the enhance PHR length
            zn_write_32bit_reg(SYS_CFG_ID, reg);
			
			
			hal_gp_timer_t timer_cfg = {0};
			timer_cfg.timer_id = TIMER2;
			timer_cfg.clk_src = PLL_CLK;//124.8MHz
			timer_cfg.clk_div = 0;
			timer_cfg.mode = TIMER_USER_DEFINE;
			timer_cfg.interrupt_en = 1;
			timer_cfg.time1 = (uint32_t)(30*1000*1000);//us
			timer_cfg.func = (TIMER_CallbackType)&ota_update_failure_proc;
			hal_gp_timer_init(&timer_cfg);
			hal_gp_timer_start(timer_cfg.timer_id);
			
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

