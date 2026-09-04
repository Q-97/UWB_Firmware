#include "range.h"
#include "hal_soc.h"
#include "hal_uwb.h"
#include "hal_flash.h"
#include "ota.h"

volatile uint8_t slave_tx_done_flag = 0;

int main(void)
{
    hal_soc_init();
    
    user_init();
    range_init();
    LOG_INFO("ota project initial done");


    while (1)
    {
        range_loop();
    }

    return 0;
}