/*****************************************************************************
* File: c_simple_rx.c
*
* Descirption: this file contains the functions support rx test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <string.h>
#include "phy_cmd.h"
#include "hal_uwb.h"
#include "hal_delay.h"
#include "zn_interface.h"

static volatile uint8_t rx_ok_flag = 0;
static volatile uint8_t rx_error_flag = 0;
static volatile uint8_t rx_timeout_flag = 0;
static volatile uint8_t rx_sts_error_flag = 0;

static uint16_t frame_len = 0;
static uint8_t rx_buffer[MAX_FRAME_LEN] = {0};
static uint8_t rx_flag_tabel[MAX_TEST_NUM] = {0};

static uint32_t first_packet = 0;

static double pdoa1 = 0.0;
static double pdoa2 = 0.0;
static double aoa1 = 0.0;
static double aoa2 = 0.0;
static uint8_t valid_flag1 = 0;
static uint8_t valid_flag2 = 0;
static uint8_t aoa_flag = 0;

#define CIR_MEM_PRINTF_LNE  1016
#define STS_MEM_PRINTF_LNE  512
static int32_t RX_I_BUFF[CIR_MEM_PRINTF_LNE] = {0};
static int32_t RX_Q_BUFF[CIR_MEM_PRINTF_LNE] = {0};
void read_rx0_cir_iq(void)
{
    zn_read_cir_memory_iprx0(RX_I_BUFF, RX_Q_BUFF);
    printf("**********CIA MEM Data of RX0 **********************\r\n");
    //printf("RX0_SFD_I=");
    for(int i = 0; i<CIR_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_I_BUFF[i]);
    }
    printf("\r\n\n");
    //printf("RX0_SFD_Q=");
    for(int i = 0; i<CIR_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_Q_BUFF[i]);
    }
    printf("\r\n\n");
}

void read_rx1_cir_iq(void)
{
    zn_read_cir_memory_iprx1(RX_I_BUFF, RX_Q_BUFF);
    printf("**********CIA MEM Data of RX1 **********************\r\n");
    //printf("RX1_SFD_I=");
    for(int i = 0; i<CIR_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_I_BUFF[i]);
    }
    printf("\r\n\n");
    //printf("RX1_SFD_Q=");
    for(int i = 0; i<CIR_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_Q_BUFF[i]);
    }
    printf("\r\n\n");
}

void read_rx0_sts_iq(void)
{
    zn_read_cir_memory_cprx0(RX_I_BUFF, RX_Q_BUFF);
    printf("**********STS MEM Data of RX0 **********************\r\n");
    //printf("RX0_STS_I=");
    for(int i = 0; i<STS_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_I_BUFF[i]);
    }
    printf("\r\n\n");
    //printf("RX0_STS_Q=");
    for(int i = 0; i<STS_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_Q_BUFF[i]);
    }
    printf("\r\n\n");
}

void read_rx1_sts_iq(void)
{
    zn_read_cir_memory_cprx1(RX_I_BUFF, RX_Q_BUFF);
    printf("**********STS MEM Data of RX1 **********************\r\n");
    //printf("RX1_STS_I=");
    for(int i = 0; i<STS_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_I_BUFF[i]);
    }
    printf("\r\n\n");
    //printf("RX1_STS_Q=");
    for(int i = 0; i<STS_MEM_PRINTF_LNE; i++)
    {
        printf("%d ", RX_Q_BUFF[i]);
    }
    printf("\r\n\n");
}

static void rx_ok_phy(const zn_cb_data_t *cb_data)
{
    frame_len = cb_data->data_length;
    rx_ok_flag = 1;
    if ((cb_data->data_length < MAX_FRAME_LEN)&&(cb_data->data_length > 0))
    {
        zn_read_rx_data(rx_buffer, cb_data->data_length);
    }
}

static void rx_err_phy(const zn_cb_data_t *cb_data)
{
    rx_error_flag = 1;
    frame_len = cb_data->data_length;

    if ((cb_data->data_length < MAX_FRAME_LEN)&&(cb_data->data_length > 0))
    {
        zn_read_rx_data(rx_buffer, cb_data->data_length);
    }
}

static void rx_time_out_phy(const zn_cb_data_t *cb_data)
{
    rx_timeout_flag = 1;
}

static void rx_sts_err_phy(const zn_cb_data_t *cb_data)
{
    rx_sts_error_flag = 1;
}

static void quick_loop_rx(uint8_t* rx_flag)
{
    uint32_t   packet_num = 0;
    uint32_t   status     = 0;
    phy_cmd_t* phy_cmd    = get_phy_cmd_addr();
    
    rx_error_flag = 0;
    rx_sts_error_flag = 0;
    rx_timeout_flag = 0;
    rx_ok_flag = 0;
    
    hal_uwb_immediate_rx();

    if(phy_cmd->interrupt_en)
    {
        while(!(rx_ok_flag | rx_error_flag | rx_timeout_flag | rx_sts_error_flag) && (phy_cmd->rx_flag != PHY_TRANSFER_STOP));
    }
    else
    {
        while(!((status = hal_read_uwb_register(SYS_STATUS_ID)) & UWB_RX_FINISH_EVENT) && (phy_cmd->tx_flag != PHY_TRANSFER_STOP));
        hal_write_uwb_register(SYS_STATUS_ID, SYS_MASK_MASK);
    }
    
    
    if((rx_ok_flag) || (status & UWB_RX_OK_EVENT))
    {
        packet_num = ((uint32_t)rx_buffer[14] << 24) | ((uint32_t)rx_buffer[15] << 16) | ((uint32_t)rx_buffer[16] << 8) | (uint32_t)rx_buffer[17];
        rx_buffer[14] = 0;
        rx_buffer[15] = 0;
        rx_buffer[16] = 0;
        rx_buffer[17] = 0;
        
        if(0 == phy_cmd->ok_count)
        {
            first_packet = phy_cmd->packet_count;
        }
        phy_cmd->ok_count++;
        rx_flag_tabel[phy_cmd->packet_count]=1;
    }
    else
    {
        rx_flag_tabel[phy_cmd->packet_count]=0;
    }
    phy_cmd->packet_count++;
    
    if(MAX_TEST_NUM == phy_cmd->packet_count)
    {
        printf("correct number is %d, total is %d\n",phy_cmd->ok_count, phy_cmd->packet_count - first_packet + 1);
        printf("correct number is %d\n", phy_cmd->ok_count);
        for(int i=0; i<MAX_TEST_NUM; i++)
        {
            printf("%d  ",rx_flag_tabel[i]);
        }
        printf("\n");
        
        *rx_flag = PHY_TRANSFER_STOP;
    }
}

void phy_simple_rx(void)
{
    hal_aoa_result_t    aoa_rlt       = {0};
    uint16_t            timeout_ms    = 0;
    uint32_t            packet_num    = 0;
    uint32_t            status        = 0;
    phy_cmd_t*          phy_cmd       = get_phy_cmd_addr();
    zn_driver_config_t* driver_config = zn_get_dirver_config_addr();
    
    
    if(phy_cmd->quick_loop_en && (phy_cmd->rx_flag != PHY_TRANSFER_STOP))
    {
        quick_loop_rx(&phy_cmd->rx_flag);
        return;
    }
    if(phy_cmd->interrupt_en)
    {
        driver_config->zn_interrupt_callback.cb_cp_err = &rx_sts_err_phy;
        driver_config->zn_interrupt_callback.cb_rx_ok = &rx_ok_phy;
        driver_config->zn_interrupt_callback.cb_rx_err = &rx_err_phy;
        driver_config->zn_interrupt_callback.cb_rx_timeout = &rx_time_out_phy;
    }
    
    timeout_ms = (phy_cmd->rx_timeout_ms > 0) ? phy_cmd->rx_timeout_ms : 1;
    #ifndef POWER_TEST
    hal_uwb_set_rx_timeout(timeout_ms * 1000);
    #else
    hal_uwb_set_rx_timeout(0);
    #endif
    
    if(phy_cmd->rx_flag != PHY_TRANSFER_STOP)
    {
        rx_error_flag = 0;
        rx_sts_error_flag = 0;
        rx_timeout_flag = 0;
        rx_ok_flag = 0;
        
        if(driver_config->phy_config.aoa_en)
        {
            if(TYPE_2D == driver_config->phy_config.aoa_dimension_mode)
            {
                hal_uwb_rx_antenna_switch(driver_config->phy_config.ant_sel);
            }
            else if(RFRAME_SP0 == hal_get_cur_frame_type())
            {
                if(phy_cmd->packet_count % 2)
                {
                    hal_uwb_rx_antenna_switch(RX1_INPUT);
                }
                else
                {
                    hal_uwb_rx_antenna_switch(RX2_INPUT);
                }
            }
            else
            {
                //hal_uwb_read_3d_pdoa_nlos_result(&pdoa1, &pdoa2, &aoa_flag);
                zn_write_32bit_reg(0x105c, 0xfc001000);//switch to ant automatic mode
            }
        }
        if(phy_cmd->agc_mem_en)
        {
            printf("enable AGC mem\r\n");
            hal_write_uwb_register(ADC_SYNC_ID, 0x1c600000); 
            hal_delay_ms(10);                    
            hal_write_uwb_register(ADC_SYNC_ID, 0x1c680000);
        }
        hal_uwb_immediate_rx();
        #ifdef POWER_TEST
        uint32_t reg = sys_ctrl_read(UWB_CLK_ICG_REG);
        reg |= 0x00001000;
        sys_ctrl_write(UWB_CLK_ICG_REG, reg);
        __asm__("wfi");
		#endif
        if(phy_cmd->interrupt_en)
        {
            while(!(rx_ok_flag | rx_error_flag | rx_timeout_flag | rx_sts_error_flag) && (phy_cmd->rx_flag != PHY_TRANSFER_STOP));
        }
        else
        {
            while(!((status = hal_read_uwb_register(SYS_STATUS_ID)) & UWB_RX_FINISH_EVENT));
            hal_write_uwb_register(SYS_STATUS_ID, SYS_MASK_MASK);
        }
        
        if(PHY_TRANSFER_SIGNLE == phy_cmd->rx_flag)
        {
            phy_cmd->rx_flag = PHY_TRANSFER_STOP;
        }
        
        if((rx_timeout_flag) || (status & UWB_RX_TIMEOUT_EVENT))
        {
            #ifndef POWER_TEST
            LOG_INFO("rx recv timeout!");
            #endif
        }
        
        if((rx_sts_error_flag) || (status & UWB_RX_STS_ERROR_EVENT))
        {
            #ifndef POWER_TEST
            LOG_INFO("rx sts error!");
            #endif
        }
        #ifndef POWER_TEST
        int rakeresult = zn_read_32bit_reg(0x19a0);
        printf("Rake Result is %X\n",rakeresult);
        int fp0 = zn_read_32bit_reg(0x1a38) >> 22;
        int peakIdx = zn_read_32bit_reg(0x1a28) >> 22;
        printf("diference between frist path and peak path is %d\n",peakIdx - fp0);

        double freq_offset = hal_uwb_get_freq_offset();
        
        LOG_INFO("clk freq offset is %3.2f", freq_offset);
        hal_uwb_show_rx0_info();
        #endif
        if(driver_config->phy_config.aoa_en)
        {
            hal_uwb_show_rx1_info();
        }
        #ifndef POWER_TEST
        LOG_INFO("recv data: psdu length is %d, status is 0x%08x", frame_len, driver_config->irq_status);
        #endif
        driver_config->irq_status = 0;
        
        if(phy_cmd->psdu_print_en)
        {
            #ifndef POWER_TEST
            printf("rx_buffer : \n");
            for(uint16_t idx = 0; idx < frame_len; idx++)
            {
                printf("%x ", rx_buffer[idx]);
                if((0 == (idx % 64)) && (idx > 0))
                {
                    printf("\n");
                }
            }
            printf("\n");
            #endif
        }
        
        if((rx_ok_flag) || (status & UWB_RX_OK_EVENT))
        {
            phy_cmd->ok_count++;
            #ifndef POWER_TEST
            LOG_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! crc good data !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            #endif
            packet_num = ((uint32_t)rx_buffer[14] << 24) | ((uint32_t)rx_buffer[15] << 16) | ((uint32_t)rx_buffer[16] << 8) | (uint32_t)rx_buffer[17];
            rx_buffer[14] = 0;
            rx_buffer[15] = 0;
            rx_buffer[16] = 0;
            rx_buffer[17] = 0;
            
            if(phy_cmd->sfd_cir_mem_en)
            {
                //hal_uwb_read_cir_mem_rx0();
                read_rx0_cir_iq();
                if(driver_config->phy_config.aoa_en)
                {
                    //hal_uwb_read_cir_mem_rx1();
                    read_rx1_cir_iq();
                }
            }
            
            if(phy_cmd->sts_cir_mem_en)
            {
                //hal_uwb_read_sts_mem_rx0();
                read_rx0_sts_iq();
                if(driver_config->phy_config.aoa_en)
                {
                    //hal_uwb_read_sts_mem_rx1();
                    read_rx1_sts_iq();
                }
            }
            
            if(driver_config->phy_config.aoa_en)
            {
                if(TYPE_2D == driver_config->phy_config.aoa_dimension_mode)
                {
                    hal_uwb_read_2d_angle(&pdoa1, &aoa1, &valid_flag1);
                    LOG_INFO("pdoa1=%7.2f, aoa1=%7.2f, flag1=%d", pdoa1, aoa1, valid_flag1);
                }
                else 
                {
                    if(RFRAME_SP0 == driver_config->phy_config.rf_cfg)
                    {
                        if(phy_cmd->packet_count % 2)
                        {
                            hal_uwb_read_2d_angle(&pdoa1, &aoa1, &valid_flag1);
                        }
                        else
                        {
                            hal_uwb_read_2d_angle(&pdoa2, &aoa2, &valid_flag2);
                            
                            uint8_t flag[3][3] = {{0, 0, 0}, {0, 1, 1}, {0, 1, 2}};
                            aoa_flag = flag[valid_flag1][valid_flag2];
                            
                            zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type3(pdoa1, pdoa2, &aoa1, &aoa2, &aoa_flag);
                            LOG_INFO("pdoa1=%7.2f, pdoa2=%7.2f, aoa1=%7.2f, aoa2=%7.2f, flag=%d", pdoa1, pdoa2, aoa1, aoa2, aoa_flag);
                        }
                    }
                    else
                    {
                        pdoa1 = 0.0;
                        pdoa2 = 0.0;
                        //hal_uwb_read_3d_angle(&pdoa1, &pdoa2, &aoa1, &aoa2, &aoa_flag);
                        //zn_read_3d_angle_result_with_antenna_vertical_type4(&pdoa1, &pdoa1, &aoa1, &aoa2, &aoa_flag);
                        zn_read_3d_pdoa_nlos_result(&pdoa1, &pdoa2, &aoa_flag);
                        double pdoa1_cal=0.0,pdoa2_cal=0.0,min1,min2;
                        uint8_t pdoa1_cal_flag=0,pdoa2_cal_flag=0;
                        #ifdef DISABLEFLOAT16
                        zn_calculate_pdoa_via_sfd_cir(&pdoa1_cal, &pdoa1_cal_flag, &min1);
                        zn_calculate_pdoa_via_sts_cir(&pdoa2_cal, &pdoa2_cal_flag, &min2);
                        #endif
                        LOG_INFO("pdoa1=%7.2f, pdoa2=%7.2f, flag=%d, pdoa1_cal=%7.2f, pdoa1_cal_flag=%d, pdoa2_cal=%7.2f, pdoa2_cal_flag=%d", pdoa1, pdoa2, aoa_flag, pdoa1_cal,pdoa1_cal_flag, pdoa2_cal, pdoa2_cal_flag);
                    }
                }
            }
        }
        
        if((rx_error_flag) || (status & UWB_RX_ERROR_EVENT & ~UWB_RX_STS_ERROR_EVENT))
        {
            if(phy_cmd->sfd_cir_mem_en)
            {
                hal_uwb_read_cir_mem_rx0();
            }
            #ifndef POWER_TEST
            LOG_INFO("rx recv crc error!");
            #endif
        }
        phy_cmd->packet_count++;
        #ifndef POWER_TEST
        LOG_INFO("packet index is %d, correct number is %d, total is %d, lnaflag: %d", packet_num, phy_cmd->ok_count, phy_cmd->packet_count, driver_config->lna_switch_flag);
        #endif
        if(phy_cmd->packet_count >= MAX_TEST_NUM)
        {
            phy_cmd->ok_count = 0;
            phy_cmd->packet_count = 0;
            #ifndef POWER_TEST
            phy_cmd->rx_flag = PHY_TRANSFER_STOP;
            #endif
        }
    }
    memset(rx_buffer, 0, MAX_FRAME_LEN);
}