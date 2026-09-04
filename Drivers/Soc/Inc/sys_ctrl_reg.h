/*
 * Reg Interface C-Header [AUTOGENERATE by SpinalHDL]
 * 
 */

#ifndef __SYS_CTRL_REG_H
#define __SYS_CTRL_REG_H

#define CHIP_ID_REG             0x0000
#define CHIP_ID_REG_CHIP_ID_SHIFT                                0
#define CHIP_ID_REG_CHIP_ID_MASK                                 0x00000000 //RO, 32 bit
#define BOOT_MODE_REG           0x0004
#define BOOT_MODE_REG_BOOT_MODE_SHIFT                            0
#define BOOT_MODE_REG_BOOT_MODE_MASK                             0x00000007 //RO, 3 bit
#define CPU0_BOOT_ADDR          0x0008
#define CPU0_BOOT_ADDR_BOOT_ADDR_EN_SHIFT                        0
#define CPU0_BOOT_ADDR_BOOT_ADDR_EN_MASK                         0x00000001 //RW, 1 bit
#define CPU0_BOOT_ADDR_BOOT_ADDR_SHIFT                           7
#define CPU0_BOOT_ADDR_BOOT_ADDR_MASK                            0xffffff80 //RW, 25 bit
#define CPU_CTRL_REG            0x000c
#define CPU_CTRL_REG_L1RSTDISABLE_SHIFT                          0
#define CPU_CTRL_REG_L1RSTDISABLE_MASK                           0x00000001 //RW, 1 bit
#define CPU_CTRL_REG_DBGEN_SHIFT                                 1
#define CPU_CTRL_REG_DBGEN_MASK                                  0x00000002 //RW, 1 bit
#define CPU_CTRL_REG_LOCKUP_EN_SHIFT                             2
#define CPU_CTRL_REG_LOCKUP_EN_MASK                              0x00000004 //RW, 1 bit
#define CPU_CTRL_REG_CORERET_SHIFT                               8
#define CPU_CTRL_REG_CORERET_MASK                                0x00000100 //RW, 1 bit
#define CPU_CTRL_REG_FPURET_SHIFT                                9
#define CPU_CTRL_REG_FPURET_MASK                                 0x00000200 //RW, 1 bit
#define CPU_CTRL_REG_DBGRET_SHIFT                                10
#define CPU_CTRL_REG_DBGRET_MASK                                 0x00000400 //RW, 1 bit
#define CPU_CTRL_REG_RAMSRET_SHIFT                               11
#define CPU_CTRL_REG_RAMSRET_MASK                                0x00000800 //RW, 1 bit
#define CPU_QSPI_REG            0x0010
#define CPU_QSPI_REG_INITQSPISCKMODE_SHIFT                       0
#define CPU_QSPI_REG_INITQSPISCKMODE_MASK                        0x00000001 //RW, 1 bit
#define CPU_QSPI_REG_INITQSPIADDRSEL_SHIFT                       1
#define CPU_QSPI_REG_INITQSPIADDRSEL_MASK                        0x00000002 //RW, 1 bit
#define CPU_QSPI_REG_INITQSPIXPREN_SHIFT                         2
#define CPU_QSPI_REG_INITQSPIXPREN_MASK                          0x00000004 //RW, 1 bit
#define CPU_QSPI_REG_INITQSPIXPRDDRMODE_SHIFT                    3
#define CPU_QSPI_REG_INITQSPIXPRDDRMODE_MASK                     0x00000008 //RW, 1 bit
#define CPU_QSPI_REG_INITQSPIXPRNUMDC_SHIFT                      4
#define CPU_QSPI_REG_INITQSPIXPRNUMDC_MASK                       0x000001f0 //RW, 5 bit
#define CPU_QSPI_REG_INITQSPIXPRXFERMODE_SHIFT                   9
#define CPU_QSPI_REG_INITQSPIXPRXFERMODE_MASK                    0x00000600 //RW, 2 bit
#define CPU_QSPI_REG_INITQSPIXPRALBSIZE_SHIFT                    11
#define CPU_QSPI_REG_INITQSPIXPRALBSIZE_MASK                     0x00000800 //RW, 1 bit
#define CPU_QSPI_REG_INITQSPIXPRALTBYTES_SHIFT                   12
#define CPU_QSPI_REG_INITQSPIXPRALTBYTES_MASK                    0x000ff000 //RW, 8 bit
#define TIMER_STATUS            0x0014
#define TIMER_STATUS_TIMER_EN_SHIFT                              0
#define TIMER_STATUS_TIMER_EN_MASK                               0x00000007 //RO, 3 bit
#define TIMER_STATUS_TIMER_PAUSE_SHIFT                           8
#define TIMER_STATUS_TIMER_PAUSE_MASK                            0x00000700 //RW, 3 bit
#define BOOT_STATUS             0x0018
#define BOOT_STATUS_BOOT0_LATCH_SHIFT                            0
#define BOOT_STATUS_BOOT0_LATCH_MASK                             0x00000001 //RO, 1 bit
#define BOOT_STATUS_BOOT1_LATCH_SHIFT                            1
#define BOOT_STATUS_BOOT1_LATCH_MASK                             0x00000002 //RO, 1 bit
#define BOOT_STATUS_BOOT0_SHIFT                                  2
#define BOOT_STATUS_BOOT0_MASK                                   0x00000004 //RO, 1 bit
#define BOOT_STATUS_BOOT1_SHIFT                                  3
#define BOOT_STATUS_BOOT1_MASK                                   0x00000008 //RO, 1 bit
#define DEBUG_CONFIG            0x001c
#define DEBUG_CONFIG_SWD_OUT_DELAY_REG_SHIFT                     0
#define DEBUG_CONFIG_SWD_OUT_DELAY_REG_MASK                      0x00000001 //RW, 1 bit
#define DEBUG_CONFIG_SWD_IN_DELAY_REG_SHIFT                      1
#define DEBUG_CONFIG_SWD_IN_DELAY_REG_MASK                       0x00000002 //RW, 1 bit
#define REG_GLB_SW_RST          0x0400
#define REG_GLB_SW_RST_GLB_SW_RST_SHIFT                          0
#define REG_GLB_SW_RST_GLB_SW_RST_MASK                           0x0000ffff //RW, 16 bit
#define REG_GLB_SW_WIDTH        0x0404
#define REG_GLB_SW_WIDTH_GLB_SW_RST_WIDTH_SHIFT                  0
#define REG_GLB_SW_WIDTH_GLB_SW_RST_WIDTH_MASK                   0x0000ffff //RW, 16 bit
#define BLK_SW_RSTN0            0x0408
#define BLK_SW_RSTN0_DMA_SW_RSTN_SHIFT                           0
#define BLK_SW_RSTN0_DMA_SW_RSTN_MASK                            0x00000001 //RW, 1 bit
#define BLK_SW_RSTN0_UART_SW_RSTN_SHIFT                          1
#define BLK_SW_RSTN0_UART_SW_RSTN_MASK                           0x00000002 //RW, 1 bit
#define BLK_SW_RSTN0_WDT_SW_RSTN_SHIFT                           2
#define BLK_SW_RSTN0_WDT_SW_RSTN_MASK                            0x00000004 //RW, 1 bit
#define BLK_SW_RSTN0_TIMER0_SW_RSTN_SHIFT                        3
#define BLK_SW_RSTN0_TIMER0_SW_RSTN_MASK                         0x00000008 //RW, 1 bit
#define BLK_SW_RSTN0_TIMER1_SW_RSTN_SHIFT                        4
#define BLK_SW_RSTN0_TIMER1_SW_RSTN_MASK                         0x00000010 //RW, 1 bit
#define BLK_SW_RSTN0_TIMER2_SW_RSTN_SHIFT                        5
#define BLK_SW_RSTN0_TIMER2_SW_RSTN_MASK                         0x00000020 //RW, 1 bit
#define BLK_SW_RSTN0_I2C_SW_RSTN_SHIFT                           6
#define BLK_SW_RSTN0_I2C_SW_RSTN_MASK                            0x00000040 //RW, 1 bit
#define BLK_SW_RSTN0_SE_SW_RSTN_SHIFT                            7
#define BLK_SW_RSTN0_SE_SW_RSTN_MASK                             0x00000080 //RW, 1 bit
#define BLK_SW_RSTN0_SE_SW_HRSTN_SHIFT                           8
#define BLK_SW_RSTN0_SE_SW_HRSTN_MASK                            0x00000100 //RW, 1 bit
#define BLK_SW_RSTN0_CAN_SW_PRSTN_SHIFT                          9
#define BLK_SW_RSTN0_CAN_SW_PRSTN_MASK                           0x00000200 //RW, 1 bit
#define BLK_SW_RSTN0_CAN_SW_RSTN_SHIFT                           10
#define BLK_SW_RSTN0_CAN_SW_RSTN_MASK                            0x00000400 //RW, 1 bit
#define BLK_SW_RSTN0_SPI0_SW_RSTN_SHIFT                          11
#define BLK_SW_RSTN0_SPI0_SW_RSTN_MASK                           0x00000800 //RW, 1 bit
#define BLK_SW_RSTN0_SPI1_SW_RSTN_SHIFT                          12
#define BLK_SW_RSTN0_SPI1_SW_RSTN_MASK                           0x00001000 //RW, 1 bit
#define BLK_SW_RSTN0_TIMER_SW_PRSTN_SHIFT                        13
#define BLK_SW_RSTN0_TIMER_SW_PRSTN_MASK                         0x00002000 //RW, 1 bit
#define BLK_SW_RSTN0_UART_SW_PRSTN_SHIFT                         14
#define BLK_SW_RSTN0_UART_SW_PRSTN_MASK                          0x00004000 //RW, 1 bit
#define BLK_SW_RSTN0_I2C_SW_PRSTN_SHIFT                          15
#define BLK_SW_RSTN0_I2C_SW_PRSTN_MASK                           0x00008000 //RW, 1 bit
#define BLK_SW_RSTN0_WDT_SW_PRSTN_SHIFT                          16
#define BLK_SW_RSTN0_WDT_SW_PRSTN_MASK                           0x00010000 //RW, 1 bit
#define BLK_SW_RSTN0_GPIO_SW_PRSTN_SHIFT                         17
#define BLK_SW_RSTN0_GPIO_SW_PRSTN_MASK                          0x00020000 //RW, 1 bit
#define BLK_SW_RSTN0_SYSTIMER_SW_PRSTN_SHIFT                     18
#define BLK_SW_RSTN0_SYSTIMER_SW_PRSTN_MASK                      0x00040000 //RW, 1 bit
#define BLK_SW_RSTN0_SYSTIMER_SW_RSTN_SHIFT                      19
#define BLK_SW_RSTN0_SYSTIMER_SW_RSTN_MASK                       0x00080000 //RW, 1 bit
#define BLK_SW_RSTN0_UART1_SW_RSTN_SHIFT                         20
#define BLK_SW_RSTN0_UART1_SW_RSTN_MASK                          0x00100000 //RW, 1 bit
#define BLK_SW_RSTN0_I2C1_SW_RSTN_SHIFT                          21
#define BLK_SW_RSTN0_I2C1_SW_RSTN_MASK                           0x00200000 //RW, 1 bit
#define BLK_SW_RSTN0_RADAR_SW_RSTN_SHIFT                         22
#define BLK_SW_RSTN0_RADAR_SW_RSTN_MASK                          0x00400000 //RW, 1 bit
#define CLK_ICG_REG             0x040c
#define CLK_ICG_REG_DMA_CLK_ICG_SHIFT                            0
#define CLK_ICG_REG_DMA_CLK_ICG_MASK                             0x00000001 //RW, 1 bit
#define CLK_ICG_REG_UART_CLK_ICG_SHIFT                           1
#define CLK_ICG_REG_UART_CLK_ICG_MASK                            0x00000002 //RW, 1 bit
#define CLK_ICG_REG_WDT_CLK_ICG_SHIFT                            2
#define CLK_ICG_REG_WDT_CLK_ICG_MASK                             0x00000004 //RW, 1 bit
#define CLK_ICG_REG_TIMER0_CLK_ICG_SHIFT                         3
#define CLK_ICG_REG_TIMER0_CLK_ICG_MASK                          0x00000008 //RW, 1 bit
#define CLK_ICG_REG_TIMER1_CLK_ICG_SHIFT                         4
#define CLK_ICG_REG_TIMER1_CLK_ICG_MASK                          0x00000010 //RW, 1 bit
#define CLK_ICG_REG_TIMER2_CLK_ICG_SHIFT                         5
#define CLK_ICG_REG_TIMER2_CLK_ICG_MASK                          0x00000020 //RW, 1 bit
#define CLK_ICG_REG_I2C_CLK_ICG_SHIFT                            6
#define CLK_ICG_REG_I2C_CLK_ICG_MASK                             0x00000040 //RW, 1 bit
#define CLK_ICG_REG_SE_CLK_ICG_SHIFT                             7
#define CLK_ICG_REG_SE_CLK_ICG_MASK                              0x00000080 //RW, 1 bit
#define CLK_ICG_REG_SE_HCLK_ICG_SHIFT                            8
#define CLK_ICG_REG_SE_HCLK_ICG_MASK                             0x00000100 //RW, 1 bit
#define CLK_ICG_REG_CAN_PCLK_ICG_SHIFT                           9
#define CLK_ICG_REG_CAN_PCLK_ICG_MASK                            0x00000200 //RW, 1 bit
#define CLK_ICG_REG_CAN_CLK_ICG_SHIFT                            10
#define CLK_ICG_REG_CAN_CLK_ICG_MASK                             0x00000400 //RW, 1 bit
#define CLK_ICG_REG_SPI0_CLK_ICG_SHIFT                           11
#define CLK_ICG_REG_SPI0_CLK_ICG_MASK                            0x00000800 //RW, 1 bit
#define CLK_ICG_REG_SPI1_CLK_ICG_SHIFT                           12
#define CLK_ICG_REG_SPI1_CLK_ICG_MASK                            0x00001000 //RW, 1 bit
#define CLK_ICG_REG_TIMER_PCLK_ICG_SHIFT                         13
#define CLK_ICG_REG_TIMER_PCLK_ICG_MASK                          0x00002000 //RW, 1 bit
#define CLK_ICG_REG_UART_PCLK_ICG_SHIFT                          14
#define CLK_ICG_REG_UART_PCLK_ICG_MASK                           0x00004000 //RW, 1 bit
#define CLK_ICG_REG_I2C_PCLK_ICG_SHIFT                           15
#define CLK_ICG_REG_I2C_PCLK_ICG_MASK                            0x00008000 //RW, 1 bit
#define CLK_ICG_REG_WDT_PCLK_ICG_SHIFT                           16
#define CLK_ICG_REG_WDT_PCLK_ICG_MASK                            0x00010000 //RW, 1 bit
#define CLK_ICG_REG_GPIO_PCLK_ICG_SHIFT                          17
#define CLK_ICG_REG_GPIO_PCLK_ICG_MASK                           0x00020000 //RW, 1 bit
#define CLK_ICG_REG_SYSTIMER_PCLK_ICG_SHIFT                      18
#define CLK_ICG_REG_SYSTIMER_PCLK_ICG_MASK                       0x00040000 //RW, 1 bit
#define CLK_ICG_REG_SYSTIMER_CLK_ICG_SHIFT                       19
#define CLK_ICG_REG_SYSTIMER_CLK_ICG_MASK                        0x00080000 //RW, 1 bit
#define CLK_ICG_REG_UART1_CLK_ICG_SHIFT                          20
#define CLK_ICG_REG_UART1_CLK_ICG_MASK                           0x00100000 //RW, 1 bit
#define CLK_ICG_REG_I2C1_CLK_ICG_SHIFT                           21
#define CLK_ICG_REG_I2C1_CLK_ICG_MASK                            0x00200000 //RW, 1 bit
#define CLK_ICG_REG_RADAR_CLK_ICG_SHIFT                          22
#define CLK_ICG_REG_RADAR_CLK_ICG_MASK                           0x00400000 //RW, 1 bit
#define SOC_CLK_CFG             0x0410
#define SOC_CLK_CFG_SOC_CLK_SEL_SHIFT                            0
#define SOC_CLK_CFG_SOC_CLK_SEL_MASK                             0x00000003 //RW, 2 bit
#define SOC_CLK_CFG_SOC_CLK_DIV_SHIFT                            4
#define SOC_CLK_CFG_SOC_CLK_DIV_MASK                             0x000000f0 //RW, 4 bit
#define SOC_CLK_CFG_SOC_HIGH_CLK_SEL_SHIFT                       8
#define SOC_CLK_CFG_SOC_HIGH_CLK_SEL_MASK                        0x00000100 //RW, 1 bit
#define SOC_CLK_CFG_PERP_HIGH_CLK_SEL_SHIFT                      9
#define SOC_CLK_CFG_PERP_HIGH_CLK_SEL_MASK                       0x00000200 //RW, 1 bit
#define SOC_CLK_CFG_SOC_CLK_FORCE_SWITCH_EN_SHIFT                20
#define SOC_CLK_CFG_SOC_CLK_FORCE_SWITCH_EN_MASK                 0x00100000 //RW, 1 bit
#define SOC_CLK_CFG_SOC_CLK_DIV_TOG_SHIFT                        31
#define TIMER0_CLK_CFG          0x0414
#define TIMER0_CLK_CFG_TIMER0_CLK_SEL_SHIFT                      0
#define TIMER0_CLK_CFG_TIMER0_CLK_SEL_MASK                       0x00000003 //RW, 2 bit
#define TIMER0_CLK_CFG_TIMER0_CLK_DIV_SHIFT                      4
#define TIMER0_CLK_CFG_TIMER0_CLK_DIV_MASK                       0x000000f0 //RW, 4 bit
#define TIMER0_CLK_CFG_TIMER0_CLK_DIV_TOG_SHIFT                  31
#define TIMER1_CLK_CFG          0x0418
#define TIMER1_CLK_CFG_TIMER1_CLK_SEL_SHIFT                      0
#define TIMER1_CLK_CFG_TIMER1_CLK_SEL_MASK                       0x00000003 //RW, 2 bit
#define TIMER1_CLK_CFG_TIMER1_CLK_DIV_SHIFT                      4
#define TIMER1_CLK_CFG_TIMER1_CLK_DIV_MASK                       0x000000f0 //RW, 4 bit
#define TIMER1_CLK_CFG_TIMER1_CLK_DIV_TOG_SHIFT                  31
#define TIMER2_CLK_CFG          0x041c
#define TIMER2_CLK_CFG_TIMER2_CLK_SEL_SHIFT                      0
#define TIMER2_CLK_CFG_TIMER2_CLK_SEL_MASK                       0x00000003 //RW, 2 bit
#define TIMER2_CLK_CFG_TIMER2_CLK_DIV_SHIFT                      4
#define TIMER2_CLK_CFG_TIMER2_CLK_DIV_MASK                       0x000000f0 //RW, 4 bit
#define TIMER2_CLK_CFG_TIMER2_CLK_DIV_TOG_SHIFT                  31
#define CAN_CLK_CFG             0x0420
#define CAN_CLK_CFG_CAN_CLK_SEL_SHIFT                            0
#define CAN_CLK_CFG_CAN_CLK_SEL_MASK                             0x00000001 //RW, 1 bit
#define CAN_CLK_CFG_CAN_CLK_DIV_SHIFT                            4
#define CAN_CLK_CFG_CAN_CLK_DIV_MASK                             0x000000f0 //RW, 4 bit
#define CAN_CLK_CFG_CAN_CLK_DIV_TOG_SHIFT                        31
#define I2C_CLK_CFG             0x0424
#define I2C_CLK_CFG_I2C_CLK_SEL_SHIFT                            0
#define I2C_CLK_CFG_I2C_CLK_SEL_MASK                             0x00000001 //RW, 1 bit
#define I2C_CLK_CFG_I2C_CLK_DIV_SHIFT                            4
#define I2C_CLK_CFG_I2C_CLK_DIV_MASK                             0x000000f0 //RW, 4 bit
#define I2C_CLK_CFG_I2C_CLK_DIV_TOG_SHIFT                        31
#define SYSTIMER_CLK_CFG        0x0428
#define SYSTIMER_CLK_CFG_SYSTIMER_CLK_SEL_SHIFT                  0
#define SYSTIMER_CLK_CFG_SYSTIMER_CLK_SEL_MASK                   0x00000003 //RW, 2 bit
#define SYSTIMER_CLK_CFG_SYSTIMER_CLK_DIV_SHIFT                  4
#define SYSTIMER_CLK_CFG_SYSTIMER_CLK_DIV_MASK                   0x000001f0 //RW, 5 bit
#define SYSTIMER_CLK_CFG_SYSTIMER_CLK_DIV_TOG_SHIFT              31
#define WDT_CLK_CFG             0x042c
#define WDT_CLK_CFG_WDT_CLK_SEL_SHIFT                            0
#define WDT_CLK_CFG_WDT_CLK_SEL_MASK                             0x00000001 //RW, 1 bit
#define UWB_CLK_CFG             0x0430
#define UWB_CLK_CFG_UWB_CLK_SEL_SHIFT                            0
#define UWB_CLK_CFG_UWB_CLK_SEL_MASK                             0x00000001 //RW, 1 bit
#define I2C1_CLK_CFG            0x0434
#define I2C1_CLK_CFG_I2C1_CLK_SEL_SHIFT                          0
#define I2C1_CLK_CFG_I2C1_CLK_SEL_MASK                           0x00000001 //RW, 1 bit
#define I2C1_CLK_CFG_I2C1_CLK_DIV_SHIFT                          4
#define I2C1_CLK_CFG_I2C1_CLK_DIV_MASK                           0x000000f0 //RW, 4 bit
#define I2C1_CLK_CFG_I2C1_CLK_DIV_TOG_SHIFT                      31
#define UWB_AUTO_CLK_CFG        0x0438
#define UWB_AUTO_CLK_CFG_HW_TX_CLK_MASK_SHIFT                    0
#define UWB_AUTO_CLK_CFG_HW_TX_CLK_MASK_MASK                     0x00000001 //RW, 1 bit
#define UWB_AUTO_CLK_CFG_HW_RX_CLK_MASK_SHIFT                    1
#define UWB_AUTO_CLK_CFG_HW_RX_CLK_MASK_MASK                     0x00000002 //RW, 1 bit
#define UWB_AUTO_CLK_CFG_RX_PREAMBLE_CLOCKGATING_SHIFT           2
#define UWB_AUTO_CLK_CFG_RX_PREAMBLE_CLOCKGATING_MASK            0x00000004 //RW, 1 bit
#define UWB_BLK_SW_RSTN0        0x043c
#define UWB_BLK_SW_RSTN0_UWB_ANA_REG_SW_RSTN_SHIFT               0
#define UWB_BLK_SW_RSTN0_UWB_ANA_REG_SW_RSTN_MASK                0x00000001 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_SYS_SW_RSTN_SHIFT                   1
#define UWB_BLK_SW_RSTN0_UWB_SYS_SW_RSTN_MASK                    0x00000002 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_TX_SW_RSTN_SHIFT                    2
#define UWB_BLK_SW_RSTN0_UWB_TX_SW_RSTN_MASK                     0x00000004 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_MAIN_CTRL_SW_RSTN_SHIFT             3
#define UWB_BLK_SW_RSTN0_UWB_MAIN_CTRL_SW_RSTN_MASK              0x00000008 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_RX0_SW_RSTN_SHIFT                   4
#define UWB_BLK_SW_RSTN0_UWB_RX0_SW_RSTN_MASK                    0x00000010 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_RX1_SW_RSTN_SHIFT                   5
#define UWB_BLK_SW_RSTN0_UWB_RX1_SW_RSTN_MASK                    0x00000020 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_RX0_CIA_SW_RSTN_SHIFT               6
#define UWB_BLK_SW_RSTN0_UWB_RX0_CIA_SW_RSTN_MASK                0x00000040 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_RX1_CIA_SW_RSTN_SHIFT               7
#define UWB_BLK_SW_RSTN0_UWB_RX1_CIA_SW_RSTN_MASK                0x00000080 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_AGC0_SW_RSTN_SHIFT                  8
#define UWB_BLK_SW_RSTN0_UWB_AGC0_SW_RSTN_MASK                   0x00000100 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_AGC1_SW_RSTN_SHIFT                  9
#define UWB_BLK_SW_RSTN0_UWB_AGC1_SW_RSTN_MASK                   0x00000200 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_ADC0_SW_RSTN_SHIFT                  10
#define UWB_BLK_SW_RSTN0_UWB_ADC0_SW_RSTN_MASK                   0x00000400 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_ADC1_SW_RSTN_SHIFT                  11
#define UWB_BLK_SW_RSTN0_UWB_ADC1_SW_RSTN_MASK                   0x00000800 //RW, 1 bit
#define UWB_BLK_SW_RSTN0_UWB_SW_HRSTN_SHIFT                      12
#define UWB_BLK_SW_RSTN0_UWB_SW_HRSTN_MASK                       0x00001000 //RW, 1 bit
#define UWB_CLK_ICG_REG         0x0440
#define UWB_CLK_ICG_REG_UWB_ANA_REG_CLK_ICG_SHIFT                0
#define UWB_CLK_ICG_REG_UWB_ANA_REG_CLK_ICG_MASK                 0x00000001 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_SYS_CLK_ICG_SHIFT                    1
#define UWB_CLK_ICG_REG_UWB_SYS_CLK_ICG_MASK                     0x00000002 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_TX_CLK_ICG_SHIFT                     2
#define UWB_CLK_ICG_REG_UWB_TX_CLK_ICG_MASK                      0x00000004 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_MAIN_CTRL_CLK_ICG_SHIFT              3
#define UWB_CLK_ICG_REG_UWB_MAIN_CTRL_CLK_ICG_MASK               0x00000008 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_RX0_CLK_ICG_SHIFT                    4
#define UWB_CLK_ICG_REG_UWB_RX0_CLK_ICG_MASK                     0x00000010 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_RX1_CLK_ICG_SHIFT                    5
#define UWB_CLK_ICG_REG_UWB_RX1_CLK_ICG_MASK                     0x00000020 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_RX0_CIA_CLK_ICG_SHIFT                6
#define UWB_CLK_ICG_REG_UWB_RX0_CIA_CLK_ICG_MASK                 0x00000040 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_RX1_CIA_CLK_ICG_SHIFT                7
#define UWB_CLK_ICG_REG_UWB_RX1_CIA_CLK_ICG_MASK                 0x00000080 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_AGC0_CLK_ICG_SHIFT                   8
#define UWB_CLK_ICG_REG_UWB_AGC0_CLK_ICG_MASK                    0x00000100 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_AGC1_CLK_ICG_SHIFT                   9
#define UWB_CLK_ICG_REG_UWB_AGC1_CLK_ICG_MASK                    0x00000200 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_ADC0_CLK_ICG_SHIFT                   10
#define UWB_CLK_ICG_REG_UWB_ADC0_CLK_ICG_MASK                    0x00000400 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_ADC1_CLK_ICG_SHIFT                   11
#define UWB_CLK_ICG_REG_UWB_ADC1_CLK_ICG_MASK                    0x00000800 //RW, 1 bit
#define UWB_CLK_ICG_REG_UWB_HCLK_ICG_SHIFT                       12
#define UWB_CLK_ICG_REG_UWB_HCLK_ICG_MASK                        0x00001000 //RW, 1 bit
#define PMU_CFG                 0x0444
#define PMU_CFG_SHUTDOWN_EN_SHIFT                                0
#define PMU_CFG_SHUTDOWN_EN_MASK                                 0x00000001 //RW, 1 bit
#define PMU_CFG_SHUTDOWN_RC_ENABLE_SHIFT                         1
#define PMU_CFG_SHUTDOWN_RC_ENABLE_MASK                          0x00000002 //RW, 1 bit
#define PMU_CFG_RAMS_OPERATION_SHIFT                             2
#define PMU_CFG_RAMS_OPERATION_MASK                              0x00000004 //RW, 1 bit
#define BUS_STARVE_CFG          0x0448
#define BUS_STARVE_CFG_STARVED_CNT0_SHIFT                        0
#define BUS_STARVE_CFG_STARVED_CNT0_MASK                         0x0000001f //RW, 5 bit
#define BUS_STARVE_CFG_STARVED_CNT1_SHIFT                        8
#define BUS_STARVE_CFG_STARVED_CNT1_MASK                         0x00001f00 //RW, 5 bit
#define BUS_STARVE_CFG_STARVED_CNT2_SHIFT                        16
#define BUS_STARVE_CFG_STARVED_CNT2_MASK                         0x001f0000 //RW, 5 bit
#define BUS_STARVE_CFG_STARVEEN_SHIFT                            24
#define BUS_STARVE_CFG_STARVEEN_MASK                             0x01000000 //RW, 1 bit
#define CLK_AUTO_ICG_REG        0x044c
#define CLK_AUTO_ICG_REG_UNLOAD_SHIFT                            0
#define CLK_AUTO_ICG_REG_UNLOAD_MASK                             0x00000001 //RW, 1 bit
#define CLK_AUTO_ICG_REG_UNLOAD1_SHIFT                           1
#define CLK_AUTO_ICG_REG_UNLOAD1_MASK                            0x00000002 //RW, 1 bit
#define CLK_AUTO_ICG_REG_UNLOAD2_SHIFT                           2
#define CLK_AUTO_ICG_REG_UNLOAD2_MASK                            0x00000004 //RW, 1 bit
#define CLK_AUTO_ICG_REG_UNLOAD3_SHIFT                           3
#define CLK_AUTO_ICG_REG_UNLOAD3_MASK                            0x00000008 //RW, 1 bit
#define CLK_AUTO_ICG_REG_HCLK_ICG_EN_SHIFT                       4
#define CLK_AUTO_ICG_REG_HCLK_ICG_EN_MASK                        0x00000010 //RW, 1 bit
#define CLK_AUTO_ICG_REG_PCLK_ICG_EN_SHIFT                       5
#define CLK_AUTO_ICG_REG_PCLK_ICG_EN_MASK                        0x00000020 //RW, 1 bit
#define CLK_AUTO_ICG_REG_SRAM_CODE_CLK_ICG_SHIFT                 6
#define CLK_AUTO_ICG_REG_SRAM_CODE_CLK_ICG_MASK                  0x00000040 //RW, 1 bit
#define CLK_AUTO_ICG_REG_SRAM_CLK_ICG_SHIFT                      7
#define CLK_AUTO_ICG_REG_SRAM_CLK_ICG_MASK                       0x00000080 //RW, 1 bit
#define CLK_AUTO_ICG_REG_ROM_CLK_ICG_SHIFT                       8
#define CLK_AUTO_ICG_REG_ROM_CLK_ICG_MASK                        0x00000100 //RW, 1 bit
#define SPI_CSN_CONTROL_CFG     0x0450
#define SPI_CSN_CONTROL_CFG_SPI0_CSN_SW_CONTROL_SHIFT            0
#define SPI_CSN_CONTROL_CFG_SPI0_CSN_SW_CONTROL_MASK             0x00000001 //RW, 1 bit
#define SPI_CSN_CONTROL_CFG_SPI0_CSN_SW_VALUE_SHIFT              1
#define SPI_CSN_CONTROL_CFG_SPI0_CSN_SW_VALUE_MASK               0x00000002 //RW, 1 bit
#define SPI_CSN_CONTROL_CFG_SPI1_CSN_SW_CONTROL_SHIFT            2
#define SPI_CSN_CONTROL_CFG_SPI1_CSN_SW_CONTROL_MASK             0x00000004 //RW, 1 bit
#define SPI_CSN_CONTROL_CFG_SPI1_CSN_SW_VALUE_SHIFT              3
#define SPI_CSN_CONTROL_CFG_SPI1_CSN_SW_VALUE_MASK               0x00000008 //RW, 1 bit
#define CLK_OBSERVE_CONFIG      0x0454
#define CLK_OBSERVE_CONFIG_CLK_OBSERVE_ENABLE_SHIFT              0
#define CLK_OBSERVE_CONFIG_CLK_OBSERVE_ENABLE_MASK               0x00000001 //RW, 1 bit
#define CLK_OBSERVE_CONFIG_DBG_CLK_OUT_SEL_SHIFT                 1
#define CLK_OBSERVE_CONFIG_DBG_CLK_OUT_SEL_MASK                  0x00000006 //RW, 2 bit
#define SOC_HIGH_CLK_INT_RAW    0x0458
#define SOC_HIGH_CLK_INT_RAW_MISSING_CLK_POSEDGE_RAW_SHIFT       0
#define SOC_HIGH_CLK_INT_FORCE  0x045c
#define SOC_HIGH_CLK_INT_FORCE_MISSING_CLK_POSEDGE_RAW_SHIFT     0
#define SOC_HIGH_CLK_INT_MASK   0x0460
#define SOC_HIGH_CLK_INT_MASK_MISSING_CLK_POSEDGE_MASK_SHIFT     0
#define SOC_HIGH_CLK_INT_MASK_MISSING_CLK_POSEDGE_MASK_MASK      0x00000001 //RW, 1 bit
#define SOC_HIGH_CLK_INT_STATUS 0x0464
#define SOC_HIGH_CLK_INT_STATUS_MISSING_CLK_POSEDGE_STATUS_SHIFT 0
#define SOC_HIGH_CLK_INT_STATUS_MISSING_CLK_POSEDGE_STATUS_MASK  0x00000001 //RO, 1 bit
#define DEBUG_EN                0x0948
#define DEBUG_EN_DEBUG_EN_W1P_SHIFT                              0
#define SWD_IN_DELAY_EN         0x094c
#define SWD_IN_DELAY_EN_SWD_IN_DELAY_W1P_SHIFT                   0
#define SWD_OUT_DELAY_EN        0x0950
#define SWD_OUT_DELAY_EN_SWD_OUT_DELAY_W1P_SHIFT                 0



#endif /* SYS_CTRL_REGIF_H */
