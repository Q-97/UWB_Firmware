/*****************************************************************************
 *  File: zn_gpio.h
 *
 *  Descirption: contains the functions support gpio driver.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-20
 *
 *****************************************************************************/

#ifndef __ZN_GPIO_H__
#define __ZN_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_gpio_reg.h"


typedef void (*GPIO_EventCallback)(uint32_t status);

/* GPIO pin refer pad_reg_*.h file */
/*
GPIO GPIOA0-27 and GPIOB0-5,reserve:GPIO_PIN28-31，GPIOB:GPIO_PIN32-36,
*/

/*
    GPIO_DRIVING_4MA = 0,
    GPIO_DRIVING_8MA,
    GPIO_DRIVING_12MA,
    GPIO_DRIVING_16MA
*/

typedef enum{
    GPIO_PIN0 = 0, //GPIOA0
    GPIO_PIN1,    //GPIOA1
    GPIO_PIN2,    //GPIOA2
    GPIO_PIN3,    //GPIOA3
    GPIO_PIN4,    //GPIOA4
    GPIO_PIN5,    //GPIOA5
    GPIO_PIN6,    //GPIOA6
    GPIO_PIN7,    //GPIOA7
    GPIO_PIN8,    //GPIOA8
    GPIO_PIN9,    //GPIOA9
    GPIO_PIN10,   //GPIOA10
    GPIO_PIN11,   //GPIOA11
    GPIO_PIN12,   //GPIOA12
    GPIO_PIN13,   //GPIOA13
    GPIO_PIN14,   //GPIOA14
    GPIO_PIN15,   //GPIOA15
    GPIO_PIN16,   //GPIOA16
    GPIO_PIN17,   //GPIOA17
    GPIO_PIN18,   //GPIOA18
    GPIO_PIN19,   //GPIOA19
    GPIO_PIN20,   //GPIOA20
    GPIO_PIN21,   //GPIOA21
    GPIO_PIN22,   //GPIOA22
    GPIO_PIN23,   //GPIOA23
    GPIO_PIN24,   //GPIOA24
    GPIO_PIN25,   //res
    GPIO_PIN26,   //res
    GPIO_PIN27,   //res
    GPIO_PIN28,   //res
    GPIO_PIN29,   //res
    GPIO_PIN30,   //res
    GPIO_PIN31,   //res
    GPIO_PIN32,   //GPIOB0
    GPIO_PIN33,   //GPIOB1
    GPIO_PIN34,   //GPIOB2
    GPIO_PIN35,   //GPIOB3
    GPIO_PIN36,   //GPIOB4

}GPIO_PinType;





/* GPIO module index enumeration. */
typedef enum
{
    GPIOA_INDEX = 0,       /*!< 0: GPIOA index */
    GPIO_INDEX_MAX
}GPIO_IndexType;


/*pad_reg register explain pull up/down enable*/
typedef enum
{
    GPIO_FLOATING = 0,
    GPIO_PU,                /*pull up*/
    GPIO_PD                 /*pull down*/
}GPIO_PuPdType;



typedef enum
{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
}GPIO_Direction;
typedef enum
{
    GPIO_TRIGGER_FALLING=0,
    GPIO_TRIGGER_RISING,
    GPIO_TRIGGER_RISING_FALLING,
    GPIO_TRIGGER_LEVEL_LOW,
    GPIO_TRIGGER_LEVEL_HIGH
}GPIO_IntTriggerType;


typedef struct
{
    GPIO_PinType gpioNum;             /*pin: 0~22 */
    GPIO_Direction gpioDirection;       /*0 - input; 1 - output*/
    uint8_t interruptEn;         /*0 – disable gpio interrupt ;1 – enable gpio interrupt*/
    GPIO_IntTriggerType gpioIntTriggerType;  /*gpio interrupt trigger type (0-5)*/
}GPIO_ConfigType;

int32_t gpio_set_dir(GPIO_PinType gpioNum, GPIO_Direction pinDir);
int32_t gpio_get_pin_value(GPIO_PinType gpioNum);
int32_t gpio_set_pin_value(GPIO_PinType gpioNum, uint32_t pinValue);
uint32_t gpio_get_int_flag(void);
uint32_t gpio1_get_int_flag(void);
uint32_t gpio_get_int_rawflag(void);
uint32_t gpio1_get_int_rawflag(void);
void gpio_clr_int_flag(uint32_t intStatus);
void gpio1_clr_int_flag(uint32_t intStatus);
int32_t gpio_int_config(GPIO_PinType pinNum, GPIO_IntTriggerType intTriggerType);
int32_t gpio_init(GPIO_ConfigType *gpioConfig);
int32_t gpio_deinit(GPIO_PinType pinNum);
void gpio_set_callback(uint32_t gpioId,GPIO_EventCallback callback);
void GPIO_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif