#include "iap_boot.h"
#include "hal_uwb.h"
#include "hal_soc.h"
#include "hal_flash.h"

hal_uwb_instance_t uwb_instance = 
{
    .phy_config = 
    {
        .channel_num = CHANNEL_9,
    }
};


int main()
{
    hal_soc_init();
    iap_boot_proc();
}