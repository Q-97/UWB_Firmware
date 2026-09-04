/*****************************************************************************
 *  File:zn_gpio_reg.h
 *
 *  Descirption: contains the functions support gpio driver.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-4-20
 *
 *****************************************************************************/

#ifndef __ZN_GPIO_REG_H__
#define __ZN_GPIO_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"


#define GPIO_SWPORTA_DR             (GPIO_BASE_ADDR+0x00UL)     /* Port A Data Register. */
#define GPIO_SWPORTA_DDR            (GPIO_BASE_ADDR+0x04UL)     /* Port A Data Direction Register. */
#define GPIO_SWPORTA_CTL            (GPIO_BASE_ADDR+0x08UL)     /* Port A Data Source, not use.*/


#define GPIO_INTEN                  (GPIO_BASE_ADDR+0x30UL)     /* Interrupt enable. Can only be a PORTA */
#define GPIO_INTMASK                (GPIO_BASE_ADDR+0x34UL)     /* Interrupt mask.Can only be a PORTA*/
#define GPIO_INTTYPE_LEVEL          (GPIO_BASE_ADDR+0x38UL)     /* Interrupt level.Can only be a PORTA*/
#define GPIO_INT_POLARITY           (GPIO_BASE_ADDR+0x3cUL)     /* Interrupt polarity.Can only be a PORTA*/
#define GPIO_INTSTATUS              (GPIO_BASE_ADDR+0x40UL)     /* Interrupt status.Can only be a PORTA*/
#define GPIO_RAW_INTSTATUS          (GPIO_BASE_ADDR+0x44UL)     /* Raw interrupt status.Can only be a PORTA*/
#define GPIO_PORTA_DEBOUNCE         (GPIO_BASE_ADDR+0x48UL)     /* Debounce enable.Can only be a PORTA*/
#define GPIO_PORTA_EOI              (GPIO_BASE_ADDR+0x4cUL)     /* Clear interrupt.Can only be a PORTA*/
#define GPIO_EXT_PORTA              (GPIO_BASE_ADDR+0x50UL)     /* External Port A, use read gpio-pin value.*/
#define GPIO_EXT_PORTB              (GPIO_BASE_ADDR+0x54UL)     /*not use*/
#define GPIO_EXT_PORTC              (GPIO_BASE_ADDR+0x58UL)     /*not use*/
#define GPIO_EXT_PORTD              (GPIO_BASE_ADDR+0x5cUL)     /*not use*/
#define GPIO_LS_SYNC                (GPIO_BASE_ADDR+0x60UL)     /*not use*/
/*GPIO info. General GPIO operation is not used*/
#define GPIO_ID_CODE                (GPIO_BASE_ADDR+0x64UL)     /* GPIO ID code*/
#define GPIO_INT_BOTHEDGE           (GPIO_BASE_ADDR+0x68UL)     /* Interrupt both edge type*/
#define GPIO_VER_ID_CODE            (GPIO_BASE_ADDR+0x6cUL)     /* GPIO Component Version*/
#define GPIO_CONFIG_REG1            (GPIO_BASE_ADDR+0x74UL)     /* GPIO Configuration Register 1*/
#define GPIO_CONFIG_REG2            (GPIO_BASE_ADDR+0x70UL)     /* GPIO Configuration Register 2*/
        


/*GPIOA intput*/
#define   GPIOA_SET_INPUT(pin)       write_mreg32(GPIO_SWPORTA_DDR,  read_mreg32(GPIO_SWPORTA_DDR)&(~(1<<(pin))))
#define   GPIOA_READ_BITS(pin)       ((read_mreg32(GPIO_EXT_PORTA)&(1<<(pin)))>>(pin))

/*GPIOA output*/
#define   GPIOA_SET_OUTPUT(pin)      write_mreg32(GPIO_SWPORTA_DDR, read_mreg32(GPIO_SWPORTA_DDR)|(1<<(pin)))
#define   GPIOA_SET_BITS(pin)        write_mreg32(GPIO_SWPORTA_DR, read_mreg32(GPIO_SWPORTA_DR)| (1<<(pin)))
#define   GPIOA_RESET_BITS(pin)      write_mreg32(GPIO_SWPORTA_DR, read_mreg32(GPIO_SWPORTA_DR)& (~(1<<(pin))))
 

/*GPIOA pin interrupt disable and enable*/ 
#define   GPIOA_INT_DISABLE(pin)        write_mreg32(GPIO_INTEN, read_mreg32(GPIO_INTEN) & (~(0x1 << (pin))))     
#define   GPIOA_INT_ENABLE(pin)         write_mreg32(GPIO_INTEN, read_mreg32(GPIO_INTEN) | (0x1 << (pin))) 

/*GPIOApin Interrupt mask disable and enable*/
#define   GPIOA_INT_UNMASK(pin)        write_mreg32(GPIO_INTMASK, read_mreg32(GPIO_INTEN) & (~(0x1 << (pin))))     
#define   GPIOA_INT_MASK(pin)          write_mreg32(GPIO_INTMASK, read_mreg32(GPIO_INTEN) | (0x1 << (pin))) 

/*GPIOA pin interrupt type config*/ 
#define   GPIOA_SET_INTTYPE_LEVEL(pin)  write_mreg32(GPIO_INTTYPE_LEVEL, read_mreg32(GPIO_INTTYPE_LEVEL) & (~(0x1 << (pin))))  /*Level-sensitive*/
#define   GPIOA_SET_INTTYPE_EDGE(pin)   write_mreg32(GPIO_INTTYPE_LEVEL, read_mreg32(GPIO_INTTYPE_LEVEL) | (0x1 << (pin)))    /* Edge-sensitive*/

/*GPIOA pin one or both egde config*/ 
#define   GPIOA_SET_ONE_EDGE(pin)         write_mreg32(GPIO_INT_BOTHEDGE, read_mreg32(GPIO_INT_BOTHEDGE) & (~(0x1 << (pin))))  /*set one edge INT*/
#define   GPIOA_SET_BOTH_EDGE(pin)        write_mreg32(GPIO_INT_BOTHEDGE, read_mreg32(GPIO_INT_BOTHEDGE) | (0x1 << (pin)))    /*set both edge INT*/

/*GPIOA pin interrupt polarity config*/
#define   GPIOA_SET_POLARITY_LOW(pin)         write_mreg32(GPIO_INT_POLARITY, read_mreg32(GPIO_INT_POLARITY) & (~(0x1 << (pin))))   /* falling-edge or active-low sensitive*/
#define   GPIOA_SET_POLARITY_HIGH(pin)         write_mreg32(GPIO_INT_POLARITY, read_mreg32(GPIO_INT_POLARITY) |(0x1 << (pin)))   /*rising-edge or active-high sensitive*/


/*GPIOA pin interrupt disable and enable*/ 
#define   GPIOA_DEBOUNCE_DISABLE(pin)        write_mreg32(GPIO_PORTA_DEBOUNCE, read_mreg32(GPIO_PORTA_DEBOUNCE) & (~(0x1 << (pin))))     
#define   GPIOA_DEBOUNCE_ENABLE(pin)         write_mreg32(GPIO_PORTA_DEBOUNCE, read_mreg32(GPIO_PORTA_DEBOUNCE) | (0x1 << (pin))) 



#define GPIO1_SWPORTA_DR             (GPIO1_BASE_ADDR+0x00UL)     /* Port A Data Register. */
#define GPIO1_SWPORTA_DDR            (GPIO1_BASE_ADDR+0x04UL)     /* Port A Data Direction Register. */
#define GPIO1_SWPORTA_CTL            (GPIO1_BASE_ADDR+0x08UL)     /* Port A Data Source, not use.*/
                         
#define GPIO1_INTEN                  (GPIO1_BASE_ADDR+0x30UL)     /* Interrupt enable. Can only be a PORTA */
#define GPIO1_INTMASK                (GPIO1_BASE_ADDR+0x34UL)     /* Interrupt mask.Can only be a PORTA*/
#define GPIO1_INTTYPE_LEVEL          (GPIO1_BASE_ADDR+0x38UL)     /* Interrupt level.Can only be a PORTA*/
#define GPIO1_INT_POLARITY           (GPIO1_BASE_ADDR+0x3cUL)     /* Interrupt polarity.Can only be a PORTA*/
#define GPIO1_INTSTATUS              (GPIO1_BASE_ADDR+0x40UL)     /* Interrupt status.Can only be a PORTA*/
#define GPIO1_RAW_INTSTATUS          (GPIO1_BASE_ADDR+0x44UL)     /* Raw interrupt status.Can only be a PORTA*/
#define GPIO1_PORTA_DEBOUNCE         (GPIO1_BASE_ADDR+0x48UL)     /* Debounce enable.Can only be a PORTA*/
#define GPIO1_PORTA_EOI              (GPIO1_BASE_ADDR+0x4cUL)     /* Clear interrupt.Can only be a PORTA*/
#define GPIO1_EXT_PORTA              (GPIO1_BASE_ADDR+0x50UL)     /* External Port A, use read gpio-pin value.*/
#define GPIO1_EXT_PORTB              (GPIO1_BASE_ADDR+0x54UL)     /*not use*/
#define GPIO1_EXT_PORTC              (GPIO1_BASE_ADDR+0x58UL)     /*not use*/
#define GPIO1_EXT_PORTD              (GPIO1_BASE_ADDR+0x5cUL)     /*not use*/
#define GPIO1_LS_SYNC                (GPIO1_BASE_ADDR+0x60UL)     /*not use*/
/*GPIO info general GPIO operation is not used*/
#define GPIO1_ID_CODE                (GPIO1_BASE_ADDR+0x64UL)     /* GPIO ID code*/
#define GPIO1_INT_BOTHEDGE           (GPIO1_BASE_ADDR+0x68UL)     /* Interrupt both edge type*/
#define GPIO1_VER_ID_CODE            (GPIO1_BASE_ADDR+0x6cUL)     /* GPIO Component Version*/
#define GPIO1_CONFIG_REG1            (GPIO1_BASE_ADDR+0x74UL)     /* GPIO Configuration Register 1*/
#define GPIO1_CONFIG_REG2            (GPIO1_BASE_ADDR+0x70UL)     /* GPIO Configuration Register 2*/
            



/*GPIO1 intput*/
#define   GPIOB_SET_INPUT(pin)       write_mreg32(GPIO1_SWPORTA_DDR,  read_mreg32(GPIO1_SWPORTA_DDR)&(~(1<<(pin))))
#define   GPIOB_READ_BITS(pin)       ((read_mreg32(GPIO1_EXT_PORTA)&(1<<(pin)))>>(pin))

/*GPIO1 output*/
#define   GPIOB_SET_OUTPUT(pin)      write_mreg32(GPIO1_SWPORTA_DDR, read_mreg32(GPIO1_SWPORTA_DDR)|(1<<(pin)))
#define   GPIOB_SET_BITS(pin)        write_mreg32(GPIO1_SWPORTA_DR, read_mreg32(GPIO1_SWPORTA_DR)| (1<<(pin)))
#define   GPIOB_RESET_BITS(pin)      write_mreg32(GPIO1_SWPORTA_DR, read_mreg32(GPIO1_SWPORTA_DR)& (~(1<<(pin))))
 

/*GPIO1 pin interrupt disable and enable*/ 
#define   GPIOB_INT_DISABLE(pin)        write_mreg32(GPIO1_INTEN, read_mreg32(GPIO1_INTEN) & (~(0x1 << (pin))))     
#define   GPIOB_INT_ENABLE(pin)         write_mreg32(GPIO1_INTEN, read_mreg32(GPIO1_INTEN) | (0x1 << (pin))) 

/*GPIO1 pin Interrupt mask disable and enable*/
#define   GPIOB_INT_UNMASK(pin)        write_mreg32(GPIO1_INTMASK, read_mreg32(GPIO1_INTEN) & (~(0x1 << (pin))))     
#define   GPIOB_INT_MASK(pin)          write_mreg32(GPIO1_INTMASK, read_mreg32(GPIO1_INTEN) | (0x1 << (pin))) 

/*GPIO1 pin interrupt type config*/ 
#define   GPIOB_SET_INTTYPE_LEVEL(pin)  write_mreg32(GPIO1_INTTYPE_LEVEL, read_mreg32(GPIO1_INTTYPE_LEVEL) & (~(0x1 << (pin))))  /*Level-sensitive*/
#define   GPIOB_SET_INTTYPE_EDGE(pin)   write_mreg32(GPIO1_INTTYPE_LEVEL, read_mreg32(GPIO1_INTTYPE_LEVEL) | (0x1 << (pin)))    /* Edge-sensitive*/

/*GPIO1 pin one or both egde config*/ 
#define   GPIOB_SET_ONE_EDGE(pin)         write_mreg32(GPIO1_INT_BOTHEDGE, read_mreg32(GPIO1_INT_BOTHEDGE) & (~(0x1 << (pin))))  /*set one edge INT*/
#define   GPIOB_SET_BOTH_EDGE(pin)        write_mreg32(GPIO1_INT_BOTHEDGE, read_mreg32(GPIO1_INT_BOTHEDGE) | (0x1 << (pin)))    /*set both edge INT*/

/*GPIO1 pin interrupt polarity config*/
#define   GPIOB_SET_POLARITY_LOW(pin)         write_mreg32(GPIO1_INT_POLARITY, read_mreg32(GPIO1_INT_POLARITY) & (~(0x1 << (pin))))   /* falling-edge or active-low sensitive*/
#define   GPIOB_SET_POLARITY_HIGH(pin)         write_mreg32(GPIO1_INT_POLARITY, read_mreg32(GPIO1_INT_POLARITY) |(0x1 << (pin)))   /*rising-edge or active-high sensitive*/


/*GPIOA pin interrupt disable and enable*/ 
#define   GPIOB_DEBOUNCE_DISABLE(pin)        write_mreg32(GPIO1_PORTA_DEBOUNCE, read_mreg32(GPIO1_PORTA_DEBOUNCE) & (~(0x1 << (pin))))     
#define   GPIOB_DEBOUNCE_ENABLE(pin)         write_mreg32(GPIO1_PORTA_DEBOUNCE, read_mreg32(GPIO1_PORTA_DEBOUNCE) | (0x1 << (pin))) 



#ifdef __cplusplus
}
#endif

#endif