/*****************************************************************************
 *  File: hal_gpio.c
 *
 * Descirption: this file contains the functions support gpio operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_gpio.h"

static uint32_t get_gpio_pad_addr(uint8_t pin)
{
    uint32_t addr = 0;
    
    if(pin <= GPIO_PIN24)
    {
        addr = pin * 4;
    }
    else if((pin >= GPIO_PIN32) && (pin <= GPIO_PIN36 ))
    {
        addr = 0x70 + (pin - GPIO_PIN32) * 4;
    }
    else
    {
        addr = 0xffffffff;
    }
    
    return addr;
}

ERROR_Type hal_gpio_init(hal_gpio_t* gpio_cfg)
{
    uint32_t        gpio_ctrl   = 0;       
    uint32_t        pad_addr    = 0;
    GPIO_ConfigType gpio_config = {0};
    
    if(NULL == gpio_cfg)
    {
        LOG_ERROR("null pointer");
        return ERROR;
    }
    
    pad_addr = get_gpio_pad_addr(gpio_cfg->pin);
    
    if(0xffffffff == pad_addr)
    {
        LOG_ERROR("error pin id");
        return ERROR;
    }
    
    if(FUNCTION_GPIO == gpio_cfg->function)
    {
        gpio_ctrl = (((uint32_t)gpio_cfg->function << FUNCTION_BIT_OFFSET) & FUNCTION_BIT_MASK) |
                     (((uint32_t)gpio_cfg->driven_strength << DRIVEN_BIT_OFFSET) & DRIVEN_BIT_MASK) | 
                     (((uint32_t)gpio_cfg->pull_config << PIN_PULL_BIT_OFFSET) & PIN_PULL_BIT_MASK) |
                     (((uint32_t)gpio_cfg->pull_en << PIN_PULL_EN_BIT_OFFSET) & PIN_PULL_EN_BIT_MASK) |
                     (((uint32_t)gpio_cfg->output_rate << OUTPUT_RATE_BIT_OFFSET) & OUTPUT_RATE_BIT_MASK) |
                     (((uint32_t)gpio_cfg->input_mode << INPUT_MODE_BIT_OFFSET) & INPUT_MODE_BIT_MASK);
        pad_reg_write(pad_addr, gpio_ctrl);
        
        gpio_config.gpioNum = gpio_cfg->pin;
        gpio_config.gpioDirection = gpio_cfg->direction;
        gpio_config.interruptEn = gpio_cfg->interrupt_en;
        gpio_config.gpioIntTriggerType = gpio_cfg->int_trigger_type;
        gpio_init(&gpio_config);
        
        if(gpio_cfg->interrupt_en)
        {
            gpio_set_callback(GPIO_PIN_TO_ID(gpio_cfg->pin) , gpio_cfg->func);
        }
    }
    else
    {
        gpio_ctrl &= ~FUNCTION_BIT_MASK;
        gpio_ctrl |= ((uint32_t)gpio_cfg->function << FUNCTION_BIT_OFFSET) & FUNCTION_BIT_MASK;
        pad_reg_write(pad_addr, gpio_ctrl);
    }
    
    return SUCCESS;
}

ERROR_Type hal_gpio_tx_en_check(uint8_t pin)
{
    if((GPIO_PIN0 == pin) || (GPIO_PIN9 == pin) || (GPIO_PIN13 == pin) || (GPIO_PIN23 == pin))
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
 
}

ERROR_Type hal_gpio_rx_en_check(uint8_t pin)
{
    if((GPIO_PIN0 == pin) || (GPIO_PIN7 == pin) || (GPIO_PIN23 == pin) || (GPIO_PIN24 == pin))
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

//mode 0: CMOS input, 1: Schmitt input
void hal_gpio_set_all_input(uint8_t mode)
{
    uint32_t gpio_ctrl    = 0;       
    uint32_t pad_addr     = 0;
    uint8_t  pin_function = 0; 
    
    for(pad_addr = 0x00; pad_addr <= MAX_PAD_ADDR; pad_addr += 4)
    {
        if((pad_addr >= 0x64) && (pad_addr <= 0x6c))
        {
            continue;
        }
        pin_function = FUNCTION_GPIO;
        
        gpio_ctrl = pad_reg_read(pad_addr);
        gpio_ctrl &= ~(FUNCTION_BIT_MASK | INPUT_MODE_BIT_MASK);
        gpio_ctrl |= (((uint32_t)pin_function << FUNCTION_BIT_OFFSET) & FUNCTION_BIT_MASK) |
                     (((uint32_t)mode << INPUT_MODE_BIT_OFFSET) & INPUT_MODE_BIT_MASK); 
        
        pad_reg_write(pad_addr, gpio_ctrl);
    }
    
    for(uint8_t pin = GPIO_PIN0; pin <= MAX_GPIO_PIN; pin++)
    {
        if(pin <= GPIO_PIN24)
        {
            GPIOA_SET_INPUT(pin);
        }
        else if(pin >= GPIO_PIN32)
        {
            GPIOB_SET_INPUT(pin- GPIO_PIN32);
        }
    }
}

void hal_gpio_set_output_default_config(uint8_t pin)
{
    uint32_t        gpio_ctrl   = 0;
    uint32_t        gpio_func   = 0;
    uint32_t        pad_addr    = 0;
    GPIO_ConfigType gpio_config = {0};
    
    gpio_config.gpioNum = pin;
    gpio_config.gpioDirection = GPIO_MODE_OUTPUT;
    gpio_func = FUNCTION_GPIO;
    
    pad_addr = get_gpio_pad_addr(pin);
    gpio_ctrl = pad_reg_read(pad_addr);

    gpio_ctrl &= ~FUNCTION_BIT_MASK;
    gpio_ctrl |= (gpio_func << FUNCTION_BIT_OFFSET) & FUNCTION_BIT_MASK;
    pad_reg_write(pad_addr, gpio_ctrl);
    gpio_init(&gpio_config);
}

void hal_gpio_set_input_default_config(uint8_t pin)
{
    uint32_t        gpio_ctrl   = 0;
    uint32_t        gpio_func   = 0;
    uint32_t        pad_addr    = 0;
    GPIO_ConfigType gpio_config = {0};
    
    gpio_config.gpioNum = pin;
    gpio_config.gpioDirection = GPIO_MODE_INPUT;
    gpio_func = FUNCTION_GPIO;
    
    pad_addr = get_gpio_pad_addr(pin);
    gpio_ctrl = pad_reg_read(pad_addr);

    gpio_ctrl &= ~FUNCTION_BIT_MASK;
    gpio_ctrl |= (gpio_func << FUNCTION_BIT_OFFSET) & FUNCTION_BIT_MASK;
    pad_reg_write(pad_addr, gpio_ctrl);
    gpio_init(&gpio_config);
}

void hal_gpio_set_tx_en_mode(uint8_t pin)
{
    uint8_t    txen_fun[24] = {3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
    hal_gpio_t gpio_cfg     = {0};
    
    if(ERROR == hal_gpio_tx_en_check(pin))
    {
        LOG_ERROR("gpio %d is not support tx_en mode", pin);
    }
    else
    {
        gpio_cfg.pin = pin;
        gpio_cfg.function = txen_fun[pin];
        hal_gpio_init(&gpio_cfg);
    }
}

void hal_gpio_set_rx_en_mode(uint8_t pin)
{
    uint8_t    rxen_fun[25]  = {4, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4};
    hal_gpio_t gpio_cfg     = {0};
    
    if(ERROR == hal_gpio_rx_en_check(pin))
    {
        LOG_ERROR("gpio %d is not support rx_en mode", pin);
    }
    else
    {
        gpio_cfg.pin = pin;
        gpio_cfg.function = rxen_fun[pin];
        hal_gpio_init(&gpio_cfg);
    }
}

void hal_gpio_set_value(uint8_t pin, uint8_t val)
{
    if(val)
    {
        gpio_set_pin_value(pin, 1);
    }
    else
    {
        gpio_set_pin_value(pin, 0);
    }
}

uint8_t hal_gpio_get_val(uint8_t pin)
{
    return gpio_get_pin_value(pin);
}