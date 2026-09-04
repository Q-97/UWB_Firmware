/*****************************************************************************
 *  File: zn_gpio.c
 *
 *  Descirption: contains the functions support gpio driver.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2023-4-22
 *
 *****************************************************************************/


#include "zn_gpio.h"


GPIO_EventCallback s_gpioCallback[2] = {NULL};



/**
* gpio_set_dir
*
* @param[in] gpioNum: GPIO number(GPIO_PIN0-GPIO_PIN22)
* @param[in] pinMode:  0 - Input,1 - Output
* @return    0: success, -1: GPIO_PinNum is too large
*
* @brief  Set a GPIO pin's pin mode
*/
int32_t gpio_set_dir(GPIO_PinType gpioNum, GPIO_Direction pinDir)
{
    if (GPIO_MODE_OUTPUT > 1)
    {
        return -1;
    }
    if (gpioNum<GPIO_PIN32)
    {
        if (GPIO_MODE_OUTPUT == pinDir)
        {
            GPIOA_SET_OUTPUT(gpioNum);
        }
        else
        {
            GPIOA_SET_INPUT(gpioNum);
        }
    }
    else
    {
           if (GPIO_MODE_OUTPUT == pinDir)
        {
            GPIOB_SET_OUTPUT(gpioNum-32);
        }
        else
        {
            GPIOB_SET_INPUT(gpioNum-32);
        }
    }
    return 0;
}

/**
* gpio_get_pin_value
*
* @param[in] gpioNum: GPIO number(GPIO_PIN0-GPIO_PIN22)
* @return    GPIO Pin input value:0-low level,1-High level
*
* @brief  Get GPIO pin input value
*/
int32_t gpio_get_pin_value(GPIO_PinType gpioNum)
{    
    if (gpioNum<GPIO_PIN32)
    {
        return GPIOA_READ_BITS(gpioNum);
    }
    else
    {
        return GPIOB_READ_BITS(gpioNum-GPIO_PIN32);
    }
}



/**
* gpio_set_pin_value
*
* @param[in] gpioNum: GPIO number(GPIO_PIN0-GPIO_PIN22)
* @param[in] pinValue: GPIO Pin output value. 1:High   0:Low
* @return    0: success, -1:fail
*
* @brief  Set GPIO pin output value
*/
int32_t gpio_set_pin_value(GPIO_PinType gpioNum, uint32_t pinValue)
{
    if (pinValue > 1)
    {
        return -1;
    }
    if (gpioNum<GPIO_PIN32)
    {
        if (1 == pinValue)
        {
            GPIOA_SET_BITS(gpioNum);
        }
        else
        {    
            GPIOA_RESET_BITS(gpioNum);
        }
    }
    else
    {
        if (1 == pinValue)
        {
            GPIOB_SET_BITS(gpioNum-GPIO_PIN32);
        }
        else
        {    
            GPIOB_RESET_BITS(gpioNum-GPIO_PIN32);
        }
    }
    return 0;
}
/**
* gpio_get_int_flag
*
* @param[in] none
*
* @return flag: GPIO  interrupt status
*
* @brief   Get gpio interrupt status
*/
uint32_t gpio_get_int_flag(void)
{
    uint32_t flag;

    flag = read_mreg32(GPIO_INTSTATUS);
    return flag;
}


/**
* gpio1_get_int_flag
*
* @param[in] none
*
* @return flag: GPIO1  interrupt status
*
* @brief   Get gpio1 interrupt status
*/
uint32_t gpio1_get_int_flag(void)
{
    uint32_t flag;

    flag = read_mreg32(GPIO1_INTSTATUS);
    return flag;
}


/**
* gpio_get_int_rawflag
*
* @param[in] none
*
* @return flag: GPIO  raw interrupt status
*
* @brief   Get gpio raw interrupt status
*/
uint32_t gpio_get_int_rawflag(void)
{
    uint32_t rawFlag;

    rawFlag = read_mreg32(GPIO_RAW_INTSTATUS);
    return rawFlag;
}


/**
* gpio1_get_int_rawflag
*
* @param[in] none
*
* @return flag: GPIO1  raw interrupt status
*
* @brief   Get gpio1 raw interrupt status
*/
uint32_t gpio1_get_int_rawflag(void)
{
    uint32_t rawFlag;

    rawFlag = read_mreg32(GPIO1_RAW_INTSTATUS);
    return rawFlag;
}
/**
* gpio_clr_int_flag
*
* @param[in] 
*
* @return  0: success, -1:fail
*
* @brief clear gpio interrupt flag
*/
void gpio_clr_int_flag(uint32_t intStatus)
{
    write_mreg32(GPIO_PORTA_EOI, intStatus);
}


/**
* gpio1_clr_int_flag
*
* @param[in] 
*
* @return  0: success, -1:fail
*
* @brief clear gpio1 interrupt flag
*/
void gpio1_clr_int_flag(uint32_t intStatus)
{
    write_mreg32(GPIO1_PORTA_EOI, intStatus);
}

/**
* gpio_int_config
*
* @param[in] gpioNum: GPIO number(GPIO_PIN0-GPIO_PIN22)
* @param[in] intTriggerType: GPIO Inttrupt Trigger Type(GPIO_TRIGGER_FALLING-GPIO_TRIGGER_LEVEL_HIGH)
*
* @@return  0: success, -1:fail
*
* @brief config gpio interrupt trigger type
*/
int32_t gpio_int_config(GPIO_PinType pinNum, GPIO_IntTriggerType intTriggerType)
{
    if (intTriggerType >GPIO_TRIGGER_LEVEL_HIGH)
    {
        return -1;
    }
    
    /*gpio_pin interrupt disable*/
    GPIOA_INT_DISABLE(pinNum);

    switch (intTriggerType)
    {
        case GPIO_TRIGGER_FALLING:
            GPIOA_SET_ONE_EDGE(pinNum);
            GPIOA_SET_INTTYPE_EDGE(pinNum);
            GPIOA_SET_POLARITY_LOW(pinNum);
        break;
        
        case GPIO_TRIGGER_RISING:
            GPIOA_SET_ONE_EDGE(pinNum);
            GPIOA_SET_INTTYPE_EDGE(pinNum);
            GPIOA_SET_POLARITY_HIGH(pinNum);
        break;
        
        case GPIO_TRIGGER_RISING_FALLING:
            GPIOA_SET_BOTH_EDGE(pinNum);
            GPIOA_SET_INTTYPE_EDGE(pinNum);
        break;
        
        case GPIO_TRIGGER_LEVEL_LOW:
            GPIOA_SET_ONE_EDGE(pinNum);
            GPIOA_SET_INTTYPE_LEVEL(pinNum);
            GPIOA_SET_POLARITY_LOW(pinNum);
        break;
        
        case GPIO_TRIGGER_LEVEL_HIGH:
            GPIOA_SET_ONE_EDGE(pinNum);
            GPIOA_SET_INTTYPE_LEVEL(pinNum);
            GPIOA_SET_POLARITY_HIGH(pinNum);
        break;
        
        default:
        break;
    }
    
    GPIOA_DEBOUNCE_ENABLE(pinNum);
    GPIOA_INT_ENABLE(pinNum);
    GPIOA_INT_UNMASK(pinNum);
    
    /*Clear spurious interrupts*/
    gpio_clr_int_flag(1<<(pinNum));
    NVIC_ClearPendingIRQ(GPIO_IRQn);
    NVIC_EnableIRQ(GPIO_IRQn);
    
    
    return 0;
}

/**
* gpio1_int_config
*
* @param[in] gpioNum: GPIO number(GPIO_PIN0-GPIO_PIN22)
* @param[in] intTriggerType: GPIO Inttrupt Trigger Type(GPIO_TRIGGER_FALLING-GPIO_TRIGGER_LEVEL_HIGH)
*
* @@return  0: success, -1:fail
*
* @brief config gpio interrupt trigger type
*/
int32_t gpio1_int_config(GPIO_PinType pinNum, GPIO_IntTriggerType intTriggerType)
{
    if (intTriggerType >GPIO_TRIGGER_LEVEL_HIGH)
    {
        return -1;
    }
    /*gpio_pin interrupt disable*/
    GPIOB_INT_DISABLE(pinNum);
    
    switch (intTriggerType)
    {
        case GPIO_TRIGGER_FALLING:
            GPIOB_SET_ONE_EDGE(pinNum);
            GPIOB_SET_INTTYPE_EDGE(pinNum);
            GPIOB_SET_POLARITY_LOW(pinNum);
        break;
        
        case GPIO_TRIGGER_RISING:
            GPIOB_SET_ONE_EDGE(pinNum);
            GPIOB_SET_INTTYPE_EDGE(pinNum);
            GPIOB_SET_POLARITY_HIGH(pinNum);
        break;
        
        case GPIO_TRIGGER_RISING_FALLING:
            GPIOB_SET_BOTH_EDGE(pinNum);
            GPIOB_SET_INTTYPE_EDGE(pinNum);
        break;
        
        case GPIO_TRIGGER_LEVEL_LOW:
            GPIOB_SET_ONE_EDGE(pinNum);
            GPIOB_SET_INTTYPE_LEVEL(pinNum);
            GPIOB_SET_POLARITY_LOW(pinNum);
        break;
        
        case GPIO_TRIGGER_LEVEL_HIGH:
            GPIOB_SET_ONE_EDGE(pinNum);
            GPIOB_SET_INTTYPE_LEVEL(pinNum);
            GPIOB_SET_POLARITY_HIGH(pinNum);
        break;
        
        default:
        break;            
    }
    
    GPIOB_DEBOUNCE_ENABLE(pinNum);
    GPIOB_INT_ENABLE(pinNum);
    GPIOB_INT_UNMASK(pinNum);
    
    /*Clear spurious interrupts*/
    gpio1_clr_int_flag(1<<(pinNum));
    NVIC_ClearPendingIRQ(GPIO_IRQn);
    NVIC_EnableIRQ(GPIO1_IRQn);
    
    
    return 0;
}


/**
* gpio_init
*
* @param[in] gpioConfig: GPIO config type pointer
* @return    0: success, -1:fail
*
* @brief  config gpio function
*/
int32_t gpio_init(GPIO_ConfigType *gpioConfig)
{
    uint8_t pinNum = gpioConfig->gpioNum;
    
    /*GPIO config interrupt*/
    if (gpioConfig->interruptEn)
    {
        if(pinNum<GPIO_PIN32)
        {
            gpio_int_config(pinNum, gpioConfig->gpioIntTriggerType);
        }
        else
        {
            gpio1_int_config(pinNum-GPIO_PIN32, gpioConfig->gpioIntTriggerType);
        }
    }
    else
    {
        /*GPIO interrupt close*/
        if(pinNum<GPIO_PIN32)
        {
            GPIOA_INT_DISABLE(pinNum);
            GPIOA_INT_MASK(pinNum);
        }
        else
        {
            GPIOB_INT_DISABLE(pinNum-GPIO_PIN32);
            GPIOB_INT_MASK(pinNum-GPIO_PIN32);
        }
    }

    if(pinNum<GPIO_PIN32)
    {
        if(GPIO_MODE_OUTPUT == gpioConfig->gpioDirection)
        {
            GPIOA_SET_OUTPUT(pinNum);
        }
        else
        {
            GPIOA_SET_INPUT(pinNum);
        }
    }
    else
    {
        if(GPIO_MODE_OUTPUT == gpioConfig->gpioDirection)
        {
            GPIOB_SET_OUTPUT(pinNum-GPIO_PIN32);
        }
        else
        {
            GPIOB_SET_INPUT(pinNum-GPIO_PIN32);
        }
    }
    return 0;
}

/**
* gpio_deinit
*
* @param[in] gpioNum: GPIO number(GPIO_PIN0-GPIO_PIN22)
* @return    0: success, -1:fail
*
* @brief  config gpio function
*/
int32_t gpio_deinit(GPIO_PinType pinNum)
{
    if(pinNum<GPIO_PIN32)
    {
        /*GPIO interrupt close*/
        GPIOA_INT_DISABLE(pinNum);
        GPIOA_INT_MASK(pinNum);
        
        /*default gpio input*/
        GPIOA_SET_INPUT(pinNum);
    }
    else
    {
        /*GPIO interrupt close*/
        GPIOB_INT_DISABLE(pinNum);
        GPIOB_INT_MASK(pinNum);
        
        /*default gpio input*/
        GPIOB_SET_INPUT(pinNum);
    }
    return 0;
}
/**
* gpio_set_callback
*
* @param[in]  gpioId: GPIO ID(0~2)
* @param[in]  GPIO_EventCallback: gpio callback
* @return none
*
* @brief GPIO module set call back
*/
void gpio_set_callback(uint32_t gpioId,GPIO_EventCallback callback)
{
    s_gpioCallback[gpioId] = callback;
}

/**
* GPIO_IRQHandler
*
* @param[in] none
*
* @return none
*
* @brief GPIO interrupt service routine
*/
void GPIO_IRQHandler(void)
{
    uint32_t status = gpio_get_int_flag();
    gpio_clr_int_flag(status);
    if (s_gpioCallback[0])
    {
        s_gpioCallback[0](status);
    }
}

/**
* GPIO1_IRQHandler
*
* @param[in] none
*
* @return none
*
* @brief GPIO1 interrupt service routine
*/
void GPIO1_IRQHandler(void)
{
    uint32_t status = gpio1_get_int_flag();
    gpio1_clr_int_flag(status);
    
    if (s_gpioCallback[1])
    {
        s_gpioCallback[1](status);
    }
   
}