#include "hal_radar.h"
#include "phy_cmd.h"
#include "phy_test.h"
#include "gconfig.h"
#include "user_app.h"
#include "math.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "cmd.h"
#include "tuwb.h"
#include "test_mode.h"

int32_t g_buffer_i_frame0[16][64]; 
int32_t g_buffer_q_frame0[16][64];
uint32_t g_ant_list[16] = {0};

static uint32_t g_framae_count = 0;



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

    g_ant_list[ant_id] = 1;
    for(uint8_t i =0 ; i<uwb_instance.radar_config.tap_len ; i++)
    {
        g_buffer_i_frame0[ant_id][i]  = buffer_i[i];
        g_buffer_q_frame0[ant_id][i]  = buffer_q[i];
    }
    g_framae_count++;
    
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
//               printf("ant_id=%d, framae_idx=%d\r\n", index, g_framae_count);
               debug_radar_printf(g_buffer_i_frame0[index],g_buffer_q_frame0[index]);
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

    user_app_proc();
}