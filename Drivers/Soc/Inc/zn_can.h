/*****************************************************************************
 *  File: zn_can.h
 *
 *  Descirption: this file contains the functions support spi operations.
 *
 *  Copyright (C) : 2022 ultraception.com
 *
 *  Author: WangJiying
 *  Mail:   
 *  Date:   2022-5-6
 *
 *****************************************************************************/
#ifndef __ZN_CAN_H__
#define __ZN_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_can_reg.h"

/* Baudrate = CAN_CLOCK / (S_PRESC + 1) / (1 + (S_SEG_1 + 1) + (S_SEG_2 + 1))  */
typedef struct
{
    uint8_t S_PRESC;               /* Prescaler                                                       */
    uint8_t S_SEG_1;               /* Bit Timing Segment 1                                            */
    uint8_t S_SEG_2;               /* Bit Timing Segment 2                                            */
    uint8_t S_SJW;                 /* Synchronization Jump Width: SJW = SEG_2 / 2 ~ SEG_2 * 2 / 3     */
} CAN_BaudrateConfig;


/* FD_Baudrate = CAN_CLOCK / (S_PRESC + 1) / (1 + (S_SEG_1 + 1) + (S_SEG_2 + 1))     */
/* FD_DataBaudrate = CAN_CLOCK / (F_PRESC + 1) / (1 + (F_SEG_1 + 1) + (F_SEG_2 + 1)) */
typedef struct
{
    uint8_t F_PRESC;               /* Prescaler                                                      */
    uint8_t F_SEG_1;               /* Bit Timing Segment 1                                           */
    uint8_t F_SEG_2;               /* Bit Timing Segment 2                                           */
    uint8_t F_SJW;                 /* Synchronization Jump Width: SJW = SEG_2 / 2 ~ SEG_2 * 2 / 3    */
} CAN_FDBaudrateConfig;

typedef struct
{
    uint8_t index;                 /* Filter index                                                  */
    uint8_t enable;                /* Enable or disable                                             */
    uint32_t code;                 /* Code data                                                     */
    uint32_t mask;                 /*< Mask data . The register corresponding to mask ,bit0-bit30,  
                                       bit 30:Acceptance mask IDE bit check enable
                                        1 -  acceptance filter accepts either standard or extended as defined by AIDE
                                        0 -  acceptance filter accepts both standard or extended frames
                                        Only filter 0 is affected by the power-on reset. All other filters stay uninitialized.
                                       bit 29 Acceptance mask IDE bit value
                                        If AIDEE=1 then:
                                        1 -  acceptance filter accepts only extended frames
                                        0 -  acceptance filter accepts only standard frames
                                        Only filter 0 is affected by the power-on reset. All other filters stay uninitialized.
                                       other bit
                                       1 -  acceptance check for these bits of receive identifier disabled
                                       0 -  acceptance check for these bits of receive identifier enable
                                    */
} CAN_FilterControl;


typedef struct _CAN_MSG_INFO
{
    uint32_t    ID;                           /*!< CAN identifier                                      */
    uint8_t     ESI;                          /*!< Transmit time-stamp enable or error state indicator */
    uint8_t     DLC;                          /*!< Data length code                                    */
    uint8_t     BRS;                          /*!< Bit rate switch                                     */
    uint8_t     FDF;                          /*!< FD format indicator                                 */
    uint8_t     RTR;                          /*!< Remote transmission request                         */
    uint8_t     IDE;                          /*!< Identifier extension                                */
    uint32_t    Data[CAN_BUF_LENGTH];         /*!< Data                                                */
    uint32_t    RTS[2];                       /*!< Receive time stamps                                 */ 
} CAN_MSG_INFO;


typedef struct
{
    uint32_t           TPSS : 1;               /* Single Shot mode for primary mode      */
    uint32_t           TSSS : 1;               /* Single Shot mode for secondary mode    */
    uint32_t           autoReset: 1;           /* Auto reset after bus off to active     */
    uint8_t            interruptEnable;        /* CAN interrupt enable                   */
    uint16_t           errorFlag;              /* CAN error flag                         */
    DeviceCallback_Type callbackFunc;          /* CAN event callback function            */
} CAN_Device;

typedef struct
{
    uint32_t canMode: 3;                      /*  CAN mode                                          */
    uint32_t clockSrc: 1;                     /*  CAN clock source                                  */
    uint32_t interruptEnable: 1;              /*  Interrupt enable                                  */
    uint32_t autoReset: 1;                    /*  Auto reset after bus off to active                */
    uint32_t TPSS: 1;                         /*  Transmission Primary Single Shot mode for PTB     */
    uint32_t TSSS: 1;                         /*  Transmission Secondary Single Shot Mode for STP   */
    uint32_t TSMODE: 1;                       /*  Transmit buffer Secondary operation MODE          */
    uint32_t ROM: 1;                          /*  Receive buffer Overflow Mode                      */
    uint32_t TIMEEN: 1;                       /* Time stamp enable ,0-disabled ,1-enabled           */
    uint32_t TIMEPOS: 1;                      /* TIME-stamping POSition,0-SOF,1-SOF                 */
    uint32_t fdModeEn:1;                      /* FD enable                                          */
    uint32_t fdIsoEn:1;                       /* FD ISO mode                                        */
    uint32_t tdcEnable:1;                     /* TDC enable (when data bitrate >= 1Mbps)            */
    uint32_t sspOffset:7;                     /* SSP offset                                         */
    uint32_t filterEn:1;                      /* 0-disable fiter function, 1-enale filter function  */
    uint8_t filter_num;                       /* Filter controller number                           */
    CAN_FilterControl *filterList;            /* Filter controller list                             */
    DeviceCallback_Type callbackFunc;          /* CAN event callback function                       */
} CAN_Config;                                 

typedef enum
{
    CAN_EVENT_WATCHTRIGGER = 1 << 22,         /*  Watch trigger interrupt flag                      */
    CAN_EVENT_TRIGGERERROR = 1 << 21,         /*  Trigger error interrupt flag                      */
    CAN_EVENT_TIMETRIGGER = 1 << 19,          /*  Time trigger interrupt flag                       */
    CAN_EVENT_ERRORWARNING = 1 << 15,         /*  Error warning interrupt flag                      */
    CAN_EVENT_ERRORPASSIVEACTIVE = 1 << 14,   /*  Error passive acitve interrupt flag               */
    CAN_EVENT_ERRORPASSIVE = 1 << 12,         /*  Error passive interrupt flag                      */
    CAN_EVENT_ARBITLOST = 1 << 10,            /*  Arbitration lost interrupt flag                   */
    CAN_EVENT_BUSERROR = 1 << 8,              /*  Bus error interrupt flag                          */
    CAN_EVENT_RECVMSG = 1 << 7,               /*  Receive message interrupt flag                    */
    CAN_EVENT_RECVBUFOVERRUN = 1 << 6,        /*  Buffer overrun interrupt flag                     */
    CAN_EVENT_RECVBUFFULL = 1 << 5,           /*  Receive buffer full interrupt flag                */
    CAN_EVENT_RECVBUFALMOSTFULL = 1 << 4,     /*  Receive buffer almost full interrupt flag         */
    CAN_EVENT_TRANSPRIMDONE = 1 << 3,         /*  Transmission primary done interrupt flag          */
    CAN_EVENT_TRANSSECDONE = 1 << 2,          /*  Transmission secondary done interrupt flag        */
    CAN_EVENT_ERROR = 1 << 1,                 /*  Error interrupt flag                              */
    CAN_EVENT_ABORT = 1 << 0,                 /*  Abort interrupt flag                              */
} CAN_EventFlag;

typedef enum
{
    CAN_MODE_INITIALIZATION,                     /* Initialization mode       */
    CAN_MODE_NORMAL,                             /* Normal mode               */
    CAN_MODE_RESTRICTED,                         /* Restricted mode           */
    CAN_MODE_MONITOR,                            /* Listen only mode          */
    CAN_MODE_LOOPBACK_INTERNAL,                  /* Loopback internal mode    */
    CAN_MODE_LOOPBACK_EXTERNAL                   /* Loopback external mode    */
} CAN_MODE;                                      
typedef enum
{
    CAN_DLC_12_BYTES = 9UL,
    CAN_DLC_16_BYTES,
    CAN_DLC_20_BYTES,
    CAN_DLC_24_BYTES,
    CAN_DLC_32_BYTES,
    CAN_DLC_48_BYTES,
    CAN_DLC_64_BYTES,
} CAN_DlcType;

/* =======================================================  TBUF/RBUF  ======================================================= */
#define CAN_INFO_ID_POS                    (0UL)                     /*!< IDE (Bit 0)                                           */
#define CAN_INFO_ID_MASK                   (0x1FFFFFFFUL)            /*!< IDE (Bitfield-Mask: 0x1FFFFFFF)                       */
#define CAN_INFO_TTSEN_POS                 (31UL)                    /*!< IDE (Bit 31)                                          */
#define CAN_INFO_TTSEN_MASK                (0x80000000UL)            /*!< IDE (Bitfield-Mask: 0x01)                             */
#define CAN_INFO_DLC_POS                   (0UL)                     /*!< IDE (Bit 0)                                           */
#define CAN_INFO_DLC_MASK                  (0x0FUL)                  /*!< IDE (Bitfield-Mask: 0x0F)                             */
#define CAN_INFO_BRS_POS                   (4UL)                     /*!< IDE (Bit 4)                                           */
#define CAN_INFO_BRS_MASK                  (0x10UL)                  /*!< IDE (Bitfield-Mask: 0x01)                             */
#define CAN_INFO_FDF_POS                   (5UL)                     /*!< IDE (Bit 5)                                           */
#define CAN_INFO_FDF_MASK                  (0x20UL)                  /*!< IDE (Bitfield-Mask: 0x01)                             */
#define CAN_INFO_RTR_POS                   (6UL)                     /*!< IDE (Bit 6)                                           */
#define CAN_INFO_RTR_MASK                  (0x40UL)                  /*!< IDE (Bitfield-Mask: 0x01)                             */
#define CAN_INFO_IDE_POS                   (7UL)                     /*!< IDE (Bit 7)                                           */
#define CAN_INFO_IDE_MASK                  (0x80UL)                  /*!< IDE (Bitfield-Mask: 0x01)                             */



uint8_t can_fd_dlc2len(uint8_t dlc);
uint8_t can_fd_len2dlc(uint8_t len);                                                                    
int32_t can_standby(ZN_CanType *CANx, uint8_t enable);
uint8_t can_get_payload_size(uint8_t dlcValue);
int32_t can_start_transmission(ZN_CanType *CANx, TRANSMIT_TYPE type, uint8_t mode);
void can_abort_transmission(ZN_CanType *CANx, TRANSMIT_TYPE type);
int32_t can_is_transmit_busy(ZN_CanType *CANx, TRANSMIT_TYPE type);
int32_t can_is_transmit_idle(ZN_CanType *CANx, TRANSMIT_TYPE type);
int32_t can_msg_read(ZN_CanType *CANx, CAN_MSG_INFO *info);
void can_set_msg_info(ZN_CanType *CANx, const CAN_MSG_INFO *info, TRANSMIT_TYPE type);
int32_t can_wait_transmission_idle(ZN_CanType *CANx, TRANSMIT_TYPE type);
int32_t can_msg_send(ZN_CanType *CANx, const CAN_MSG_INFO *info, TRANSMIT_TYPE type);
int32_t can_init(ZN_CanType *CANx, CAN_Config *config, const CAN_BaudrateConfig *baudrate);
int32_t canfd_init(ZN_CanType *CANx, CAN_Config *config, const CAN_BaudrateConfig *baudrate, const CAN_FDBaudrateConfig *databaudrate);



#ifdef __cplusplus
}
#endif

#endif