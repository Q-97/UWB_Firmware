#ifndef _TEST_MODE_H_
#define _TEST_MODE_H_

#include <stdint.h>

#include "uci.h"
#include "msg_uci.h"


#define STATUS_TX_DONE  0x01
#define STATUS_RX_DONE  0x02
#define STATUS_RX_OK    0x04
#define STATUS_RX_ERR   0x08
#define STATUS_RX_TO    0x10
#define STATUS_STS_ERR  0x20
#define FROM_US_TO_4NS(x)       ((x)*249+((x)*6)/10)


#define MAX_PSDU_LEN 255
typedef struct test_process     //≤‚ ‘Ω¯≥Ã
{
    uint32_t  cb_flag;
    uint8_t   psduRxOk[MAX_PSDU_LEN + 1];
    uint32_t  psduLen;
    uint64_t  txTimeStamp;
    uint64_t  rxTimeStamp;
    uint8_t   txTimeStampBuf[5];
    uint8_t   rxTimeStampBuf[5];
}test_process_t;
extern test_process_t testProc;

typedef struct test_ctrl        //≤‚ ‘øÿ÷∆
{
    uint8_t   test_start;
    uint8_t   test_cw_start;
    uint16_t  trx_count;
    uint32_t  tx_timestamp;
    uint32_t  rx_ok_count;
    uint32_t  rx_done_count;
    uint32_t  rx_to_count;
    uint32_t  rx_err_count;
}test_ctrl_t;
extern test_ctrl_t test_ctrl;


void uwb_test_mode_config(void);
void test_release(void);

//void zn_vga_to_test_mode(void);
//void zn_vga_to_radar(void);

void test_mode_loop(void);


#endif //_TEST_MODE_H_
