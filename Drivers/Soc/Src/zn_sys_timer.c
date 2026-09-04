#include "zn_sys_timer.h"


 
static SysTimerCallback systimer_callbackFunc = NULL;
uint32_t systimer_get_cur_val(void)
{
    return  read_mreg32(SYSTIMER_REG_SYSTIMER_TIMER_REG); 
}

void systimer_timer_clear(uint8_t en)
{
    if(en)
    {
        set_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_CLEAR_SHIFT);
    }
    else
    {
        clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_CLEAR_SHIFT);
    }
}



void systimer_timer_pause(uint8_t en)
{
    if(en)
    {
        set_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_PAUSE_SHIFT);
    }
    else
    {
        clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_PAUSE_SHIFT);
    }
}

void systimer_timer_run(void)
{
    clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_CLEAR_SHIFT);
    clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_PAUSE_SHIFT);
}


int32_t systimer_cmp_channel_ctrl(uint32_t channel_id,uint8_t status)
{

    int32_t ret = -1; 
    if(channel_id<CMP_CHANNEL_NUM && status<2)
    {
        if (ENABLE == status)
        {
            clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_PAUSE_SHIFT);
            clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG_CLEAR_SHIFT);
            set_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,channel_id);
        }
        else
        {
            clear_bit(SYSTIMER_REG_SYSTIMER_CMP_CTRL_REG,channel_id);
        }
        ret = 0;
    }

    return ret;
}





int32_t systimer_cap_channel_ctrl(uint32_t channel_id,uint8_t status)
{
    int32_t ret = -1; 
    if(channel_id<CAP_CHANNEL_NUM && status<2)
    {
        if (ENABLE == status)
        {
            set_bit(SYSTIMER_REG_SYSTIMER_CAP_CTRL_REG,channel_id);
        }
        else
        {
            clear_bit(SYSTIMER_REG_SYSTIMER_CAP_CTRL_REG,channel_id);
        }
        ret = 0;
    }


    return ret;
}



int32_t systimer_cap_set_edge_mode(uint32_t channel_id,SYSTIMER_CapGpioEdgeType mode)
{
    int32_t ret = -1; 
    uint32_t val = 0;
    if(channel_id<CAP_CHANNEL_NUM)
    {
        val = read_mreg32(SYSTIMER_REG_SYSTIMER_CAP_EDGE_REG);
        clear_bit(val, (2*channel_id));
        clear_bit(val, (2*channel_id+1));
        val |= (mode<<(2*channel_id));
        write_mreg32(SYSTIMER_REG_SYSTIMER_CAP_EDGE_REG, val);
        ret = 0;
    }
    return ret;    
}


int32_t systimer_cap_get_edge_mode(uint32_t channel_id,SYSTIMER_CapGpioEdgeType *mode)
{
    int32_t ret = -1; 
    if(channel_id<CAP_CHANNEL_NUM && mode != NULL)
    {
        *mode = (read_mreg32(SYSTIMER_REG_SYSTIMER_CAP_EDGE_REG)>>(2*channel_id))&0x03;
        ret = 0;
    }
    return ret;    
}


int32_t systimer_cmp_set_compare_value(uint32_t channel_id,uint32_t value)
{
    int32_t ret = -1; 
    if(channel_id<CMP_CHANNEL_NUM)
    {
        write_mreg32(SYSTIMER_REG_SYSTIMER_CMP_VALUE_REG(channel_id),value);
        ret = 0;
    }

    return ret;    
}

int32_t systimer_cmp_get_compare_value(uint32_t *value)
{
    int32_t ret = -1; 
    if(NULL != value)
    {
        *value = read_mreg32(SYSTIMER_REG_SYSTIMER_TIMER_REG);
        ret = 0;
    }

    return ret;    
}

int32_t systimer_cap_set_gpio_sel(uint32_t channel_id,uint8_t gpio_pin)
{
    int32_t ret = -1; 
    uint32_t val = 0;
    if(channel_id<CAP_CHANNEL_NUM)
    {        
        val = read_mreg32(SYSTIMER_REG_SYSTIMER_CAP_GPIO_SEL_REG);
        val &= ~(0x1F<<(8*channel_id));
        val |=(gpio_pin<<(8*channel_id));
        write_mreg32(SYSTIMER_REG_SYSTIMER_CAP_GPIO_SEL_REG, val);
        ret = 0; 
    }

    return ret;    
}


int32_t systimer_cap_get_gpio_sel(uint32_t channel_id,uint8_t *gpio_pin)
{
    int32_t ret = -1; 
    uint32_t val = 0;
    if(channel_id<CAP_CHANNEL_NUM && gpio_pin!=NULL)
    {        
        val = read_mreg32(SYSTIMER_REG_SYSTIMER_CAP_GPIO_SEL_REG);
        *gpio_pin = (val >> (8*channel_id))&0x1F;
        ret = 0; 
    }

    return ret;    
}
int32_t systimer_get_cap_val(uint8_t channel_id, uint32_t *capval)
{
    int32_t ret = -1;
    if(channel_id<CAP_CHANNEL_NUM && NULL != capval)
    {
        *capval =read_mreg32(SYSTIMER_REG_SYSTIMER_CAP_VALUE_REG(channel_id));
        ret = 0;
    }
    return ret;
}

int32_t systimer_cap_set_irq_enable(uint32_t channel_id)
{
    int32_t ret = -1; 
    if(channel_id<CAP_CHANNEL_NUM)
    {
        clear_bit(SYSTIMER_REG_SYSTIMER_INT_MASK,(channel_id+9));
        ret = 0; 
    }
    return ret;
}


int32_t systimer_cap_set_irq_disable(uint32_t channel_id)
{
    int32_t ret = -1; 
    if(channel_id<CAP_CHANNEL_NUM)
    {
        set_bit(SYSTIMER_REG_SYSTIMER_INT_MASK,(channel_id+9));
        ret = 0; 
    }
    return ret;
}

int32_t systimer_cmp_set_irq_enable(uint32_t channel_id)
{
    int32_t ret = -1; 
    if(channel_id<CMP_CHANNEL_NUM)
    {
        clear_bit(SYSTIMER_REG_SYSTIMER_INT_MASK,(channel_id));
        ret = 0; 
    }
    return ret;
}

int32_t systimer_ovf_set_irq_enable(void)
{
    clear_bit(SYSTIMER_REG_SYSTIMER_INT_MASK,SYSTIMER_REG_SYSTIMER_INT_MASK_OVF_IRQ_MASK_SHIFT);
    return 0;
}

int32_t systimer_ovf_set_irq_disable(void)
{
    set_bit(SYSTIMER_REG_SYSTIMER_INT_MASK,SYSTIMER_REG_SYSTIMER_INT_MASK_OVF_IRQ_MASK_SHIFT);
    return 0;
}

int32_t systimer_cmp_set_irq_disable(uint32_t channel_id)
{
    int32_t ret = -1; 
    if(channel_id<CMP_CHANNEL_NUM)
    {
        set_bit(SYSTIMER_REG_SYSTIMER_INT_MASK,(channel_id));
        ret = 0; 
    }
    return ret;
}


void systimer_clear_irq_status(void)
{
    write_mreg32(SYSTIMER_REG_SYSTIMER_INT_RAW, read_mreg32(SYSTIMER_REG_SYSTIMER_INT_RAW));
}
uint32_t systimer_get_irq_status(void)
{
    return read_mreg32(SYSTIMER_REG_SYSTIMER_INT_STATUS);
}
void systimer_set_callback(SysTimerCallback callback)
{
    systimer_callbackFunc = callback;
}
void SYSTIM_IRQHandler(void)
{
    uint32_t irq_status = systimer_get_irq_status();
    systimer_clear_irq_status();
    if(NULL != systimer_callbackFunc)
    {
        systimer_callbackFunc(irq_status);
    }
}

void systimer_cap_init(SYSTIMER_CfgCapType *capConfig)
{
    systimer_cap_set_edge_mode(capConfig->capId,capConfig->capMode);
    systimer_cap_set_gpio_sel(capConfig->capId,capConfig->gpio_pin);
    if (capConfig->interruptEn)
    {
        systimer_cap_set_irq_enable(capConfig->capId);
        systimer_ovf_set_irq_enable();
        NVIC_EnableIRQ(SYSTEMTIM_IRQn);
    }
}


void systimer_cmp_init(SYSTIMER_CfgCmpType *cmpConfig)
{
    systimer_cmp_set_compare_value(cmpConfig->cmpId,cmpConfig->cmpval);
    if(cmpConfig->interruptEn)
    {
        systimer_cmp_set_irq_enable(cmpConfig->cmpId);
        systimer_ovf_set_irq_enable();
        NVIC_EnableIRQ(SYSTEMTIM_IRQn);
    }
}