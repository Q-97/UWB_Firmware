#include "zn_radar.h"
#include "zn_soc.h"
#include "hal_gpio.h"
#include "hal_ant.h"

hal_radar_ant_status_t g_hal_radar_ant_switch_seq[MAX_TX_RX_SWITCH_NUM + 1] = 
{
    {TX_SWTICH1_RX_SWITCH1,FALSE,FALSE},
    {TX_SWTICH1_RX_SWITCH2,FALSE,FALSE},
    {TX_SWTICH1_RX_SWITCH3,FALSE,FALSE},
    {TX_SWTICH1_RX_SWITCH4,FALSE,FALSE},
    {TX_SWTICH2_RX_SWITCH1,TRUE,FALSE},
    {TX_SWTICH2_RX_SWITCH2,TRUE,FALSE},
    {TX_SWTICH2_RX_SWITCH3,TRUE,FALSE},
    {TX_SWTICH2_RX_SWITCH4,TRUE,FALSE},
    {TX_SWTICH3_RX_SWITCH1,FALSE,FALSE},
    {TX_SWTICH3_RX_SWITCH2,FALSE,FALSE},
    {TX_SWTICH3_RX_SWITCH3,FALSE,FALSE},
    {TX_SWTICH3_RX_SWITCH4,FALSE,FALSE},
    {TX_SWTICH4_RX_SWITCH1,FALSE,FALSE},
    {TX_SWTICH4_RX_SWITCH2,FALSE,FALSE},    
    {TX_SWTICH4_RX_SWITCH3,FALSE,FALSE},
    {TX_SWTICH4_RX_SWITCH4,FALSE,FALSE},     
    {MAX_TX_RX_SWITCH_NUM,FALSE,FALSE}, 
};

void hal_ant_four_t_r_mode_ant_gpio_init()
{    
    hal_gpio_set_output_default_config(RX2_V1);
    hal_gpio_set_output_default_config(RX2_V2);
    hal_gpio_set_output_default_config(TRX_V1);
    hal_gpio_set_output_default_config(TRX_V2);
    zn_radar_four_t_r_mode_sel(TX_SWTICH1_RX_SWITCH1);
    for(uint8_t index = 0; index < MAX_TX_RX_SWITCH_NUM ;index++)
    {
        zn_radar_ant_switch_seq[index].ant_seq = g_hal_radar_ant_switch_seq[index].ant_seq;
        zn_radar_ant_switch_seq[index].pre_status = g_hal_radar_ant_switch_seq[index].pre_status;
        zn_radar_ant_switch_seq[index].valid = g_hal_radar_ant_switch_seq[index].valid;
    }
    
}

void hal_ant_two_t_two_r_ant_init(void)
{
//    hal_gpio_set_output_default_config(TRX_SWITCH);
    hal_gpio_set_output_default_config(GPIO_PIN7);
    hal_gpio_set_output_default_config(GPIO_PIN0);
}
uint8_t hal_ant_get_four_t_four_r_valid_ant_num(void)
{
    uint8_t vaild_ant_num = 0;
    for(uint8_t index = 0; index < MAX_TX_RX_SWITCH_NUM ;index++)
    {
        if(TRUE == g_hal_radar_ant_switch_seq[index].valid)
        {
            vaild_ant_num++;
        }
    }
    return vaild_ant_num;
}
