/*
 * Reg Interface C-Header [AUTOGENERATE by SpinalHDL]
 * 
 */

#ifndef __PAD_REG_H__
#define __PAD_REG_H__



#define GPIO_0_PREG        0x0000
#define GPIO_0_PREG_GPIO_0_PREG_SHIFT               0
#define GPIO_0_PREG_GPIO_0_PREG_MASK                0x000001ff //RW, 9 bit
#define GPIO_1_PREG        0x0004
#define GPIO_1_PREG_GPIO_1_PREG_SHIFT               0
#define GPIO_1_PREG_GPIO_1_PREG_MASK                0x000001ff //RW, 9 bit
#define GPIO_2_PREG        0x0008
#define GPIO_2_PREG_GPIO_2_PREG_SHIFT               0
#define GPIO_2_PREG_GPIO_2_PREG_MASK                0x000001ff //RW, 9 bit
#define GPIO_3_PREG        0x000c
#define GPIO_3_PREG_SHIFT                           0
#define GPIO_3_PREG_MASK                            0x000001ff //RW, 9 bit
#define GPIO_4_PREG        0x0010
#define GPIO_4_PREG_SHIFT                           0
#define GPIO_4_PREG_MASK                            0x000001ff //RW, 9 bit
#define SWDIO_PREG         0x0014
#define SWDIO_PREG_SWDIO_PREG_SHIFT                 0
#define SWDIO_PREG_SWDIO_PREG_MASK                  0x000001ff //RW, 9 bit
#define SWCLK_PREG         0x0018
#define SWCLK_PREG_SWCLK_PREG_SHIFT                 0
#define SWCLK_PREG_SWCLK_PREG_MASK                  0x000001ff //RW, 9 bit
#define I2C0_SCL_PREG      0x001c
#define I2C0_SCL_PREG_I2C0_SCL_PREG_SHIFT           0
#define I2C0_SCL_PREG_I2C0_SCL_PREG_MASK            0x000001ff //RW, 9 bit
#define I2C0_SDA_PREG      0x0020
#define I2C0_SDA_PREG_I2C0_SDA_PREG_SHIFT           0
#define I2C0_SDA_PREG_I2C0_SDA_PREG_MASK            0x000001ff //RW, 9 bit
#define SPI0_CLK_PREG      0x0024
#define SPI0_CLK_PREG_SPI0_CLK_PREG_SHIFT           0
#define SPI0_CLK_PREG_SPI0_CLK_PREG_MASK            0x000001ff //RW, 9 bit
#define SPI0_MISO_PREG     0x0028
#define SPI0_MISO_PREG_SPI0_MISO_PREG_SHIFT         0
#define SPI0_MISO_PREG_SPI0_MISO_PREG_MASK          0x000001ff //RW, 9 bit
#define SPI0_MOSI_PREG     0x002c
#define SPI0_MOSI_PREG_SPI0_MOSI_PREG_SHIFT         0
#define SPI0_MOSI_PREG_SPI0_MOSI_PREG_MASK          0x000001ff //RW, 9 bit
#define SPI1_CLK_PREG      0x0030
#define SPI1_CLK_PREG_SPI1_CLK_PREG_SHIFT           0
#define SPI1_CLK_PREG_SPI1_CLK_PREG_MASK            0x000001ff //RW, 9 bit
#define SPI1_MISO_PREG     0x0034
#define SPI1_MISO_PREG_SPI1_MISO_PREG_SHIFT         0
#define SPI1_MISO_PREG_SPI1_MISO_PREG_MASK          0x000001ff //RW, 9 bit
#define SPI1_MOSI_PREG     0x0038
#define SPI1_MOSI_PREG_SPI1_MOSI_PREG_SHIFT         0
#define SPI1_MOSI_PREG_SPI1_MOSI_PREG_MASK          0x000001ff //RW, 9 bit
#define UART0_RXD_PREG     0x003c
#define UART0_RXD_PREG_UART0_RXD_PREG_SHIFT         0
#define UART0_RXD_PREG_UART0_RXD_PREG_MASK          0x000001ff //RW, 9 bit
#define UART0_TXD_PREG     0x0040
#define UART0_TXD_PREG_UART0_TXD_PREG_SHIFT         0
#define UART0_TXD_PREG_UART0_TXD_PREG_MASK          0x000001ff //RW, 9 bit
#define QSPI_CLK_PREG      0x0044
#define QSPI_CLK_PREG_QSPI_CLK_PREG_SHIFT           0
#define QSPI_CLK_PREG_QSPI_CLK_PREG_MASK            0x000001ff //RW, 9 bit
#define QSPI_CSN_PREG      0x0048
#define QSPI_CSN_PREG_QSPI_CSN_PREG_SHIFT           0
#define QSPI_CSN_PREG_QSPI_CSN_PREG_MASK            0x000001ff //RW, 9 bit
#define QSPI_SIO_IO0_PREG  0x004c
#define QSPI_SIO_IO0_PREG_QSPI_SIO_IO0_PREG_SHIFT   0
#define QSPI_SIO_IO0_PREG_QSPI_SIO_IO0_PREG_MASK    0x000001ff //RW, 9 bit
#define QSPI_SOI_IO1_PREG  0x0050
#define QSPI_SOI_IO1_PREG_QSPI_SOI_IO1_PREG_SHIFT   0
#define QSPI_SOI_IO1_PREG_QSPI_SOI_IO1_PREG_MASK    0x000001ff //RW, 9 bit
#define QSPI_WP_IO2_PREG   0x0054
#define QSPI_WP_IO2_PREG_QSPI_WP_IO2_PREG_SHIFT     0
#define QSPI_WP_IO2_PREG_QSPI_WP_IO2_PREG_MASK      0x000001ff //RW, 9 bit
#define QSPI_HOLD_IO3_PREG 0x0058
#define QSPI_HOLD_IO3_PREG_QSPI_HOLD_IO3_PREG_SHIFT 0
#define QSPI_HOLD_IO3_PREG_QSPI_HOLD_IO3_PREG_MASK  0x000001ff //RW, 9 bit
#define CAN_TXD_PREG       0x005c
#define CAN_TXD_PREG_CAN_TXD_PREG_SHIFT             0
#define CAN_TXD_PREG_CAN_TXD_PREG_MASK              0x000001ff //RW, 9 bit
#define CAN_STBY_PREG      0x0060
#define CAN_STBY_PREG_CAN_STBY_PREG_SHIFT           0
#define CAN_STBY_PREG_CAN_STBY_PREG_MASK            0x000001ff //RW, 9 bit

/*************these three gpio pins are not brought out in the package*****************/
#define GPIO_25_PREG        0x0064
#define GPIO_25_PREG_GPIO_3_PREG_SHIFT              0
#define GPIO_25_PREG_GPIO_3_PREG_MASK               0x000001ff //RW, 9 bit
#define GPIO_26_PREG        0x0068
#define GPIO_26_PREG_GPIO_4_PREG_SHIFT              0
#define GPIO_26_PREG_GPIO_4_PREG_MASK               0x000001ff //RW, 9 bit
#define GPIO_27_PREG        0x006c
#define GPIO_27_PREG_GPIO_5_PREG_SHIFT              0
#define GPIO_27_PREG_GPIO_5_PREG_MASK               0x000001ff //RW, 9 bit


#define CAN_RXD_PREG       0x0070
#define CAN_RXD_PREG_CAN_RXD_PREG_SHIFT             0
#define CAN_RXD_PREG_CAN_RXD_PREG_MASK              0x00000007 //RW, 3 bit
#define SPI0_CSN_PREG      0x0074
#define SPI0_CSN_PREG_SPI0_CSN_PREG_SHIFT           0
#define SPI0_CSN_PREG_SPI0_CSN_PREG_MASK            0x00000007 //RW, 3 bit
#define SPI1_CSN_PREG      0x0078
#define SPI1_CSN_PREG_SPI1_CSN_PREG_SHIFT           0
#define SPI1_CSN_PREG_SPI1_CSN_PREG_MASK            0x00000007 //RW, 3 bit
#define BOOT0_PREG         0x007c
#define BOOT0_PREG_BOOT0_PREG_SHIFT                 0
#define BOOT0_PREG_BOOT0_PREG_MASK                  0x00000007 //RW, 3 bit
#define BOOT1_PREG         0x0080
#define BOOT1_PREG_BOOT1_PREG_SHIFT                 0
#define BOOT1_PREG_BOOT1_PREG_MASK                  0x00000007 //RW, 3 bit
#define SEL_GROUP          0x0100
#define SEL_GROUP_SELGP_SYNC_SHIFT                  0
#define SEL_GROUP_SELGP_SYNC_MASK                   0x00000001 //RW, 1 bit
#define SEL_GROUP_SELGP_QSPI_SHIFT                  1
#define SEL_GROUP_SELGP_QSPI_MASK                   0x00000002 //RW, 1 bit
#define SEL_GROUP_SELGP_UART1_SHIFT                 2
#define SEL_GROUP_SELGP_UART1_MASK                  0x0000000c //RW, 2 bit
#define SEL_GROUP_SELGP_CAN_RXD_SHIFT               4
#define SEL_GROUP_SELGP_CAN_RXD_MASK                0x00000010 //RW, 1 bit
#define SEL_GROUP_SELGP_I2C1_SCL_SHIFT              5
#define SEL_GROUP_SELGP_I2C1_SCL_MASK               0x00000020 //RW, 1 bit
#define SEL_GROUP_SELGP_I2C1_SDA_SHIFT              6
#define SEL_GROUP_SELGP_I2C1_SDA_MASK               0x00000040 //RW, 1 bit



/*GPIOA0*/
#define GPIOA0_AF_REV0          (0)
#define GPIOA0_AF_GPIO          (1)
#define GPIOA0_AF_RX1_EN        (2)
#define GPIOA0_AF_TX_EN         (3)
#define GPIOA0_AF_RX0_EN        (4)
#define GPIOA0_AF_PWM_0         (5)
#define GPIOA0_AF_RX_RFSL       (6)



/*GPIOA1*/
#define GPIOA1_AF_REV0          (0)
#define GPIOA1_AF_GPIO          (1)
#define GPIOA1_AF_REV2          (2)
#define GPIOA1_AF_REV3          (3)
#define GPIOA1_AF_REV4          (4)
#define GPIOA1_AF_REV5          (5)
#define GPIOA1_AF_REV6          (6)




/*GPIOA2*/
#define GPIOA2_AF_REV0          (0)
#define GPIOA2_AF_GPIO          (1)
#define GPIOA2_AF_REV2          (2)
#define GPIOA2_AF_REV3          (3)
#define GPIOA2_AF_REV4          (4)
#define GPIOA2_AF_REV5          (5)
#define GPIOA2_AF_REV6          (6)



/*GPIOA3*/                
#define GPIOA3_AF_CAN_TXD                       (0)
#define GPIOA3_AF_GPIO                          (1)
#define GPIOA3_AF_REV2                          (2)
#define GPIOA3_AF_REV3                          (3)
#define GPIOA3_AF_REV4                          (4)
#define GPIOA3_AF_REV5                          (5)

/*GPIOA4*/
#define GPIOA4_AF_CAN_STBY                      (0)
#define GPIOA4_AF_GPIO                          (1)
#define GPIOA4_AF_REV2                          (2)
#define GPIOA4_AF_REV3                          (3)
#define GPIOA4_AF_REV4                          (4)
#define GPIOA4_AF_REV5                          (5)

/*GPIOA5*/
#define GPIOA5_AF_SWDIO                         (0)
#define GPIOA5_AF_GPIO                          (1)
#define GPIOA5_AF_REV2                          (2)
#define GPIOA5_AF_I2C1_SCL                      (3)
#define GPIOA5_AF_UART1_RXD                     (4)
#define GPIOA5_AF_REV5                          (5)
#define GPIOA5_AF_REV6                          (6)

/*GPIOA6*/
#define GPIOA6_AF_SWCLK                         (0)
#define GPIOA6_AF_GPIO                          (1)
#define GPIOA6_AF_REV2                          (2)
#define GPIOA6_AF_I2C1_SDA                      (3)
#define GPIOA6_AF_UART1_TXD                     (4)
#define GPIOA6_AF_REV5                          (5)
#define GPIOA6_AF_REV6                          (6)

/*GPIOA7*/
#define GPIOA7_AF_I2C0_SCL                      (0)
#define GPIOA7_AF_GPIO                          (1)
#define GPIOA7_AF_RX1_EN                        (2)
#define GPIOA7_AF_RX0_EN                        (3)
#define GPIOA7_AF_UART1_RXD                     (4)
#define GPIOA7_AF_SPI1_CS1                      (5)
#define GPIOA7_AF_REV6                          (6)
#define GPIOA7_AF_ANT_SW0                       (7)

/*GPIOA8*/
#define GPIOA8_AF_I2C0_SDA                      (0)
#define GPIOA8_AF_GPIO                          (1)
#define GPIOA8_AF_RX1_DONE_WRAP                 (2)
#define GPIOA8_AF_SYNC                          (3)
#define GPIOA8_AF_UART1_TXD                     (4)
#define GPIOA8_AF_SPI0_CS1                      (5)
#define GPIOA8_AF_REV6                          (6)
#define GPIOA8_AF_ANT_SW1                       (7)

/*GPIOA9*/        
#define GPIOA9_AF_SPI0_CLK                       (0)
#define GPIOA9_AF_GPIO                           (1)
#define GPIOA9_AF_TX_EN                          (2)
#define GPIOA9_AF_I2C1_SCL                       (3)
#define GPIOA9_AF_UART1_RXD                      (4)
#define GPIOA9_AF_REV5                           (5)
#define GPIOA9_AF_dbg_clk_out_mux                (6)
#define GPIOA9_AF_QSPI_CLK                       (7)

/*GPIOA10*/
#define GPIOA10_AF_SPI0_MISO                     (0)
#define GPIOA10_AF_GPIO                          (1)
#define GPIOA10_AF_TX_DONE_WARP                  (2)
#define GPIOA10_AF_I2C1_SDA                      (3)
#define GPIOA10_AF_UART1_TXD                     (4)
#define GPIOA10_AF_REV5                          (5)
#define GPIOA10_AF_dout_clk_32khz_1p1_dbg        (6)
#define GPIOA10_AF_QSPI_CSN                      (7)



/*GPIOA11*/
#define GPIOA11_AF_SPI0_MOSI                       (0)
#define GPIOA11_AF_GPIO                            (1)
#define GPIOA11_AF_TXLED                           (2)
#define GPIOA11_AF_RX_PHE                          (3)
#define GPIOA11_AF_REV4                            (4)
#define GPIOA11_AF_REV5                            (5)
#define GPIOA11_AF_REV6                            (6)
#define GPIOA11_AF_QSPI_SIO_IO0                    (7)


/*GPIOA12*/
#define GPIOA12_AF_SPI1_CLK                       (0)
#define GPIOA12_AF_GPIO                           (1)
#define GPIOA12_AF_EXLED                          (2)
#define GPIOA12_AF_RX_RFSL                        (3)
#define GPIOA12_AF_CAN_TXD                        (4)
#define GPIOA12_AF_PWM_0                          (5)
#define GPIOA12_AF_dout_xo_tstclkrdy_1v           (6)
#define GPIOA12_AF_QSPI_SIO_IO1                   (7)


/*GPIOA13*/        
#define GPIOA13_AF_SPI1_MISO                      (0)
#define GPIOA13_AF_GPIO                           (1)
#define GPIOA13_AF_RXOK                           (2)
#define GPIOA13_AF_TX_EN                          (3)
#define GPIOA13_AF_REV4                           (4)
#define GPIOA13_AF_PWM_1                          (5)
#define GPIOA13_AF_d_efuse_vqps_en_1p1            (6)
#define GPIOA13_AF_QSPI_WP_IO2                    (7)


/*GPIOA14*/
#define GPIOA14_AF_SPI1_MOSI                      (0)
#define GPIOA14_AF_GPIO                           (1)
#define GPIOA14_AF_SYNC                           (2)
#define GPIOA14_AF_RX1_DONE_WRAP                  (3)
#define GPIOA14_AF_CAN_STBY                       (4)
#define GPIOA14_AF_PWM_2                          (5)
#define GPIOA14_AF_RXLED                          (6)
#define GPIOA14_AF_QSPI_HOLD_IO3                  (7)

/*GPIOA15*/
#define GPIOA15_AF_UART0_RXD                       (0)
#define GPIOA15_AF_GPIO                            (1)
#define GPIOA15_AF_TXLED                           (2)
#define GPIOA15_AF_SPI1_CS1                        (3)
#define GPIOA15_AF_RX0_DONE_WRAP                   (4)
#define GPIOA15_AF_TX_DONE_WRAP                    (5)
#define GPIOA15_AF_CAN_TXD                         (6)
#define GPIOA15_AF_REV7                            (7)


/*GPIOA16*/            
#define GPIOA16_AF_UART0_TXD                       (0)
#define GPIOA16_AF_GPIO                            (1)
#define GPIOA16_AF_RXLED                           (2)
#define GPIOA16_AF_SPI0_CS1                        (3)
#define GPIOA16_AF_TX_DONE_WRAP                    (4)
#define GPIOA16_AF_RX0_DONE_WRAP                   (5)
#define GPIOA16_AF_CAN_STBY                        (6)
#define GPIOA16_AF_REV7                            (7)


/*GPIOA17*/
#define GPIOA17_AF_QSPI_CLK                        (0)
#define GPIOA17_AF_GPIO                            (1)


/*GPIOA18*/
#define GPIOA18_AF_QSPI_CSN                        (0)
#define GPIOA18_AF_GPIO                            (1)

/*GPIOA19*/
#define GPIOA19_AF_QSPI_SIO_IO0                    (0)
#define GPIOA19_AF_GPIO                            (1)

/*GPIOA20*/
#define GPIOA20_AF_QSPI_SIO_IO1                    (0)
#define GPIOA20_AF_GPIO                            (1)


/*GPIOA21*/
#define GPIOA21_AF_QSPI_WP_IO2                     (0)
#define GPIOA21_AF_GPIO                            (1)

/*GPIOA22*/
#define GPIOA22_AF_QSPI_HOLD_IO3                   (0)
#define GPIOA22_AF_GPIO                            (1)



/*GPIOA23*/
#define GPIOA23_AF_CAN_TXD                        (0)
#define GPIOA23_AF_GPIO                           (1)
#define GPIOA23_AF_TX_EN                          (2)
#define GPIOA23_AF_RX1_EN                         (3)
#define GPIOA23_AF_RX0_EN                         (4)
#define GPIOA23_AF_PWM_1                          (5)
#define GPIOA23_AF_RX_PHE                         (6)


/*GPIOA24*/
#define GPIOA24_AF_CAN_STBY                         (0)
#define GPIOA24_AF_GPIO                             (1)
#define GPIOA24_AF_RX0_DONE_WRAP                    (2)
#define GPIOA24_AF_TX_DONE_WRAP                     (3)
#define GPIOA24_AF_RX0_EN                           (4)
#define GPIOA24_AF_PWM_2                            (5)
#define GPIOA24_AF_RXLED                            (6)


/*************these three gpio pins are not brought out in the package*****************/
/*GPIOA25*/
#define GPIOA25_AF_REV0                             (0)
#define GPIOA25_AF_GPIO                             (1)


/*GPIOA26*/
#define GPIOA26_AF_REV0                             (0)
#define GPIOA26_AF_GPIO                             (1)


/*GPIOA27*/
#define GPIOA27_AF_REV0                             (0)
#define GPIOA27_AF_GPIO                             (1)


/*GPIOB0*/            
#define GPIOB0_AF_CAN_RXD                           (0)
#define GPIOB0_AF_GPIO                              (1)
#define GPIOB0_AF_REV2                              (2)
#define GPIOB0_AF_TXLED                             (3)
#define GPIOB0_AF_REV4                              (4)
#define GPIOB0_AF_RX1_DONE_WRAP                     (5)
#define GPIOB0_AF_REV6                              (6)
#define GPIOB0_AF_REV7                              (7)

/*GPIOB1*/
#define GPIOB1_AF_SPI0_CS0                          (0)
#define GPIOB1_AF_GPIO                              (1)


/*GPIOB2*/
#define GPIOB2_AF_SPI1_CS0                          (0)
#define GPIOB2_AF_GPIO                              (1)



/*GPIOB3*/
#define GPIOB3_AF_BOOT0                             (0)
#define GPIOB3_AF_GPIO                              (1)


/*GPIOB4*/
#define GPIOB4_AF_BOOT1                             (0)
#define GPIOB4_AF_GPIO                              (1)



#endif /* PAD_REG_REGIF_H */
