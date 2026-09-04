#ifndef _UCI_H
#define _UCI_H

#include <stdint.h>


/**********************************************************MACRO DEFINES*************************************/
#define MAX_SESSION_NUM       1
#define MAX_CONTIOLEES_NUM    8

#define STATE_CHANGE_WITH_SESSION_MANAGEMENT_COMMANDS    0x00
#define MAX_RANGING_ROUND_RETRY_COUNT_REACHED            0x01
#define MAX_NUMBER_OF_MEASUREMENTS_REACHED               0x02
#define ERROR_SLOT_LENGTH_NOT_SUPPORTED                  0x20
#define ERROR_INSUFFICIENT_SLOTS_PER_RR                  0x21
#define ERROR_MAC_ADDRESS_MODE_NOT_SUPPORTED             0x22
#define ERROR_INVALID_RANGING_INTERVAL                   0x23
#define ERROR_INVALID_STS_CONFIG                         0x24
#define ERROR_INVALID_RFRAME_CONFIG                      0x25


#define STATUS_OK_MULTICAST_LIST_UPDATE                  0x00
#define STATUS_ERROR_MULTICAST_LIST_FULL_UPDATE          0x01
#define STATUS_ERROR_KEY_FETCH_FAIL_UPDATE               0x02
#define STATUS_ERROR_SUB_SESSION_ID_NOT_FOUND_UPDATE     0x03

#define GID_UCI_CORE                                     0x00
#define GID_UWB_SESSION_CFG                              0x01
#define GID_UWB_SESSION_CTRL                             0x02
#define GID_FIRA_TEST                                    0x0d
#define GID_PROPRIETARY_GROUP                            0x0E
#define GID_PHY_DEBUG                                    0x0F

#define OID_CORE_DEVICE_RESET                            0x00
#define OID_CORE_DEVICE_STATUS_NTF                       0x01
#define OID_CORE_GET_DEVICE_INF                          0x02
#define OID_CORE_GET_CAPS_INF                            0x03
#define OID_CORE_SET_CONFIG                              0x04
#define OID_CORE_GET_CONFIG                              0x05
#define OID_CORE_GENERIC_ERROR_NTF                       0x07
#define OID_QUERY_DEVICE_CLOCK_TIMSTAMP                  0x08
#define OID_CORE_DEVICE_SUSPEND                          0x09

#define OID_SESSION_INIT                                 0x00
#define OID_SESSION_DEINIT                               0x01
#define OID_SESSION_STATUS_NTF                           0x02
#define OID_SESSION_SET_APP_CONFIG                       0x03
#define OID_SESSION_GET_APP_CONFIG                       0x04
#define OID_SESSION_GET_COUNT                            0x05
#define OID_SESSION_GET_STATE                            0x06
#define OID_SESSION_UPDATE_CONROLLER_MULTICAST_LIST      0x07

#define OID_RANGE_START                                  0x00
#define OID_RANGE_STOP                                   0x01
#define OID_RANGE_GET_RANGING_COUNT                      0x03

#define OID_TEST_CONFIG_SET                              0x00
#define OID_TEST_CONFIG_GET                              0x01
#define OID_TEST_PERIODIC_TX                             0x02
#define OID_TEST_PER_RX                                  0x03
#define OID_TEST_RX                                      0x05
#define OID_TEST_LOOPBACK                                0x06
#define OID_TEST_STOP_SESSION                            0x07
#define OID_TEST_SS_TWR                                  0x08
//---out of  fira
#define OID_TEST_DS_TWR                                  0x09
#define OID_TEST_CW                                      0x0A
#define OID_TEST_CALIBRATION                             0x0B
//---out of  fira

//ccc GID_PROPRIETARY_GROUP 
#define OID_SET_APP_CFG_PAGE_VALUES_CMD                  0x26
#define OID_SET_APP_CFG_PAGE_VALUES_RSP                  0x26
#define OID_SET_APP_CFG_PAGE_VALUES_NTF                  0x26
#define OID_GET_APP_CFG_PAGE_VALUES_CMD                  0x28 
#define OID_GET_APP_CFG_PAGE_VALUES_RSP                  0x28 
#define OID_GET_APP_CFG_PAGE_VALUES_NTF                  0x28 

#define OID_LOG_NTF                                      0x00
#define OID_TEST_START_CMD                               0x20
#define OID_TEST_START_RSP                               0x20
#define OID_TEST_STOP_CMD                                0x21
#define OID_TEST_STOP_RSP                                0x21
#define OID_TEST_STOP_NTF                                0x21

#define OID_PHY_DEBUG_CAL                                0x20


#define OID_TEST_NULL                                    0x30

#define STATUS_OK                                        0x00
#define STATUS_REJECTED                                  0x01
#define STATUS_FAILED                                    0x02
#define STATUS_SYNTAX_ERROR                              0x03
#define STATUS_INVALID_PARAM                             0x04
#define STATUS_INVALID_RANGE                             0x05
#define STATUS_INVALID_MESSAGE_SIZE                      0x06
#define STATUS_UNKNOWN_GID                               0x07
#define STATUS_UNKNOWN_OID                               0x08
#define STATUS_READD_ONLY                                0x09
#define STATUS_COMMAND_RETRY                             0x0a
#define STATUS_ERROR_SESSION_NOT_EXIST                   0x11
#define STATUS_ERROR_SESSION_DUPLICATE                   0x12
#define STATUS_ERROR_SESSION_ACTIVE                      0x13
#define STATUS_ERROR_MAX_SESSION_EXCEEDED                0x14
#define STATUS_ERROR_SESSION_NOT_CONFIGURED              0x15
#define STATUS_ERROR_ACTIVE_SESSION_ONGOING              0x16
#define STATUS_ERROR_MULTICAST_LIST_FULL                 0x17
#define STATUS_ERROR_ADDRESS_NOT_FOUND                   0x18
#define STATUS_ERROR_ADDRESS_ALREADY_PRESENT             0x19
#define STATUS_RANGING_TX_FAILED                         0x20
#define STATUS_RANGING_RX_TIMEOUT                        0x21
#define STATUS_RANGING_RX_PHY_DEC_FAILED                 0x22
#define STATUS_RANGING_RX_PHY_TOA_FAILED                 0x23
#define STATUS_RANGING_RX_PHY_STS_FAILED                 0x24
#define STATUS_RANGING_RX_MAC_DEC_FAILED                 0x25
#define STATUS_RANGING_RX_MAC_IE_DEC_FAILED              0x26
#define STATUS_RANGING_RX_MAC_IE_MISSING                 0x27

#define CTRL_MSG_CMD          1
#define CTRL_MSG_RSP          2
#define CTRL_MSG_NTF          3

#define CTRL_MSG_COMPLETE     0
#define CTRL_MSG_SEGMENT      1

#define SESSION_TYPE_RANGE    0x00
#define SESSION_TYPE_CCC      0xA0
#define SESSION_TYPE_TEST     0xD0
#define SESSION_TYPE_RADAR    0xE0


#define MAX_VENDORSPEC_INF_NUM          8
#define MAX_CAPPARAM_NUM                128
#define MAX_DEVICE_CFG_NUM              16
#define MAX_SESSION_CFG_NUM             256
#define MAX_SESSION_CONTROLEE_NUM       16
#define MAX_RANGE_MEAR_NUM              16

#define RANGE_STATUS_NTF_MEAS_LEN       31
#define MAX_UCI_PAYLOAD_LEN             255


#define LOG_RX_STATUS_MASK          0x00000001
#define LOG_TX_STATUS_MASK          0x00000002
#define LOG_RX_TIMESTAMP_MASK       0x00000020
#define LOG_TX_TIMESTAMP_MASK       0x00000040
#define LOG_RX_PSDU_MASK            0x00000080
#define LOG_TX_PSDU_MASK            0x00000100

/*********************************************************ENUM DEFINES******************************************/
typedef enum state_device
{
    DEVICE_STATE_READY = 1,
    DEVICE_STATE_ACTIVE,
    DEVICE_STATE_ERR = 255
}state_device_t;

typedef enum state_session
{
    SESSION_STATE_INIT = 0,
    SESSION_STATE_DEINIT,
    SESSION_STATE_ACTIVE,
    SESSION_STATE_IDLE
}state_session_t;

typedef enum uci_control_msg
{
    CORE_DEVICE_RESET_CMD       = 0,
    CORE_DEVICE_RESET_RSP,
    CORE_DEVICE_STATUS_NTF,
    CORE_GET_DEVICE_INFO_CMD,
    CORE_GET_DEVICE_INFO_RSP,
    CORE_GET_CAPS_INFO_CMD      =5,
    CORE_GET_CAPS_INFO_RSP,
    CORE_SET_CONFIG_CMD,
    CORE_SET_CONFIG_RSP,
    CORE_GET_CONFIG_CMD,
    CORE_GET_CONFIG_RSP         =10,
    CORE_GENERIC_ERROR_NTF,

    SESSION_INIT_CMD,
    SESSION_INIT_RSP,
    SESSION_STATUS_NTF,
    SESSION_SET_APP_CONFIG_CMD  = 15,
    SESSION_SET_APP_CONFIG_RSP,
    RANGE_START_CMD,
    RANGE_START_RSP,
    RANGE_DATA_NTF,
    RANGE_STOP_CMD              = 20,
    RANGE_STOP_RSP,
    SESSION_DEINIT_CMD,
    SESSION_DEINIT_RSP,

    RANGE_GET_RANGING_COUNT_CMD,
    RANGE_GET_RANGING_COUNT_RSP     = 25,
    SESSION_GET_APP_CONFIG_CMD,
    SESSION_GET_APP_CONFIG_RSP,
    SESSION_GET_COUNT_CMD,
    SESSION_GET_COUNT_RSP,
    SESSION_GET_STATE_CMD           = 30,
    SESSION_GET_STATE_RSP,
    SESSION_UPDATE_CONTROLLER_MULTICAST_LIST_CMD,
    SESSION_UPDATE_CONTROLLER_MULTICAST_LIST_RSP,
    SESSION_UPDATE_CONTROLLER_MULTICAST_LIST_NTF,

    TEST_CONFIG_SET_CMD     = 50,
    TEST_CONFIG_SET_RSP,
    TEST_CONFIG_GET_CMD,
    TEST_CONFIG_GET_RSP,
    TEST_PERIODIC_TX_CMD,
    TEST_PERIODIC_TX_RSP    = 55,
    TEST_PERIODIC_TX_NTF,
    TEST_PER_RX_CMD,
    TEST_PER_RX_RSP,
    TEST_PER_RX_NTF,
    TEST_RX_CMD             = 60,
    TEST_RX_RSP,
    TEST_RX_NTF,
    TEST_LOOPBACK_CMD,
    TEST_LOOPBACK_RSP,
    TEST_LOOPBACK_NTF       = 65,
    TEST_STOP_SESSION_CMD,
    TEST_STOP_SESSION_RSP,
    TEST_SS_TWR_CMD,
    TEST_SS_TWR_RSP,
    TEST_SS_TWR_NTF         = 70,
    TEST_DS_TWR_CMD,
    TEST_DS_TWR_RSP,
    TEST_DS_TWR_NTF,
    TEST_CW_CMD,
    TEST_CW_RSP             = 75,
    TEST_CALIBRATION_CMD,
    TEST_CALIBRATION_RSP,
    SET_APP_CFG_PAGE_VALUES_CMD, 
    GET_APP_CFG_PAGE_VALUES_CMD,
    TEST_START_CMD = 80,
    TEST_STOP_CMD,
    
    TEST_PHY_DEBUG_CMD,
    TEST_PHY_TEST_CAL_RSP,
    QUERY_UWB_TIMESTAMP,

    NULL_MSG
}uci_control_msg_t;

typedef enum core_cfg_tag
{
    DEVICE_STATE = 0x00,
    LOW_POWER_MODE = 0x01,   
}core_cfg_tag_t;

typedef enum low_power_mode
{
    LOW_POWER_MODE_DISABLE = 0x00,
    LOW_POWER_MODE_ENABLE = 0x01
}low_power_mode_t;

typedef enum session_cfg_tag
{
    DEVICE_TYPE = 0x00,
    RANGING_ROUND_USAGE,
    STS_CONFIG,
    MULTI_MODE_MODE,
    CHANNEL_NUMBER,
    NUMBER_OF_CONTROLEES,
    DEVICE_MAC_ADDRESS,
    DST_MAC_ADDRESS,
    SLOT_DURATION,
    RANGING_INTERVAL,
    STS_INDEX,
    MAC_FCS_TYPE,
    RANGING_ROUND_CONTROL,
    AOA_RESULT_REQ,
    RANGE_DATA_NTF_CONFIG,
    RANGE_DATA_NTF_PROXIMITY_NEAR,
    RANGE_DATA_NTF_PROXIMITY_FAR,
    DEVICE_ROLE,
    RFRAME_CONFIG,
    PREAMBLE_CODE_INDEX = 0x14,
    SFD_ID,
    PSDU_DATA_RATE,
    PREAMBLE_DURATION,
    RANGING_TIME_STRUCT = 0x1a,
    SLOTS_PER_RR,
    TX_ADAPTIVE_PAYLOAD_POWER,
    RESPONDER_SLOT_INDEX = 0x1e,
    PRF_MODE,
    SCHEDULED_MODE = 0x22,
    KEY_ROTATION,
    KEY_ROTATION_RATE,
    SESSION_PRIORITY,
    MAC_ADDRESS_MODE,
    VENDOR_ID,
    STATIC_STS_IV,
    NUMBER_OF_STS_SEGMENTS,
    MAX_RR_RETRY,
    UWB_INITIATION_TIME,
    HOPPING_MODE,
    BLOCK_STRIDE_LENGTH,
    RESULT_REPORT_CONFIG,
    IN_BAND_TERMINATION_ATTEMPT_COUNT,
    SUB_SESSION_ID,
    BPRF_PHR_DATA_RATE,
    MAX_NUMBER_OF_MEASURE,
    STS_LENGTH = 0x35,
    HOP_MODE_KEY = 0xa0,

    PROTOCOL_VER = 0xa3,
    UWB_CONFIG_ID,
    PULSE_SHAPE_CAMBO,
    //NXP support
    STATIC_KEYS = 0xE9,
    RXTX_ENABLE = 0xF0,
    RR_RETRY_THR = 0xf1,
    TX_POWER_ID = 0xf2,
    LOGGING_ENABLE = 0xF5,
    LOG_PARAMS_CONF = 0xF6, 
}session_cfg_tag_t;

typedef enum test_cfg_tag
{
    NUM_PACKETS = 0x00,
    T_GAP,
    T_START,
    T_WIN,
    RANDOMIZE_PSDU,
    RMARKER_TX_START,
    RMARKER_RX_START,
    STS_INDEX_AUTO_INCR,
    GAIN_INDEX = 0xA0,        //tx power cal , 1 Octets
    CAP_SWC_INDEX,            //tx xtal o cal, 1 Octets
    CAP_SWF_INDEX,            //tx xtal i cal, 1 Octets
    ANT_TX_DELAY,             //ANT_TX_DELY, 4 Octets
    ANT_RX_DELAY,             //ANT_RX_DELY, 4 Octets
}test_cfg_tag_t;

typedef enum app_cfg_page_value_tag
{
    TX_POWER_DIFF = 0x00,
    FREQ_DIFF = 0x01,
    ANTENNA_DELAY,
    CURRENT_LIMITER,
    GROUP_DELAY,
    TEMP_COMPENS_FLAG,
    ADAPTIVE_POWER_ID,
    DDFS_TONE_VALUES,
    MINIMUM_WUP_TIME_DPD = 0x0B,
    MINIMUM_RX_RAMPUP_TIME,
    MINIMUM_TX_RAMPUP_TIME    
}app_cfg_page_value_tag_t;

typedef enum static_key_type
{
    SALT = 0x00,
    M_URSK,
    M_UPSK1,
    SALTED_HASH,
    D_URSK,
    D_UDSK   
}static_key_type_t;

typedef enum test_mode
{
    RECEIVE_MODE = 0x00,
    TRANSMIT_MODE,
    CW_TRANSMIT_MODE,
    LOOP_BACK_MODE,
    SS_TWR_MODE
}test_mode_t;

typedef enum test_start_tag
{
    MODE = 0x00,
    DELAY,
    FRAME_TYPE,
    PSDU,
    TIME_OUT,
    EVENT_COUNTER_MAX = 0x05,
    TX_CYCLE_TIME,
    CRC_ENABLE = 0x08,
    PHR_RANGING_BIT,
}test_start_tag_t;

typedef enum log_para_tag
{
    RX_STATUS = 0x00,
    TX_STATUS,
    RX_CIR_LOG,
    UWB_SESSION_ID,
    BLOCK_INDEX,
    RX_TIMESTAMP = 0x05,
    TX_TIMESTAMP,
    RX_PSDU,
    TX_PSDU_DECRYPTED
}log_para_tag_t;

typedef enum timestamp_status
{
    NO_TIMESTAMP = 0x00,
    RX1_TIMESTAMP,
    RX2_TIMESTAMP,
    TX1_TIMESTAMP,
    TX2_TIMESTAMP,
    INVALID_TIMESTAMP = 0xFF,
}timestamp_status_t;

typedef enum app_cfg_page_status
{
    APPLIED = 0x00,
    CORRUPTED,
    FAILURE,
    FAILURE_GROUPDELAY,
    NVM_ERROR,
    FAILURE_CURRENT_LIMITER,
}app_cfg_page_status_t;

typedef void (*host_uci_control_msg_handler_t)(uci_control_msg_t next_uci_ctl_msg);
typedef void (*uwbs_uci_control_msg_handler_t)(uint8_t *uci_msg_payload, uint8_t payload_len);

/*********************************************************STRUCT DEFINES****************************************/
/***********************Device Capability *************************/
typedef struct list_of_optional_channels_supported_capability
{
    uint8_t is_channel5_supported:1;
    uint8_t is_channel6_supported:1;
    uint8_t is_channel8_supported:1;
    uint8_t is_channel10_supported:1;
    uint8_t is_channel12_supported:1;
    uint8_t is_channel13_supported:1;
    uint8_t is_channel14_supported:1;
}list_of_optional_channels_supported_capability_t;

typedef struct aoa_capability
{
    uint8_t is_aoa_azimuth_measurement_support:1;
    uint8_t is_aoa_elevation_measurement_support:1;
    uint8_t is_aoa_fom_measurement_support:1;
    uint8_t is_aoa_azimuth_request:1;
    uint8_t is_aoa_elevation_request:1;
    uint8_t is_aoa_fom_request:1;
}aoa_capability_t;

typedef struct xprf_parameter_capability
{
    uint32_t is_hprf_supported;
    uint32_t is_hprfParameter_set3_supported:1;
    uint32_t is_hprfParameter_set4_supported:1;
    uint32_t is_hprfParameter_set5_supported:1;
    uint32_t is_hprfParameter_set7_supported:1;
    uint32_t is_hprfParameter_set9_supported:1;
    uint32_t is_hprfParameter_set11_supported:1;
    uint32_t is_hprfParameter_set13_supported:1;
    uint32_t is_hprfParameter_set14_supported:1;
    uint32_t is_hprfParameter_set15_supported:1;
    uint32_t is_hprfParameter_set16_supported:1;
    uint32_t is_hprfParameter_set17_supported:1;
    uint32_t is_hprfParameter_set18_supported:1;
    uint32_t is_hprfParameter_set19_supported:1;
    uint32_t is_hprfParameter_set21_supported:1;
    uint32_t is_hprfParameter_set23_supported:1;
    uint32_t is_hprfParameter_set25_supported:1;
    uint32_t is_hprfParameter_set27_supported:1;
    uint32_t is_hprfParameter_set29_supported:1;
    uint32_t is_hprfParameter_set31_supported:1;
    uint32_t is_non_systematic_convolutional_coding_for_hprf_supported:1;
    uint32_t is_bprf_parameter_set5_supported:1;
    uint32_t is_bprf_parameter_set6_supported:1;
}xprf_parameter_capability_t;

typedef struct controlee_mac_address
{
    uint8_t number_of_controlees;
    uint8_t controlee_extended_mac_addresses[8];
    uint8_t initiator_extended_mac_addresses[8];
}controlee_mac_address_t;

typedef struct controlee_capability
{
    list_of_optional_channels_supported_capability_t list_of_optional_channels_supported_capability;
    aoa_capability_t                                 aoa_capability;
    xprf_parameter_capability_t                      xprf_parameter_capability;
    controlee_mac_address_t                          controlee_mac_address;

    uint32_t is_initiator_feature_capability_supported:1;
    uint32_t is_one_to_many_feature_capability_supported:1;
    uint32_t is_sp0_rframe_feature_supported:1;
    uint32_t is_sp1_rframe_feature_supported:1;
    uint32_t is_non_deferred_mode_supported:1;
    uint32_t is_tof_request:1;
    uint32_t is_block_striding_capability_supported:1;
    uint32_t fira_sts_type:1;
    uint32_t device_class:2;
    uint32_t uwb_initiation_time:22;
}controlee_capability_t;

/*********************** Device Config *************************/
typedef struct device_state
{
    state_device_t    cur_state;
    state_device_t    next_state;
}device_state_t;

typedef struct session_state_t
{
    state_session_t    cur_state;
    state_session_t    next_state;
}session_state_t;

typedef struct static_key
{
    uint8_t     key_type;
    uint8_t     key_encry_info;
    uint8_t     key_value[32];
}static_key_t;

typedef struct session_cfg
{
    uint8_t     device_type;
    uint8_t     ranging_round_usage;

    uint8_t     channel_no;
    uint8_t     controlee_num;
    uint8_t     mac_fcs_type;

    uint8_t     aoa_req;
    uint8_t     range_data_ntf_cfg;
    uint8_t     range_role;
    uint8_t     rframe_cfg;
    uint8_t     sfd_id;

    uint8_t     preamble_code_idx;
    uint8_t     psdu_data_rate;

    uint8_t     range_mode;
    uint8_t     tx_adaptive_payload_power;
    uint8_t     schedule_mode;
    uint8_t     key_rotation;
    uint8_t     hopping_mode;
    uint8_t     preamble_duration;
    uint8_t     prf_mode;
    uint8_t     ranging_time_struct;
    uint8_t     responder_slot_index;

    uint8_t     ranging_round_ctrl;
    uint8_t     slots_per_ranging_round;
    uint8_t     priority;
    uint8_t     result_report_cfg;
    uint8_t     bprf_phr_data_rate;
    uint8_t     sts_cfg;
    uint8_t     sts_len;
    uint8_t     number_of_sts_segments;
    uint32_t    sts_index0;
    uint16_t    self_mac_addr;
    uint16_t    vendor_id;
    uint16_t    max_ranging_round_retry;
    uint16_t    slot_duration;
    uint16_t    max_num_of_measurements;
    uint32_t    ranging_interval;
    uint8_t     key_rotation_rate;
    uint64_t    uwb_init_time;
    uint32_t    sub_session_id;
    uint32_t    hopping_mode_key;
    uint16_t    protocol_ver;
    uint16_t    uwb_config_id;
    uint8_t     pulse_cambo;
    uint32_t    ecb_ursk[8];
    uint8_t     radar_type;
    uint32_t    rcm_margin_time;
    uint32_t    rcm_timeout;
    uint16_t    rr_retry_thr;
    uint8_t     tx_power_id;
    static_key_t static_key[6];
}session_cfg_t;

typedef struct session_inst
{
    uint8_t          session_is_used;
    uint32_t         session_id;
    uint8_t          session_type;
    uint8_t          session_is_cfg;
    uint8_t          test_is_cfg;
    uint32_t         session_handle;
    session_cfg_t    session_cfg;
    session_state_t  session_state;
    uint32_t         session_err_codes;
    uint32_t         session_ranging_count;
    uint8_t          session_reason_code;
}session_inst_t;

typedef struct core_cap_para
{
    uint8_t slot_bit_mask;
    uint32_t sync_code_mask;
    uint8_t hopping_config_mask;
    uint8_t channel_mask;
    uint16_t support_protocol_verion;
    uint16_t support_uwb_config_id[2];
    uint8_t uwb_cambo_shape;
}core_cap_para_t;

typedef struct ranging_meas
{
    uint8_t     status;
    uint8_t     slot_index;
    uint8_t     nlos;
    uint8_t     aoa_dest_elevation_fom;
    uint8_t     aoa_elevation_fom;
    uint8_t     aoa_dest_azimuth_fom;
    uint16_t    addr;
    uint16_t    distance;
    uint16_t    aoa_azimuth;
    uint16_t    aoa_azimuth_fom;
    uint16_t    aoa_elevation;
    uint16_t    aoa_dest_azimuth;
    uint16_t    aoa_dest_elevation;
}ranging_meas_t;

typedef struct measurement_rlt
{
    uint32_t       seq_num;
    uint32_t       cur_ranging_interval;
    uint8_t        ranging_meas_type;
    uint8_t        addr_type;
    uint8_t        ranging_meas_num;
    ranging_meas_t ranging_meas[MAX_RANGE_MEAR_NUM];
}measurement_rlt_t;

typedef struct ap_session
{
    uint8_t           session_type;
    uint32_t          session_id;
    measurement_rlt_t session_meas_rlt;
    uint8_t           session_cfg[255];
}ap_session_t;

typedef struct host_device_inst
{
    uint8_t      cur_session_idx;
    uint8_t      session_num;
    uint8_t      exist_session_num;
    uint8_t      device_type;
    ap_session_t ap_session[MAX_SESSION_NUM];
}host_device_inst_t;

typedef struct ap_core_set_cfg_t
{
    uint8_t    param_num;
    uint8_t    param[MAX_DEVICE_CFG_NUM];
}ap_core_set_cfg_t;

typedef struct test_set_cfg
{
    uint32_t   num_packets;
    uint16_t   psdu_len;
    uint32_t   t_gap;
    uint32_t   t_start;
    uint32_t   t_win;
    uint32_t   randomize_psdu;
    uint32_t   phr_ranging_bit;
    uint32_t   rmarker_tx_start;
    uint32_t   rmarker_rx_start;
    uint32_t   sts_index_auto_incr;
    uint16_t   gain_index;
    uint16_t   cap_swc_index;
    uint16_t   cap_swf_index;
    uint32_t   tx_ant_delay;
    uint32_t   rx_ant_delay;    
}test_set_cfg_t;

/*****************************UCI Control Message**************************************************/
#pragma pack (1)
typedef struct uci_core_get_dev_inf_rsp
{
    uint8_t    status;
    uint16_t   uci_generic_version;
    uint16_t   mac_version;
    uint16_t   phy_version;
    uint16_t   uci_test_version;
    uint8_t    vendor_spec_inf_len;
    uint8_t    vendor_spec_inf[MAX_VENDORSPEC_INF_NUM];
}uci_core_get_dev_inf_rsp_t;

typedef struct uci_core_get_caps_rsp
{
    uint8_t    status;
    uint8_t    cap_param_num;
    uint8_t    cap_param[MAX_CAPPARAM_NUM];
}uci_core_get_caps_rsp_t;

typedef struct uci_core_get_cfg_cmd
{
    uint8_t    param_num;
    uint8_t    param[MAX_DEVICE_CFG_NUM];
}uci_core_get_cfg_cmd_t;

typedef struct uci_core_get_cfg_rsp
{
    uint8_t    status;
    uint8_t    param_num;
    uint8_t    param[MAX_DEVICE_CFG_NUM];
}uci_core_get_cfg_rsp_t;

typedef struct uci_core_set_cfg_cmd
{
    uint8_t    param_num;
    uint8_t    param[MAX_DEVICE_CFG_NUM];
}uci_core_set_cfg_cmd_t;

typedef struct uci_core_set_cfg_rsp
{
    uint8_t    status;
    uint8_t    param_num;
    uint8_t    param[MAX_DEVICE_CFG_NUM];
}uci_core_set_cfg_rsp_t;

typedef struct uci_core_dev_status_ntf
{
    uint8_t    dev_state;
}uci_core_dev_status_ntf_t;

typedef struct uci_core_dev_reset_cmd
{
    uint8_t    reset_cfg;
}uci_core_dev_reset_cmd_t;

typedef struct uci_core_dev_reset_rsp
{
    uint8_t    status;
}uci_core_dev_reset_rsp_t;

typedef struct uci_core_error_ntf
{
    uint8_t    status;
}uci_core_error_ntf_t;

typedef struct uci_session_init_cmd
{
    uint32_t    session_id;
    uint8_t     session_type;
}uci_session_init_cmd_t;

typedef struct uci_session_init_rsp
{
    uint8_t    status;
    uint32_t   session_handle;
}uci_session_init_rsp_t;

typedef struct uci_session_deinit_cmd
{
    uint32_t    session_handle;
}uci_session_deinit_cmd_t;

typedef struct uci_session_deinit_rsp
{
    uint32_t    status;
}uci_session_deinit_rsp_t;

typedef struct uci_session_status_ntf
{
    uint32_t    session_handle;
    uint8_t     session_state;
    uint8_t     reason_code;
}uci_session_status_ntf_t;

typedef struct uci_session_set_app_cfg_cmd
{
    uint32_t    session_handle;
    uint8_t     app_cfg_num;
    uint8_t     app_cfg_param[MAX_SESSION_CFG_NUM];
}uci_session_set_app_cfg_cmd_t;

typedef struct uci_session_set_app_cfg_rsp
{
    uint8_t    status;
    uint8_t    app_cfg_num;
    uint8_t    app_cfg_param[MAX_SESSION_CFG_NUM];
}uci_session_set_app_cfg_rsp_t;

typedef struct uci_session_get_app_cfg_cmd
{
    uint32_t    session_handle;
    uint8_t     app_cfg_num;
    uint8_t     app_cfg_param[MAX_SESSION_CFG_NUM];
}uci_session_get_app_cfg_cmd_t;

typedef struct uci_session_get_app_cfg_rsp
{
    uint8_t    status;
    uint8_t    app_cfg_num;
    uint8_t    app_cfg_param[MAX_SESSION_CFG_NUM];
}uci_session_get_app_cfg_rsp_t;

typedef struct uci_session_get_state_cmd
{
    uint32_t    session_handle;
}uci_session_get_state_cmd_t;

typedef struct uci_session_get_state_rsp
{
    uint8_t    status;
    uint8_t    session_state;
}uci_session_get_state_rsp_t;

typedef struct uci_session_get_count_rsp
{
    uint8_t    status;
    uint8_t    sessions_count;
}uci_session_get_count_rsp_t;

typedef struct uci_session_update_controller_multicast_list_cmd
{
    uint32_t    session_handle;
    uint8_t     action;
    uint8_t     controlee_num;
    uint8_t     controlee_list[MAX_SESSION_CONTROLEE_NUM];
}uci_session_update_controller_multicast_list_cmd_t;

typedef struct uci_session_update_controller_multicast_list_rsp
{
    uint8_t    status;
}uci_session_update_controller_multicast_list_rsp_t;

typedef struct uci_session_update_controller_multicast_list_ntf
{
    uint32_t    session_handle;
    uint8_t     remain_list_size;
    uint8_t     controlee_num;
    uint8_t     status_list[MAX_SESSION_CONTROLEE_NUM];
}uci_session_update_controller_multicast_list_ntf_t;

typedef struct uci_range_start_cmd
{
    uint32_t    session_handle;
}uci_range_start_cmd_t;

typedef struct uci_range_start_rsp
{
    uint8_t    status;
}uci_range_start_rsp_t;

typedef struct uci_range_data_ntf
{
    uint32_t    sequence_num;
    uint32_t    session_handle;
    uint8_t     rsv;
    uint32_t    cur_range_intrval;
    uint8_t     range_type;
    uint8_t     rsv1;
    uint8_t     addr_mode;
    uint8_t     rsv2[8];
    uint8_t     range_mea_num;
    uint8_t     range_meaurements[MAX_RANGE_MEAR_NUM * RANGE_STATUS_NTF_MEAS_LEN];
}uci_range_data_ntf_t;

typedef struct uci_range_stop_cmd
{
    uint32_t    session_handle;
}uci_range_stop_cmd_t;

typedef struct uci_range_stop_rsp
{
    uint8_t    status;
}uci_range_stop_rsp_t;

typedef struct uci_range_get_count_cmd
{
    uint32_t   session_handle;
}uci_range_get_count_cmd_t;

typedef struct uci_range_get_count_rsp
{
    uint8_t    status;
    uint32_t   count;
}uci_range_get_count_rsp_t;

typedef struct uci_invalid_gid_oid_rsp
{
    uint8_t    status;
}uci_invalid_gid_oid_rsp_t;

typedef struct uci_set_app_cfg_page_values_cfg_cmd
{
    uint8_t     para_num;
    uint8_t     param[MAX_SESSION_CFG_NUM];
}uci_set_app_cfg_page_values_cfg_cmd_t;

typedef struct uci_get_app_cfg_page_values_cfg_cmd
{
    uint8_t     para_num;
    uint8_t     param[MAX_SESSION_CFG_NUM];
}uci_get_app_cfg_page_values_cfg_cmd_t;

typedef struct uci_log_ntf
{
    uint8_t     para_num;
    uint8_t     param[MAX_SESSION_CFG_NUM];
}uci_log_ntf_t;

typedef struct uci_msg_header
{
    uint8_t    gid:4;
    uint8_t    pbf:1;
    uint8_t    msg_type:3;

    uint8_t    oid:6;
    uint8_t    rsv:2;
    
    uint8_t    rsv1;
    uint8_t    payload_len;
}uci_msg_header_t;


typedef struct uci_msg
{
    uci_msg_header_t                                          msg_header;
    union
    {
        uci_core_get_dev_inf_rsp_t                            core_get_dev_inf_rsp;
        uci_core_get_caps_rsp_t                               core_get_caps_rsp;
        uci_core_get_cfg_cmd_t                                core_get_cfg_cmd;
        uci_core_get_cfg_rsp_t                                core_get_cfg_rsp;
        uci_core_set_cfg_cmd_t                                core_set_cfg_cmd;
        uci_core_set_cfg_rsp_t                                core_set_cfg_rsp;
        uci_core_dev_status_ntf_t                             core_dev_status_ntf;
        uci_core_dev_reset_cmd_t                              core_dev_rst_cmd;
        uci_core_dev_reset_rsp_t                              core_dev_rst_rsp;
        uci_core_error_ntf_t                                  core_err_ntf;
        uci_session_init_cmd_t                                session_init_cmd;
        uci_session_init_rsp_t                                session_init_rsp;
        uci_session_deinit_cmd_t                              session_deinit_cmd;
        uci_session_deinit_rsp_t                              session_deinit_rsp;
        uci_session_status_ntf_t                              session_status_ntf;
        uci_session_set_app_cfg_cmd_t                         session_set_cfg_cmd;
        uci_session_set_app_cfg_rsp_t                         session_set_cfg_rsp;
        uci_session_get_app_cfg_cmd_t                         session_get_cfg_cmd;
        uci_session_get_app_cfg_rsp_t                         session_get_cfg_rsp;
        uci_session_get_state_cmd_t                           session_get_state_cmd;
        uci_session_get_state_rsp_t                           session_get_state_rsp;
        uci_session_get_count_rsp_t                           session_get_count_rsp;
        uci_session_update_controller_multicast_list_cmd_t    session_update_controller_list_cmd;
        uci_session_update_controller_multicast_list_rsp_t    session_update_controller_list_rsp;
        uci_session_update_controller_multicast_list_ntf_t    session_update_controller_list_ntf;
        uci_range_start_cmd_t                                 range_start_cmd;
        uci_range_start_rsp_t                                 range_start_rsp;
        uci_range_data_ntf_t                                  range_data_ntf;
        uci_range_stop_cmd_t                                  range_stop_cmd;
        uci_range_stop_rsp_t                                  range_stop_rsp;
        uci_range_get_count_cmd_t                             range_get_count_cmd;
        uci_range_get_count_rsp_t                             range_get_count_rsp;
        uci_invalid_gid_oid_rsp_t                             invalid_gid_oid_rsp;
        uci_log_ntf_t                                         log_ntf;
    }msg_data;
}uci_msg_t;

typedef struct ranging_measurement
{
    uint16_t        mac_address;
    uint8_t         status;
    uint8_t         nloS;
    uint16_t        distance;
    int16_t         aoa_azimuth;
    uint8_t         aoa_azimuth_fom;
    uint16_t        aoa_elevation;
    uint8_t         aoa_elevation_fom;
    uint16_t        aoa_destination_azimuth;
    uint8_t         aoa_destination_azimuth_fom;
    uint16_t        aoa_destination_elevation;
    uint8_t         aoa_destination_elevation_fom;
    uint8_t         slot_index;
    uint8_t         reserve[12];
}ranging_measurement_t;

typedef struct distance_msg
{
    uint8_t  node_type;
    uint8_t  flag;
    uint16_t round_index;
    uint32_t block_index;
    uint16_t distance[4];
}distance_msg_t;

typedef struct test_config_set_cmd
{
    uint32_t session_handle;
    uint8_t  num_of_cfg;
    uint8_t  cfg[127];
}test_config_set_cmd_t;

typedef struct test_config_set_rsp
{
    uint8_t  status;
    uint8_t  num_of_cfg;
    uint8_t  cfg[127];
}test_config_set_rsp_t;

typedef struct test_config_get_cmd
{
    uint32_t session_handle;
    uint8_t  num_of_cfg;
    uint8_t  cfg[127];
}test_config_get_cmd_t;

typedef struct test_config_get_rsp
{
    uint8_t  status;
    uint8_t  num_of_cfg;
    uint8_t  cfg[127];
}test_config_get_rsp_t;

typedef struct test_periodic_tx_cmd
{
    uint8_t psdu_data[127];
}test_periodic_tx_cmd_t;

typedef struct test_periodic_tx_rsp
{
    uint8_t status;
}test_periodic_tx_rsp_t;

typedef struct test_periodic_tx_ntf
{
    uint8_t status;
}test_periodic_tx_ntf_t;

typedef struct test_periodic_rx_cmd
{
    uint8_t psdu_data[127];
}test_periodic_rx_cmd_t;

typedef struct test_periodic_rx_rsp
{
    uint8_t status;
}test_periodic_rx_rsp_t;

typedef struct test_periodic_rx_ntf
{
    uint8_t  status;
    uint32_t attempts;
    uint32_t acq_detect;
    uint32_t acq_reject;
    uint32_t rx_fail;
    uint32_t sync_cir_ready;
    uint32_t sfd_fail;
    uint32_t sfd_found;
    uint32_t phr_dec_error;
    uint32_t phr_bit_error;
    uint32_t psdu_ded_error;
    uint32_t psdu_bit_error;
    uint32_t sts_found;
    uint32_t eof;
}test_periodic_rx_ntf_t;

typedef struct test_rx_rsp
{
    uint8_t status;
}test_rx_rsp_t;

typedef struct test_rx_ntf
{
    uint8_t  status;
    uint32_t rx_done_ts_int;
    uint16_t rx_done_ts_frac;
    uint16_t aoa_azimuth;
    uint16_t aoa_elevation;
    uint8_t  toa_gap;
    uint16_t phr;
    uint16_t psdu_data_length;
    uint8_t  psdu_data[127];
}test_rx_ntf_t;

typedef struct test_loopback_cmd
{
    uint8_t psdu_data[127];
}test_loopback_cmd_t;

typedef struct test_loopback_rsp
{
    uint8_t status;
}test_loopback_rsp_t;

typedef struct test_loopback_ntf
{
    uint8_t  status;
    uint32_t tx_ts_int;
    uint16_t tx_ts_frac;
    uint32_t rx_ts_int;
    uint16_t rx_ts_frac;
    uint16_t aoa_azimuth;
    uint16_t aoa_elevation;
    uint16_t phr;
    uint16_t psdu_data_length;
    uint8_t  psdu_data[127];
}test_loopback_ntf_t;

typedef struct test_ss_twr_cmd
{
    uint8_t psdu_data[127];
}test_ss_twr_cmd_t;

typedef struct test_ss_twr_rsp
{
    uint8_t status;
}test_ss_twr_rsp_t;

typedef struct test_ss_twr_ntf
{
    uint8_t status;
    uint32_t measurement;
}test_ss_twr_ntf_t;

typedef struct test_ds_twr_cmd
{
    uint8_t psdu_data[127];
}test_ds_twr_cmd_t;

typedef struct test_ds_twr_rsp
{
    uint8_t status;
}test_ds_twr_rsp_t;

typedef struct test_ds_twr_ntf
{
    uint8_t  status;
    uint32_t round1;
    uint32_t reply2;
}test_ds_twr_ntf_t;

typedef struct test_stop_session_rsp
{
    uint8_t status;
}test_stop_session_rsp_t;

//out of fira uci
typedef struct test_cal_cmd
{
    uint32_t session_handle;
    uint8_t  num_of_cfg;
    uint8_t  cfg[127];
}test_cal_cmd_t;

typedef struct test_cal_rsp
{
    uint8_t  status;
    uint8_t  num_of_cfg;
    uint8_t  cfg[127];
}test_cal_rsp_t;
//out of fira uci

typedef struct uci_test_msg
{
    uci_msg_header_t                                          msg_header;
    union
    {
        test_config_set_cmd_t                                 test_config_set_cmd;
        test_config_set_rsp_t                                 test_config_set_rsp;
        test_config_get_cmd_t                                 test_config_get_cmd;
        test_config_get_rsp_t                                 test_config_get_rsp;
        test_periodic_tx_cmd_t                                test_periodic_tx_cmd;
        test_periodic_tx_rsp_t                                test_periodic_tx_rsp;
        test_periodic_tx_ntf_t                                test_periodic_tx_ntf;
        test_periodic_rx_cmd_t                                test_periodic_rx_cmd;
        test_periodic_rx_rsp_t                                test_periodic_rx_rsp;
        test_periodic_rx_ntf_t                                test_periodic_rx_ntf;
        test_rx_rsp_t                                         test_rx_rsp;
        test_rx_ntf_t                                         test_rx_ntf;
        test_loopback_cmd_t                                   test_loopback_cmd;
        test_loopback_rsp_t                                   test_loopback_rsp;
        test_loopback_ntf_t                                   test_loopback_ntf;
        test_ss_twr_cmd_t                                     test_ss_twr_cmd;
        test_ss_twr_rsp_t                                     test_ss_twr_rsp;
        test_ss_twr_ntf_t                                     test_ss_twr_ntf;
        test_stop_session_rsp_t                               test_stop_session_rsp;
        test_ds_twr_cmd_t                                     test_ds_twr_cmd;
        test_ds_twr_rsp_t                                     test_ds_twr_rsp;
        test_ds_twr_ntf_t                                     test_ds_twr_ntf;
        test_cal_cmd_t                                        test_calibration_cmd;
        test_cal_rsp_t                                        test_calibration_rsp;
    }msg_data;
}uci_test_msg_t;


typedef struct tx_power_diff
{
    uint8_t     ch;
    uint8_t     sign;//0:+ 1:-
    uint8_t     offset;//0.17dB steps 0:0dB,1:0.17dB,12:2dB(negattive max),18:3dB(positive max)
}tx_power_diff_t;

typedef struct freq_diff
{
    uint8_t     ch;
    uint8_t     sign;//0:+ 1:-
    uint16_t    offset;//0x00: 0ppm 0x0A00: 2560 = 256 ppm (max. supported frequency offset)
}freq_diff_t;

typedef struct antenna_diff
{
    uint8_t     ch;
    uint16_t    offset;//in 15.65ps resolution,0x00: 0ps(no delay),0xFFFF:1025638.4ps(max)
}antenna_diff_t;

typedef struct group_delay
{
    uint8_t     index;//groupdelay index
    uint8_t     NBIC_type;//0:NBIC disabled,1:NBIC enabled,2:NBIC enable with low frequency config
    uint32_t    delay;//group delay in 15.65ps 0x00:0ps,0xFFFFFFFF 67216238166.75 ps (max)
}group_delay_t;

typedef struct host_msg_state_table
{
    uci_control_msg_t              uci_control_msg;
    host_uci_control_msg_handler_t uci_control_msg_handler;
    uci_control_msg_t              next_uci_control_msg;
}host_msg_state_table_t;

typedef struct uwbs_msg_state_table
{
    uci_control_msg_t              uci_control_msg;
    uwbs_uci_control_msg_handler_t uci_control_msg_handler;
}uwbs_msg_state_table_t;


#pragma pack ()


typedef struct device_cfg
{
    uint8_t         low_power_mode;
    uint8_t         rx_en;
    uint8_t         tx_en;
    uint8_t         log_radar_en;
    uint8_t         log_rx_phy_en;
    uint8_t         log_tx_phy_en;
/*
    RX status and error bit 0
    TX status and error bit 1
    CIR log bit 2
    UWB session ID bit 3
    Block index bit 4
    RX timestamp bit 5
    TX timestamp bit 6
    RX PSDU bit 7
    TX PSDU bit 8
    STS index bit 9
    RX first path info bit 10
    RX carrier frequency offset bit 11
    MAC decoding status bit 12
    Reason of MAC decoding failure bit 13
    MAC frame compliance bit 14
    RX MAC header bit 15
    RX MAC payload bit 16
    Scheduler status bit 17
    Scheduler info bit 18
    RX PDoA result bit 19
    RFU bit 20
    Radar status bit 21
    Radar CIR data bit 22
*/
    uint32_t        log_para_conf;
    tx_power_diff_t power_diff[5];
    freq_diff_t     freq_diff[5];
    antenna_diff_t  ant_diff[5];
    group_delay_t   group_delay[8];
}device_cfg_t;

typedef struct test_cfg
{
    /*
    0x00 : Receive Mode
    0x01 : Transmit Mode
    0x02 : CW transmit Mode
    0x03 : Loopback mode
    0x06: SS-TWR mode
    */
    uint8_t         test_mode;
    /*
    Start delay in us.
    Range: [0x3E8 0xFFFF] (1000 us to 65535us)
    Default: 0x3E8 (1000us)
    Note: Applied for receive mode and transmit mode.
    */
    uint16_t        test_delay; 
    /*
    0x00 : SP0 type which has only PSDU without STS
    0x03 : SP3 type which has only STS
    */
    uint8_t         frame_type;
    uint8_t         psdu[128];
    uint8_t         psdu_len;
    /*
    Timeout value for Receive Mode in ms resolution 1 LSB = 1ms
    Timeout shall be equal at least 1ms.
    Default: 100ms
    Note: Applied for Receive Mode only
    */
    uint16_t        time_out;
    uint32_t        event_cout_max;
    /*
    Cycle time for periodic mode. Defined from Start of TX to Start of next TX. 1
    LSB = 1us.
    [1000us .. 10s] = [0x3E8us .. 0x989680us]
    Default: 1000us
    Note: Applied for Transmit Mode only
    */
    uint32_t        tx_cycle_time;
    uint8_t         crc_en;
    uint8_t         phr_range_bit;
}test_cfg_t;

typedef struct device_inst
{
    device_cfg_t      device_cfg;
    device_state_t    device_state;
    core_cap_para_t   core_capality;
    uint32_t          device_err_codes;
    uint8_t           session_num;
    session_inst_t    session_inst[MAX_SESSION_NUM];
    test_cfg_t        test_cfg;
}device_inst_t;

extern uint8_t g_uci_cmd_origin;


#endif
