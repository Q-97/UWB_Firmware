/*****************************************************************************
* File: gpio_test.c
* Descirption: this file contains the functions support gpio test.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/

#include "gpio_test.h"

volatile uint32_t gpio_intc_count = 0;

/**
 * wait_for_reply - Waits for a reply on UART0
 *
 * @param[in] None
 * @return 0 if the reply is 'n', 1 if the reply is 'y', and 2 otherwise
 *
 * @brief This function waits for a reply on UART0 and returns the result. 
 */
static uint32_t wait_for_reply(void)
{
    uint8_t i;
    uint8_t ch;
    char answer[20];

    for(i = 0; i < 20; i++)
    {
        answer[i] = '\0';
    }
    i = 0;
    while(1)
    {
        ch = hal_uart_get_char(0);
        
        //JJJ_DEBUG CK_Uart_PutChar(consoleuart,ch);
        if (ch == '\n' || ch == '\r')
        {
            answer[i] = '\0';
            if(i)
            {
                break;
            }
            else
            {
                continue;
            }
            break;
        }
        if(ch == '\b')
        {
             if(i > 0)
             {
                i--;
                hal_uart_put_char(0, ch);
             }
        }
        else
        {
            answer[i++] = ch;
            hal_uart_put_char(0, ch);
        }
    }
    if((i == 1) && (answer[0] == 'y'))
    {
        return 1;
    }
    else if((i == 1) && (answer[0] == 'n'))
    {
        return 0;
    }
    else if((i == 1) && (answer[0] >= '0') && (answer[0] <='9'))
    {
        return answer[0] - '0';
    }
    return 2;
}

static void gpio_output_test(uint8_t pin)
{
    uint8_t ret_value = 0;
    
    LOG_INFO("-----gpio output test begin-----");
    
    hal_gpio_set_output_default_config(pin);
    
    hal_gpio_set_value(pin, 1);
    LOG_INFO("\n\t Is A%d high level? [y/n] ", pin);
    if(wait_for_reply() != 1)
    {
        ret_value = 1;
        goto end;
    }
    
    hal_gpio_set_value(pin, 0);
    LOG_INFO("\n\t Is A%d low level? [y/n] ", pin);
    if(wait_for_reply() != 1)
    {
        ret_value = 1;
        goto end;
    }
    
    end:
    if(ret_value)
    {
        LOG_INFO("\n\t - - - FAILURE");
    }
    else
    {
        LOG_INFO("\n\t - - - PASS");
    }
    
    LOG_INFO("-----gpio output test end-----");
    
}

static void gpio_input_test(uint8_t pin)
{
    uint8_t input_level = 0;
    uint8_t pin_level   = 0;
    uint8_t ret_value   = 0;
    
    LOG_INFO("-----GPIO input test begin-----");
    
    hal_gpio_set_input_default_config(pin);

    LOG_INFO("For this test to run correctly, connect the gpio to high or low level");
    LOG_INFO("connection done, continue? - - - [y/n] ");
    
    DPRINTF("input 0 or 1,0 -- input low level, 1 -- input high level\n");
    
    while(1)
    {
        input_level = hal_uart_get_char(0);
        
        if(('0' == input_level) || ('1' == input_level))
        {
            hal_uart_put_char(0, input_level);
            break;
        }
    }
    input_level -= '0';
    
    pin_level = hal_gpio_get_val(pin);
    if(pin_level != input_level)
    {
        LOG_INFO("\t - - -FAILURE");
    }
    else
    {
        LOG_INFO("\t - - - PASS");
    }
    LOG_INFO("-----gpio input test end-----");
}


static void gpio_intc_check(uint8_t pin)
{
    while (1)
    {
        if (gpio_intc_count > 1)
        {
            break; 
        }
    }

    LOG_INFO("\t - - -PASS");
    LOG_INFO("-----GPIO interrupt test end-----");
    
    NVIC_DisableIRQ(GPIO_IRQn);
}


static void gpio_irq_callback(void)
{
    gpio_intc_count++;
    LOG_INFO("interrupt,intc cnt=%d", gpio_intc_count);
    if(gpio_intc_count > 10)
    {
        NVIC_DisableIRQ(GPIO_IRQn);
    }
}    

static void gpio_interrupt_test(uint8_t pin)
{
    hal_gpio_t gpio_cfg = {0};
    
    LOG_INFO("GPIO-IRQ: level low\r\n");
    gpio_cfg.pin = pin;
    gpio_cfg.function = FUNCTION_GPIO;
    gpio_cfg.direction = GPIO_INPUT;
    gpio_cfg.interrupt_en = 1;
    gpio_cfg.int_trigger_type = LOW_LEVEL;
    gpio_cfg.driven_strength = DRIVEN_12MA;
    gpio_cfg.func = (GPIO_EventCallback)&gpio_irq_callback;
    gpio_intc_count = 0;
    hal_gpio_init(&gpio_cfg);
    gpio_intc_check(pin);
    
    LOG_INFO("GPIO-IRQ: level high\r\n");
    gpio_cfg.pin = pin;
    gpio_cfg.function = FUNCTION_GPIO;
    gpio_cfg.direction = GPIO_INPUT;
    gpio_cfg.interrupt_en = 1;
    gpio_cfg.int_trigger_type = HIGH_LEVEL;
    gpio_cfg.driven_strength = DRIVEN_12MA;
    gpio_cfg.func = (GPIO_EventCallback)&gpio_irq_callback;
    gpio_intc_count = 0;
    hal_gpio_init(&gpio_cfg);
    gpio_intc_check(pin);
    
    LOG_INFO("GPIO-IRQ: edge falling\r\n");
    gpio_cfg.pin = pin;
    gpio_cfg.function = FUNCTION_GPIO;
    gpio_cfg.direction = GPIO_INPUT;
    gpio_cfg.interrupt_en = 1;
    gpio_cfg.int_trigger_type = FALLING_EDGE;
    gpio_cfg.driven_strength = DRIVEN_12MA;
    gpio_cfg.func = (GPIO_EventCallback)&gpio_irq_callback;
    gpio_intc_count = 0;
    hal_gpio_init(&gpio_cfg);
    gpio_intc_check(pin);
    
    LOG_INFO("GPIO-IRQ: edge rising\r\n");
    gpio_cfg.pin = pin;
    gpio_cfg.function = FUNCTION_GPIO;
    gpio_cfg.direction = GPIO_INPUT;
    gpio_cfg.interrupt_en = 1;
    gpio_cfg.int_trigger_type = RISING_EDGE;
    gpio_cfg.driven_strength = DRIVEN_12MA;
    gpio_cfg.func = (GPIO_EventCallback)&gpio_irq_callback;
    gpio_intc_count = 0;
    hal_gpio_init(&gpio_cfg);
    gpio_intc_check(pin);
    
    LOG_INFO("GPIO-IRQ: edge both\r\n");
    gpio_cfg.pin = pin;
    gpio_cfg.function = FUNCTION_GPIO;
    gpio_cfg.direction = GPIO_INPUT;
    gpio_cfg.interrupt_en = 1;
    gpio_cfg.int_trigger_type = DOUBLE_EDGE;
    gpio_cfg.driven_strength = DRIVEN_12MA;
    gpio_cfg.func = (GPIO_EventCallback)&gpio_irq_callback;
    gpio_intc_count = 0;
    hal_gpio_init(&gpio_cfg);
    gpio_intc_check(pin);
}


void user_init(void)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 0;
    uart_cfg.baurdrate = B115200;
    
    hal_uart_init(&uart_cfg);
}



void user_test(void)
{
    uint8_t test_ins = 0;
    
    LOG_INFO("input test instruction, 1: output test, 2: input test, 3: interrupt test");
    
    test_ins = wait_for_reply();
    
    if(1 == test_ins)
    {
        LOG_INFO("gpio output test");
        gpio_output_test(TEST_PIN);
    }
    else if(2 == test_ins)
    {
        LOG_INFO("gpio input test");
        gpio_input_test(TEST_PIN);
    }
    else if(3 == test_ins)
    {
        LOG_INFO("gpio interrupt test");
        gpio_interrupt_test(TEST_PIN);
    }
    else
    {
        LOG_INFO("error instruction");
    }
}
