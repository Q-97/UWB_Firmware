
#ifndef __BASE_ADDR_SOC_H__
#define __BASE_ADDR_SOC_H__

#define CKROM_BASE_ADDR            0x00000000     //   128k
#define FLASH_BASE_ADDR            0x08000000     //   64M
#define XRAM0_CODE_BASE_ADDR       0X1ffe0000     //   128K
#define XRAM0_BASE_ADDR            0X20000000     //   128K
#define DMA_BASE_ADDR              0X40000000
#define AHB1_SLAVE_BASE_ADDR       0X41000000
#define APB_PERP0_BASE_ADDR        0X42000000          
#define APB_PERP1_BASE_ADDR        0X43000000          

// perp0
#define TIMER_BASE_ADDR              (APB_PERP0_BASE_ADDR + 0X0000 )    //   4K
#define WDT_BASE_ADDR                (APB_PERP0_BASE_ADDR + 0X1000 )    //   4K
#define GPIO_BASE_ADDR               (APB_PERP0_BASE_ADDR + 0X2000 )    //   4K
#define SYSCTRL_BASE_ADDR            (APB_PERP0_BASE_ADDR + 0X3000 )    //   4K
#define PADREG_BASE_ADDR             (APB_PERP0_BASE_ADDR + 0X4000 )    //   4K
#define CHIPCTRL_BASE_ADDR           (APB_PERP0_BASE_ADDR + 0X5000 )    //   4K
#define SYSTIMER_BASE_ADDR           (APB_PERP0_BASE_ADDR + 0X6000 )
#define GPIO1_BASE_ADDR              (APB_PERP0_BASE_ADDR + 0X7000 ) 
#define DEBUG_BASE_ADDR              (APB_PERP0_BASE_ADDR + 0X20000 )   //   128K

#define CRM_BASE_ADDR                SYSCTRL_BASE_ADDR 

// perp1
#define SPI0_BASE_ADDR              (APB_PERP1_BASE_ADDR + 0X0000 )    //   4K
#define SPI1_BASE_ADDR              (APB_PERP1_BASE_ADDR + 0X1000 )    //   4K
#define CAN_BASE_ADDR               (APB_PERP1_BASE_ADDR + 0X2000 )    //   4K
#define I2C0_BASE_ADDR              (APB_PERP1_BASE_ADDR + 0X3000 )    //   4K
#define UART0_BASE_ADDR             (APB_PERP1_BASE_ADDR + 0X4000 )    //   4K
#define UART1_BASE_ADDR             (APB_PERP1_BASE_ADDR + 0X5000 )    //   4K
#define I2C1_BASE_ADDR              (APB_PERP1_BASE_ADDR + 0X6000 )    //   4K
#define RESV2_PP1_BASE_ADDR         (APB_PERP1_BASE_ADDR + 0X7000 )    //   4K

#define UWB_BASE_ADDR               (AHB1_SLAVE_BASE_ADDR + 0x000000)
#define SE_BASE_ADDR                (AHB1_SLAVE_BASE_ADDR + 0x100000)
#define TEMP_BUF_BASE_ADDR          (AHB1_SLAVE_BASE_ADDR + 0x200000)
#define TX_BUF_BASE_ADDR            (AHB1_SLAVE_BASE_ADDR + 0x200400)
#define RX0_BUF_BASE_ADDR           (AHB1_SLAVE_BASE_ADDR + 0x200800)
#define RX1_BUF_BASE_ADDR           (AHB1_SLAVE_BASE_ADDR + 0x200c00)
#define RADAR_BASE_ADDR             (AHB1_SLAVE_BASE_ADDR + 0x300000)
#define SE_ADDR_OFFSET              0x100000
#define TEMP_BUF_ADDR_OFFSET        0x200000
#define TX_BUF_ADDR_OFFSET          0x200400
#define RX0_BUF_ADDR_OFFSET         0x200800
#define RX1_BUF_ADDR_OFFSET         0x200c00



#define KDF_CONTROL_REG           (SE_BASE_ADDR + 0x00)

#define NONCE_REG_0               (SE_BASE_ADDR + 0x04)
#define NONCE_REG_1               (SE_BASE_ADDR + 0x08)
#define NONCE_REG_2               (SE_BASE_ADDR + 0x0c)
#define NONCE_REG_3               (SE_BASE_ADDR + 0x10)
#define NONCE_REG_4               (SE_BASE_ADDR + 0x14)
#define NONCE_REG_5               (SE_BASE_ADDR + 0x18)
#define NONCE_REG_6               (SE_BASE_ADDR + 0x1c)
#define NONCE_REG_7               (SE_BASE_ADDR + 0x20)
#define NONCE_REG_8               (SE_BASE_ADDR + 0x24)
#define NONCE_REG_9               (SE_BASE_ADDR + 0x28)
#define NONCE_REG_10              (SE_BASE_ADDR + 0x2c)
#define NONCE_REG_11              (SE_BASE_ADDR + 0x30)


#define KDFFREEKEY_REG_0          (SE_BASE_ADDR + 0x34)
#define KDFFREEKEY_REG_1          (SE_BASE_ADDR + 0x38)
#define KDFFREEKEY_REG_2          (SE_BASE_ADDR + 0x3c)
#define KDFFREEKEY_REG_3          (SE_BASE_ADDR + 0x40)
#define KDFFREEKEY_REG_4          (SE_BASE_ADDR + 0x44)
#define KDFFREEKEY_REG_5          (SE_BASE_ADDR + 0x48)
#define KDFFREEKEY_REG_6          (SE_BASE_ADDR + 0x4c)
#define KDFFREEKEY_REG_7          (SE_BASE_ADDR + 0x50)

#define KDFKEYOUT_REG_0           (SE_BASE_ADDR + 0x54)
#define KDFKEYOUT_REG_1           (SE_BASE_ADDR + 0x58)
#define KDFKEYOUT_REG_2           (SE_BASE_ADDR + 0x5c)
#define KDFKEYOUT_REG_3           (SE_BASE_ADDR + 0x60)
#define KDFKEYOUT_REG_4           (SE_BASE_ADDR + 0x64)
#define KDFKEYOUT_REG_5           (SE_BASE_ADDR + 0x68)
#define KDFKEYOUT_REG_6           (SE_BASE_ADDR + 0x6c)
#define KDFKEYOUT_REG_7           (SE_BASE_ADDR + 0x70)

#define CCM_CONTROLLER_REG        (SE_BASE_ADDR + 0x74)
#define AES_CONTROLLER_REG        (SE_BASE_ADDR + 0x78)
#define DATA_CONTROL_REG          (SE_BASE_ADDR + 0x7c)
#define DATA_SIZE_REG             (SE_BASE_ADDR + 0x80)

#define STATUS_REG                (SE_BASE_ADDR + 0x84)
#define SE_INT_RAW                (SE_BASE_ADDR + 0x88)
#define SE_INT_FORCE              (SE_BASE_ADDR + 0x8c)
#define SE_INT_MASK               (SE_BASE_ADDR + 0x90)
#define SE_INT_STATUS             (SE_BASE_ADDR + 0x94)
#define ECBCONTROLREG             (SE_BASE_ADDR + 0x98)

#define SE_INT_ENABLE             (SE_BASE_ADDR + 0x88)

#define ROOT_KEY_REG_0            (SE_BASE_ADDR + 0x200)
#define ROOT_KEY_REG_1            (SE_BASE_ADDR + 0x204)
#define ROOT_KEY_REG_2            (SE_BASE_ADDR + 0x208)
#define ROOT_KEY_REG_3            (SE_BASE_ADDR + 0x20c)
#define LOAD_STORE_KEY            (SE_BASE_ADDR + 0x210)
#define LOAD_STORE_STATUS         (SE_BASE_ADDR + 0x214)
#define PERI_BASE                 (0x00000000)
#define PHYSICAL_ADDRESS(x)    (volatile CK_UINT32 *)((CK_UINT32)x - PERI_BASE)
#endif
