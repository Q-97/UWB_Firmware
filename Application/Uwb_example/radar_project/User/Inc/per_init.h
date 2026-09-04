#ifndef _PER_INIT_H_
#define _PER_INIT_H_

#include <stdint.h>
#include <string.h>

#include "hal_uart.h"
#include "hal_can.h"

#include "gconfig.h"


#define CAN_MAX_LEN         (64)

#define DEFAULT_UART_BR     (B1000000)//B230400  B1000000

#define UCI_MSG_RCV_BUFF_SIZE   (255)

#define PIN_NUM_MAX 37
typedef struct
{
    uint8_t piunum;     /*gpio num*/
    uint8_t istest;     /*0-not test;1-test*/
    uint32_t padreg;
} gpio_test_type_t;
extern gpio_test_type_t g_gpio_test_tab[PIN_NUM_MAX];
extern hal_gp_timer_t gp_timer;

// ============================ uart ==============================

extern uint32_t g_uart_rcv_counter;
extern uint8_t  g_uart_rx_flag;
extern uint8_t  g_uart_rx_buffer[UCI_MSG_RCV_BUFF_SIZE];
extern uint32_t g_uart_rtick;

void uart_update_flag(void);
void uart0_init(UART_Baudrate baudRate);

// ============================ can ==============================

extern uint8_t              g_canRxMsgFlag;
extern hal_can_msg_info_t   g_canRxMessage;

void can_init_hardwr(void);
void can_send_msg(uint8_t *pbuf, uint16_t len, uint16_t can_id);

// ============================ spi ==============================

#define SPI_RX_BUFF_LENGTH     16
#define SPI_TX_BUFF_LENGTH     16
extern uint32_t g_spiRxDataBuff[SPI_RX_BUFF_LENGTH];
extern uint32_t g_spiTxDataBuff[SPI_TX_BUFF_LENGTH];
extern uint8_t g_spiRxMsgFlag;
extern uint8_t g_spi_rx_index;

void spi_slave_init(void);
void spi_send_msg(uint8_t *pbuf, uint8_t len);


// =================================================================

void peripheral_init(void);


#endif //_PER_INIT_H_
