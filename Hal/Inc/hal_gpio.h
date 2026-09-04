/*****************************************************************************
* File: hal_gpio.h
*
* Descirption: this file contains the gpio hal functions.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_gpio.h"

#define GPIO_INPUT    0
#define GPIO_OUTPUT   1

#define FALLING_EDGE   0
#define RISING_EDGE    1
#define DOUBLE_EDGE    2
#define LOW_LEVEL      3
#define HIGH_LEVEL     4

#define FUNCTION_GPIO       0x01
#define FUNCTION_BIT_OFFSET 0x00
#define FUNCTION_BIT_MASK   0x07


#define PIN_PULL_UP            0x01
#define PIN_PULL_DOWN          0x00
#define PIN_PULL_BIT_OFFSET    0x05
#define PIN_PULL_BIT_MASK      0x20

#define PIN_PULL_DISABLE       0x00
#define PIN_PULL_ENABLE        0x01
#define PIN_PULL_EN_BIT_OFFSET 0x06
#define PIN_PULL_EN_BIT_MASK   0x40


#define DRIVEN_4MA        0x00
#define DRIVEN_8MA        0x01
#define DRIVEN_12MA       0x02
#define DRIVEN_16MA       0x03
#define DRIVEN_BIT_OFFSET 0x03
#define DRIVEN_BIT_MASK   0x18

#define OUTPUT_FAST            0x00
#define OUTPUT_SLOW            0x01
#define OUTPUT_RATE_BIT_OFFSET 0x07
#define OUTPUT_RATE_BIT_MASK   0x80

#define INPUT_CMOS            0x00
#define INPUT_SCHMITT         0x01
#define INPUT_MODE_BIT_OFFSET 0x08
#define INPUT_MODE_BIT_MASK   0x100

#define MAX_PAD_ADDR  0x80
#define MAX_GPIO_PIN  GPIO_PIN36

#define GPIO_PIN_TO_ID(x)     (((x) > GPIO_PIN32) ? 1 : 0)

typedef struct hal_gpio
{
    GPIO_PinType  pin;              //pin number, pin0-pin23
    
    uint8_t function : 3;           //pin function, see pad_reg.h
    uint8_t direction : 1;          //0: input, 1: output
    uint8_t interrupt_en : 1;       //0: disable, 1: enable
    uint8_t int_trigger_type : 3;   //0: falling edge, 1: rising edge, 2: double edge, 3: low level, 4: high level
    
    uint8_t pull_config : 1;        //0: pull down, 1: pull up 
    uint8_t pull_en : 1;            //0: disable, 1: enable
    uint8_t driven_strength : 2;    //0: 4mA, 1: 8mA, 2: 12mA, 3: 16mA default 2
    uint8_t output_rate : 1;        //0: fast, 1: slow  indicate output 0-1 change rate.
    uint8_t input_mode : 2;         //0: CMOS input, 1: Schmitt input
    uint8_t rsv : 1;
    
    GPIO_EventCallback func;        //interrupt callback
}hal_gpio_t;








ERROR_Type hal_gpio_init(hal_gpio_t* gpio_cfg);
ERROR_Type hal_gpio_tx_en_check(uint8_t pin);
ERROR_Type hal_gpio_rx_en_check(uint8_t pin);
void hal_gpio_set_all_input(uint8_t mode); //mode 0: CMOS input, 1: Schmitt input
void hal_gpio_set_output_default_config(uint8_t pin);
void hal_gpio_set_input_default_config(uint8_t pin);
void hal_gpio_set_tx_en_mode(uint8_t pin);
void hal_gpio_set_rx_en_mode(uint8_t pin);
void hal_gpio_set_value(uint8_t pin, uint8_t val);
uint8_t hal_gpio_get_val(uint8_t pin);



#ifdef __cplusplus
}
#endif

#endif