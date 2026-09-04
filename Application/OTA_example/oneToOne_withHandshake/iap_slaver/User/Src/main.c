#include "iap_boot_ota.h"
#include "hal_uwb.h"
#include "hal_soc.h"
#include "hal_flash.h"
#include "ota.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_sleep.h"

static uint8_t s_range_recv_buf[100]        = {0};
#define LED_PIN                             GPIO_PIN3
volatile uint8_t slave_rx_ok_flag = 0;
volatile uint8_t slave_rx_error_flag = 0;
volatile uint8_t slave_rx_timeout_flag = 0;
volatile uint8_t slave_rx_cp_error_flag = 0;
volatile uint8_t slave_tx_done_flag = 0;

hal_uwb_instance_t uwb_instance = 
{
    .phy_config = 
    {
        .channel_num = CHANNEL_5,
        .tia_level = 4,
        .frame_type = RFRAME_SP0,
        .preamble_code_idx = PREAMBLE_CODE_INDEX_24,
        .sfd_id = SFD_ID_SFD8,
        .psdu_data_rate= PSDU_RATE_681,
        .bprf_phr_data_rate = BPRF_PHR_RATE_850,
        .preamble_duration = PREAMBLE_128,
        .prf_mode = PRF_624,
        .pa_level = PA_LEVEL_7,
        .sts_seg_num = STS_SEG_1,
        .sts_seg_len = STS_SEG_LEN_64,
        .sfd_to = 128 + 8, //preamble len + sfd len
        .ant_delay = 13077,
        .rx_ts_left_find_len = 70,
        .rx_ts_thresold_len = 200,
    },
    
    .aoa_config = 
    {
        .aoa_en = 0,
        .aoa_mode = TYPE_AOA,
        .aoa_dimension_mode = TYPE_2D,
        .ant_sel = RX2_INPUT,
        .phase_compen_rx0_rx1 = 0.0,
        .phase_compen_rx0_rx2 = 0.0,
        .ant_distance_rx0_rx1 = 1.8,
        .ant_distance_rx0_rx2 = 1.8,
        .ant_distance_rx1_rx2 = 1.8,
        .delay_rx0_rx1 = 0,
    },

    .interrupt_config = 
    {
        .bits.bit0_int_en = 1,
        .bits.bit7_tx_frs = 1,
        .bits.bit8_rx_prd = 1,
        .bits.bit9_rx_sfdd = 1,
        .bits.bit14_rx_fcg = 1,
        .bits.bit13_rx_dfr = 1,
        .bits.bit28_rx_cperr = 1,
        .bits.bit17_rx_rfto = 1,
        .bits.bit26_rx_sfdto = 1,
    },

    .fem_en = 0,
    .rx_ts_retry_en = 1,
    .delay_mode = MODE_UNBLOCK,
    .driver_timer_id = TIMER0
};

static void tx_done_proc(const zn_cb_data_t *cb_data)
{
    slave_tx_done_flag = 1;
}
void rx_ok_proc(const zn_cb_data_t *rx_data)
{
    printf("rx ok\n");
    
    if((!rx_data) || (0 == rx_data->data_length) || (rx_data->data_length > 100))
    {
        printf("The Frame is NULL!");

        return;
    }

    zn_read_rx_data(s_range_recv_buf, rx_data->data_length);
    if(!memcmp(s_range_recv_buf, g_ota_req_msg_head, 3))
    {
        OTA_Slave_Req_Proc(s_range_recv_buf);
        slave_rx_ok_flag = 1;
        return;
    }
}

void rx_error_proc(const zn_cb_data_t *rx_data)
{
    slave_rx_error_flag = 1;
    printf("rx err\n");
}

void rx_cp_err_proc(const zn_cb_data_t *rx_data)
{
    slave_rx_cp_error_flag = 1;
    printf("rx cp err\n");
}

void rx_timeout_proc(const zn_cb_data_t *rx_data)
{
    slave_rx_timeout_flag = 1;
    printf("rx timeout\n");
}

static void uwb_irq_init(hal_uwb_interrupt_callback_t *irq_callback)
{
    irq_callback->cb_tx_done = &tx_done_proc;
    irq_callback->cb_rx_ok = &rx_ok_proc;
    irq_callback->cb_rx_err = &rx_error_proc;
    irq_callback->cb_cp_err = &rx_cp_err_proc;
    irq_callback->cb_rx_timeout = &rx_timeout_proc;
}

static void uwb_init(void)
{
    uint16_t num = 0;
    hal_uwb_phy_config_t *uwb_phy_config = &uwb_instance.phy_config;
    hal_uwb_interrupt_callback_t *uwb_irq_callback = &uwb_instance.interrupt_callback;

    uwb_irq_init(uwb_irq_callback);
    hal_uwb_config_init(&uwb_instance);
    printf("begin rx\n");
    while(num < 4)
    {
        hal_force_uwb_off();
        hal_uwb_set_rx_timeout(50000);
        hal_uwb_immediate_rx();
        while((!slave_rx_cp_error_flag) && (!slave_rx_error_flag) && (!slave_rx_ok_flag) && (!slave_rx_timeout_flag));
        num++;
        if(slave_rx_ok_flag)
        {
            ota_info.status = UP_STATUS_SLAVE_OTA_RSP;
            while(1)
            {
                OTA_Loop();
            }
        }
        slave_rx_cp_error_flag = 0;
        slave_rx_error_flag = 0;
        slave_rx_timeout_flag = 0;
        slave_rx_ok_flag = 0;
    }
}
static void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 1;
    uart_cfg.baurdrate = B115200;
    uart_cfg.func = NULL;
    
    hal_uart_init(&uart_cfg);
  
    hal_gpio_set_tx_en_mode(GPIO_PIN13);
    hal_gpio_set_rx_en_mode(GPIO_PIN2);
    hal_gpio_set_output_default_config(LED_PIN);
}
int main()
{
    user_init();
    printf("iap running\n");
    hal_soc_init();
    uint8_t ret = hal_sleep_get_wakeup_status();
    if(WAKEUP_BY_AUTO_CNT != ret)
    {
        uwb_init();
    }
    iap_boot_proc();
}