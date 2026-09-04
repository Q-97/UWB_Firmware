#include "zn_interface.h"
typedef struct _radar_cfg
{
    uint8_t     pulse_type;
    uint16_t    tx_power_level;
    uint8_t     rx_gain_level;
    uint8_t     preamble_length;
    uint32_t    fp_threshold;
    uint8_t     cir_tap_len;
    uint16_t    frame_interval;
    uint16_t    acc_Threshold;
    uint8_t     win_leftLen;
    uint8_t     win_startshift;
    uint8_t     cir_type;
    uint8_t     user_algo_flag;
    uint32_t    timeout;
    uint8_t     radar_ant_type;
}hal_old_radar_cfg;

void hal_radar_old_init();
void hal_send_radar_signle_start(void);
void hal_radar_data_proc(void);
void user_cir_data(int32_t *buffer_i,int32_t *buffer_q,uint8_t ant_id);
void hal_radar_old_timer_init(uint8_t timer_id);