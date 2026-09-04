#ifndef __HAL_RADAR_ANT_H
#define __HAL_RADAR_ANT_H

#include "hal_radar.h"
#include "zn_radar.h"

typedef struct hal_radar_ant_status
{
    uint8_t    ant_seq;
    uint8_t    valid;
    uint8_t    pre_status;
}hal_radar_ant_status_t;

extern hal_radar_ant_status_t g_hal_radar_ant_switch_seq[MAX_TX_RX_SWITCH_NUM + 1];

void hal_ant_four_t_r_mode_ant_gpio_init();
void hal_ant_two_t_two_r_ant_init();
uint8_t hal_ant_get_four_t_four_r_valid_ant_num(void);
#endif