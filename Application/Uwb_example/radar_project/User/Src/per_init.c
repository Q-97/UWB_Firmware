#include "per_init.h"

#include "hal_gpio.h"
#include "hal_can.h"
#include "hal_spi.h"
#include "hal_gp_timer.h"
#include "hal_radar.h"

#include "phy_cmd.h"
#include "gconfig.h"


hal_gp_timer_t gp_timer = {0};


static void rx_error_proc(const zn_cb_data_t* cb_data)
{

}
static void rx_timeout_proc(const zn_cb_data_t* cb_data)
{

}
static void rx_ok_proc(const zn_cb_data_t* cb_data)
{

}
static void tx_done_proc(const zn_cb_data_t* cb_data)
{

}
static void rx_cp_err_proc(const zn_cb_data_t* cb_data)
{

}

static void uwb_irq_init(hal_uwb_interrupt_callback_t* irq_callback)
{
    irq_callback->cb_tx_done = &tx_done_proc;
    irq_callback->cb_rx_ok = &rx_ok_proc;
    irq_callback->cb_rx_err = &rx_error_proc;
    irq_callback->cb_rx_timeout = &rx_timeout_proc;
    irq_callback->cb_cp_err = &rx_cp_err_proc;
}

static void uwb_cfg_init(void)
{
    hal_uwb_phy_config_t*         uwb_phy_config   = &uwb_instance.phy_config;
    hal_uwb_interrupt_callback_t* uwb_irq_callback = &uwb_instance.interrupt_callback;
    
    uwb_irq_init(uwb_irq_callback);
    hal_uwb_config_init(&uwb_instance);
}



// ========================= uart api==========================

uint32_t g_uart_rcv_counter = 0;
uint8_t  g_uart_rx_flag = 0;
uint8_t  g_uart_rx_buffer[UCI_MSG_RCV_BUFF_SIZE] = {0};
uint32_t g_uart_rtick = 0;
static void user_uart_irq_callback( ZN_UartType *UARTx, uint32_t wpara, uint32_t lpara)
{
    uint8_t intc_state; 
	uint8_t data;
    uint8_t uart_id = UART_ID(UARTx);
    
	intc_state = hal_uart_get_int_state(uart_id);

	/* Received data available.
     * - Receiver data available (non-FIFO mode or FIFOs disabled) 
	 * - or RCVR FIFO trigger level reached (FIFO mode and FIFOs enabled)
	*/
	if (hal_uart_rx_buff_is_not_empty(uart_id)) 
	{
		data = hal_uart_get_rx_data(uart_id);
        
		g_uart_rx_buffer[g_uart_rcv_counter++] = data;
        g_uart_rtick =  hal_get_cur_sys_time();
        g_uart_rx_flag = 4;
	}
}
void uart_update_flag(void)
{
    uint32_t cur_tick = hal_get_cur_sys_time();

    if(g_uart_rx_flag > 1)
    {
        if(cur_tick >= g_uart_rtick)
        {
            if((SYS_TO_US(cur_tick - g_uart_rtick) / 1000) > 3) //msg timeout 10ms
            {
                g_uart_rx_flag--;
            }
        }
        else
        {
            if((SYS_TO_US(0xffffffffUL - g_uart_rtick + cur_tick) / 1000) > 3) //msg timeout 10ms
            {
                g_uart_rx_flag--;
            }
        }
    }
}
void uart0_init(UART_Baudrate baudRate)
{
    hal_uart_t uart_cfg = {0};
    
    uart_cfg.is_block_mode = 0;
    uart_cfg.is_tx_int_en = 0;
    uart_cfg.is_rx_int_en = 1;
    uart_cfg.baurdrate = baudRate;
    uart_cfg.func = (DeviceCallback_Type)&user_uart_irq_callback;
    
    hal_uart_init(&uart_cfg);
}



// ===================================== canfd api========================================

uint8_t             g_canRxMsgFlag        = FALSE;
hal_can_msg_info_t  g_canRxMessage        = {0};

static void can_irq_callback(void *CANx, uint32_t event, uint32_t err)
{
//    printf("errInt = 0x%02x,err(KOER) = 0x%02x\r\n",(event>>8)&0xFF,err);
    if (event & CAN_EVENT_RECVMSG)
    {
        if(hal_can_is_msg_in_rxbuff())
        {
            hal_can_msg_read(&g_canRxMessage);
            g_canRxMsgFlag = TRUE;
        }
    }
}
void can_init_hardwr(void)
{
    hal_can_t can_cfg = {0};

    can_cfg.baudrate_config.presc = 3;      //1M
    can_cfg.baudrate_config.seg_1 = 14;
    can_cfg.baudrate_config.seg_2 = 3;
    can_cfg.baudrate_config.sjw = 3;
    
    can_cfg.datarate_config.presc = 1;      //2M
    can_cfg.datarate_config.seg_1 = 14;
    can_cfg.datarate_config.seg_2 = 3;
    can_cfg.datarate_config.sjw = 3;
    
    can_cfg.config.clock_src = 0;    //select 80M clock
    can_cfg.config.clock_div = 0;
    can_cfg.config.interrupt_en = 1;
    can_cfg.config.tpss = 1;
    can_cfg.config.tsss = 1;
    can_cfg.config.can_mode = NORMAL_MODE;
    can_cfg.config.auto_reset = 1;
    can_cfg.config.filter_en = 0;
    //can_cfg.config.filter_list = g_can_filter_tab;
    can_cfg.config.fd_mode_en = 1;
    can_cfg.config.fd_iso_en = 1;
    can_cfg.config.tdc_en = 1;
    can_cfg.config.ssp_offset = can_cfg.datarate_config.seg_1 + 2;
    can_cfg.config.time_en = 1;
    can_cfg.config.time_pos = 1;
    can_cfg.config.func = (DeviceCallback_Type)&can_irq_callback;
    
    hal_can_init(&can_cfg);
}

void can_send_msg(uint8_t *pbuf, uint16_t len, uint16_t can_id)
{
    hal_can_msg_info_t g_send_msg_Info = {0};
    uint8_t           pg_number = 0;
    uint8_t           index = 0;

    if ((len % CAN_MAX_LEN) != 0)
    {
        pg_number = (len / CAN_MAX_LEN) + 1;
    }
    else
    {
        pg_number = len / CAN_MAX_LEN;
    }
    
    while(index < pg_number)
    {
        if(!hal_can_is_transmit_busy(PRIMARY_SEND))
        {
            g_send_msg_Info.dlc = 0x0f;
            g_send_msg_Info.can_id = can_id;
            g_send_msg_Info.fdf = 1;//canfd数据包 该位为0表示是can数据包
            g_send_msg_Info.brs = 1;
            memcpy(g_send_msg_Info.data, (pbuf + index * CAN_MAX_LEN), (index == (pg_number -1))?(len % CAN_MAX_LEN):CAN_MAX_LEN);
            hal_can_msg_send(&g_send_msg_Info, PRIMARY_SEND);
            index++;
        }
    }
}


// ======================================== spi api =========================================

uint32_t g_spiRxDataBuff[SPI_RX_BUFF_LENGTH] = {0};
uint32_t g_spiTxDataBuff[SPI_TX_BUFF_LENGTH] = {0};
uint8_t g_spiRxMsgFlag        = FALSE;
uint8_t g_spi_rx_index        = 0;

static void spi_irq_callback(ZN_SpiType *SPIx, uint32_t wpara, uint32_t lpara)
{
    uint32_t spi_id = SPI_INDEX(SPIx);
    uint32_t temp = 0;

    if (wpara & RX_AVL_INTF_MSK) /*This bit is set when Receiver FIFO has received enough data(depend on rxtlf--Global Control Register bit 5).*/
    {
        /*receiver FIFO has available data*/
        while(spi_rx_is_avl(SPIx))
        {
            if (g_spi_rx_index < SPI_RX_BUFF_LENGTH)
            {
                g_spiRxDataBuff[g_spi_rx_index] = spi_read_data(SPIx);
                g_spi_rx_index++;
                if(g_spi_rx_index == SPI_RX_BUFF_LENGTH)
                {
                    g_spiRxMsgFlag = TRUE;
                }
            }
            else
            {
                temp = spi_read_data(SPIx);
            }
        }
    }
}

void spi_slave_init(void)
{
    hal_spi_t spi_cfg = {0};
    
    spi_cfg.spi_id = 0;
    spi_cfg.spi_role = 0;   //slave
    spi_cfg.clk_div = 4;
    spi_cfg.data_size = 32;
    spi_cfg.spi_mode = 0;
    spi_cfg.is_lsb = 0;
    spi_cfg.rx_fifo_en = 0;
    spi_cfg.tx_fifo_en = 0;
    spi_cfg.rx_interrupt_en = 1;
    spi_cfg.func = (DeviceCallback_Type)&spi_irq_callback;
    
    hal_spi_init(&spi_cfg);
    hal_spi_rx_enable(spi_cfg.spi_id);
}

static void byte_to_4_convert(uint8_t *data, uint32_t *data4byte, uint8_t len)
{
    uint8_t  idx          = 0;
    uint8_t  jdx          = 0;

    for(idx = 0; idx < len/4; idx++)
    {
        data4byte[idx] = (data[jdx] << 24) | (data[jdx+1] << 16) | (data[jdx+2] << 8) | (data[jdx+3]);
        jdx += 4;
    }
}
void spi_send_msg(uint8_t *pbuf, uint8_t len)
{
    ZN_SpiType *SPIx = SPI0;
    uint8_t dma_id = 0;
    
    memset(g_spiTxDataBuff, 0, SPI_TX_BUFF_LENGTH * sizeof(uint32_t));
    byte_to_4_convert(pbuf, g_spiTxDataBuff, SPI_TX_BUFF_LENGTH * sizeof(uint32_t));

    GPIOA_RESET_BITS(0);
    spi_transmit_poll(SPIx,0,(uint8_t *)g_spiTxDataBuff, SPI_TX_BUFF_LENGTH * sizeof(uint32_t));
    GPIOA_SET_BITS(0);
}


// =================================== timer =====================================

static void timer2_irq_proc(void)
{
    //15s timeout auto to radar mode
    hal_gp_timer_close(TIMER2);
    g_work_mode = WORK_MODE_RADAR;
}
static void config_wait_test_mode()
{
    hal_gp_timer_t timer_cfg={0};
    timer_cfg.timer_id = TIMER2;
    timer_cfg.clk_src = PLL_CLK;
    timer_cfg.clk_div = 0;
    timer_cfg.mode = TIMER_USER_DEFINE;
    timer_cfg.interrupt_en = 1;
    timer_cfg.time1 = 15000000;//15s
    timer_cfg.func = (TIMER_CallbackType)&timer2_irq_proc;
    hal_gp_timer_init(&timer_cfg);
}


// ==================================== gpio ======================================
gpio_test_type_t g_gpio_test_tab[PIN_NUM_MAX]=
{
    {0, 1, 0x00},  /*GPIOA0*/               //GPIO_PIN0
    {1, 1, 0x04},  /*GPIOA1*/               //GPIO_PIN1, 
    {2, 1, 0x08},  /*GPIOA2*/               //GPIO_PIN2, 
    {3, 1, 0x0C},  /*GPIOA3*/               //GPIO_PIN3, 
    {4, 1, 0x10},  /*GPIOA4*/               //GPIO_PIN4, 
    {5, 0, 0x14},  /*GPIOA5*/               //GPIO_PIN5, 
    {6, 0, 0x18},  /*GPIOA6*/               //GPIO_PIN6, 
    {7, 1, 0x1C},  /*GPIOA7*/               //GPIO_PIN7, 
    {8, 1, 0x20},  /*GPIOA8*/               //GPIO_PIN8, 
    {9, 1, 0x24},  /*GPIOA9*/               //GPIO_PIN9, 
    {10,1, 0x28},  /*GPIOA10*/              //GPIO_PIN10,
    {11,1, 0x2C},  /*GPIOA11*/              //GPIO_PIN11,
    {12,1, 0x30},  /*GPIOA12*/              //GPIO_PIN12,
    {13,1, 0x34},  /*GPIOA13*/              //GPIO_PIN13,
    {14,1, 0x38},  /*GPIOA14*/              //GPIO_PIN14,
    {15,1, 0x3C},  /*GPIOA15,UART0_RX*/     //GPIO_PIN15,
    {16,1, 0x40},  /*GPIOA16,UART0_TX*/     //GPIO_PIN16,
    {17,0, 0x44},  /*GPIOA17*/              //GPIO_PIN17,        
    {18,0, 0x48},  /*GPIOA18*/              //GPIO_PIN18,        
    {19,0, 0x4C},  /*GPIOA19*/              //GPIO_PIN19,
    {20,0, 0x50},  /*GPIOA20*/              //GPIO_PIN20
    {21,0, 0x54},  /*GPIOA21*/              //GPIO_PIN21,
    {22,0, 0x58},  /*GPIOA22*/              //GPIO_PIN22,
    {23,1, 0x5C},  /*GPIOA23*/              //GPIO_PIN23,
    {24,1, 0x60},  /*GPIOA24*/              //GPIO_PIN24,
    {25,1, 0x64},  /*GPIOA25*/              //GPIO_PIN25,
    {26,1, 0x68},  /*GPIOA26*/              //GPIO_PIN26,
    {27,1, 0x6C},  /*GPIOA27*/              //GPIO_PIN27,
    {28,0, 0x00},  /*GPIOA28,res*/          //GPIO_PIN28,
    {29,0, 0x00},  /*GPIOA29,res*/          //GPIO_PIN29,
    {30,0, 0x00},  /*GPIOA30,res*/          //GPIO_PIN30,
    {31,0, 0x00},  /*GPIOA31,res*/          //GPIO_PIN31,
    {32,1, 0x70},  /*GPIOB0*/               //GPIO_PIN32,
    {33,1, 0x74},  /*GPIOB1*/               //GPIO_PIN33,
    {34,1, 0x78},  /*GPIOB2*/               //GPIO_PIN34,
    {35,1, 0x7C},  /*GPIOB3*/               //GPIO_PIN35,
    {36,1, 0x80},  /*GPIOB4*/               //GPIO_PIN36,
};

void user_set_all_gpio_input()
{
    for(uint8_t i = 0; i < PIN_NUM_MAX; i++)
    {
        if(g_gpio_test_tab[i].istest)
        {
            pad_reg_write(g_gpio_test_tab[i].padreg, 0x161);
        }
    }
    sys_ctrl_write(UWB_CLK_ICG_REG,0X0);
    write_mreg32(UWB_BASE_ADDR +0X0A0C,0X1);
    dca_write(0x112,0xd9);
    dca_write(0x113,0xd9);
    dca_write(0x116,0xd9);
}


// ============================================================================================

void peripheral_init(void)
{
    user_set_all_gpio_input();
    
    uart0_init(DEFAULT_UART_BR);
    can_init_hardwr();
    uwb_cfg_init();
       
    if(uwb_instance.radar_config.radar_en)
    {
        hal_radar_init(&uwb_instance);
        
        hal_radar_timer_init();
    }
}


