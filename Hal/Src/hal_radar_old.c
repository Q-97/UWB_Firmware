#include "hal_radar.h"
#include "zn_interface.h"
#include "hal_radar_old.h"
#include "gconfig.h"
#include "math.h"
#include "radar_ant.h"
#include "user_app.h"
#include "phy_cmd.h"

#define  CIR_MEM_MAX_LEN (128)
int32_t     g_buffer[CIR_MEM_MAX_LEN * 2] = {0};
int32_t     *g_buffer_I = g_buffer;
int32_t     *g_buffer_Q = &g_buffer[CIR_MEM_MAX_LEN];

int32_t     *g_buffer_I;
int32_t     *g_buffer_Q;
hal_old_radar_cfg   g_hal_radar_cfg = {};
uint8_t     cirMemory[8192]; 
uint16_t    g_msg_send_len;

uint8_t     g_cali_flag = TRUE;
uint8_t g_send_cir_data_done  = FALSE;
uint8_t g_ant_id = 0;

hal_radar_rx_gain_index_t hal_radar_rx_gain_list[] = 
{
    {0,0,0},
    {0,1,0},
    {0,2,0},
    {0,3,0},
    {0,4,0},
    {0,5,0},
    {0,5,1},
    {0,5,2},
    {0,5,3},
    {0,5,4},
    {0,5,5},
    {0,5,6},
    {0,5,7},
    {0,5,8},
    {0,5,9},   //14
    {0,5,10},
    {0,5,11},
    {0,5,12},
    {0,5,13},
    {0,5,14},  //index = 19     
    {1,0,0},
    {1,1,0},
    {1,2,0},
    {1,3,0},
    {1,4,0},
    {1,5,0},
    {1,5,1},
    {1,5,2},
    {1,5,3},
    {1,5,4},
    {1,5,5},
    {1,5,6},
    {1,5,7},
    {1,5,8},
    {1,5,9},   //34
    {1,5,10},
    {1,5,11},
    {1,5,12},
    {1,5,13},
    {1,5,14}  //index = 39 
};

void hal_radar_config_update(hal_uwb_radar_old_config_t *radar_cfg)
{
    g_hal_radar_cfg.tx_power_level = radar_cfg->tx_power_level;
    g_hal_radar_cfg.rx_gain_level = radar_cfg->rx_gain_level;
    g_hal_radar_cfg.fp_threshold = radar_cfg->fp_threshold;
    g_hal_radar_cfg.cir_tap_len = radar_cfg->cir_tap_len;
    g_hal_radar_cfg.preamble_length = radar_cfg->preamble_length;
    g_hal_radar_cfg.frame_interval = radar_cfg->frame_interval;
    g_hal_radar_cfg.user_algo_flag = radar_cfg->user_algo_flag;
    g_hal_radar_cfg.timeout = radar_cfg->timeout;
    g_hal_radar_cfg.acc_Threshold = radar_cfg->acc_Threshold;
    g_hal_radar_cfg.cir_type = radar_cfg->cir_type;
    g_hal_radar_cfg.win_leftLen = radar_cfg->win_leftLen;
    g_hal_radar_cfg.win_startshift = radar_cfg->win_startshift;
    g_hal_radar_cfg.radar_ant_type = radar_cfg->radar_ant_type;
}
void radar_old_timer_irq_proc(void)
{
    uint8_t seq = 0xff;
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();
    if(phy_cmd->phy_debug_flag == WORK_MODE_NORMAL)
    {
        if(g_hal_radar_cfg.radar_ant_type == FOUR_T_FOUR_R_MODE)
        {
            seq = hal_radar_four_t_r_mode_find_first_valid_swtich();
            if(seq == 0xff)
            {
                printf("no valid ant,switch default ant id 0\r\n");
                seq = 0x00;
                
            }            
            g_ant_id = seq;
            g_hal_radar_ant_switch_seq[seq].pre_status = TRUE;
            hal_radar_four_t_r_mode_sel(seq);
        }
    }
    hal_send_radar_signle_start();
}
void hal_radar_old_timer_init(uint8_t timer_id)
{
    hal_gp_timer_t timer_config = {0};
    
    timer_config.timer_id = TIMER1;
    timer_config.clk_src = PLL_CLK;
    timer_config.clk_div = 0;
    timer_config.mode = TIMER_USER_DEFINE;
    timer_config.interrupt_en = 1;
    timer_config.time1 = (uint32_t)(g_hal_radar_cfg.frame_interval * 1000);
    timer_config.func = (TIMER_CallbackType)&radar_old_timer_irq_proc;
    
    hal_gp_timer_init(&timer_config);
    hal_gp_timer_start(timer_config.timer_id);
    

}

void radar_to_trx_state()
{
    dca_write(AON_D_BUCK_CONTROL4,0x00);
    sys_ctrl_write(UWB_CLK_ICG_REG, 0);
    zn_clear_bit(0x1084, 24);
    sys_set_bit(UWB_AUTO_CLK_CFG,UWB_AUTO_CLK_CFG_HW_RX_CLK_MASK_SHIFT);//can read sts mem: enable clock
    zn_clear_bit(0x0828, 8);
    zn_write_32bit_reg(0x084c, 0x82210800);
    zn_wait_pll_stable(0xa7);
}
void hal_radar_fixed_gain_cfg()
{
    uint8_t lna_level = hal_radar_rx_gain_list[g_hal_radar_cfg.rx_gain_level].lna_level;
    uint8_t tia_level = hal_radar_rx_gain_list[g_hal_radar_cfg.rx_gain_level].tia_level;
    uint8_t vga_level = hal_radar_rx_gain_list[g_hal_radar_cfg.rx_gain_level].vag_level;
    zn_fixed_gain_cfg_rx1(lna_level,tia_level,vga_level);

}
void hal_radar_register_init(void)
{
    uint32_t reg_value;
    uint8_t  tx_msg[1] ={0};

    zn_write_32bit_reg(0x105c, 0xfc001500);
//   
    hal_radar_fixed_gain_cfg();
    radar_to_trx_state(); 
    zn_write_32bit_reg(0x1600, 0x20004020);
    
////    // TX Power
    zn_pa_set(g_hal_radar_cfg.tx_power_level);
//    // RX Timeout           
    hal_uwb_set_rx_timeout(g_hal_radar_cfg.timeout);    
    
}
uint32_t radar_calibration(uint32_t fp_threshold)
{
	uint8_t  fp_check_idx = 0;
	uint8_t  fp_check_num = 10;
	g_hal_radar_cfg.fp_threshold = fp_threshold;
    
    while((fp_check_idx < fp_check_num)&&(g_hal_radar_cfg.fp_threshold >=50))
    {
        fp_check_idx++;
        hal_send_radar_signle_start();
        mdelay(100);
        if(g_cali_flag == FALSE)
        {
            break;
        }
        g_hal_radar_cfg.fp_threshold -= 50;
    }
    return g_hal_radar_cfg.fp_threshold;
    
}    

void hal_radar_old_init()
{
    uint32_t fp_thr_value = 0;
    uint8_t  flash_data[60]      = {0};

    uint32_t change_32_to_8_len = 0;
    
    hal_uwb_radar_old_config_t *hal_radar_old_config = &uwb_instance.radar_old_config;
    
    hal_radar_config_update(hal_radar_old_config);
    
    hal_radar_register_init();
    
}


uint8_t zn_readcirmemery_iprx1(int32_t *buffer_I, int32_t *buffer_Q)
{
    uint32_t addr = 0x4000;
    uint32_t N = 0xFFFFFF;
    uint32_t N_1 = 0x7FFFFF;
    uint32_t ValueTmp = 0;
    uint8_t IQFlag = 0;        
    uint16_t readIdx = 0;
    uint8_t leftLen = g_hal_radar_cfg.win_leftLen, rightLen = g_hal_radar_cfg.cir_tap_len - 1;			// LeftLen + rightLen + 1 == CIR_MEM_LEN
	uint8_t win_startshift = g_hal_radar_cfg.win_startshift;
    uint16_t accNum = zn_read_32bit_reg(IP_NACC1_ID) >> IP_NACC0_BIT_OFFSET;
    uint32_t threshold = g_hal_radar_cfg.fp_threshold * accNum;
    uint32_t IP_Compe_I = zn_read_32bit_reg(0x1d4c);
    uint32_t IP_Compe_Q = zn_read_32bit_reg(0x1d50);
    int32_t Compe_I = IP_Compe_I > 2097151 ? (int32_t)(IP_Compe_I - 4194304) : (int32_t)IP_Compe_I;   
    int32_t Compe_Q = IP_Compe_Q > 2097151 ? (int32_t)(IP_Compe_Q - 4194304) : (int32_t)IP_Compe_Q;   
    float cs, si;
    if(g_hal_radar_cfg.cir_type){
        if(Compe_Q == 0){
            si = 0.0;
            cs = Compe_I >= 0 ? 1 : -1;
        }
        else if(Compe_I == 0){
            cs = 0.0;
            si =  Compe_Q >= 0 ? 1 : -1;
        }
        else{
            double phase = Compe_I < 0 ? 3.1415 + atan((double)Compe_Q/Compe_I) : atan((double)Compe_Q/Compe_I);
            si = sin(phase);
            cs = cos(phase); 
        }
    }
	
    // consider peak index
    uint16_t fpIdx = (zn_read_32bit_reg(0x1b14) >> 22);
    double IQ_T = 0, IQ_T_P = 0;
    uint8_t fpMemory[8];
    uint8_t readDoneFlg = 0;
    
    if(threshold > 0)
    {
			fpIdx = fpIdx <= 1 ? 1014 + fpIdx : fpIdx - 2;
    	for(uint16_t i=0; i<1016; i++)
        {
        	fpIdx = fpIdx == 1015 ? 0 : fpIdx + 1;
        	zn_read_from_device(addr + ( fpIdx << 3 ), 8, fpMemory);
        	uint32_t I_Tmp = fpMemory[0] + (fpMemory[1] << 8) + (fpMemory[2] << 16) + (fpMemory[3] << 24);
        	uint32_t Q_Tmp = fpMemory[4] + (fpMemory[5] << 8) + (fpMemory[6] << 16) + (fpMemory[7] << 24);
        	int32_t  I = I_Tmp > N_1 ? I_Tmp - N : I_Tmp;
        	int32_t  Q = Q_Tmp > N_1 ? Q_Tmp - N : Q_Tmp;
        	double   IQ = sqrt((double)I*I + (double)Q*Q);
            if( IQ > threshold )
            {
            	// fpIdx = fpIdx == 0 ? 1015 : fpIdx - 1;
            	readDoneFlg = 1;
            	break;
        	}
        	else
            {
            	IQ_T_P = IQ_T;
            	IQ_T = IQ;
        	}
    	}
    }
    else
    {
        readDoneFlg = 1;   
    }
    
    if( readDoneFlg ){
				fpIdx += win_startshift;
				if(fpIdx > 1015){
					fpIdx = fpIdx - 1016;
				}
        if(fpIdx < leftLen){
            uint16_t startLeftPoint = (1016 - leftLen) + fpIdx;
            uint8_t  len = leftLen - fpIdx;
            zn_read_from_device(addr + ( startLeftPoint << 3 ), len << 3, cirMemory);
            zn_read_from_device(addr, (g_hal_radar_cfg.cir_tap_len - len) << 3, &cirMemory[len << 3]);
        }
        else if(fpIdx > 1015 - rightLen){
            uint16_t startLeftPoint = fpIdx - leftLen;
            uint8_t len = 1016 - startLeftPoint;
            zn_read_from_device(addr + ( startLeftPoint << 3 ), len << 3, cirMemory);
            zn_read_from_device(addr, (g_hal_radar_cfg.cir_tap_len - len) << 3, &cirMemory[len << 3]);
        }
        else{
            uint16_t startLeftPoint = fpIdx - leftLen;
            zn_read_from_device(addr + ( startLeftPoint << 3 ), g_hal_radar_cfg.cir_tap_len << 3, cirMemory);
        }
    
        // for(int i = 0 ; i < 768; i++)            
        for(int i = 0 ; i < g_hal_radar_cfg.cir_tap_len * 8; i++)
        {
            if( ((i+1) & 0x3) == 0)
            {
                if(IQFlag == 0)
                {
                    buffer_I[readIdx] = ValueTmp > N_1 ? ValueTmp - N : ValueTmp ;
                    buffer_I[readIdx] =  ( buffer_I[readIdx] + (accNum >> 1) )/accNum;
                    IQFlag = 1;
                }
                else
                {
                    buffer_Q[readIdx] =  ValueTmp > N_1 ? ValueTmp - N : ValueTmp ;
                    buffer_Q[readIdx] = ( buffer_Q[readIdx] + (accNum >> 1) ) /accNum;
                    readIdx++;
                    IQFlag = 0;
                }
                ValueTmp = 0;
            }
            else
            {
                ValueTmp += (cirMemory[i] << ((i&0x3)<<3));
            }
        }
		
        if(g_hal_radar_cfg.cir_type)
        {
            for(uint8_t i=0; i<g_hal_radar_cfg.cir_tap_len; i++)
            {
                double I = buffer_I[i] * cs + buffer_Q[i] * si;
                double Q = buffer_Q[i] * cs - buffer_I[i] * si;
                buffer_I[i] = (int32_t)I;
                buffer_Q[i] = (int32_t)Q;
            }
        }
		
    }
    else{
        printf("threshold configured missed\n");
    }
    return readDoneFlg;
}




void hal_send_radar_signle_start(void)
{
    uint32_t regValue;
    uint8_t  tx_msg[1] ={0};
    uint8_t  rx_gain_level;

    // RX0 clock gating
    zn_write_32bit_reg(0x1874, 0x5);

//    zn_write_32bit_reg(0x084C, 0x82210000);
    // TX Message
    zn_write_tx_data(1, tx_msg, 0); //Zero offset in TX buffer.
    zn_write_tx_frame_ctrl(3, 0, 0); //Zero offset in TX buffer, no ranging.

   
    zn_write_32bit_reg(0x1848, 0x12080504);
    udelay(10);

    zn_write_32bit_reg(0x1848, 0x52080504);

}



void hal_radar_tx_rx1_rx2_frame_proc()
{
    uint32_t reg = zn_read_32bit_reg(0x105c);
    if(reg == 0xfc001500)
    {
        g_ant_id = 0;
        hal_gp_timer_close(TIMER1);
        zn_write_32bit_reg(0x105c, 0xfc001900);
        hal_send_radar_signle_start();
    }
    else if(reg == 0xfc001900)
    {
        g_ant_id = 1;
        zn_write_32bit_reg(0x105c, 0xfc001500);
        hal_gp_timer_start(TIMER1);
    }
}

uint8_t hal_radar_four_t_r_mode_frame_proc()
{
    uint8_t ret = FALSE;
    uint8_t seq = hal_radar_four_t_r_mode_find_next_valid_swtich();
    if(0xff == seq)              /*  */
    {
        hal_radar_four_t_four_r_switch_status_init();
        hal_gp_timer_start(TIMER1);
        ret = TRUE;
    }
    else
    {
        g_ant_id = seq;
        g_hal_radar_ant_switch_seq[seq].pre_status = TRUE;
        hal_radar_four_t_r_mode_sel(seq);
        hal_gp_timer_close(TIMER1);
        hal_send_radar_signle_start();
        ret = FALSE;
    }
    return ret;

}


void printf_cir(int32_t *buffer_I, int32_t *buffer_Q)
{
    uint8_t index =0;
    for(index = 0; index < g_hal_radar_cfg.cir_tap_len;index++ )
    {
        printf("%d ",(uint32_t)sqrt(buffer_I[index]*buffer_I[index] + buffer_Q[index]*buffer_Q[index]));
        
    }
    printf("\r\n");
//    for(index = 0; index < g_radar_confg.cir_tap_len;index++ )
//    {
//        printf("%d ",buffer_I[index]);
//        
//    }
//    printf("\r\n");
//    for(index = 0; index < g_radar_confg.cir_tap_len;index++ )
//    {
//        printf("%d ",buffer_Q[index]);
//        
//    }
//    printf("\r\n");    
}
void hal_radar_data_proc(void)
{
    uint8_t ant_id = 0;
    zn_write_32bit_reg(0x1848, 0x02080504);
    
    if((zn_read_32bit_reg(IP_NACC1_ID) >> IP_NACC0_BIT_OFFSET) < g_hal_radar_cfg.acc_Threshold)
    {
        printf("nacc is error\r\n");
        return;
    }

    if(zn_readcirmemery_iprx1(g_buffer_I, g_buffer_Q))
    {
        if(g_cali_flag != TRUE)
        { 
            //user algorithm
            if(g_hal_radar_cfg.user_algo_flag != 0)
            {
                user_radar_call_back(g_buffer_I, g_buffer_Q,g_ant_id);  
                if(g_hal_radar_cfg.radar_ant_type == ONE_T_ONE_R_MODE)
                {
                    g_ant_id = 0;
                }
                else if(g_hal_radar_cfg.radar_ant_type == ONE_T_TWO_R_MODE)
                {
                    hal_radar_tx_rx1_rx2_frame_proc();
                }
                else if(g_hal_radar_cfg.radar_ant_type == FOUR_T_FOUR_R_MODE)
                {
                    hal_radar_four_t_r_mode_frame_proc();
                }   
              
            }
            else //uart output
            {   
                //send_IQ_data_to_uart(g_buffer_I, g_buffer_Q);
                if(g_hal_radar_cfg.radar_ant_type == ONE_T_ONE_R_MODE)
                {
                    g_ant_id = 5;
                    //send_ant_IQ_data_to_uart(g_buffer_I, g_buffer_Q,ant_id);
                    g_send_cir_data_done = TRUE;  
                }
                else if(g_hal_radar_cfg.radar_ant_type == ONE_T_TWO_R_MODE)
                {
                    //g_ant_num = send_tx_rx1_rx2_frame_proc();
                }
                else if(g_hal_radar_cfg.radar_ant_type == FOUR_T_FOUR_R_MODE)
                {
                    //send_tx_rx_swtich_frame_proc();
                }
                
            }
        }
        
        g_cali_flag = FALSE;
        
        zn_force_trx_off();
    }
}
