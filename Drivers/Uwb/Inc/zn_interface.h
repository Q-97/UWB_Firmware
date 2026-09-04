/*****************************************************************************
* File: interface.h
*
* Descirption: this file contains the functions support driver interface.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef ZN_INTERFACE_H_
#define ZN_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_macro.h"
#include "cali_reg.h"
#include "zn_regs.h"
#include "zn_log.h"
#include "zn_delay.h"

#define MAX_PA_SET_NUM    15
#define CHANNEL_2         1
#define CHANNEL_5         3
#define CHANNEL_9         6

#define MAX_CHANNEL_NUM   7

#define FEM_CTRL_AUTO     0x00
#define FEM_CTRL_MANUAL   0x01

#define MAX_CH_NUM    3
#define MAX_RX_NUM    2
#define MAX_LNA_CASE_NUM    2
#define MAX_TIA_NUM    6
#define MAX_VGA_NUM    15

#define CHANNLE_ID(ch)    ((CHANNEL_2 == (ch)) ? 0 : ((CHANNEL_5 == (ch)) ? 1 : 2))

#define FLASH_WR_FLAG    0xa1b2c3d4

typedef enum rframe_config
{
    RFRAME_SP0 = 0,
    RFRAME_SP1 = 1,
    RFRAME_SP3 = 3
}rframe_config_t;

//802.15.4 Table 15-6 15-7 and 802.15.4z
typedef enum preamble_code_index
{
    PREAMBLE_CODE_INDEX_9   = 8,
    PREAMBLE_CODE_INDEX_10,
    PREAMBLE_CODE_INDEX_11  = 10,
    PREAMBLE_CODE_INDEX_12,
    PREAMBLE_CODE_INDEX_13,
    PREAMBLE_CODE_INDEX_14,
    PREAMBLE_CODE_INDEX_15,
    PREAMBLE_CODE_INDEX_16,
    PREAMBLE_CODE_INDEX_17,
    PREAMBLE_CODE_INDEX_18,
    PREAMBLE_CODE_INDEX_19,
    PREAMBLE_CODE_INDEX_20,
    PREAMBLE_CODE_INDEX_21  = 20,
    PREAMBLE_CODE_INDEX_22,
    PREAMBLE_CODE_INDEX_23,
    PREAMBLE_CODE_INDEX_24,
    PREAMBLE_CODE_INDEX_25,
    PREAMBLE_CODE_INDEX_26,
    PREAMBLE_CODE_INDEX_27,
    PREAMBLE_CODE_INDEX_28,
    PREAMBLE_CODE_INDEX_29,
    PREAMBLE_CODE_INDEX_30,
    PREAMBLE_CODE_INDEX_31 = 30,
    PREAMBLE_CODE_INDEX_32
}preamble_code_index_t;

typedef enum sfd_id
{
    SFD_ID_LEGACY_SFD8  = 0,    //802.15.4z Table 15-7c SFD#0
    SFD_ID_SFD8,                //802.15.4z Table 15-7c SFD#2
    SFD_ID_SFD16,               //802.15.4z Table 15-7c SFD#3
    SFD_ID_SFD4,                //802.15.4z Table 15-7c SFD#1
    SFD_ID_USER8,
    SFD_ID_USER16
}sfd_id_t;

typedef enum psdu_data_rate
{
    PSDU_RATE_850 = 1,      //850 Kbps
    PSDU_RATE_681,          //6.81 Mbps
    PSDU_RATE_272,          //27.2 Mbps
    PSDU_RATE_780 = 4,      //7.8Mbps
    PSDU_RATE_312,          //31.2Mbps
    PSDU_RATE_540           //54 Mbps  
}psdu_data_rate_t;

typedef enum bprf_phr_data_rate
{
    BPRF_PHR_RATE_850 = 0
}bprf_phr_data_rate_t;

typedef enum preamble_duration
{
    PREAMBLE_16     = 0,
    PREAMBLE_64,
    PREAMBLE_1024,
    PREAMBLE_4096,
    PREAMBLE_32,
    PREAMBLE_128     = 5,
    PREAMBLE_256,
    PREAMBLE_512,
    PREAMBLE_2048
}preamble_duration_t;

typedef enum prf_mode 
{
    PRF_624 = 0,   //BPRF  62.4MHZ
    PRF_1248,      //HPRF  124.8MHZ
    PRF_2496,      //HPRF  249.6MHZ
    PRF_4992       //HPRF  499.2MHZ
}prf_mode_t;

typedef enum sts_seg_num
{
    STS_SEG_1 = 0,
    STS_SEG_2,   //only tx support
    STS_SEG_3,   //only tx support
    STS_SEG_4    //only tx support
}sts_seg_num_t;

typedef enum pmsc_state
{
    PMSC_INIT = 1,
    PMSC_IDLE_RC,
    PMSC_IDLE,
    PMSC_TX,
    PMSC_RX
}pmsc_state_t;

typedef enum tia_gain_set
{
    TIA_LEVEL_0,
    TIA_LEVEL_1,
    TIA_LEVEL_2,
    TIA_LEVEL_3,
    TIA_LEVEL_4,
    TIA_LEVEL_5,
    MAX_TIA_LEVEL
}tia_gain_set_t;

typedef enum pa_gain_set
{
    PA_LEVEL_0 = 0,
    PA_LEVEL_1,
    PA_LEVEL_2,
    PA_LEVEL_3,
    PA_LEVEL_4,
    PA_LEVEL_5,
    PA_LEVEL_6,
    PA_LEVEL_7,
    PA_LEVEL_8,
    PA_LEVEL_9,
    PA_LEVEL_10,
    PA_LEVEL_11,
    PA_LEVEL_12,
    PA_LEVEL_13,
    PA_LEVEL_14,
    PA_LEVEL_15,
    MAX_PA_LEVEL
}pa_gain_set_t;

typedef enum sts_seg_len
{
    STS_SEG_LEN_16 = 16,   //only tx support
    STS_SEG_LEN_32 = 32,   //only tx support
    STS_SEG_LEN_64 = 64,
    STS_SEG_LEN_128 = 128, //only tx support
    STS_SEG_LEN_256 = 256  //only tx support
}sts_seg_len_t;


typedef enum aoa_mode
{
    TYPE_AOA = 0,
    TYPE_PDOA
}aoa_mode_e;

typedef enum aoa_dimension_mode
{
    TYPE_2D = 0,
    TYPE_3D
}aoa_dimension_mode_e;

typedef enum aoa_3d_ant_type
{
    AOA_3D_ANTENNA_TYPE_CEILING_TYPE1 = 0,
    AOA_3D_ANTENNA_TYPE_CEILING_TYPE2,
    AOA_3D_ANTENNA_TYPE_CEILING_TYPE3,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE1,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE2,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE3,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE4,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE5,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE6,
    AOA_3D_ANTENNA_TYPE_VERTICAL_TYPE7,
}aoa_3d_ant_type_e;

typedef enum
{
    TYPE_VBAT,
    TYPE_ATESTP,
    TYPE_TEMPERATURE
}adc_mode_t;
    

typedef enum pdoa_ant_state
{
    RX2_INPUT = 1,
    RX1_INPUT = 2,
}pdoa_ant_state_e;

typedef enum user_sfd_sequence
{
    USER_SFD8_SEQ = 0x0000AAE0,
    USER_SFD16_SEQ =  0xAAEEBEB0,
}user_sfd_sequence_t;


typedef struct zn_tstart_twin
{
    uint32_t start;
    uint32_t win;
}zn_tstart_twin_t;

// TX/RX call-back data
typedef struct zn_cb_data
{
    uint32_t status;       //initial value of register as ISR is entered
    uint16_t data_length;  //length of frame
    uint8_t  rx_flags;     //RX frame flags, see above
    uint8_t  rsv;
    uint8_t  data[1023];   //frame control bytes
    uint8_t  rsv1;
} zn_cb_data_t;

typedef struct zn_config
{
    uint8_t                 channel_num;         //3:ch5, 6:ch9 default:ch9 must be same with app_cfg.h
    uint8_t                 rf_cfg;              //0:SP0, 1:SP1, 3:SP3; default:sp0
    uint8_t                 rf_ext_en;           //0:disable ext frame, 1:enable ext frame
    uint8_t                 preamble_code_idx;   //0:INDEX_9, 1:INDEX_10, ..., 31:INDEX_32; default:INDEX_10
    uint8_t                 sfd_id;              //0:LEGACY_SFD8, 1:SFD8, 2:SFD16, SFD4; default:SFD8
    uint8_t                 psdu_data_rate;      //1:850k, 2:6.81M, 3:27.2M; default:2
    uint8_t                 bprf_phr_data_rate;  //0:850k; default:0
    uint8_t                 preamble_duration;   //0:16,1:64,2:1024,3:4096,4:32,5:128,6:256,7:512,8:2048; default:1
    uint8_t                 prf_mode;            //0:BPRF 62.4MHZ,1:HPRF 124.8MHZ,2:HPRF 249.6MHZ
    uint8_t                 pa_level;            //pa level: PA_LEVEL_0 -PA_LEVEL_7
    uint8_t                 rx_signle_switch_en;
    uint8_t                 sts_seg_num;         //0:SEG_1, 1:SEG_2, 2:SEG_3, 4:SEG_4; default:0
    uint16_t                sts_seg_len;         //16, 32, 64, 128;default:64
    uint16_t                sfd_to;              //set sfd timeout time which value is preamble_len + sfd_len
    uint8_t                 aoa_en;
    aoa_mode_e              aoa_mode;
    aoa_dimension_mode_e    aoa_dimension_mode;
    pdoa_ant_state_e        ant_sel;
    aoa_3d_ant_type_e       aoa_3d_ant_type;
    double                  phase_compen_rx0_rx1;
    double                  phase_compen_rx0_rx2;
    double                  ant_distance_rx0_rx1;
    double                  ant_distance_rx0_rx2;
    double                  ant_distance_rx1_rx2;
    int32_t                 delay_rx0_rx1;
    uint8_t                 fem_en;
    uint8_t                 fem_ctrl_mode;
    uint8_t                 fem_tx_pin;
    uint8_t                 fem_rx0_pin;
    uint8_t                 fem_rx1_pin;
    uint8_t                 fem_rx2_pin;
    uint8_t                 flash_save_en;
    uint8_t                 agc_mode;
    uint8_t                 tia_level;
    uint8_t                 radar_en;
}zn_config_t;

// Call-back type for all interrupt events
typedef void (*zn_cb_t)(const zn_cb_data_t *);

typedef struct
{
    zn_cb_data_t        cb_data;              // Callback data structure
    zn_cb_t             cb_tx_done;           // Callback for TX confirmation event
    zn_cb_t             cb_rx_ok;             // Callback for RX good frame event
    zn_cb_t             cb_rx_timeout;        // Callback for RX timeout events
    zn_cb_t             cb_rx_err;            // Callback for RX error events
    zn_cb_t             cb_rx_done;
    zn_cb_t             cb_cp_err;
    zn_cb_t             cb_prd;
    zn_cb_t             cb_rx_preamble_timeout;
    zn_cb_t             cb_rx_sfd_timeout;
    zn_cb_t             cb_rx_sfd_done;
    zn_cb_t             cb_rx_phr_err;
    zn_cb_t             cb_rx_phd;
} zn_local_data_t ;


typedef struct zn_driver_config
{
    uint8_t            last_channel;
    uint8_t            timer_id;
    uint32_t           timer_freq;
    uint8_t            rx_after_tx_flag;
    uint32_t           rx_after_tx_us;
    zn_config_t        phy_config;
    zn_local_data_t    zn_interrupt_callback;
    uint8_t            prd_timer_flag;
    uint8_t            rx_ok_flag;
    uint8_t            paver_save_flag;
    int16_t            inside_ant_delay;
    int32_t            rx0_rx1_diff_index;
    uint32_t           irq_status;
    uint8_t            rx_gain_switch_flg;
    uint8_t            lna_switch_flag;
}zn_driver_config_t;

// two timestamp parameters
typedef struct zn_twoTimeStampParam
{
    uint16_t          firstPath_ThrLow;    // 3~5.  typ is 4
    uint16_t          firstPath_Thrhigh;   // 15 ~1015. typ is 20. if try to bypass this limit, it coule config to 1018
}zn_twoTimeStampParam_t;


/*************************************************************************************************************
* Description: this function return addr of variable zn_interrupt_callback
* Input param: None
* Output param: None
* Return value: pointer of the addr for varibale zn_interrupt_callback
*************************************************************************************************************/
zn_driver_config_t* zn_get_dirver_config_addr(void);

#define LNA_TIA_TABLE_MAX 5//for agc normal mode
extern uint32_t  lna_tia_table[];
extern double   lna_tia_dB[];
extern uint8_t  lna_min_table[];
extern uint8_t  lna_max_table[];

/*************************************************************************************************************
* Description: this function is used to read 32 - bit value from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* Output param: None
* Return value: 32 bit register value
*************************************************************************************************************/
uint32_t zn_read_32bit_reg(uint32_t reg_file_id);

/*************************************************************************************************************
* Description: this function is used to write 32 - bit value to the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* reg_val - the value to write
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_32bit_reg(uint32_t reg_file_id, uint32_t reg_val);

/*************************************************************************************************************
* Description: this function is used to read 16 - bit value from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* Output: None
* Return value: 16 bit register value
*************************************************************************************************************/
uint16_t zn_read_16bit_reg(uint32_t reg_file_id);

/*************************************************************************************************************
* Description: this function is used to write 16 - bit value to the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* reg_val - the value to write
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_16bit_reg(uint32_t reg_file_id, uint32_t reg_val);

/*************************************************************************************************************
* Description: this function is used to read an 8 - bit value from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* Output param: None
* Return value: 8 - bit register value
*************************************************************************************************************/
uint8_t zn_read_8bit_reg(uint32_t reg_file_id);

/*************************************************************************************************************
* Description: this function is used to write an 8 - bit value to the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* reg_val - the value to write
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_8bit_reg(uint32_t reg_file_id, uint8_t reg_val);

/*************************************************************************************************************
* Description: this function is used to OR a 32 - bit value to the ZN device registers
* Input param:
* reg_file_id : ID of register file or buffer being accessed
* or_value : the value to OR to register
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_or_32bit_reg(const uint32_t reg_file_id, const uint32_t or_value);

/*************************************************************************************************************
* Description: this function is used to AND a 32 - bit value to the ZN device registers
* Input param:
* reg_file_id : ID of register file or buffer being accessed
* and_value: the value to AND to register
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_and_32bit_reg(const uint32_t reg_file_id, const uint32_t and_value);

/*************************************************************************************************************
* Description: this function is used to write a commond to the ZN device registers.
* Input param:
* cmd - fast command
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_fast_cmd(uint16_t cmd);

/*************************************************************************************************************
* Description: this function is used to write to the ZN device registers.
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* length - number of bytes being written
* buffer - pointer to buffer containing the 'length' bytes to be written
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_write_to_device(uint32_t reg_file_id, uint16_t length, uint8_t *buffer);

/*************************************************************************************************************
* Description: this function is used to read from the ZN device registers
* Input param:
* reg_file_id - ID of register file or buffer being accessed
* length - number of bytes being read
* buffer - pointer to buffer in which to return the read data.
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_read_from_device(uint32_t reg_file_id, uint16_t length, uint8_t *buffer);

/*************************************************************************************************************
* Description: this function is used to init ZN global config
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_init_global_config(void);

/*************************************************************************************************************
* Description: this function is used to init ZN analog registers
* Input param:
* rframe_cfg - frame config: RFRAME_SP0  RFRAME_SP1  RFRAME_SP3
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_analog_regs_init(void);
/*************************************************************************************************************
* Description: this function is used to init ZN digit registers
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_digit_regs_init(void);

/*************************************************************************************************************
* Description: this function is used to init ZN pdoa registers
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_pdoa_init(void);

/*******************************************************************************************************************
* Description: This API function writes the supplied TX data into the ZN's TX buffer.
* Input param:
* tx_data_length - This is the total length of data (in bytes) to write to the tx buffer.
* tx_data_bytes - Pointer to the user s buffer containing the data to send.
* tx_buffer_offset - This specifies an offset in the ZN IC TX Buffer at which to start writing data.
* Output param: None
* Returns value: ZN_SUCCESS for success, or ZN_ERROR for error
*******************************************************************************************************************/
int32_t zn_write_tx_data(uint16_t tx_data_length, uint8_t *tx_data_bytes, uint16_t tx_buffer_offset);

/*******************************************************************************************************************
* Description: This function read the supplied TX data from the ZN's TX buffer.
* Input param:
* buffer - Pointer to the user's buffer containing the data to read.
* length - This is the total length of data (in bytes) to read from the tx buffer.
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_read_tx_data(uint8_t *buffer, uint16_t length);

/*******************************************************************************************************************
* Description: This API function configures the TX frame control register before the transmission of a frame
* Input param:
* tx_frame_length - this is the length of TX message (including the 2 byte CRC) - max is 1023
* NOTE: standard PHR mode allows up to 127 bytes
* if > 127 is programmed, ZN_PHRMODE_EXT needs to be set in the phrMode configuration
* see zn_configure function
* tx_buffer_offset - the offset in the tx buffer to start writing the data
* ranging - 1 if this is a ranging frame, else 0
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_write_tx_frame_ctrl(uint16_t tx_frame_length, uint16_t tx_buffer_offset, uint8_t ranging);

/*******************************************************************************************************************
* Description: This is used to read the data from the RX buffer, from an offset location give by offset parameter
* Input param:
* buffer - the buffer into which the data will be read
* length - the length of data to read (in bytes)
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_read_rx_data(uint8_t *buffer, uint16_t length);

/*******************************************************************************************************************
* Description: This API function configures the delayed transmit time or the delayed RX on time
* Input param:
* start_time - the TX/RX start time (the 32 bits should be the high 32 bits of the system time at which to send the message,
* The time parameter used here is in 4ns units
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_set_delayed_trx_time(uint32_t start_time);

/*******************************************************************************************************************
* Description: This is used to read the TX timestamp (adjusted with the programmed antenna delay)
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read TX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_tx_timestamp(uint8_t *timestamp);

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the TX timestamp raw (no adjusted with the programmed antenna delay)
* Input param: None
* Output param: None
* Return value: high 32-bits of TX timestamp raw
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_raw(void);

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the TX timestamp (adjusted with the programmed antenna delay)
* Input param: None
* Output param: None
* Return value: high 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_high32(void);

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the TX timestamp (adjusted with the programmed antenna delay)
* Input param: None
* Output param: None
* Return value: low 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_low32(void);

/*******************************************************************************************************************
* Description: This is used to read the TX timestamp (adjusted with the programmed antenna delay) for STS case
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read TX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_tx_timestamp_sts(uint8_t *timestamp);

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the TX timestamp (adjusted with the programmed antenna delay) for STS case
* Input param: None
* Output param: None
* Return value: high 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_high32_sts(void);

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the TX timestamp (adjusted with the programmed antenna delay) for STS case
* Input Param: None
* Output Param: None
* Return value: low 32-bits of TX timestamp
*******************************************************************************************************************/
uint32_t zn_read_tx_timestamp_low32_sts(void);

/*******************************************************************************************************************
* Description: This is used to read the RX timestamp (adjusted time of arrival)
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_rx_timestamp(uint8_t *timestamp);

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the RX timestamp raw (no adjusted with the programmed antenna delay)
* Input Param: None
* Output Param: None
* Return value: high 32-bits of RX timestamp raw
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_raw(void);

/******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the RX timestamp
* Input param: None
* Output param: None
* Return value: high 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_high32(void);

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the RX timestamp
* Input param: None
* Output param: None
* Return value: high 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_low32(void);

/*******************************************************************************************************************
* Description: This is used to read the RX timestamp (adjusted time of arrival) w.r.t. STS CIR
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: no return value
*******************************************************************************************************************/
void zn_read_rx_timestamp_sts(uint8_t *timestamp);

/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the RX timestamp for STS case
* Input param: None
* Output param: None
* Return value: high 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_high32_sts(void);

/*******************************************************************************************************************
* Description: This is used to read the low 32 - bits of the RX timestamp for STS case
* Input param: None
* Output param: None
* Return value: low 32-bits of RX timestamp
*******************************************************************************************************************/
uint32_t zn_read_rx_timestamp_low32_sts(void);


/*******************************************************************************************************************
* Description: This is used to read the RX2 timestamp (adjusted time of arrival)
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: None
*******************************************************************************************************************/
void zn_read_rx2_timestamp(uint8_t *timestamp2);


/*******************************************************************************************************************
* Description: This is used to read the RX2 timestamp (adjusted time of arrival) w.r.t. STS CIR
* Input param: None
* Output param:
* timestamp - a pointer to a 5-byte buffer which will store the read RX timestamp time
* Return value: no return value
*******************************************************************************************************************/
void zn_read_rx2_timestamp_sts(uint8_t *timestamp);
/*******************************************************************************************************************
* Description: This is used to read the high 32 - bits of the system time
* Input Param: None
* Output Param: None
* Return value: 32 - bits of the system time
*******************************************************************************************************************/
uint32_t zn_get_sys_time(void);

/********************************************************************************************************************
* Description: This sets the receiver turn on delay time after a transmission of a frame
* Input Param:
* rx_delay_time - (20 bits) - the delay is us
* Output Param: None
* Return value: None
********************************************************************************************************************/
void zn_set_rx_after_tx_delay(uint32_t rx_delay_time);

/*******************************************************************************************************************
* Description: This function is used to register the different callbacks called when one of the corresponding event occurs.
*
* NOTE: Callbacks can be undefined (set to NULL).In this case, zn_isr() will process the event as usual but the 'null'
* callback will not be called.
*
* Input param:
* cb_tx_done - the pointer to the TX confirmation event callback function
* cb_rx_ok - the pointer to the RX good frame event callback function
* cb_rx_to - the pointer to the RX timeout events callback function
* cb_rx_err - the pointer to the RX error events callback function
* cb_rx_done - the pointer to the Rx Done events callback function
* cb_cp_err - the pointer to the cp error events callback function
* cb_prd - the pointer to the prd events callback function
* Output param: None
* Return value: None
*******************************************************************************************************************/
void zn_set_callbacks(zn_cb_t cb_tx_done, zn_cb_t rx_ok, zn_cb_t cb_rx_to, zn_cb_t cb_rx_err, zn_cb_t cb_cp_err);
void zn_set_callbacks_ex(zn_cb_t rx_done, zn_cb_t prd, zn_cb_t pto, zn_cb_t sfd_to,zn_cb_t sfd_done,zn_cb_t phe,zn_cb_t phd);
/*************************************************************************************************************
* Description: This call enables preamble timeout (SY_STAT_RXPTO event)
* Input Param:
* timeout - Preamble detection timeout, the timeout must be an integer multiple of 127.
*           Every 127 corresponds to one time of PAC. ex: 127 corresponds one time of PAC, 127*2 corresponds two  times of PAC.
* Output Param: None
* Return value: None
*************************************************************************************************************/
void zn_set_preamble_detect_timeout(uint16_t timeout);

/*****************************************************************************************
* Description: This is the ZN's general Interrupt Service Routine.
* Input param: None
* Output param: None
* Return value: None
*****************************************************************************************/
void zn_isr(void);

/*******************************************************************************************************************
* Description: This call initiates the transmission
* Input param:
* mode - if mode = ZN_START_TX_IMMEDIATE - immediate TX
* if mode = ZN_START_TX_DELAYED - delayed TX  at specified time (time in DX_TIME register set by function zn_set_delayed_trx_time)
* Output param: None
* Return value: ZN_SUCCESS for success, or ZN_ERROR for error (e.g. a delayed transmission will be cancelled if the delayed time has passed)
*******************************************************************************************************************/
int32_t zn_start_tx(uint8_t mode);
void zn_rx_state_check(void);

/*******************************************************************************************************************
* Description: This is used to turn off the transceiver
* Input param: None
* Output param: None
* Return value: None
*******************************************************************************************************************/
void zn_force_trx_off(void);

/*******************************************************************************************************************
* Description: This call turns on the receiver, can be immediate or delayed (depending on the mode parameter).
* The receiver will stay turned on, listening to any messages until
* it either receives a good frame, an error (CRC, PHY header, Reed Solomon) or it times out (SFD, Preamble or Frame).
* Input param:
* mode - this can be one of the following allowed values:
* ZN_START_RX_IMMEDIATE  Enable the receiver immediately
* ZN_START_RX_DELAYED  delayed RX  at specified time (time in DX_TIME register set by function zn_set_delayed_trx_time)
* Output param: None
* Return value: ZN_SUCCESS for success, or ZN_ERROR for error
*******************************************************************************************************************/
int32_t zn_rx_enable(uint8_t mode);

/*************************************************************************************************************
* Description: This call enables RX timeout (SYS_STATUS_RFTO event)
* Input param: 
* time - how long the receiver remains on from the RX enable command
* The time parameter used here is in 1us units
* If set to 0 the timeout is disabled.
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_rx_timeout(uint32_t time);

/*************************************************************************************************************
* Description: This call enables RX sfd timeout (SYS_STATUS_SFDTO event)
* Input param: 
* time - how long the receiver remains on from the RX enable command
* The time parameter used here is in 1us units
* If set to 0 the timeout is disabled.
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_rx_sfd_timeout(uint32_t time);

/*************************************************************************************************************
* Description: This call get device state
* Input param: None
* Output param: None
* Return value: 1:INIT 2:IDLE_RC 3:IDLE 4:TX state 5:RX state
*************************************************************************************************************/
uint8_t zn_get_pmsc_state(void);

/*************************************************************************************************************
* Description: This function enables the specified events to trigger an interrupt.
* The following events can be found in SYS_ENABLE_LO register.
* Input param:
* bit_mask - sets the events which will generate interrupt
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_interrupt(uint32_t bit_mask);

/*************************************************************************************************************
* Description: This function is dc estimate.
* Input param: flag
* Output param: None
* Return value: dc estimate value
*************************************************************************************************************/
int32_t zn_dc_estimate(int32_t flag);

/*************************************************************************************************************
* Description: This function is dc Check.
* Input param:
* flag - I or Q flag
* chain_flag - chain flag
* addr - register addr
* proc_flag - proc flag
* Output param:
* gain - gain value
* dc_tmp - dc value
* dc_v - dc value
* r - return value
* return_flag - return flag
* Return value: None
*************************************************************************************************************/
void zn_dc_check(int32_t flag/*I or Q */, int32_t chain_flag/* P or n for step 0 or Q*/, int32_t *gain, int32_t *dc_tmp, int32_t *dc_v, int32_t *r , int32_t *return_flag, int32_t addr, int32_t proc_flag);

/*************************************************************************************************************
* Description: This function is to get VGA dc value one time.
* Input param:
* iq_flag - iq flag
* addr - register addr
* Output param: None
* Return value: VGA dc value
*************************************************************************************************************/
int32_t zn_vga_dc_one_time(int32_t iq_flag, uint32_t addr);

/*************************************************************************************************************
* Description: This function init the dci.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_dc_init(void);

/*************************************************************************************************************
* Description: This function is change 32 to 8.
* Input param:
* data_in - input data
* len - input data length
* Output param:
* data_out - output data
* Return value: output data length
*************************************************************************************************************/
uint32_t change_32_to_8(uint32_t *data_in, uint8_t *data_out, uint32_t len);


/*************************************************************************************************************
* Description: This function store calc val to inner buffer.
* Input param:  None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_calib_store(uint8_t channel);

/*************************************************************************************************************
* Description: This function is load calc val from inner buffer to registers.
* Input param:  None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_calib_load(uint8_t channel);

/*******************************************************************************************************************
* Description: this function is process the inside loop to calibrate the timestamp.
* Input para: None
* 
* Output para: None
* Returns Value: None
*******************************************************************************************************************/
void zn_inside_loop(void);

/*************************************************************************************************************
* Description: This function is waiting until pll is locked or timeout.
* Input param:
* mask - register mask value
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_wait_pll_stable(uint8_t mask);

/*************************************************************************************************************
* Description: This function is to the tx state.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_to_tx_state(void);

/*************************************************************************************************************
* Description: This function is off the rx.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_rf_to_idle_state(void);

/*************************************************************************************************************
* Description: This function is switch the soc to idle state.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_soc_to_idle_state(void);


/*************************************************************************************************************
* Description: This function is to the rx state.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_to_rx_state(void);

void zn_soc_to_work_state(void);

void zn_uwb_reg_clk_switch(uint8_t en);

/*************************************************************************************************************
* Description: This function is to do some preprocess after open rx, for lna switch between one frame.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_preprocess_after_rx_enable(void);

/*************************************************************************************************************
* Description: This function is pa set.
* Input param: 
* value - power level : PA_LEVEL_0 ... PA_LEVEL_7
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_pa_set(uint16_t value);

void set_lna_off_calib_value(void);
void set_lna_on_calib_value(void);

/*************************************************************************************************************
* Description: This function is switch the tx rx antenna.
* Input param: is_on: 1 is to tx antenna, 0 is to rx antenna
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_switch_tx_antenna(uint8_t is_on);

/*************************************************************************************************************
* Description: This function is modify the channel num.
* Input param:
* channel_num - channel num
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_channel(uint32_t channel_num);

/*************************************************************************************************************
* Description: This function is modify the sfd id.
* Input param:
* sfd_id - sfd id
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_sfd_id(uint32_t sfd_id);

/*************************************************************************************************************
* Description: This function is modify the preamble code idx.
* Input param:
* preamble_code_idx - preamble code index
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_preamble_code_idx(uint32_t preamble_code_idx);

/*************************************************************************************************************
* Description: This function is modify the rframe config.
* Input param:
* rframe_cfg - rframe config
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_rframe_cfg(uint32_t rframe_cfg);

/*************************************************************************************************************
* Description: This function is modify the bprf phr data rate.
* Input param:
* bprf_phr_data_rate - bprf phr data rate
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_bprf_phr_data_rate(uint32_t bprf_phr_data_rate);

/*************************************************************************************************************
* Description: This function is modify the sts segment number.
* Input param:
* sts_seg_num - sts segment num
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_sts_seg_num(uint32_t sts_seg_num);

/*************************************************************************************************************
* Description: This function is modify the sts segement length.
* Input param:
* sts_seg_len - sts segment length
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_sts_seg_len(uint32_t sts_seg_len);

/*************************************************************************************************************
* Description: This function is modify the preamble duration.
* Input param:
* preamble_duration - preamble duration
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_preamble_duration(uint32_t preamble_duration);

/*************************************************************************************************************
* Description: This function is modify the psdu data rate.
* Input param:
* psdu_data_rate - psdu data rete
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_psdu_data_rate(uint32_t psdu_data_rate);

/*************************************************************************************************************
* Description: This function is modify the prf mode.
* Input param:
* prf - prf mode
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_prf_mode(uint8_t prf);


/*************************************************************************************************************
* Description: This function is to set the offset between tx send time and timestamp.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_set_tx_ts_offset(uint8_t preamble_duration, uint8_t sfd_id, uint8_t rf_cfg);

/*************************************************************************************************************
* Description: This function is to get the offset between tx send time and timestamp.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
uint32_t zn_get_tx_ts_offset(void);

/*************************************************************************************************************
* Description: This function is to modify the zn config.
* Input param:
* config - config value pointer address
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_config(zn_config_t *config);

/*************************************************************************************************************
* Description: This function is to open loopback.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_loopback_open(void);

/*************************************************************************************************************
* Description: This function is to close loopback.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_loopback_close(void);

/*************************************************************************************************************
* Description: This function is to send cw.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_start_send_cw(void);

/*************************************************************************************************************
* Description: This function is to stop send cw.
* Input param: None
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_stop_send_cw(void);

/*************************************************************************************************************
* Description: This function is to modify the swc.
* Input param:
* value - swc value
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_swc(uint16_t value);

/*************************************************************************************************************
* Description: This function is to modify the swf.
* Input param:
* value - swf value
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_modify_swf(uint16_t value);

/***************************************************************************************************************
* Description: This is used to read the dif_phase and convert to the aoa angle
* Input param:
* channel - channel id
* Output param:
* aoa - aoa result
* valid_flag - indicate the valid flag of the pdoa result
* Return value: None
****************************************************************************************************************/
void zn_read_aoa_result(double *aoa, uint8_t *valid_flag, aoa_mode_e aoa_mode);

/***************************************************************************************************************
* Description: This is used to read the 2d diff_phase
* Input param:
* ant_state - antenna state
* Output param:
* pdoa1 - pdoa1 result
* valid_flag - indicate the valid flag of the pdoa result
* Return value: None
****************************************************************************************************************/
void zn_read_2d_pdoa_nlos_result(double *pdoa1, uint8_t *detectLevel);

/***************************************************************************************************************
* Description: This is used to read the 2d angle
* Input param: None
* Output param:
* pdoa - pdoa angle result
* aoa - aoa angle result
* valid_flag - indicate the valid flag of the pdoa result
* Return value: None
****************************************************************************************************************/
void zn_read_2d_angle(double *pdoa, double *aoa, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 2d aoa angle with no fit method
* Input param:
* pdoa - pdoa value
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* aoa - aoa result
* Return value: None
****************************************************************************************************************/
void zn_cal_2d_angle_by_pdoa(double pdoa, double *aoa, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 2d aoa angle with fit method
* Input param:
* pdoa - pdoa value
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* aoa - aoa result
* Return value: None
****************************************************************************************************************/
void zn_cal_2d_angle_by_pdoa_fit(double pdoa, double *aoa, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d diff_phase
* Input param: None
* Output param:
* pdoa1 - pdoa1 result
* pdoa2 - pdoa2 result
* detectLevel - indicate the quality of the pdoa result:0: bad, 1:not good enough, 2:very good
* Return value: None
****************************************************************************************************************/
void zn_read_3d_pdoa_nlos_result(double *pdoa1, double *pdoa2, uint8_t *detectLevel);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna ceiling type1
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: ceiling(rx0 is origin(O))
* rx0 - rx1
*  |
* rx2
****************************************************************************************************************/
void zn_read_3d_angle_with_antenna_ceiling_type1(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: ceiling(rx0 is origin(O))
* rx0 - rx1
*  |
* rx2
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type1(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: ceiling(rx0 is origin(O))
* rx0 - rx1
*  |
* rx2
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type1_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna ceiling type2
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: ceiling(rx0 is origin(O))
*    rx2
*   /   \
* rx0 - rx1
****************************************************************************************************************/
void zn_read_3d_angle_with_antenna_ceiling_type2(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: ceiling(rx0 is origin(O))
*    rx2
*   /   \
* rx0 - rx1
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type2(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: ceiling(rx0 is origin(O))
*    rx2
*   /   \
* rx0 - rx1
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type2_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna ceiling type3
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: ceiling(The origin(O) is midpoint of rx0 and rx1)
*    rx2
*   /   \
* rx0 - rx1 
****************************************************************************************************************/
void zn_read_3d_angle_with_antenna_ceiling_type3(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: ceiling(The origin(O) is midpoint of rx0 and rx1)
*    rx2
*   /   \
* rx0 - rx1 
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type3(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: ceiling(The origin(O) is midpoint of rx0 and rx1)
*    rx2
*   /   \
* rx0 - rx1 
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_ceiling_type3_fit(double pdoa_sfd, double pdoa_sts,  double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type1
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
* rx2
* |
* rx0 - rx1
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type1(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
* rx2
* |
* rx0 - rx1
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type1(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
* rx2
* |
* rx0 - rx1
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type1_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type2
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
*       rx1        rx0 - rx2
*        |    or    |
* rx2 - rx0        rx1
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type2(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
*       rx1        rx0 - rx2
*        |    or    |
* rx2 - rx0        rx1
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type2(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
*       rx1        rx0 - rx2
*        |    or    |
* rx2 - rx0        rx1
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type2_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type3
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
* rx0 - rx1
*  |
* rx2
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type3(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
* rx0 - rx1
*  |
* rx2
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type3(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
* rx0 - rx1
*  |
* rx2
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type3_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type4
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx0 and rx1)
*    rx2
*   /   \
* rx0 - rx1 
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type4(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx0 and rx1)
*    rx2
*   /   \
* rx0 - rx1 
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type4(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx0 and rx1)
*    rx2
*   /   \
* rx0 - rx1 
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type4_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type5
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx0 and rx2)
*    rx1
*   /   \
* rx2 - rx0
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type5(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx0 and rx2)
*    rx1
*   /   \
* rx2 - rx0
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type5(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx0 and rx2)
*    rx1
*   /   \
* rx2 - rx0
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type5_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type6
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx1 and rx2)
*    rx0         rx2 - rx1
*   /   \    or    \   /
* rx1 - rx2         rx0
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type6(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx1 and rx2)
*    rx0         rx2 - rx1
*   /   \    or    \   /
* rx1 - rx2         rx0
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type6(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(The origin(O) is midpoint of rx1 and rx2)
*    rx0         rx2 - rx1
*   /   \    or    \   /
* rx1 - rx2         rx0
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type6_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to read the 3d azimuth angle and elevation angle with antenna vertical type7
* Input param: None
* Output param:
* pdoa_sfd - sfd pdoa angle result
* pdoa_sts - sts pdoa angle result
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* valid_flag - indicate the valid flag of the aoa result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
*       rx0
*        |
* rx1 - rx2
****************************************************************************************************************/
void zn_read_3d_angle_result_with_antenna_vertical_type7(double *pdoa_sfd, double *pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with no fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
*       rx0
*        |
* rx1 - rx2
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type7(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/***************************************************************************************************************
* Description: This is used to cal the 3d azimuth angle and elevation angle by pdoa with fit method
* Input param:
* pdoa_sfd - horizontal pdoa
* pdoa_sts - vertical pdoa
* valid_flag - indicate the valid flag of the pdoa
* Output param:
* azimuth_angle - azimuth angle result
* elevation_angle - elevation angle result
* Return value: None
* ANT location: vertical(rx0 is origin(O))
*       rx0
*        |
* rx1 - rx2
****************************************************************************************************************/
void zn_cal_3d_angle_by_pdoa_with_antenna_vertical_type7_fit(double pdoa_sfd, double pdoa_sts, double *azimuth_angle, double *elevation_angle, uint8_t *valid_flag);

/*************************************************************************************************************
* Description: This function is switch the antenna switch.
* Input param: ant_state: 
1:pdoa sw froce to rx2 input.
2:pdoa sw force to rxl input
* Output param: None
* Return value: None
*************************************************************************************************************/
void zn_pdoa_antenna_switch(uint8_t ant_state);

/*******************************************************************************************************************
* Description: This is used to calculate estimated clock frequency offset
* Input param: None
* Output param: None
* Return value: frequency offset value
********************************************************************************************************************/
double zn_read_frequency_offset_result(void);

/********************************************************************************************************************
* Description: This is used to read the OTP data from given address into provided array
* Input Param:
* address - this is the OTP address to read from
* length - this is the number of 32 bit words to read (array needs to be at least this length)
* Output Param:
* array - this is the pointer to the array into which to read the data
* Return value: None
********************************************************************************************************************/
void zn_otp_read(uint16_t address, uint32_t *array, uint8_t length);

/********************************************************************************************************************
* Description: This is used to write the OTP data from provided array into given address
* Input Param:
* address - this is the OTP address to write to
* array - this is the pointer to the array from which to write the data
* length - this is the number of 32 bit words to write
* Output Param: None
* Return value: None
********************************************************************************************************************/
void zn_otp_write(uint16_t address, uint32_t *array, uint8_t length);

/********************************************************************************************************************
* Description: This is used to load the otp value to register
* Input Param: None
* Output Param: None
* Return value: None
********************************************************************************************************************/
void zn_otp_load(void);

/*******************************************************************************************************************
* Description: This is set STS_IV and STS_Key value from configured not from the AES register
* Input param: None
* Output param: None
* Return value: None
********************************************************************************************************************/
void zn_sts_load_cfg(void);

/*******************************************************************************************************************
* Description: This is set the STS_IV
* Input param:
* sts_iv - sts iv value
* Output param: None
* return value: None
********************************************************************************************************************/
void zn_sts_iv_set(uint32_t *sts_iv);

/*******************************************************************************************************************
* Description: This is set the STS_Key
* Input param:
* sts_key - sts key value
* Output param: None
* return value: None
********************************************************************************************************************/
void zn_sts_key_set(uint32_t *sts_key);

/*******************************************************************************************************************
* Description: This is set the sts index
* Input param:
* crypto_sts_index - crypto sts index
* Output param: None
* return value: None
********************************************************************************************************************/
void zn_crypto_sts_idx_set(uint32_t crypto_sts_index);

/*******************************************************************************************************************
* Description: This is used to read the data from the CIR_Memery.Preamble CIR Memory contains 8182 valid data and
* STS Cir Memory contains 4224 valid data
* Input param: None
* Output param: 
* buffer_i - read the I data in the Cir memory
* buffer_q - read the Q data in the Cir memory
* Returns value: None
*******************************************************************************************************************/
void zn_read_cir_memory_iprx0(int32_t *buffer_i, int32_t *buffer_q);

/*******************************************************************************************************************
* Description: preamble accumulated Cir memory of RX1 chain
* Input param: None
* Output param:
* buffer_i - read the I data in the Cir memory
* buffer_q - read the Q data in the Cir memory
* Returns value: None
*******************************************************************************************************************/
void zn_read_cir_memory_iprx1(int32_t *buffer_i, int32_t *buffer_q);

/*******************************************************************************************************************
* Description: STS accumulated Cir memory of RX0 chain
* Input param: None
* Output param:
* buffer_i - read the I data in the Cir memory
* buffer_q - read the Q data in the Cir memory
* Returns value: None
*******************************************************************************************************************/
void zn_read_cir_memory_cprx0(int32_t *buffer_i, int32_t *buffer_q);

/*******************************************************************************************************************
* Description: STS accumulated Cir memory of RX1 chain
* Input param: None
* Output param:
* buffer_i - read the I data in the Cir memory
* buffer_q - read the Q data in the Cir memory
* Returns value: None
*******************************************************************************************************************/
void zn_read_cir_memory_cprx1(int32_t *buffer_i, int32_t *buffer_q);

/*******************************************************************************************************************
* Description: this function is change the uci channel_num to zn config
* Input param:
* channel_no - uci channel_num
* Output param: None
* Returns value: zn channel_num
*******************************************************************************************************************/
uint8_t zn_uci_channel_num_to_zn_cfg(uint8_t channel_no);

/*******************************************************************************************************************
* Description: this function is change the uci SFD id to zn config
* Input param:
* sfd_id - uci SFD id
* Output param: None
* Returns value: zn SFD id
*******************************************************************************************************************/
uint8_t zn_uci_sfd_id_to_zn_cfg(uint8_t sfd_id);

/*******************************************************************************************************************
* Description: this function is change the uci preamble code idx to zn config
* Input param:
* index - uci preamble code index
* Output param: None
* Returns value: zn preamble code index
*******************************************************************************************************************/
uint8_t zn_preamble_code_idx_to_zn_cfg(uint8_t index);

/*******************************************************************************************************************
* Description: this function is change the uci seg num to zn config
* Input param:
* seg - uci seg num
* Output param: None
* Returns value: zn seg num
*******************************************************************************************************************/
uint8_t zn_sts_seg_num_to_zn_cfg(uint8_t seg);

/*******************************************************************************************************************
* Description: this function is change the uci data rate to zn config
* Input param:
* rate - uci data rate
* Output param: None
* Returns value: zn data rate
*******************************************************************************************************************/
uint8_t zn_psdu_data_rate_to_zn_cfg(uint8_t rate);

/*******************************************************************************************************************
* Description: this function is change the uci preamble duration to zn config
* Input param:
* duration - uci preamble duration
* Output param: None
* Returns value: zn preamble duration
*******************************************************************************************************************/
uint8_t zn_preamble_duration_to_zn_cfg(uint8_t duration);

/*******************************************************************************************************************
* Description: this function is change the uci phr data rate to zn config
* Input param:
* rate - uci phr data rate
* Output param: None
* Returns value: zn phr data rate
*******************************************************************************************************************/
uint8_t zn_phr_data_rate_to_zn_cfg(uint8_t rate);

/*******************************************************************************************************************
* Description: this function is change the uci rframe cfg to zn config
* Input param:
* cfg - uci rframe cfg
* Output param: None
* Returns value: zn rframe cfg
*******************************************************************************************************************/
uint8_t zn_rframe_cfg_to_zn_cfg(uint8_t cfg);

/*******************************************************************************************************************
* Description: this function is change the uci prf mode to zn config
* Input param:
* cfg - uci prf mode
* Output param: None
* Returns value: zn prf mode
*******************************************************************************************************************/
uint8_t zn_prf_mode_to_zn_cfg(uint8_t prf);

/*******************************************************************************************************************
* Description: this function is change the uci sts seg len to zn config
* Input param:
* seg_len - uci sts seg len
* Output param: None 
* Returns value: zn sts seg len
*******************************************************************************************************************/
uint16_t zn_sts_segments_len_to_zn_cfg(uint8_t seg_len);

/*******************************************************************************************************************
* Description: this function is change the zn psdu data rate to uci config
* Input param:
* rate - zn psdu data rate
* Output param: None
* Returns value: uci psdu data rate
*******************************************************************************************************************/
uint8_t zn_psdu_data_rate_to_uci_cfg(uint8_t rate);

/*******************************************************************************************************************
* Description: this function is change the zn preamble duration to uci config
* Input param: 
* duration - zn preamble duration
* Output param: None
* Returns value: uci preamble duration
*******************************************************************************************************************/
uint8_t zn_preamble_duration_to_uci_cfg(uint8_t duration);

/*******************************************************************************************************************
* Description: this function is cfg rx preamble config
* Input param: 
* rf_cfg  - zn frame config
* duration - zn preamble duration
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_set_rx_preamble_config(uint8_t rf_cfg, uint8_t preamble_duration);

/*******************************************************************************************************************
* Description: this function is cfg rx sfd config
* Input param: 
* sfd_id - zn sfd index
* Output param: None
* Returns value: None
*******************************************************************************************************************/
void zn_set_rx_sfd_config(uint8_t sfd_id);

int AGCLUTstep2dB(int i);

/*******************************************************************************************************************
* Description: This is used to calculate receiver power for the first path
* Input param: None
* Output param: None
* Returns value: receive power
*******************************************************************************************************************/
double zn_recv_power_for_first_path(void);

/*******************************************************************************************************************
* Description: This is used to calculate receiver power for the second path
* Input param: None
* Output param: None
* Returns value: receive power
*******************************************************************************************************************/
double zn_recv_power_for_second_path(void);

/*******************************************************************************************************************
* Description: This is used to output the accumulated symbol number in CIR Memory
* Input param:
* Output param:   nacc: accumulated symbols in CIR Memory
* Returns value: receive power
*******************************************************************************************************************/
uint16_t zn_read_acc_num(void);

/*******************************************************************************************************************
* Description: This is used to output the estimated power based in the CIR Memory
* Input param:
* Output param: noiseResult: estimated noise power based in the CIR Memory. Note that this value is also used as one 
*               of the threshold in first path detection
* Returns value: receive power
*******************************************************************************************************************/
float zn_noise_estimation(void);

/*******************************************************************************************************************
* Description: Configure LED Paremters
* Input param:
*         winLen: the first path search window before peak power path. Depend on the max area of ranging
*         scaleFactor0: scale factor with the estimate noise. May small than 1.5
*         scaleFactor1: scale factor with the max peak in noise area. May small than 4.0
* Output param:
* Returns value:
********************************************************************************************************************/
void zn_led_scalefactor_configuration(float scaleFactor0, float scaleFactor1, uint16_t winLen);

/*******************************************************************************************************************
* Description: Read Vbat voltage
* Input param: mode   TYPE_VBAT: the source is vbat, TYPE_ATESTP: the source is atestp
* Output param:
* Returns value: 
********************************************************************************************************************/
uint16_t zn_read_vbat_voltage(adc_mode_t mode);

/*******************************************************************************************************************
* Description: Read First Path Index in Cir Memory
* Input param: 
* Output param:
* Returns value: 
********************************************************************************************************************/
uint16_t    zn_read_firstPath_index(void);

/*******************************************************************************************************************
* Description: Read First Path Index in Cir Memory
* Input param: 
* Output param:
* Returns value: 
********************************************************************************************************************/
uint16_t    zn_read_peak_index(void);

/*******************************************************************************************************************
* Description: This is used to calculate receiver power for the peak path
* Input param: None
* Output param: None
* Returns value: receive power
*******************************************************************************************************************/
double zn_recv_power_for_peak_path(void);

/*******************************************************************************************************************
* Description: read CIR Memory based by the defined window and based index
* Input param:
*                 baseType :  0: Based on the first path index    1: Based on the peak index 
*                 leftLen  :  length of left part with the base index
*               rightLen :  length of right part with the based index
* Output param: 
*                 buffer_i :  I 
*                buffer_q :  Q
* Returns value: receive power
*******************************************************************************************************************/
void zn_read_cir_memory_iprx0_window(uint8_t baseType, uint16_t leftLen, uint16_t rightLen, int32_t *buffer_i, int32_t *buffer_q);

/*******************************************************************************************************************
* Description: zn_set_user_sfd config
* Input param:  sfd_id_t: SFD_ID_USER8 or SFD_ID_USER16
* Output param:  null
* Returns value: null
*******************************************************************************************************************/
void zn_set_user_sfd(sfd_id_t sfd);
/*******************************************************************************************************************
* Description: set user sfd sequence when set user SFD_ID_USER8 or SFD_ID_USER16
* Input param:  sfd_sequence
* Output param:  null
* Returns value: null
*******************************************************************************************************************/
void zn_set_user_sfd_sequence(uint32_t sfd_sequence);

/***************************************************************************************************************
* Description: This is used to read the 3d diff_phase
* Input param:
* Output param:
* pdoa1 - pdoa1 result
* pdoa2 - pdoa2 result
* valid_flag - indicate the valid flag of the pdoa result
* Return value: None
****************************************************************************************************************/
void zn_read_3d_pdoa_via_cir(double *pdoa1, double *pdoa2, uint8_t *valid_flag);

void zn_set_ext_frame_mode(uint8_t en);

void zn_modify_PDOA_RX1_TIME_en(uint32_t rx_en);
void zn_modify_hprf_en(uint32_t isHPRFen);
void zn_modify_cc_mode(uint32_t ccMode);
void zn_modify_rs_dis(uint32_t disRS);
void zn_modify_hprf_phr_extend_mode(uint32_t extendMode);
void zn_modify_sts_mode(uint32_t stsMode);
uint8_t zn_uci_sfd_id_to_sfd_symbol_num(uint8_t sfd_id);
uint16_t zn_preamble_duration_to_preamble_symbol_num(uint8_t duration);



void zn_32k_calib(void);
void zn_calib_reg_field_wr(const FileConfig *fileConfig, uint32_t field_value);
uint32_t zn_calib_reg_field_rd(const FileConfig *fileConfig);

int32_t zn_dc_estimate_debug(int32_t flag);

void zn_agc_config(void);
void zn_rx0_agcout(uint8_t *lna_tia,uint8_t *vga, uint8_t *ant_flag, uint8_t *lna_flag);
void zn_rx1_agcout(uint8_t *lna_tia,uint8_t *vga, uint8_t *lna_flag);
void zn_read_rx0_lna_tia_vga(void);
void zn_read_rx1_lna_tia_vga(void);
void zn_set_digital_and_analog_fixed_table_index(uint32_t Lna_Fix_Gain_index);
void read_cfg(void);
void read_2nd_cfg(void);
void read_ana_reg_cfg(void);
void zn_write_cal_to_flash(uint8_t channel_num);
void zn_read_cal_from_flash(uint8_t channel_num);

void calib_ana_cfg(void);
//void zn_set_tia_lna_gain(uint32_t gain_value);
void zn_set_tia_lna_gain_rx0(uint32_t gain_value);
void zn_set_tia_lna_gain_rx1(uint32_t gain_value);
void zn_set_tia_word_ovrd_rx0(uint32_t lna_case,uint32_t tia_case);
void zn_set_tia_word_ovrd_rx1(uint32_t lna_case,uint32_t tia_case);
void zn_set_fix_ana_tia_lna_gain_rx0(uint32_t lna_case,uint32_t tia_case);
void zn_set_fix_ana_tia_lna_gain_rx1(uint32_t lna_case,uint32_t tia_case);
void zn_vga_calib_once_rx0(uint32_t vga_case,uint32_t lna_case,uint32_t tia_case);
void zn_vga_calib_once_rx1(uint32_t vga_case,uint32_t lna_case,uint32_t tia_case);
void zn_get_rx0_dc(void);
void zn_get_rx1_dc(void);
void zn_cfg_after_calib(void);
void zn_cfg_after_calib_rx0(void);
void zn_cfg_after_calib_rx1(void);
void zn_vga_calib(void);
void zn_tia_calib(void);
void zn_32k_manual_calib(void);
void zn_32k_calib(void);
void zn_rfpll_calib(void);
void zn_clkpll_calib(void);
void zn_rfpll_calib_load(uint8_t channel);
void zn_pll_calib(uint8_t channel, uint8_t en);
uint32_t zn_get_flash_flag(uint8_t channel);
void zn_calibration(uint8_t channel, uint8_t is_cal);

void zn_fix_gain_calib_rx0(uint32_t vga_case,uint32_t lna_case,uint32_t tia_case);
void zn_fix_gain_calib_rx1(uint32_t vga_case,uint32_t lna_case,uint32_t tia_case);
void zn_fixed_gain_cfg_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void zn_fixed_gain_cfg_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void zn_fixed_ana_gain_cfg_rx0(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void zn_fixed_ana_gain_cfg_rx1(uint32_t lna_case,uint32_t tia_case,uint32_t vga_case);
void zn_vga_recalib_once_rx0(uint32_t vga_case,uint32_t lna_case,uint32_t tia_case);
void zn_vga_recalib_once_rx1(uint32_t vga_case,uint32_t lna_case,uint32_t tia_case);
void zn_vga_optimize_word_rx0(uint32_t *reg_i ,uint32_t *reg_q);
void zn_vga_optimize_word_rx1(uint32_t *reg_i ,uint32_t *reg_q);

void zn_calib_reg_wr_rd_test(void);
void zn_calib_word_map_check(void);
void zn_calib_status_check(void);
void zn_scan_dc(void);
void pll_init(void);
void zn_set_rake_param();
void zn_radar_isr();
void c_radar_test();
void c_radar_timing_verification(uint8_t* , int8_t* );

/***************************************************************************
if timestamp is invalid , using the row stamp to fallback 
*****************************************************************************/
uint64_t timestamp_raw_calc(void);
uint64_t timestamp_raw_calc_rx2(void);
uint8_t timestamp_retry(uint16_t leftfindLen, uint16_t threshold_len, uint64_t timestamp_raw, uint64_t* timestamp_new);
uint8_t timestamp_retry_rx2(uint16_t leftfindLen, uint16_t threshold_len, uint64_t timestamp_raw, uint64_t* timestamp_new);
uint8_t timestamp_retry_peak(uint16_t leftfindLen, uint16_t threshold_len, uint64_t timestamp_raw, uint64_t* timestamp_new);
uint8_t timestamp_retry_peak_rx2(uint16_t leftfindLen, uint16_t threshold_len, uint64_t timestamp_raw, uint64_t* timestamp_new);
uint8_t ranging_confidence_calc(void);
uint8_t ranging_confidence_calc_rx2(void);

void zn_fem_to_tx_state(void);
void zn_fem_to_rx_state(void);
void zn_fem_to_idle_state(void);
void zn_tia_calc(void);
void zn_agc_one_time_clac_rx0(void);
void zn_agc_one_time_clac_rx1(void);
void zn_agc_auto_clac_rx0(void);
void zn_agc_auto_clac_rx1(void);
void zn_read_adc_mem(uint8_t mem_id);
void zn_read_cir_mem_rx0(void);
void zn_read_cir_mem_rx1(void);
void zn_read_sts_mem_rx0(void);
void zn_read_sts_mem_rx1(void);
void zn_agc_gain_mem_read(void);
void zn_calculate_pdoa_via_sfd_cir(double *pdoa, uint8_t *valid_flag, double *min_value_diff);
void zn_calculate_pdoa_via_sts_cir(double *pdoa, uint8_t *valid_flag, double *min_value_diff);
void zn_get_device_id(uint8_t* buf);
// RX0 RX1 dif time 
#define INITIATAL_FRAME_NUM    4
int time_filter_check(double T, int index, int rx0rx1flg);
void zn_two_timestamp_param_config(uint16_t firstPath_Thrlow,  uint16_t firstPath_Thrhigh);
void dif_time_filter( int* deltaRX0, int* deltaRX1, int* valid_rx0, int* valid_rx1 );
int64_t dif_time_combine_in_frame(int64_t dif_s, int64_t dif_p, int valid_s, int valid_p, uint8_t valid_thr_poll,uint8_t valid_thr_final, uint8_t* validRound);
int64_t dif_time_filter_combine(int64_t difTime, uint8_t valid, double distance, double *distanceOut);
#ifdef __cplusplus
}
#endif

#endif

