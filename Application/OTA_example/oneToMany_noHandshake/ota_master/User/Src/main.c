//#include "ota.h"
#include "range.h"
#include "hal_soc.h"
#include "hal_uwb.h"
#include "hal_flash.h"

uint8_t g_soft_ver[4] = {0x20,0x26,0x05,0x31};
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