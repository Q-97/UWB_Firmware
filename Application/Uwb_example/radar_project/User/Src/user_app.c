#include "hal_radar.h"
#include "phy_cmd.h"
#include "phy_test.h"
#include "gconfig.h"
#include "user_app.h"
#include "math.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "hal_uwb.h"
#include "cmd.h"
#include "tuwb.h"
#include "test_mode.h"

#define TS_LOG_EN 0

int32_t g_buffer_i_frame0[16][64]; 
int32_t g_buffer_q_frame0[16][64];
uint32_t g_ant_list[16] = {0};

static uint32_t g_frame_count = 0;

volatile uint32_t ts_t1, ts_radar_start, ts_radar_irq, ts_cp0, ts_cp1;
uint32_t g_ts_t1[16], g_ts_radar_start[16], g_ts_radar_irq[16], g_ts_cp0[16], g_ts_cp1[16];
volatile uint32_t s_timer1_cnt;

extern void debug_radar_printf(int32_t *buffer_i,int32_t *buffer_q);

/*************************************************************************************************************
* Description: This function is used to get cir data.
* Input param: 
* Output param:
    buffer_i : I-channel
    buffer_q : Q-channel
    ant_id   : IQ-chnnel antenna id
* Return value: None
*************************************************************************************************************/
void user_radar_call_back(int32_t *buffer_i,int32_t *buffer_q,uint8_t ant_id)
{
    ts_cp0 = hal_get_cur_sys_time();

    g_ant_list[ant_id] = 1;
    for(uint8_t i =0 ; i<uwb_instance.radar_config.tap_len ; i++)
    {
        g_buffer_i_frame0[ant_id][i]  = buffer_i[i];
        g_buffer_q_frame0[ant_id][i]  = buffer_q[i];
    }
    g_frame_count++;

    ts_cp1 = hal_get_cur_sys_time();
    g_ts_t1[ant_id]          = ts_t1;           //[TS] t1:TIMER1帧定时中断
    g_ts_radar_start[ant_id] = ts_radar_start;  //[TS] t2:下发采集启动命令
    g_ts_radar_irq[ant_id]   = ts_radar_irq;    //[TS] t3:雷达采集完成中断
    g_ts_cp0[ant_id]         = ts_cp0;          //[TS] t4:进入拷贝回调
    g_ts_cp1[ant_id]         = ts_cp1;          //[TS] t5:拷贝完成
}

void debug_radar_printf(int32_t *buffer_i,int32_t *buffer_q)
{    
    for(uint8_t j=0; j<uwb_instance.radar_config.tap_len; j++)
    {
        printf("%d %d ",buffer_i[j], buffer_q[j]);
    }
    printf("\n");
//    for(uint8_t j=0; j<uwb_instance.radar_config.tap_len; j++)
//    {
//        printf("%d ",buffer_i[j]);
//    }
//    printf("\n");    
//    for(uint8_t j=0; j<uwb_instance.radar_config.tap_len; j++)
//    {
//        printf("%d ",buffer_q[j]);
//    }
//    printf("\n");      
}


/*************************************************************************************************************
* Description: This function is used to add algrothim.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void user_app_proc()
{
    if(g_radar_done_flag == 1) // 
    {
        /*add user code*/
        /*eg*/
        g_radar_done_flag = 0;
        for(uint8_t index = 0;index < 16;index++)
        {
           if(g_ant_list[index] ==1)
           {
               g_ant_list[index] = 0;
               printf("index= %d\r\n",index);

                #if TS_LOG_EN   //[TS]
                               printf("[TS] ant=%d t1=%u st=%u irq=%u cp0=%u cp1=%u\r\n", index,
                                      g_ts_t1[index], g_ts_radar_start[index], g_ts_radar_irq[index],
                                      g_ts_cp0[index], g_ts_cp1[index]);
                #endif          //[TS]

              // printf("ant_id=%d, framae_idx=%d\r\n", index, g_framae_count);
              //  debug_radar_printf(g_buffer_i_frame0[index],g_buffer_q_frame0[index]);
           }
        }
    }

}


void user_loop(void)
{
    phy_cmd_t* phy_cmd = get_phy_cmd_addr();

    phy_test_loop();
    
    uci_cmd_recv_loop();
    
    uwbs_loop();
    
    if(phy_cmd->phy_debug_flag == WORK_MODE_PHY_DEBUG)
    {
        return;
    }

    test_mode_loop();

    // static uint8_t s_calib_done = 0;
    // if(s_calib_done == 0)
    // {
    //     s_calib_done = 1;
    //
    //     uint32_t u0 = hal_get_cur_sys_time();
    //     hal_delay_ms(100);              //墙钟100ms(38.4M晶体,可靠)
    //     uint32_t u1 = hal_get_cur_sys_time();
    //     printf("[TS] uwb_tick_per_100ms=%u  ->  per_ms=%u\r\n",
    //            (uint32_t)(u1-u0), (uint32_t)((u1-u0)/100));   //UWB计数器速率
    //
    //     s_timer1_cnt = 0;
    //     hal_delay_ms(5000);             //墙钟5秒,期间TIMER1正常触发
    //     printf("[TS] timer1_cnt_in_5s=%u  (周期=5000/该值 ms)\r\n", s_timer1_cnt);  //TIMER1真实周期
    // }

    user_app_proc();
}