/*****************************************************************************
* File: zn_driver.c
*
* Descirption: this file contains the functions support driver.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "zn_regs.h"
#include "zn_interface.h"
#include "zn_soc.h"
#include "zn_gpio.h"
#include "zn_qspi_gd25q40.h"
#include "zn_timer.h"
#include "zn_dca.h"


uint32_t  lna_tia_table[]={0x18, 0x0E, 0x08, 0x04, 0x02, 0x01};
double   lna_tia_dB[]    ={2.0,  6.0,  9.8,  13.9, 17.5, 20.5};
uint8_t  lna_min_table[]={0x0, 0x7, 0xf, 0x0};//Lna1,Lna1Bias2,Lna2Bias,Lna2
uint8_t  lna_max_table[]={0x7, 0x7, 0xf, 0x3};//Lna1,Lna1Bias2,Lna2Bias,Lna2


uint32_t s_tx_ts_offset = 0;
zn_driver_config_t driver_config = {0};

zn_local_data_t global_zn_config = {0};
static uint8_t  s_last_channel        = CHANNEL_9;

zn_driver_config_t* zn_get_dirver_config_addr(void)
{
    return &driver_config;
}


/*************************************************************************************************************
* Description: this function is used to read 32 - bit value from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* Output param: None
* Return value: 32 bit register value
*************************************************************************************************************/
uint32_t zn_read_32bit_reg(uint32_t reg_file_id)
{
    return read_mreg32(UWB_BASE_ADDR + reg_file_id);
}

/*************************************************************************************************************
* Description: this function is used to write 32 - bit value to the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* reg_val - the value to write
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_32bit_reg(uint32_t reg_file_id, uint32_t reg_val)
{
    write_mreg32(UWB_BASE_ADDR + reg_file_id, reg_val);
}

/*************************************************************************************************************
* Description: this function is used to read 16 - bit value from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* Output: None
* Return value: 16 bit register value
*************************************************************************************************************/
uint16_t zn_read_16bit_reg(uint32_t reg_file_id)
{
    return read_mreg16(UWB_BASE_ADDR + reg_file_id);
}

/*************************************************************************************************************
* Description: this function is used to write 16 - bit value to the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* reg_val - the value to write
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_16bit_reg(uint32_t reg_file_id, uint32_t reg_val)
{
    write_mreg16(UWB_BASE_ADDR + reg_file_id, reg_val);
}

/*************************************************************************************************************
* Description: this function is used to read an 8 - bit value from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* Output param: None
* Return value: 8 - bit register value
*************************************************************************************************************/
uint8_t zn_read_8bit_reg(uint32_t reg_file_id)
{
    return read_mreg8(UWB_BASE_ADDR + reg_file_id);
}

/*************************************************************************************************************
* Description: this function is used to write an 8 - bit value to the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* reg_val - the value to write
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_8bit_reg(uint32_t reg_file_id, uint8_t reg_val)
{
    write_mreg8(UWB_BASE_ADDR + reg_file_id, reg_val);
}

/*************************************************************************************************************
* Description: this function is used to OR a 32 - bit value to the ZN device registers
* Input param:
* reg_file_id : ID of register file or buffer being accessed
* or_value : the value to OR to register
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_or_32bit_reg(const uint32_t reg_file_id, const uint32_t or_value)
{
    uint32_t reg_value = zn_read_32bit_reg(reg_file_id);

    reg_value |= or_value;
    zn_write_32bit_reg(reg_file_id, reg_value);

    return;
}

/*************************************************************************************************************
* Description: this function is used to AND a 32 - bit value to the ZN device registers
* Input param:
* reg_file_id : ID of register file or buffer being accessed
* and_value: the value to AND to register
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_and_32bit_reg(const uint32_t reg_file_id, const uint32_t and_value)
{
    uint32_t reg_value = zn_read_32bit_reg(reg_file_id);

    reg_value &= and_value;
    zn_write_32bit_reg(reg_file_id, reg_value);

    return;
}

/*************************************************************************************************************
* Description: this function is used to write a commond to the ZN device registers.
* Input param:
* cmd - fast command
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_fast_cmd(uint16_t cmd)
{
    uint32_t reg_value = zn_read_32bit_reg(FAST_CMD_ID);

    reg_value &= ~(FAST_CMD_BIT_MASK);
    reg_value |= ((cmd << FAST_CMD_BIT_OFFSET) & FAST_CMD_BIT_MASK);
    zn_write_32bit_reg(FAST_CMD_ID, reg_value);

    zn_or_32bit_reg(FAST_CMD_VLD_ID, FAST_CMD_VLD_BIT_MASK);
}

/*************************************************************************************************************
* Description: this function is used to write to the ZN device registers.
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* length - number of bytes being written
* buffer - pointer to buffer containing the 'length' bytes to be written
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_to_device(uint32_t reg_file_id, uint16_t length, uint8_t *buffer)
{
    uint16_t idx = 0;
    uint16_t div_len = length / 4;
    uint16_t rem_len = length % 4;

    for(idx = 0; idx < div_len; idx++)
    {
        write_mreg32((UWB_BASE_ADDR + reg_file_id + idx * 4), *((uint32_t *)(buffer + idx * 4)));
    }

    for(idx = 0; idx < rem_len; idx++)
    {
        write_mreg8((UWB_BASE_ADDR + reg_file_id + div_len * 4 + idx), *(buffer + div_len * 4 + idx));
    }
}

/*************************************************************************************************************
* Description: this function is used to read from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* length - number of bytes being read
* buffer - pointer to buffer in which to return the read data.
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_read_from_device(uint32_t reg_file_id, uint16_t length, uint8_t *buffer)
{
    uint16_t idx = 0;
    uint16_t div_len = length / 4;
    uint16_t rem_len = length % 4;

    for(idx = 0; idx < div_len; idx++)
    {
        *((uint32_t *)(buffer + idx * 4)) = read_mreg32(UWB_BASE_ADDR + reg_file_id + idx * 4);
    }
    for(idx = 0; idx < rem_len; idx++)
    {
        *(buffer + div_len * 4 + idx) = read_mreg8(UWB_BASE_ADDR + reg_file_id + div_len * 4 + idx);
    }
}

/*************************************************************************************************************
* Description: this function is used to init ZN global config
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_init_global_config(void)
{
    memset(&global_zn_config.cb_data, 0, sizeof(zn_cb_data_t));
    global_zn_config.cb_tx_done = NULL;
    global_zn_config.cb_rx_ok = NULL;
    global_zn_config.cb_rx_timeout = NULL;
    global_zn_config.cb_rx_err = NULL;
    global_zn_config.cb_rx_done = NULL;
    global_zn_config.cb_cp_err = NULL;
    global_zn_config.cb_prd = NULL;
    global_zn_config.cb_rx_preamble_timeout = NULL;
    global_zn_config.cb_rx_sfd_timeout = NULL;
    global_zn_config.cb_rx_sfd_done = NULL;
    global_zn_config.cb_rx_phr_err = NULL;
}


/*******************************************************************************************************************
* Description: This API function writes the supplied TX data into the ZN's TX buffer.
* Input param:
* tx_data_length - This is the total length of data (in bytes) to write to the tx buffer.
* tx_data_bytes - Pointer to the user s buffer containing the data to send.
* tx_buffer_offset - This specifies an offset in the ZN IC TX Buffer at which to start writing data.
* Output param: None
* Returns value: ZN_SUCCESS for success, or ZN_ERROR for error
*******************************************************************************************************************/
int32_t zn_write_tx_data(uint16_t tx_data_length, uint8_t *tx_data_bytes, uint16_t tx_buffer_offset)
{
    if (tx_data_length < TX_BUFFER_MAX_LEN)
    {
        zn_write_to_device(TX_BUF_ADDR_OFFSET + tx_buffer_offset, tx_data_length, tx_data_bytes);
        return ZN_SUCCESS;
    }
    else
    {
        return ZN_ERROR;
    }
}

/*******************************************************************************************************************
* Description: This function read the supplied TX data from the ZN's TX buffer.
* Input param:
* buffer - Pointer to the user's buffer containing the data to read.
* length - This is the total length of data (in bytes) to read from the tx buffer.
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_read_tx_data(uint8_t *buffer, uint16_t length)
{
    zn_read_from_device(TX_BUF_ADDR_OFFSET, length, buffer);
}

/*******************************************************************************************************************
* Description: This API function configures the TX frame control register before the transmission of a frame
* Input param:
* tx_frame_length - this is the length of TX message (including the 2 byte CRC) - max is 1023
* NOTE: standard PHR mode allows up to 127 bytes
* if > 127 is programmed, ZN_PHRMODE_EXT needs to be set in the phrMode configuration
* see zn_configure function
* tx_buffer_offset - the offset in the tx buffer to start writing the data
* ranging - 1 if this is a ranging frame, else 0
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_write_tx_frame_ctrl(uint16_t tx_frame_length, uint16_t tx_buffer_offset, uint8_t ranging)
{
    uint32_t reg32 = tx_frame_length 
                     | ((tx_buffer_offset << TX_DATA_CTRL_TXB_OFFSET_BIT_OFFSET) & TX_DATA_CTRL_TXB_OFFSET_BIT_MASK)
                     | ((ranging << TX_DATA_CTRL_TXTR_BIT_OFFSET) & (TX_DATA_CTRL_TXTR_BIT_MASK));

    zn_and_32bit_reg(TX_DATA_CTRL_ID, ~(TX_DATA_CTRL_TXB_OFFSET_BIT_MASK | TX_DATA_CTRL_TXFLEN_BIT_MASK | TX_DATA_CTRL_TXTR_BIT_MASK));
    zn_or_32bit_reg(TX_DATA_CTRL_ID, reg32);
}

/*******************************************************************************************************************
* Description: This is used to read the data from the RX buffer, from an offset location give by offset parameter
* Input param:
* buffer - the buffer into which the data will be read
* length - the length of data to read (in bytes)
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_read_rx_data(uint8_t *buffer, uint16_t length)
{
    zn_read_from_device(RX0_BUF_ADDR_OFFSET, length, buffer);
}

/*******************************************************************************************************************
* Description: This API function configures the delayed transmit time or the delayed RX on time
* Input param:
* start_time - the TX/RX start time (the 32 bits should be the high 32 bits of the system time at which to send the message,
* The time parameter used here is the absolute vaule of systemcounter which can get with zn_get_sys_time 
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_set_delayed_trx_time(uint32_t start_time)
{
    zn_write_32bit_reg(DX_TIME_ID, start_time); // Note: bit 0 of this register is ignored
}

/*******************************************************************************************************************
* Description: This is used to read the TX timestamp (adjusted with the programmed antenna delay)
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read TX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_tx_timestamp(uint8_t *timestamp)
{
    zn_read_from_device(TX_STAMP_L8_ID, TX_STAMP_L8_LEN, timestamp);       // Read bytes directly into buffer
    zn_read_from_device(TX_STAMP_H32_ID, TX_STAMP_H32_LEN, timestamp + 1); // Read bytes directly into buffer

    return;
}

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the TX timestamp raw (no adjusted with the programmed antenna delay)
* Input param: None
* Output param: None
* Return value: high 32-bits of TX timestamp raw
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_raw(void)
{
    return zn_read_32bit_reg(TX_STAMP_RAW_ID); // Offset is 1 to get the 4 upper bytes out of 5
}

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the TX timestamp (adjusted with the programmed antenna delay)
* Input param: None
* Output param: None
* Return value: high 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_high32(void)
{
    return zn_read_32bit_reg(TX_STAMP_H32_ID);
}

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the TX timestamp (adjusted with the programmed antenna delay)
* Input param: None
* Output param: None
* Return value: low 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_low32(void)
{
    uint32_t time_value = 0;

    time_value = zn_read_32bit_reg(TX_STAMP_L8_ID);
    time_value |= (zn_read_32bit_reg(TX_STAMP_H32_ID) << TX_STAMP_L8_BIT_LEN);

    return time_value;
}

/*******************************************************************************************************************
* Description: This is used to read the TX timestamp (adjusted with the programmed antenna delay) for STS case
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read TX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_tx_timestamp_sts(uint8_t *timestamp)
{
    zn_read_from_device(IP_STS_TX_STAMP_L8, IP_STS_TX_STAMP_L8_LEN, timestamp);       // Read bytes directly into buffer
    zn_read_from_device(IP_STS_TX_STAMP_H32, IP_STS_TX_STAMP_H32_LEN, timestamp + 1); // Read bytes directly into buffer

    return;
}

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the TX timestamp (adjusted with the programmed antenna delay) for STS case
* Input param: None
* Output param: None
* Return value: high 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_high32_sts(void)
{
    return zn_read_32bit_reg(IP_STS_TX_STAMP_H32);
}

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the TX timestamp (adjusted with the programmed antenna delay) for STS case
* Input Param: None
* Output Param: None
* Return value: low 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_low32_sts(void)
{
    uint32_t time_value = zn_read_8bit_reg(IP_STS_TX_STAMP_L8);

    time_value |= (zn_read_32bit_reg(IP_STS_TX_STAMP_H32) << 8);

    return time_value;
}

/*******************************************************************************************************************
* Description: This is used to read the RX timestamp (adjusted time of arrival)
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_rx_timestamp(uint8_t *timestamp)
{
    zn_read_from_device((IP_TOA_L8_ID + (IP_TOA_L8_BIT_OFFSET / IP_TOA_L8_BIT_LEN)), IP_TOA_L8_LEN, timestamp); // Get the adjusted time of arrival
    zn_read_from_device(IP_TOA_H32_ID, IP_TOA_H32_LEN, timestamp + 1); // Get the adjusted time of arrival
}

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the RX timestamp raw (no adjusted with the programmed antenna delay)
* Input Param: None
* Output Param: None
* Return value: high 32-bits of RX timestamp raw
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_raw(void)
{
    return zn_read_32bit_reg(RX_STAMP_RAW_ID);
}

/******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the RX timestamp
* Input param: None
* Output param: None
* Return value: high 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_high32(void)
{
    return zn_read_32bit_reg(IP_TOA_H32_ID); // Offset is 1 to get the 4 upper bytes out of 5 byte tiemstamp
}

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the RX timestamp
* Input param: None
* Output param: None
* Return value: high 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_low32(void)
{
    uint32_t time_value = zn_read_8bit_reg(IP_TOA_L8_ID + 3);

    time_value |= (zn_read_32bit_reg(IP_TOA_H32_ID) << TX_STAMP_L8_BIT_LEN);

    return time_value;
}

/*******************************************************************************************************************
* Description: This is used to read the RX timestamp (adjusted time of arrival) w.r.t. STS CIR
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: no return value
*******************************************************************************************************************/
void zn_read_rx_timestamp_sts(uint8_t *timestamp)
{
    zn_read_from_device((CP_TOA_L8_ID + 3), CP_TOA_L8_LEN, timestamp); // Get the adjusted time of arrival
    zn_read_from_device(CP_TOA_H32_ID, CP_TOA_H32_LEN, timestamp + 1); // Get the adjusted time of arrival
}

/*******************************************************************************************************************
* Description: This is used to read the RX2 timestamp (adjusted time of arrival) w.r.t. STS CIR
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: no return value
*******************************************************************************************************************/
void zn_read_rx2_timestamp_sts(uint8_t *timestamp)
{
    zn_read_from_device((CP_TOA_L8_ID2 + 3), CP_TOA_L8_LEN2, timestamp); // Get the adjusted time of arrival
    zn_read_from_device(CP_TOA_H32_ID2, CP_TOA_H32_LEN2, timestamp + 1); // Get the adjusted time of arrival
}

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the RX timestamp for STS case
* Input param: None
* Output param: None
* Return value: high 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_high32_sts(void)
{
    return zn_read_32bit_reg(CP_TOA_H32_ID);
}

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the RX timestamp for STS case
* Input param: None
* Output param: None
* Return value: low 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_low32_sts(void)
{
    uint32_t time_value = zn_read_8bit_reg(CP_TOA_L8_ID + 3);

    time_value |= (zn_read_32bit_reg(CP_TOA_H32_ID) << 8);

    return time_value;
}

/*******************************************************************************************************************
* Description: This is used to read the RX2 timestamp (adjusted time of arrival)
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_rx2_timestamp(uint8_t *timestamp2)
{
    zn_read_from_device((IP_TOA_L8_ID2 + (IP_TOA_L8_BIT_OFFSET2 / IP_TOA_L8_BIT_LEN2)), IP_TOA_L8_LEN, timestamp2); // Get the adjusted time of arrival
    zn_read_from_device(IP_TOA_H32_ID2, IP_TOA_H32_LEN2, timestamp2 + 1); // Get the adjusted time of arrival
}

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the system time
* Input Param: None
* Output Param: None
* Return value: 32 - bits of the system time
*******************************************************************************************************************/
uint32_t zn_get_sys_time(void)
{
    return zn_read_32bit_reg(SYS_TIME_ID);
}

/********************************************************************************************************************
* Description: This sets the receiver turn on delay time after a transmission of a frame
* Input Param:
* rx_delay_time - (20 bits) - the delay is in us
* Output Param: None
* Return value: None
********************************************************************************************************************/
void zn_set_rx_after_tx_delay(uint32_t rx_delay_time)
{
    uint32_t val = zn_read_32bit_reg(ACK_RESP_ID);            // Read ACK_RESP_T_ID register

    val &= (~ACK_RESP_WAIT4RESP_TIM_BIT_MASK);                // Clear the timer (19:0)

    val |= (rx_delay_time & ACK_RESP_WAIT4RESP_TIM_BIT_MASK); // In UWB microseconds (e.g. turn the receiver on 20uus after TX)

    zn_write_32bit_reg(ACK_RESP_ID, val);
}

/*******************************************************************************************************************
* Description: This function is used to register the different callbacks called when one of the corresponding event occurs.
*
* NOTE: Callbacks can be undefined (set to NULL).In this case, zn_isr() will process the event as usual but the 'null'
* callback will not be called.
*
* Input param:
* cb_tx_done - the pointer to the TX confirmation event callback function
* cb_rx_ok - the pointer to the RX good frame event callback function
* cb_rx_to - the pointer to the RX timeout events callback function
* cb_rx_err - the pointer to the RX error events callback function
* cb_rx_done - the pointer to the Rx Done events callback function
* cb_cp_err - the pointer to the cp error events callback function
* cb_prd - the pointer to the prd events callback function
* Output param: None
* Return value: None
*******************************************************************************************************************/
void zn_set_callbacks(zn_cb_t cb_tx_done, zn_cb_t rx_ok, zn_cb_t cb_rx_to, zn_cb_t cb_rx_err, zn_cb_t cb_cp_err)
{
    NVIC_DisableIRQ(UWB_IRQn);
    global_zn_config.cb_tx_done = cb_tx_done;
    global_zn_config.cb_rx_ok = rx_ok;
    global_zn_config.cb_rx_timeout = cb_rx_to;
    global_zn_config.cb_rx_err = cb_rx_err;
    global_zn_config.cb_cp_err = cb_cp_err;
    NVIC_EnableIRQ(UWB_IRQn);
}

void zn_set_callbacks_ex(
    zn_cb_t rx_done, 
    zn_cb_t prd, 
    zn_cb_t pto, 
    zn_cb_t sfd_to, 
    zn_cb_t sfd_done,
    zn_cb_t phe,
    zn_cb_t phd)
{
    NVIC_DisableIRQ(UWB_IRQn);    
    global_zn_config.cb_rx_done = rx_done;
    global_zn_config.cb_prd = prd;
    global_zn_config.cb_rx_preamble_timeout = pto;
    global_zn_config.cb_rx_sfd_timeout = sfd_to;
    global_zn_config.cb_rx_sfd_done = sfd_done;
    global_zn_config.cb_rx_phr_err = phe;
    global_zn_config.cb_rx_phd = phd;
    NVIC_EnableIRQ(UWB_IRQn);
}

/*************************************************************************************************************
* Description: This call enables preamble timeout (SY_STAT_RXPTO event)
* Input Param:
* timeout - Preamble detection timeout, the timeout must be an integer multiple of 127.
*           Every 127 corresponds to one time of PAC. ex: 127 corresponds one time of PAC, 127*2 corresponds two  times of PAC.
* Output Param: None
* Return value: None
*************************************************************************************************************/
void zn_set_preamble_detect_timeout(uint16_t timeout)
{
    zn_write_32bit_reg(DRX_PRETOC_ID, (timeout << DRX_PRETOC_BIT_OFFSET));
}

/*******************************************************************************************************************
* Description: This call initiates the transmission
* Input param:
* mode - if mode = ZN_START_TX_IMMEDIATE - immediate TX
* if mode = ZN_START_TX_DELAYED - delayed TX  at specified time (time in DX_TIME register set by function zn_set_delayed_trx_time)
* Output param: None
* Return value: ZN_SUCCESS for success, or ZN_ERROR for error (e.g. a delayed transmission will be cancelled if the delayed time has passed)
*******************************************************************************************************************/
int32_t zn_start_tx(uint8_t mode)
{
    uint8_t fastcmd[6] = {CMD_TX, CMD_DTX, CMD_TX_W4R, CMD_DTX_W4R, CMD_CCA_TX, CMD_CCA_TX_W4R};

    if(mode > 6)
    {
        return ZN_ERROR;
    }
    zn_write_fast_cmd(fastcmd[mode]);

    return ZN_SUCCESS;
}

/*******************************************************************************************************************
* Description: This is used to turn off the transceiver
* Input param: None
* Output param: None
* Return value: None
*******************************************************************************************************************/
void zn_force_trx_off(void)
{
    zn_write_fast_cmd(CMD_TXRXOFF);
    zn_write_32bit_reg(SYS_STATUS1_ID, 0xffffffff);
    zn_write_32bit_reg(SYS_STATUS_ID, 0xffffffff);
}

/*******************************************************************************************************************
* Description: This call turns on the receiver, can be immediate or delayed (depending on the mode parameter).
* The receiver will stay turned on, listening to any messages until
* it either receives a good frame, an error (CRC, PHY header, Reed Solomon) or it times out (SFD, Preamble or Frame).
* Input param:
* mode - this can be one of the following allowed values:
* ZN_START_RX_IMMEDIATE  Enable the receiver immediately
* ZN_START_RX_DELAYED  delayed RX  at specified time (time in DX_TIME register set by function zn_set_delayed_trx_time)
* Output param: None
* Return value: ZN_SUCCESS for success, or ZN_ERROR for error
*******************************************************************************************************************/
int32_t zn_rx_enable(uint8_t mode)
{
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();

    if(mode == ZN_START_RX_IMMEDIATE)
    {
        zn_write_fast_cmd(CMD_RX);
    }
    else if(mode == ZN_START_RX_DELAYED)
    {
        zn_write_fast_cmd(CMD_DRX);
    }
    driver_config->prd_timer_flag = 1;
    return ZN_SUCCESS;
}

//void zn_rx_state_check(void)
//{
//    static uint8_t      loop_count     = 0;
//    zn_driver_config_t* driver_config  = zn_get_dirver_config_addr();

//    if(zn_read_32bit_reg(SYS_STATE_ID) != 0x00050000)
//    {
//        return;
//    }

//    if(driver_config->pre_prd_timer_flag)
//    {
//        if(0 == zn_read_32bit_reg(IP_NACC0_ID))
//        {
//            if(loop_count >= 10)
//            {
//                if(driver_config->prd_chuck_last == zn_read_32bit_reg(CHUNK_NUM0_ID))
//                {
//                    driver_config->prd_chuck_count++;
//                }
//                else
//                {
//                    driver_config->prd_chuck_count = 0;
//                }
//                driver_config->prd_chuck_last = zn_read_32bit_reg(CHUNK_NUM0_ID);
//                loop_count = 0;
//            }
//            else
//            {
//                loop_count++;
//            }
//        }
//    }
//    else
//    {
//        loop_count = 0;
//        driver_config->prd_chuck_last = 0;
//        driver_config->prd_chuck_count = 0;
//    }

//    if(driver_config->prd_chuck_count >= 5000)
//    {
//        loop_count = 0;
//        zn_force_trx_off();
//        zn_to_rx_state();
//        zn_rx_enable(ZN_START_RX_IMMEDIATE);
//    }
//}

void zn_rx_state_check(void)
{
    zn_driver_config_t* driver_config  = zn_get_dirver_config_addr();
    uint8_t             timer_id      = driver_config->timer_id;
    uint32_t            clk_freq      = driver_config->timer_freq;

    if(zn_read_32bit_reg(SYS_STATE_ID) != 0x00050000)
    {
        return;
    }

    if((driver_config->prd_timer_flag) && (driver_config->phy_config.aoa_en))
    {
        if((zn_read_32bit_reg(IP_NACC0_ID) > 0) || (zn_read_32bit_reg(IP_NACC1_ID) > 0))
        {
            driver_config->prd_timer_flag = 0;
            timer_disable(timer_id);
            timer_set_loadval(timer_id, USEC_TO_COUNT(1000, clk_freq));
            timer_enable(timer_id);
        }
    }
}
/*************************************************************************************************************
* Description: This call enables RX timeout (SYS_STATUS_RFTO event)
* Input param: 
* time - how long the receiver remains on from the RX enable command
* The time parameter used here is in 1us units
* If set to 0 the timeout is disabled.
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_rx_timeout(uint32_t time)
{
    zn_write_32bit_reg(RX_FWTO_ID, time * 125);
    zn_or_32bit_reg(SYS_CFG_ID, SYS_CFG_RXWTOE_BIT_MASK); //set the RX FWTO bit
}

/*************************************************************************************************************
* Description: This call enables RX sfd timeout (SYS_STATUS_SFDTO event)
* Input param: 
* time - how long the receiver remains on from the RX enable command
* The time parameter used here is in 1us units
* If set to 0 the timeout is disabled.
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_rx_sfd_timeout(uint32_t time)
{
    uint32_t sfd_timeout = time;
    zn_write_32bit_reg(DRX_SFDTOC_ID, sfd_timeout << DRX_SFDTOC_BIT_OFFSET);
}

/*************************************************************************************************************
* Description: This call get device state
* Input param: None
* Output param: None
* Return value: 1:INIT 2:IDLE_RC 3:IDLE 4:TX state 5:RX state
*************************************************************************************************************/
uint8_t zn_get_pmsc_state(void)
{
    return ((zn_read_32bit_reg(SYS_STATE_ID) & SYS_STATE_PMSC_BIT_MASK) >> SYS_STATE_PMSC_BIT_OFFSET);
}

/*************************************************************************************************************
* Description: This function enables the specified events to trigger an interrupt.
* The following events can be found in SYS_ENABLE_LO register.
* Input param:
* bit_mask - sets the events which will generate interrupt
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_interrupt(uint32_t bit_mask)
{
    NVIC_DisableIRQ(UWB_IRQn);
    zn_write_32bit_reg(SYS_MASK_ID, bit_mask); // New value
    zn_write_32bit_reg(SYS_MASK1_ID, SYS_MASK_MRXSAT_BIT_MASK);//MRXSAT interrupt
    NVIC_EnableIRQ(UWB_IRQn);
}

/*************************************************************************************************************
* Description: This function is pa set.
* Input param: 
* value - power level : PA_LEVEL_0 ... PA_LEVEL_15
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_pa_set(uint16_t value)
{
    if(value >= MAX_PA_LEVEL)
    {
        value = PA_LEVEL_15;
    }
    
    uint32_t reg = zn_read_32bit_reg(TX_FLG_ID);
    
    reg &= ~TX_PA_GAIN_SEL_BIT_MASK;
    reg |= (value << TX_PA_GAIN_SEL_BIT_OFFSET) & TX_PA_GAIN_SEL_BIT_MASK;
    
    zn_write_32bit_reg(TX_FLG_ID, reg);
}

/*************************************************************************************************************
* Description: This function is modify the channel num.
* Input param:
* channel_num - channel num
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_channel(uint32_t channel_num)
{
    uint32_t reg_value = 0;
    uint32_t reg_0810             = 0;
    uint32_t reg_0828             = 0;
    uint32_t reg_084c             = 0;
    uint32_t reg_0818             = 0;
    uint32_t reg_0820             = 0;

    reg_value = zn_read_32bit_reg(SYSTEM_PARAM_ID); // clear bit to 0
    reg_value &= (~SYSTEM_PARAM_RF_CHAN_BIT_MASK);
    reg_value |= (channel_num & SYSTEM_PARAM_RF_CHAN_BIT_MASK);
    zn_write_32bit_reg(SYSTEM_PARAM_ID, reg_value);

#if 0
    if(s_last_channel != channel_num)
    {
        reg_0810 = (CHANNEL_5 == channel_num) ? 0x298c8092 : 0x508c8092;
        reg_0818 = (CHANNEL_2 == channel_num) ? 0x7f729304 : 0x60729304;
        reg_0820 = (CHANNEL_2 == channel_num) ? 0x40bf2400 : 0x40a02400;
        reg_0828 = driver_config.phy_config.aoa_en ? ((CHANNEL_2 == channel_num) ? 0x01402800 : 0x01412800) : ((CHANNEL_2 == channel_num) ? 0x01400800 : 0x01410800);
        reg_084c = driver_config.phy_config.aoa_en ? 0x82000800 : 0x82000000;
        

        zn_write_32bit_reg(0x0810, reg_0810);
        zn_write_32bit_reg(0x0818, reg_0818);
        zn_write_32bit_reg(0x0820, reg_0820);
        zn_write_32bit_reg(0x0828, reg_0828);
        zn_write_32bit_reg(0x084C, reg_084c);

        s_last_channel = channel_num;
    }
#endif
    return;
}

/*************************************************************************************************************
* Description: This function is modify the sfd id.
* Input param:
* sfd_id - sfd id
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_sfd_id(uint32_t sfd_id)
{
    if(sfd_id<SFD_ID_USER8)
    {
        uint32_t reg_value = 0;

        reg_value = zn_read_32bit_reg(SYSTEM_PARAM_ID); // clear bit to 0
        reg_value &= (~SYSTEM_PARAM_SFD_TYPE_BIT_MASK);
        reg_value |= ((sfd_id << SYSTEM_PARAM_SFD_TYPE_BIT_OFFSET) & SYSTEM_PARAM_SFD_TYPE_BIT_MASK);
        zn_write_32bit_reg(SYSTEM_PARAM_ID, reg_value);
        zn_write_32bit_reg(SFD_TYPE_USED_ID, 0);
        
    }
    else
    {
        zn_set_user_sfd(sfd_id);
    }

    return;
}

/*************************************************************************************************************
* Description: This function is modify the preamble code idx.
* Input param:
* preamble_code_idx - preamble code index
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_preamble_code_idx(uint32_t preamble_code_idx)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(SYSTEM_PARAM_ID); // clear bit to 0
    reg_value &= (~SYSTEM_PARAM_TX_PCODE_BIT_MASK);
    reg_value |= ((preamble_code_idx << SYSTEM_PARAM_TX_PCODE_BIT_OFFSET) & SYSTEM_PARAM_TX_PCODE_BIT_MASK);
    reg_value &= (~SYSTEM_PARAM_RX_PCODE_BIT_MASK);
    reg_value |= ((preamble_code_idx << SYSTEM_PARAM_RX_PCODE_BIT_OFFSET) & SYSTEM_PARAM_RX_PCODE_BIT_MASK);
    zn_write_32bit_reg(SYSTEM_PARAM_ID, reg_value);

    return;
}

/*************************************************************************************************************
* Description: This function is modify the rframe config.
* Input param:
* rframe_cfg - rframe config
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_rframe_cfg(uint32_t rframe_cfg)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(SYS_CFG_ID); // clear bit to 0
    reg_value &= (~SYS_CFG_STS_MODE_BIT_MASK);
    reg_value |= ((rframe_cfg << SYS_CFG_STS_MODE_BIT_OFFSET) & SYS_CFG_STS_MODE_BIT_MASK);
    zn_write_32bit_reg(SYS_CFG_ID, reg_value);

    if(RFRAME_SP0 != rframe_cfg)
    {
        reg_value = zn_read_32bit_reg(STS_CFG_ID);
        reg_value |= (1 << STS_DELTA_BIT_OFFSET);
        zn_write_32bit_reg(STS_CFG_ID, reg_value);
    }

    return;
}

/*************************************************************************************************************
* Description: This function is modify the bprf phr data rate.
* Input param:
* bprf_phr_data_rate - bprf phr data rate
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_bprf_phr_data_rate(uint32_t bprf_phr_data_rate)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(SYS_CFG_ID); // clear bit to 0
    reg_value &= (~SYS_CFG_PHR_6M8_BIT_MASK);
    reg_value |= ((bprf_phr_data_rate << SYS_CFG_PHR_6M8_BIT_OFFSET) & SYS_CFG_PHR_6M8_BIT_MASK);
    zn_write_32bit_reg(SYS_CFG_ID, reg_value);

    return;
}

/*************************************************************************************************************
* Description: This function is modify the sts segment number.
* Input param:
* sts_seg_num - sts segment num
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_sts_seg_num(uint32_t sts_seg_num)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(STS_CFG_ID);
    reg_value &= (~STS_STS_SEG_NUM_BIT_MASK);
    reg_value |= ((sts_seg_num << STS_STS_SEG_NUM_BIT_OFFSET) & STS_STS_SEG_NUM_BIT_MASK);
    zn_write_32bit_reg(STS_CFG_ID, reg_value);

    return;
}

/*************************************************************************************************************
* Description: This function is modify the sts segement length.
* Input param:
* sts_seg_len - sts segment length
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_sts_seg_len(uint32_t sts_seg_len)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(STS_CFG_ID);
    reg_value &= (~STS_CPS_LEN_BIT_MASK);
    reg_value |= ((sts_seg_len << STS_CPS_LEN_BIT_OFFSET) & STS_CPS_LEN_BIT_MASK);
    zn_write_32bit_reg(STS_CFG_ID, reg_value);

    return;
}


/*************************************************************************************************************
* Description: This function is modify the preamble duration.
* Input param:
* preamble_duration - preamble duration
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_preamble_duration(uint32_t preamble_duration)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(TX_PHR_CTRL_ID);
    reg_value &= (~TX_PHR_CTRL_TXPSR_PE_BIT_MASK);
    reg_value |= ((preamble_duration << TX_PHR_CTRL_TXPSR_PE_BIT_OFFSET) & TX_PHR_CTRL_TXPSR_PE_BIT_MASK);
    zn_write_32bit_reg(TX_PHR_CTRL_ID, reg_value);

    return;
}

/*************************************************************************************************************
* Description: This function is modify the psdu data rate.
* Input param:
* psdu_data_rate - psdu data rete
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_psdu_data_rate(uint32_t psdu_data_rate)
{
    uint32_t reg_value = 0;
    uint8_t channel = (zn_read_32bit_reg(SYSTEM_PARAM_ID) & SYSTEM_PARAM_RF_CHAN_BIT_MASK) >> SYSTEM_PARAM_RF_CHAN_BIT_OFFSET;

    reg_value = zn_read_32bit_reg(TX_PHR_CTRL_ID);
    reg_value &= (~TX_PHR_CTRL_TXBR_BIT_MASK);
    reg_value |= ((psdu_data_rate << TX_PHR_CTRL_TXBR_BIT_OFFSET) & TX_PHR_CTRL_TXBR_BIT_MASK);
    zn_write_32bit_reg(TX_PHR_CTRL_ID, reg_value);

    if(PSDU_RATE_540 == psdu_data_rate)
    {
        zn_write_32bit_reg(PRF_MODE_ID, 0x00000005);
    }
    else if(PSDU_RATE_850 == psdu_data_rate)
    {
        zn_write_32bit_reg(DRX_PSDU_CFG_ID, 0x00fe8022);

        if(channel == CHANNEL_2)
        {
            reg_value = 0x5dffd4e0;
            zn_write_32bit_reg(DRX_PSDU_CFG_ID, 0x00ff0011);
        }
    }
    else
    {
        zn_write_32bit_reg(DRX_PSDU_CFG_ID, 0x40fe8022);
        if( channel == CHANNEL_2 )
        {
            zn_write_32bit_reg(DRX_PSDU_CFG_ID, 0x40ff0011);
        }
    }

    return;
}
/*************************************************************************************************************
* Description: This function is modify the prf mode.
* Input param:
* prf - prf mode
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_prf_mode(uint8_t prf)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(PRF_MODE_ID);
    if(prf == PRF_624)
    {
        reg_value &= (~PRF_MODE_HPRF_EN_BIT_MASK); 
    }
    else if(prf == PRF_1248)
    {
        reg_value |= PRF_MODE_HPRF_EN_BIT_MASK; 
        reg_value &= (~PRF_MODE_HPRF_MODE_BIT_MASK);        
    }
    else if(prf == PRF_2496)
    {
        reg_value |= PRF_MODE_HPRF_EN_BIT_MASK; 
        reg_value &= (~PRF_MODE_HPRF_MODE_BIT_MASK);
        reg_value |= (1 << PRF_MODE_HPRF_MODE_BIT_OFFSET); 
    }
    else if(prf == PRF_4992)
    {
        reg_value |= PRF_MODE_HPRF_EN_BIT_MASK; 
        reg_value &= (~PRF_MODE_HPRF_MODE_BIT_MASK);
        reg_value |= (2 << PRF_MODE_HPRF_MODE_BIT_OFFSET); 
    }
    zn_write_32bit_reg(PRF_MODE_ID, reg_value);

    return;
}
/*************************************************************************************************************
* Description: This function is to config Start and win, see fira.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_cfg_t_start_and_win(void *config)
{
    zn_tstart_twin_t *start_win = (zn_tstart_twin_t *)config;
    uint32_t         reg_value  = 0;

    if(!config)
    {
        return;
    }

    reg_value = zn_read_32bit_reg(DRX_SFDTOC_ID); // clear bit to 0
    reg_value &= (~DRX_SFDTOC_BIT_MASK);
    reg_value |= ((start_win->start << DRX_SFDTOC_BIT_OFFSET) & DRX_SFDTOC_BIT_MASK);
    zn_write_32bit_reg(DRX_SFDTOC_ID, reg_value);
    zn_write_32bit_reg(RX_FWTO_ID, start_win->win);
}

/*************************************************************************************************************
* Description: This function is to set the offset between tx send time and timestamp.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_tx_ts_offset(uint8_t preamble_duration, uint8_t sfd_id, uint8_t rf_cfg)
{
    uint16_t preamble_len[9] = {16, 64, 1024, 4096, 32, 128, 256, 512, 2048};
    uint8_t  sfd_len[6] = {8, 8, 16, 4, 8, 16};
    
    if((preamble_duration > PREAMBLE_2048) || (sfd_id > SFD_ID_USER16))
    {
        return;
    }

    s_tx_ts_offset = (preamble_len[preamble_duration] + sfd_len[sfd_id]) * 254 + 6;

}

/*************************************************************************************************************
* Description: This function is to get the offset between tx send time and timestamp.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
uint32_t zn_get_tx_ts_offset(void)
{
    return s_tx_ts_offset;
}

void zn_set_ext_frame_mode(uint8_t en)
{
    uint32_t reg = 0;
    
    reg = zn_read_32bit_reg(SYS_CFG_ID);

    reg = en ? (reg | SYS_CFG_PHR_MODE_BIT_MASK) : (reg & ~SYS_CFG_PHR_MODE_BIT_MASK);   
    zn_write_32bit_reg(SYS_CFG_ID,reg);
}

/*************************************************************************************************************
* Description: This function is to modify the zn config.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_config(zn_config_t *config)
{
    if(!config)
    {
        return;
    }

    NVIC_DisableIRQ(UWB_IRQn);
    zn_modify_rframe_cfg(config->rf_cfg);
    zn_modify_channel(config->channel_num);
    zn_modify_sfd_id(config->sfd_id);
    zn_modify_preamble_code_idx(config->preamble_code_idx);
    zn_modify_bprf_phr_data_rate(config->bprf_phr_data_rate);
    zn_modify_preamble_duration(config->preamble_duration);
    zn_modify_sts_seg_num(config->sts_seg_num);
    zn_modify_sts_seg_len(config->sts_seg_len);
    zn_modify_prf_mode(config->prf_mode);
    zn_set_rx_preamble_config(config->rf_cfg, config->preamble_duration);
    zn_set_rx_sfd_config(config->sfd_id);
    zn_modify_psdu_data_rate(config->psdu_data_rate);
    zn_set_tx_ts_offset(config->preamble_duration, config->sfd_id, config->rf_cfg);
    zn_pa_set(config->pa_level);
    zn_set_ext_frame_mode(config->rf_ext_en);
    if(config->aoa_en)
    {
        zn_set_rx_sfd_timeout(0);
    }
    else
    {
        zn_set_rx_sfd_timeout(config->sfd_to + 5);
    }
    if(config->fem_en)
    {
        zn_write_32bit_reg(0x1600, 0x53801820);//fem config
    }

    zn_set_rake_param();
    NVIC_EnableIRQ(UWB_IRQn);
}

/*************************************************************************************************************
* Description: This function is to send cw.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_start_send_cw(void)
{
    zn_or_32bit_reg(TX_CTRL_ID, TX_CTRL_PA_CW_OUT_BIT_MASK);
}

/*************************************************************************************************************
* Description: This function is to stop send cw.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_stop_send_cw(void)
{
    zn_and_32bit_reg(TX_CTRL_ID, ~TX_CTRL_PA_CW_OUT_BIT_MASK);
}

/*************************************************************************************************************
* Description: This function is to modify the swc.
* Input param:
* value - swc value
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_swc(uint16_t value)
{
    uint32_t reg_value = zn_read_32bit_reg(CLK_XO_ID);

    reg_value &= ((~D_XO_SWC_O_BIT_MASK) & (~D_XO_SWC_I_BIT_MASK));
    reg_value |= (((value << D_XO_SWC_I_BIT_OFFSET) & D_XO_SWC_I_BIT_MASK) | ((value << D_XO_SWC_O_BIT_OFFSET) & D_XO_SWC_O_BIT_MASK));
    zn_write_32bit_reg(CLK_XO_ID, reg_value);
}

/*************************************************************************************************************
* Description: This function is to modify the swf.
* Input param:
* value - swf value
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_swf(uint16_t value)
{
    uint32_t reg_value = zn_read_32bit_reg(CLK_XO_ID);

    reg_value &= (~D_XO_SWF_BIT_MASK) ;
    reg_value |= ((value << D_XO_SWF_BIT_OFFSET) & D_XO_SWF_BIT_MASK);
    zn_write_32bit_reg(CLK_XO_ID, reg_value);
}

static void sys_ctrl_write_t(uint32_t addr, uint32_t val)
{
    sys_ctrl_write(addr, val);
}

/*************************************************************************************************************
* Description: This function is switch the soc to idle state.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_soc_to_idle_state(void)
{
    zn_write_32bit_reg(0x0a0c, 0);
    sys_ctrl_write_t(CLK_ICG_REG, 0x7F9FD5);
    #if TEST_MODE
    sys_ctrl_write_t(SOC_CLK_CFG, 0xf1); //tx:f1  rx:21
    #else
    sys_ctrl_write_t(SOC_CLK_CFG, 0x21); //tx:f1  rx:21
    #endif
}
/*************************************************************************************************************
* Description: This function is switch the soc to work state.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_soc_to_work_state(void)
{
    sys_ctrl_write_t(SOC_CLK_CFG, 0x10); //soc witch to pllclk
    sys_ctrl_write_t(CLK_ICG_REG, 0x719E55); //0x40319E55 0x7D319E55
    zn_write_32bit_reg(0x0a0c, 1);
}

/*************************************************************************************************************
* Description: This function is switch the antenna switch.
* Input param: ant_state: 
1:pdoa sw froce to rx2 input.
2:pdoa sw force to rxl input
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_pdoa_antenna_switch(uint8_t ant_state)
{
    uint32_t reg_value = 0;

    reg_value = zn_read_32bit_reg(ANALOG_ANTENNA_SWITCH_ID); // clear bit to 0
    reg_value &= (~PDOA_SW_FORCE_RX1RX2_INPUT_SWITCH_MASK);
    reg_value |= ((ant_state<<PDOA_SW_FORCE_TO_RX2_INPUT_BIT_OFFSET) & PDOA_SW_FORCE_RX1RX2_INPUT_SWITCH_MASK);
    zn_write_32bit_reg(ANALOG_ANTENNA_SWITCH_ID, reg_value);
}


/*******************************************************************************************************************
* Description: This is used to calculate estimated clock frequency offset
* Input param: None
* Output param: None
* Return value: frequency offset value
********************************************************************************************************************/
double zn_read_frequency_offset_result(void)
{
    uint16_t a = (zn_read_32bit_reg(COE_PPM_ID) >> COE_PPM_BIT_OFFSET) & (COE_PPM_BIT_MASK >> COE_PPM_BIT_OFFSET);
    int16_t  f = (a >= 32768 ? a - 65536 : a);

    return (double)f / 512;
}

/*******************************************************************************************************************
* Description: This is set STS_IV and STS_Key value from configured not from the AON
* Input param: None
* Output param: None
* Return value: None
********************************************************************************************************************/
void zn_sts_load_cfg(void)
{
    zn_and_32bit_reg(STS_LOAD_ID, ~(STS_CP_LOADIV_BIT_MASK | STS_CP_LOADKEY_BIT_MASK));
}

/*******************************************************************************************************************
* Description: This is set the STS_IV
* Input param:
* sts_iv - sts iv value
* Output param: None
* return value: None
********************************************************************************************************************/
void zn_sts_iv_set(uint32_t *sts_iv)
{
    zn_write_32bit_reg(STS_IV_P0, sts_iv[0]);
    zn_write_32bit_reg(STS_IV_P1, sts_iv[1]);
    zn_write_32bit_reg(STS_IV_P2, sts_iv[2]);
    zn_write_32bit_reg(STS_IV_P3, sts_iv[3]);
}

/*******************************************************************************************************************
* Description: This is set the STS_Key
* Input param:
* sts_key - sts key value
* Output param: None
* return value: None
********************************************************************************************************************/
void zn_sts_key_set(uint32_t *sts_key)
{
    zn_write_32bit_reg(STS_KEY_P0, sts_key[0]);
    zn_write_32bit_reg(STS_KEY_P1, sts_key[1]);
    zn_write_32bit_reg(STS_KEY_P2, sts_key[2]);
    zn_write_32bit_reg(STS_KEY_P3, sts_key[3]);
}

/*******************************************************************************************************************
* Description: This is set the sts index
* Input param:
* crypto_sts_index - crypto sts index
* Output param: None
* return value: None
********************************************************************************************************************/
void zn_crypto_sts_idx_set(uint32_t crypto_sts_index)
{
    zn_write_32bit_reg(STS_IV_P1, crypto_sts_index);
}


/*******************************************************************************************************************
* Description: this function is change the uci channel_num to zn config
* Input param:
* channel_no - uci channel_num
* Output param: None
* Returns value: zn channel_num
*******************************************************************************************************************/
uint8_t zn_uci_channel_num_to_zn_cfg(uint8_t channel_no)
{
    uint8_t chanel = CHANNEL_9;

    switch(channel_no)
    {
        case 2:
        {
            chanel = CHANNEL_2;
            break;
        }
        case 5:
        {
            chanel = CHANNEL_5;
            break;
        }
        case 9:
        {
            chanel = CHANNEL_9;
            break;
        }
        default:
        {
            chanel = CHANNEL_9;
            break;
        }
    }
    return chanel;
}

/*******************************************************************************************************************
* Description: this function is change the uci SFD id to zn config
* Input param:
* sfd_id - uci SFD id
* Output param: None
* Returns value: zn SFD id
*******************************************************************************************************************/
uint8_t zn_uci_sfd_id_to_zn_cfg(uint8_t sfd_id)
{
    sfd_id_t sfd = SFD_ID_SFD8;

    switch(sfd_id)
    {
        case 0:
        {
            sfd = SFD_ID_LEGACY_SFD8;
            break;
        }
        case 1:
        {
            sfd = SFD_ID_SFD4;
            break;
        }
        case 2:
        {
            sfd = SFD_ID_SFD8;
            break;
        }
        case 3:
        {
            sfd = SFD_ID_SFD16;
            break;
        }
        default:
        {
            sfd = SFD_ID_SFD8;
            break;
        }
    }

    return sfd;
}


/*******************************************************************************************************************
* Description: this function is change the uci SFD id to SFD symbol num
* Input param:
* sfd_id - uci SFD id
* Output param: None
* Returns value: SFD symbol num
*******************************************************************************************************************/
uint8_t zn_uci_sfd_id_to_sfd_symbol_num(uint8_t sfd_id)
{
    uint8_t sfd_symbol_num = 0;

    switch(sfd_id)
    {
        case 0:
        {
            sfd_symbol_num = 8;
            break;
        }
        case 1:
        {
            sfd_symbol_num = 4;
            break;
        }
        case 2:
        {
            sfd_symbol_num = 8;
            break;
        }
        case 3:
        {
            sfd_symbol_num = 16;
            break;
        }
        default:
        {
            sfd_symbol_num = 8;
            break;
        }
    }

    return sfd_symbol_num;
}

/*******************************************************************************************************************
* Description: this function is change the uci preamble code idx to zn config
* Input param:
* index - uci preamble code index
* Output param: None
* Returns value: zn preamble code index
*******************************************************************************************************************/
uint8_t zn_preamble_code_idx_to_zn_cfg(uint8_t index)
{
    preamble_code_index_t preamble_code_idx = PREAMBLE_CODE_INDEX_10;

    switch(index)
    {
        case 9:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_9;
            break;
        }
        case 10:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_10;
            break;
        }
        case 11:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_11;
            break;
        }
        case 12:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_12;
            break;
        }
        case 13:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_13;
            break;
        }
        case 14:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_14;
            break;
        }
        case 15:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_15;
            break;
        }
        case 16:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_16;
            break;
        }
        case 17:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_17;
            break;
        }
        case 18:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_18;
            break;
        }
        case 19:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_19;
            break;
        }
        case 20:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_20;
            break;
        }
        case 21:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_21;
            break;
        }
        case 22:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_22;
            break;
        }
        case 23:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_23;
            break;
        }
        case 24:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_24;
            break;
        }
        case 25:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_25;
            break;
        }
        case 26:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_26;
            break;
        }
        case 27:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_27;
            break;
        }
        case 28:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_28;
            break;
        }
        case 29:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_29;
            break;
        }
        case 30:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_30;
            break;
        }
        case 31:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_31;
            break;
        }
        case 32:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_32;
            break;
        }
        default:
        {
            preamble_code_idx = PREAMBLE_CODE_INDEX_10;
            break;
        }
    }

    return preamble_code_idx;
}

/*******************************************************************************************************************
* Description: this function is change the uci seg num to zn config
* Input param:
* seg - uci seg num
* Output param: None
* Returns value: zn seg num
*******************************************************************************************************************/
uint8_t zn_sts_seg_num_to_zn_cfg(uint8_t seg)
{
    sts_seg_num_t sts_seg_num = STS_SEG_1;

    switch(seg)
    {
        case 1:
        {
            sts_seg_num = STS_SEG_1;
            break;
        }
        case 2:
        {
            sts_seg_num = STS_SEG_2;
            break;
        }
        case 3:
        {
            sts_seg_num = STS_SEG_3;
            break;
        }
        case 4:
        {
            sts_seg_num = STS_SEG_4;
            break;
        }
        default:
        {
            sts_seg_num = STS_SEG_1;
            break;
        }
    }

    return sts_seg_num;
}

/*******************************************************************************************************************
* Description: this function is change the uci data rate to zn config
* Input param:
* rate - uci data rate
* Output param: None
* Returns value: zn data rate
*******************************************************************************************************************/
uint8_t zn_psdu_data_rate_to_zn_cfg(uint8_t rate)
{
    psdu_data_rate_t psdu_data_rate = PSDU_RATE_681;

    switch(rate)
    {
        case 0:
        {
            psdu_data_rate = PSDU_RATE_681;
            break;
        }
        case 2:
        {
            psdu_data_rate = PSDU_RATE_272;
            break;
        }
        case 4:
        {
            psdu_data_rate = PSDU_RATE_850;
            break;
        }
        default:
        {
            psdu_data_rate = PSDU_RATE_681;
            break;
        }
    }

    return psdu_data_rate;
}

/*******************************************************************************************************************
* Description: this function is change the uci preamble duration to zn config
* Input param:
* duration - uci preamble duration
* Output param: None
* Returns value: zn preamble duration
*******************************************************************************************************************/
uint8_t zn_preamble_duration_to_zn_cfg(uint8_t duration)
{
    switch(duration)
    {
        case 0:
        {
            duration = PREAMBLE_32;
            break;
        }
        case 1:
        {
            duration = PREAMBLE_64;
            break;
        }
        case 2:
        {
            duration = PREAMBLE_1024;
            break;
        }
        case 3:
        {
            duration = PREAMBLE_4096;
            break;
        }
        case 4:
        {
            duration = PREAMBLE_16;
            break;
        }
        case 8:
        {
            duration = PREAMBLE_128;
            break;
        }
        case 9:
        {
            duration = PREAMBLE_256;
            break;
        }
        default:
        {
            duration = PREAMBLE_64;
            break;
        }
    }
    return duration;
}

/*******************************************************************************************************************
* Description: this function is change the uci phr data rate to zn config
* Input param:
* rate - uci phr data rate
* Output param: None
* Returns value: zn phr data rate
*******************************************************************************************************************/
uint8_t zn_phr_data_rate_to_zn_cfg(uint8_t rate)
{
    bprf_phr_data_rate_t phr_data_rate = BPRF_PHR_RATE_850;

    switch(rate)
    {
        case 0:
        {
            phr_data_rate = BPRF_PHR_RATE_850;
            break;
        }
        default:
        {
            phr_data_rate = BPRF_PHR_RATE_850;
            break;
        }
    }
    return phr_data_rate;
}

/*******************************************************************************************************************
* Description: this function is change the uci preamble duration to preamble symbol num
* Input param:
* duration - uci preamble duration
* Output param: None
* Returns value: preamble symbol num
*******************************************************************************************************************/
uint16_t zn_preamble_duration_to_preamble_symbol_num(uint8_t duration)
{
    uint16_t sym_num = 0;

    switch(duration)
    {
        case 0:
        {
            sym_num = 32;
            break;
        }
        case 1:
        {
            sym_num = 64;
            break;
        }
        case 2:
        {
            sym_num = 128;
            break;
        }
        case 3:
        {
            sym_num = 256;
            break;
        }
        case 4:
        {
            sym_num = 512;
            break;
        }
        default:
        {
            sym_num = 64;
            break;
        }
    }

    return sym_num;
}

/*******************************************************************************************************************
* Description: this function is change the uci rframe cfg to zn config
* Input param:
* cfg - uci rframe cfg
* Output param: None
* Returns value: zn rframe cfg
*******************************************************************************************************************/
uint8_t zn_rframe_cfg_to_zn_cfg(uint8_t cfg)
{
    rframe_config_t rframe_cfg = RFRAME_SP0;

    switch(cfg)
    {
        case 0:
        {
            rframe_cfg = RFRAME_SP0;
            break;
        }
        case 1:
        {
            rframe_cfg = RFRAME_SP1;
            break;
        }
        case 3:
        {
            rframe_cfg = RFRAME_SP3;
            break;
        }
        default:
        {
            rframe_cfg = RFRAME_SP0;
            break;
        }
    }

    return rframe_cfg;
}

/*******************************************************************************************************************
* Description: this function is change the uci prf mode to zn config
* Input param:
* cfg - uci prf mode
* Output param: None
* Returns value: zn prf mode
*******************************************************************************************************************/
uint8_t zn_prf_mode_to_zn_cfg(uint8_t prf)
{
    uint8_t prf_mode = PRF_624;

    switch(prf)
    {
        case 0:
        {
            prf_mode = PRF_624;
            break;
        }
        case 1:
        {
            prf_mode = PRF_1248;
            break;
        }
        case 2:
        {
            prf_mode = PRF_2496;
            break;
        }
        default:
        {
            prf_mode = PRF_624;
            break;
        }
    }

    return prf_mode;
}

/*******************************************************************************************************************
* Description: this function is change the uci sts seg len to zn config
* Input param:
* seg_len - uci sts seg len
* Output param: None 
* Returns value: zn sts seg len
*******************************************************************************************************************/
uint16_t zn_sts_segments_len_to_zn_cfg(uint8_t seg_len)
{
    uint16_t sts_seg_len = STS_SEG_LEN_64;

    switch(seg_len)
    {
        case 0:
        {
            sts_seg_len = STS_SEG_LEN_32;
            break;
        }
        case 1:
        {
            sts_seg_len = STS_SEG_LEN_64;
            break;
        }
        case 2:
        {
            sts_seg_len = STS_SEG_LEN_128;
            break;
        }
        default:
        {
            sts_seg_len = STS_SEG_LEN_64;
            break;
        }
    }

    return sts_seg_len;
}

/*******************************************************************************************************************
* Description: this function is change the zn psdu data rate to uci config
* Input param:
* rate - zn psdu data rate
* Output param: None
* Returns value: uci psdu data rate
*******************************************************************************************************************/
uint8_t zn_psdu_data_rate_to_uci_cfg(uint8_t rate)
{
    psdu_data_rate_t psdu_data_rate = PSDU_RATE_681;

    switch(rate)
    {
        case PSDU_RATE_681:
        {
            psdu_data_rate = 0;
            break;
        }
        case PSDU_RATE_272:
        {
            psdu_data_rate = 2;
            break;
        }
        case PSDU_RATE_850:
        {
            psdu_data_rate = 4;
            break;
        }
        default:
        {
            psdu_data_rate = 0;
            break;
        }
    }

    return psdu_data_rate;
}

/*******************************************************************************************************************
* Description: this function is change the zn preamble duration to uci config
* Input param: 
* duration - zn preamble duration
* Output param: None
* Returns value: uci preamble duration
*******************************************************************************************************************/
uint8_t zn_preamble_duration_to_uci_cfg(uint8_t duration)
{
    switch(duration)
    {
        case PREAMBLE_32:
        {
            duration = 0;
            break;
        }
        case PREAMBLE_64:
        {
            duration = 1;
            break;
        }
        default:
        {
            duration = 1;
            break;
        }
    }

    return duration;
}

/*******************************************************************************************************************
* Description: this function is cfg rx preamble config
* Input param: 
* rf_cfg  - zn frame config
* duration - zn preamble duration
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_set_rx_preamble_config(uint8_t rf_cfg, uint8_t preamble_duration)
{
//    if(driver_config.phy_config.aoa_en)
//    {
//        zn_write_32bit_reg(PREAMBLE_CFG_ID, 0x2a7fc7d2); //pdoa digital config
//    }
//    else
//    {
        if(preamble_duration == PREAMBLE_16 || preamble_duration == PREAMBLE_32 || preamble_duration == PREAMBLE_64)
        {
            zn_write_32bit_reg(PREAMBLE_CFG_ID, 0x2a3fc7d0);//0x2b3fc7c8
        }
        else
        {
            if (driver_config.phy_config.aoa_en)
            {
                zn_write_32bit_reg(PREAMBLE_CFG_ID, 0x2a7fc7d2);//0x2b3fc7d2
            }
            else
            {
                zn_write_32bit_reg(PREAMBLE_CFG_ID, 0x2a3fc7d0);//0x2affcfc8
            }
        }
//    }

    return;
}
/*******************************************************************************************************************
* Description: this function is cfg rx sfd config
* Input param: 
* sfd_id - zn sfd index
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_set_rx_sfd_config(uint8_t sfd_id)
{
    uint8_t channel = (zn_read_32bit_reg(SYSTEM_PARAM_ID) & SYSTEM_PARAM_RF_CHAN_BIT_MASK) >> SYSTEM_PARAM_RF_CHAN_BIT_OFFSET;
    
    if(SFD_ID_LEGACY_SFD8 == sfd_id) 
    {
        zn_write_32bit_reg(SFD_CFG_ID, 0x76500024);
    }
    else if(SFD_ID_SFD4 == sfd_id) 
    {
        zn_write_32bit_reg(SFD_CFG_ID, 0x574b10e0);
    }
    else
    {
//        if(driver_config.phy_config.fem_en)
//        {
//            zn_write_32bit_reg(SFD_CFG_ID, 0x575014e4);
//            if( channel == CHANNEL_2   )
//            {
//                zn_write_32bit_reg(SFD_CFG_ID, 0x5d5014e0);
//            }
//        }
//        else
//        {
//            zn_write_32bit_reg(SFD_CFG_ID, 0x575014e4);//0x57ffd4e4
//            if( channel == CHANNEL_2   )
//            {
//                zn_write_32bit_reg(SFD_CFG_ID, 0x5dffd4e0);
//            }
//        }
        if(driver_config.phy_config.aoa_en)
        {
            zn_write_32bit_reg(SFD_CFG_ID, 0x57ffd4e4);
        }
        else
        {
            zn_write_32bit_reg(SFD_CFG_ID, 0x575014e4);
        }
    }
    return;
}

/*******************************************************************************************************************
* Description: This is used to output the accumulated symbol number in CIR Memory
* Input param:
* Output param:   nacc: accumulated symbols in CIR Memory
* Returns value: receive power
*******************************************************************************************************************/
uint16_t zn_read_acc_num(void)
{
    // NACC
    uint16_t         nacc = (zn_read_32bit_reg(IP_NACC0_ID) >> 20);
    return nacc;
}

/*******************************************************************************************************************
* Description: This is used to output the estimated power based in the CIR Memory
* Input param:
* Output param: noiseResult: estimated noise power based in the CIR Memory. Note that this value is also used as one 
*               of the threshold in first path detection
* Returns value: receive power
*******************************************************************************************************************/
float zn_noise_estimation(void)
{
    // NACC
    uint16_t         nacc = (zn_read_32bit_reg(IP_NACC0_ID) >> 20);
    // delta Noise
    float        deltaNoise = (float)( zn_read_32bit_reg(IP_DELTA_NOISE_ID) >> IP_DELTA_NOISE_BIT_OFFSET ) / 512;
    float        noiseResult = deltaNoise * (float)sqrt(nacc) * 56.57;
    return noiseResult;
}

void zn_internal_clk_calibration(void)
{
    zn_write_32bit_reg(0x101c, 0x30000000);
}
/*******************************************************************************************************************
* Description: Read Vbat voltage
* Input param: mode   TYPE_VBAT: the source is vbat, TYPE_ATESTP: the source is atestp
* Output param:
* Returns value: 
********************************************************************************************************************/
uint16_t zn_read_vbat_voltage(adc_mode_t mode)
{
    uint16_t dout     = 0;
    uint32_t temp     = 0;
    uint32_t reg_1054 = zn_read_32bit_reg(0x1054);
    uint32_t reg_105c = zn_read_32bit_reg(0x105c);
    uint32_t reg_dca_120 = dca_read(0x120);
    uint32_t value_add = 0;
    uint8_t index = 0;
    uint32_t reg_uwb_clk = sys_ctrl_read(UWB_CLK_ICG_REG);
    
    sys_ctrl_write(UWB_CLK_ICG_REG, reg_uwb_clk & 0xfffffffe);//open ana reg clk

    if(TYPE_VBAT == mode)
    {
        zn_write_32bit_reg(0x1060, 0x08580000);
        zn_write_32bit_reg(0x1054, 0x01704000);
        
        for(index = 0; index < 3; index++)
        {
            cpu_delay(10);
            value_add += zn_read_32bit_reg(0x107c) & 0x3ff;
        }

        dout = value_add/10;
    }
    else if(TYPE_ATESTP == mode)
    {
        dca_write(0x120,0x00);
        zn_write_32bit_reg(0x1054, 0x01704000);
        zn_write_32bit_reg(0x1060, 0x08480000);
        temp = (reg_105c & (~0x03000000)) | 0x01000000;
        zn_write_32bit_reg(0x105c, temp);
        
        for(index = 0; index < 3; index++)
        {
            cpu_delay(10);
            value_add += zn_read_32bit_reg(0x107c) & 0x3ff;
        }
        dout = value_add/10;
    }
    else if(TYPE_TEMPERATURE == mode)
    {
        zn_write_32bit_reg(0x1060, 0x08680000);
        zn_write_32bit_reg(0x1054, 0x01704000);
        
        for(index = 0; index < 3; index++)
        {
            cpu_delay(10);
            value_add += zn_read_32bit_reg(0x107c) & 0x3ff;
        }
        dout = value_add/10;
    }
    else
    {
        dout = 0;
    }
    
    zn_write_32bit_reg(0x1054, reg_1054);
    zn_write_32bit_reg(0x105c, reg_105c);
    dca_write(0x120, reg_dca_120);

    sys_ctrl_write(UWB_CLK_ICG_REG, reg_uwb_clk);

    return dout;
}


void zn_modify_PDOA_RX1_TIME_en(uint32_t rx_en)
{
//    uint32_t  regValue = 0;
//    regValue = zn_read_32bit_reg(SYS_CFG_ID);// clear bit to 0
//    regValue &= (~SYS_CFG_PDOA_RX1_TIME_EN_BIT_MASK);
//    regValue |= ((rx_en << SYS_CFG_PDOA_RX1_TIME_EN_BIT_OFFSET) & SYS_CFG_PDOA_RX1_TIME_EN_BIT_MASK);
//    zn_write_32bit_reg(SYS_CFG_ID, regValue);
    return;
}
//isHPRFen 0:HPRF disable 1:enable HPRF
void zn_modify_hprf_en(uint32_t isHPRFen)
{
//    uint32_t  regValue = 0;
//    regValue = zn_read_32bit_reg(SYS_CFG_ID);// clear bit to 0
//    regValue &= (~SYS_CFG_HPRF_EN_BIT_MASK);
//    regValue |= ((isHPRFen << SYS_CFG_HPRF_EN_BIT_OFFSET) & SYS_CFG_HPRF_EN_BIT_MASK);
//    zn_write_32bit_reg(SYS_CFG_ID, regValue);
    return;
}

//ccMode 0:K3 1:K7
void zn_modify_cc_mode(uint32_t ccMode)
{
//    uint32_t  regValue = 0;
//    regValue = zn_read_32bit_reg(SYS_CFG_ID);// clear bit to 0
//    regValue &= (~SYS_CFG_CC_MODE_BIT_MASK);
//    regValue |= ((ccMode << SYS_CFG_CC_MODE_BIT_OFFSET) & SYS_CFG_CC_MODE_BIT_MASK);
//    zn_write_32bit_reg(SYS_CFG_ID, regValue);
    return;
}
//disRS 1:disable RS 0:enable RS
void zn_modify_rs_dis(uint32_t disRS)
{
//    uint32_t  regValue = 0;
//    regValue = zn_read_32bit_reg(SYS_CFG_ID);// clear bit to 0
//    regValue &= (~SYS_CFG_DIS_RS_BIT_MASK);
//    regValue |= ((disRS << SYS_CFG_DIS_RS_BIT_OFFSET) & SYS_CFG_DIS_RS_BIT_MASK);
//    zn_write_32bit_reg(SYS_CFG_ID, regValue);
    return;
}

//extendMode 0:<=1023byte 1:<=2047byte 2:<=4095byte
void zn_modify_hprf_phr_extend_mode(uint32_t extendMode)
{
//    uint32_t  regValue = 0;
//    regValue = zn_read_32bit_reg(SYS_CFG_ID);// clear bit to 0
//    regValue &= (~SYS_CFG_HPRF_PHR_EXTEND_BIT_MASK);
//    regValue |= ((extendMode << SYS_CFG_HPRF_PHR_EXTEND_BIT_OFFSET) & SYS_CFG_HPRF_PHR_EXTEND_BIT_MASK);
//    zn_write_32bit_reg(SYS_CFG_ID, regValue);
    return;
}

//extendMode 0:std <=127byte 1 extend:<=1023byte
void zn_modify_bprf_phr_extend_mode(uint32_t extendMode)
{
    uint32_t  regValue = 0;
    regValue = zn_read_32bit_reg(SYS_CFG_ID);
    regValue &= (~SYS_CFG_PHR_MODE_BIT_MASK);
    regValue |= ((extendMode << SYS_CFG_PHR_MODE_BIT_OFFSET) & SYS_CFG_PHR_MODE_BIT_MASK);
    zn_write_32bit_reg(SYS_CFG_ID, regValue);
    return;
}

//stsMode 1:BPRF 0:HPRF
void zn_modify_sts_mode(uint32_t stsMode)
{
    uint32_t  regValue = zn_read_32bit_reg(STS_CFG_ID);
    regValue &= (~STS_DELTA_BIT_MASK);
    regValue |= ((stsMode << STS_DELTA_BIT_OFFSET) & STS_DELTA_BIT_MASK);
    zn_write_32bit_reg(STS_CFG_ID, regValue);
    return;
}

/*******************************************************************************************************************
* Description: zn_set_user_sfd config
* Input param:  sfd_id_t: SFD_ID_USER8 or SFD_ID_USER16
* Output param:  null
* Returns value: null
*******************************************************************************************************************/
void zn_set_user_sfd(sfd_id_t sfd)
{
    uint32_t  regValue = 0;
    if(SFD_ID_USER8 == sfd)
    {
        regValue = SFD_CONFIGED_BIT_MASK;
        zn_set_user_sfd_sequence(USER_SFD8_SEQ);
    }
    else if(SFD_ID_USER16 == sfd)
    {
        regValue = SFD_CONFIGED_BIT_MASK | SFD_LEN_BIT_MASK;
        zn_set_user_sfd_sequence(USER_SFD16_SEQ);
    }
    else
    {
        regValue = 0;
    }
    zn_write_32bit_reg(SFD_TYPE_USED_ID, regValue);
    return;
}

/*******************************************************************************************************************
* Description: set user sfd sequence when set user SFD_ID_USER8 or SFD_ID_USER16
* Input param:  sfd_sequence
* Output param:  null
* Returns value: null
*******************************************************************************************************************/
void zn_set_user_sfd_sequence(uint32_t sfd_sequence)
{
    zn_write_32bit_reg(SFD_SEQUENCE_ID, sfd_sequence);
    return;
}

/*******************************************************************************************************************
* Description: set dw phr extend mode
* Input param:  dw phr extend mode isOn 0:disable 1:enable
* Output param:  null
* Returns value: null
*******************************************************************************************************************/
void zn_set_dw_phr_mode(uint8_t isOn)
{
    uint32_t  regValue = zn_read_32bit_reg(DW_PHR_CGF_ID);
    regValue &= (~PHR_EXTEND_MODE_1_BIT_MASK);
    regValue |= ((isOn << PHR_EXTEND_MODE_1_BIT_OFFSET) & PHR_EXTEND_MODE_1_BIT_MASK);
    zn_write_32bit_reg(DW_PHR_CGF_ID, regValue);
    return;
}

/*******************************************************************************************************************
* Description: set dw phr extend mode
* Input param:  dw phr extend mode preamble duration bit isSet 0:disable 1:enable
* Output param:  null
* Returns value: null
*******************************************************************************************************************/
void zn_set_dw_phr_mode_preamble_duration_bit(uint8_t isSet)
{
    uint32_t  regValue = zn_read_32bit_reg(DW_PHR_CGF_ID);
    regValue &= (~PREAMBLE_DURING_BIT_MASK);
    regValue |= ((isSet << PREAMBLE_DURING_BIT_OFFSET) & PREAMBLE_DURING_BIT_MASK);
    zn_write_32bit_reg(DW_PHR_CGF_ID, regValue);
    return;
}

void zn_fem_to_tx_state(void)
{
    GPIOA_SET_BITS(driver_config.phy_config.fem_tx_pin);
    GPIOA_RESET_BITS(driver_config.phy_config.fem_rx0_pin);
    if(driver_config.phy_config.aoa_en)
    {
        if(TYPE_3D == driver_config.phy_config.aoa_dimension_mode)
        {
            GPIOA_RESET_BITS(driver_config.phy_config.fem_rx1_pin);
            GPIOA_RESET_BITS(driver_config.phy_config.fem_rx2_pin);
        }
        else
        {
            GPIOA_RESET_BITS(driver_config.phy_config.fem_rx1_pin);
        }
    }
}

void zn_fem_to_rx_state(void)
{
    GPIOA_RESET_BITS(driver_config.phy_config.fem_tx_pin);
    GPIOA_SET_BITS(driver_config.phy_config.fem_rx0_pin);
    if(driver_config.phy_config.aoa_en)
    {
        if(TYPE_3D == driver_config.phy_config.aoa_dimension_mode)
        {
            if(RX1_INPUT == driver_config.phy_config.ant_sel)
            {
                GPIOA_SET_BITS(driver_config.phy_config.fem_rx1_pin);
                GPIOA_RESET_BITS(driver_config.phy_config.fem_rx2_pin);
            }
            else
            {
                GPIOA_RESET_BITS(driver_config.phy_config.fem_rx1_pin);
                GPIOA_SET_BITS(driver_config.phy_config.fem_rx2_pin);
            }
        }
        else
        {
            GPIOA_SET_BITS(driver_config.phy_config.fem_rx1_pin);
        }
    }
}

void zn_fem_to_idle_state(void)
{
    GPIOA_RESET_BITS(driver_config.phy_config.fem_tx_pin);
    GPIOA_RESET_BITS(driver_config.phy_config.fem_rx0_pin);
    if(driver_config.phy_config.aoa_en)
    {
        if(TYPE_3D == driver_config.phy_config.aoa_dimension_mode)
        {
            GPIOA_RESET_BITS(driver_config.phy_config.fem_rx1_pin);
            GPIOA_RESET_BITS(driver_config.phy_config.fem_rx2_pin);
        }
        else
        {
            GPIOA_RESET_BITS(driver_config.phy_config.fem_rx1_pin);
        }
    }
}