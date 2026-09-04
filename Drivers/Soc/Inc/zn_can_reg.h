/*****************************************************************************
 *  File: zn_can_reg.h
 *
 *  Descirption: contains the functions support  can.
 *
 *  Copyright (C) : 2023 ultraception.com.
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-12
 *
 *****************************************************************************/

#ifndef __ZN_CAN_REG_H__
#define __ZN_CAN_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"


#define CAN_DATALEN_MAX (64)
#define CAN_BUF_LENGTH (CAN_DATALEN_MAX/4)                 /* CAN buffer length (64 Bytes), CAN 2.0A/B  only use 8 Bytes */

/* CAN receive buffer register define structure*/
typedef volatile struct
{
    uint32_t ID                     : 29;   /* Identifier */
    uint32_t                        : 2;    /* Reserved   */
    uint32_t ESI                    : 1;    /* Error State Indicator */
    uint32_t DLC                    : 4;    /* Data length code  */
    uint32_t BRS                    : 1;    /* Bit Rate Switch  */
    uint32_t FDF                    : 1;    /* FD Format indicator */
    uint32_t RTR                    : 1;    /* Remote transmission request */
    uint32_t IDE                    : 1;    /* Identifier extension */
    uint32_t                        : 4;    /* Reserved */
    uint32_t TX                     : 1;    /* Status bit TX in RBUF is set to 1 if the loop back mode (chap. 3.9.10.4) is activated and the core has received its own transmitted frame.*/ 
    uint32_t KOER                   : 3;    /* Status bit TX in RBUF */
    uint32_t CYCLE_TIME             : 16;   /* Cycle time for TTCAN */
    uint32_t Data[CAN_BUF_LENGTH];          /* Buffer data */
    uint32_t RTS[2];                        /* Receive time stamps */
} CAN_RBUF_TYPE;

/*CAN transmit buffer register define structure */
typedef volatile struct
{                                                                       
    uint32_t ID                  : 29;   /* Identifier                  */
    uint32_t                     : 2;    /* Reserved                    */
    uint32_t TTSEN               : 1;    /* Transmit Time-Stamp ENable  */
    uint32_t DLC                 : 4;    /* Data length code            */
    uint32_t BRS                 : 1;    /* Bit Rate Switch             */
    uint32_t FDF                 : 1;    /* FD Format indicator         */
    uint32_t RTR                 : 1;    /* Remote transmission request */
    uint32_t IDE                 : 1;    /* Identifier extension        */
    uint32_t                     : 24;   /* Reserved                    */
    uint32_t Data[CAN_BUF_LENGTH];       /* Buffer data                 */
    uint32_t TTS[2];                     /* Transmission Time Stamp     */
} CAN_TBUF_TYPE;                                                        

/* CAN register define structure */
typedef volatile struct
{                                              
    CAN_RBUF_TYPE        RBUF;                 /*  Receive buffer  */
    CAN_TBUF_TYPE        TBUF;                 /*  Transmit buffer */
    union {
        struct {
            uint32_t CFG_STAT    : 8;       /* Configuration and Status Register               */
            uint32_t TCMD        : 8;       /* Command Register                                */
            uint32_t TCTRL       : 8;       /* Transmit Control Register                       */
            uint32_t RCTRL       : 8;       /* Receive Control Register                        */
            uint32_t RTIE        : 8;       /* Receive and Transmit Interrupt Enable Register  */
            uint32_t RTIF        : 8;       /* Receive and Transmit Interrupt Flag Register    */
            uint32_t ERRINT      : 8;       /* Error Interrupt Enable and Flag Register        */
            uint32_t LIMIT       : 8;       /* Warning Limits Register                         */
            uint32_t S_Seg_1     : 8;       /* Bit Timing Register 1                           */
            uint32_t S_Seg_2     : 8;       /* Bit Timing Register 2                           */
            uint32_t S_SJW       : 8;       /* Synchronization Jump Width                      */
            uint32_t S_PRESC     : 8;       /* Prescaler                                       */
            uint32_t F_Seg_1     : 8;       /* Bit Timing Register 1 (fast spee)               */
            uint32_t F_Seg_2     : 8;       /* Bit Timing Register 2 (fast spee)               */
            uint32_t F_SJW       : 8;       /* Synchronization Jump Width (fast spee)          */
            uint32_t F_PRESC     : 8;       /* Prescaler(fast spee)                            */
            uint32_t EALCAP      : 8;       /* Error and Arbitration Lost Capture Register     */
            uint32_t TDC         : 8;       /* Transmitter Delay Compensation Register TDC     */
            uint32_t RECNT       : 8;       /* Receive Error Count                             */
            uint32_t TECNT       : 8;       /* Transmit Error Count                            */
            uint32_t ACFCTRL     : 8;       /* Acceptance Filter Control Register              */
            uint32_t TIMECFG     : 8;       /* CiA 603 Time-Stamping                           */
            uint32_t ACF_EN_0    : 8;       /* Acceptance Filter Enable                        */
            uint32_t ACF_EN_1    : 8;       /* Acceptance Filter Enable                        */
            uint32_t ACF_0       : 8;       /* Acceptance CODE Register                        */
            uint32_t ACF_1       : 8;       /* Acceptance CODE Register                        */
            uint32_t ACF_2       : 8;       /* Acceptance CODE Register                        */
            uint32_t ACF_3       : 8;       /* Acceptance CODE Register                        */
            uint32_t VER_0       : 8;       /* Version                                         */
            uint32_t VER_1       : 8;       /* Version                                         */
            uint32_t TBSLOT      : 8;       /* TB Slot Pointer                                 */
            uint32_t TTCFG       : 8;       /* Time Trigger Configuration                      */
            uint32_t REF_MSG_0   : 8;       /* Reference message                               */
            uint32_t REF_MSG_1   : 8;       /* Reference message                               */
            uint32_t REF_MSG_2   : 8;       /* Reference message                               */
            uint32_t REF_MSG_3   : 8;       /* Reference message                               */
            uint32_t TRIG_CFG    : 32;      /* trigger configuration                           */
            //uint32_t TRIG_CFG_0  : 8;       // Trigger Configuration
            //uint32_t TRIG_CFG_1  : 8;       // Trigger Configuration
            //uint32_t TT_TRIG_0   : 8;       // Trigger Time
            //uint32_t TT_TRIG_1   : 8;       // Trigger Time
            uint32_t TT_WTRIG_0  : 8;       /* Watch Trigger Time                              */
            uint32_t TT_WTRIG_1  : 8;       /* Watch Trigger Time                              */
            uint32_t             : 16;      /* Reserved                                        */
        } REG;
        struct {
            //CAN_CFG_STAT_TYPE    CFG_STAT;    //(CAN_BASE + 0xa0)
            uint32_t BUSOFF      : 1;       /* Bus off status                                  */
            uint32_t TACTIVE     : 1;       /* Transmission active status                      */
            uint32_t RACTIVE     : 1;       /* Reception active status                         */
            uint32_t TSSS        : 1;       /* Transmit STB - single shot mode                 */
            uint32_t TPSS        : 1;       /* Transmit PTB - single shot mode                 */
            uint32_t LBMI        : 1;       /* Loop-back mode: internal                        */
            uint32_t LBME        : 1;       /* Loop-back mode: external                        */
            uint32_t RESET       : 1;       /* Software reset                                  */

            //CAN_TCMD_TYPE        TCMD;        //(CAN_BASE + 0xa1)
            uint32_t TSA         : 1;       /* Transmit secondary abort                       */
            uint32_t TSALL       : 1;       /* Transmit secondary enable - all messages       */
            uint32_t TSONE       : 1;       /* Transmit secondary enable - one message        */
            uint32_t TPA         : 1;       /* Transmit primary abort                         */
            uint32_t TPE         : 1;       /* Transmit primary enable                        */
            uint32_t STBY        : 1;       /* Transceiver standby mode                       */
            uint32_t LOM         : 1;       /* Listen-only mode                               */
            uint32_t TBSEL       : 1;       /* Transmit buffer selector (0 for PTB, 1 for STB)*/

            //CAN_TCTRL_TYPE       TCTRL;       //(CAN_BASE + 0xa2)
            uint32_t TSSTAT      : 2;       /* Transmit secondary status                                               */
            uint32_t             : 2;       /* Reserved                                                                */
            uint32_t TTTBM       : 1;       /* TTCAN Transmit Buffer Mode                                              */
            uint32_t TSMODE      : 1;       /* Transmit secondary: operation mode (FIFO (0) or priority decision (1))  */
            uint32_t TSNEXT      : 1;       /* Transmit secondary: next message slot                                   */
            uint32_t FD_ISO      : 1;       /* CAN FD ISO mode                                                         */

            //CAN_RCTRL_TYPE       RCTRL;       //(CAN_BASE + 0xa3)
            uint32_t RSTAT       : 2;       /* Receiver status                        */
            uint32_t             : 1;       /* Reserved                               */
            uint32_t RBALL       : 1;       /* Receive Buffer stores ALL data frames  */
            uint32_t RREL        : 1;       /* Reception buffer message slot release  */
            uint32_t ROV         : 1;       /* Reception buffer overflow              */
            uint32_t ROM         : 1;       /* Reception buffer overflow mode         */
            uint32_t SACK        : 1;       /* Self-ACKnowledge                       */

            //CAN_RTIE_TYPE        RTIE;        //(CAN_BASE + 0xa4)
            uint32_t TSFF        : 1;       /* Transmit seconadary full flag                  */                
            uint32_t EIE         : 1;       /* Error interrupt enable                         */
            uint32_t TSIE        : 1;       /* Transmit secondary interrupt enable            */
            uint32_t TPIE        : 1;       /* Transmit primary interrupt enable              */
            uint32_t RAFIE       : 1;       /* Receive buffer almost full interrupt enable    */
            uint32_t RFIE        : 1;       /* Receive buffer full interrupt enable           */
            uint32_t ROIE        : 1;       /* Receive buffer overflow interrupt enable       */
            uint32_t RIE         : 1;       /* Receive buffer interrupt enable                */

            //CAN_RTIF_TYPE        RTIF;        //(CAN_BASE + 0xa5)
            uint32_t AIF         : 1;       /* Abort interrupt flag                           */
            uint32_t EIF         : 1;       /* Error interrupt flag                           */
            uint32_t TSIF        : 1;       /* Transmit secondary interrupt flag              */
            uint32_t TPIF        : 1;       /* Transmit primary interrupt flag                */
            uint32_t RAFIF       : 1;       /* Receive buffer almost full interrupt flag      */
            uint32_t RFIF        : 1;       /* Receive buffer full interrupt flag             */
            uint32_t ROIF        : 1;       /* Receive buffer overflow interrupt flag         */
            uint32_t RIF         : 1;       /* Receive buffer interrupt flag                  */

            //CAN_ERRINT_TYPE      ERRINT;      //(CAN_BASE + 0xa6)
            uint32_t BEIF        : 1;       /* Bus error interrupt flag                      */
            uint32_t BEIE        : 1;       /* Bus error interrupt enable                    */
            uint32_t ALIF        : 1;       /* Arbitration lost interrupt flag               */
            uint32_t ALIE        : 1;       /* Arbitration lost interrupt enable             */
            uint32_t EPIF        : 1;       /* Error passive interrupt flag                  */
            uint32_t EPIE        : 1;       /* Error passive interrupt enable                */
            uint32_t EPASS       : 1;       /* Error passive mode                            */
            uint32_t EWARN       : 1;       /* Error warning limit reached                   */

            //CAN_LIMIT_TYPE       LIMIT;       //(CAN_BASE + 0xa7)
            uint32_t EWL         : 4;       /* Error warning limit                           */
            uint32_t AFWL        : 4;       /* Almost full warning limit                     */

            //CAN_S_CONFIG_TYPE    BIT_CONFIG;  //(CAN_BASE + 0xa8)
            uint32_t S_SEG_1     : 8;       /* Bit Timing Segment 1                         */
            uint32_t S_SEG_2     : 7;       /* Bit Timing Segment 2                         */
            uint32_t             : 1;       /* Reserved                                     */
            uint32_t S_SJW       : 7;       /* Synchronization Jump Width                   */
            uint32_t             : 1;       /* Reserved                                     */
            uint32_t S_PRESC     : 8;       /* Prescaler                                    */

            //CAN_F_CONFIG_TYPE    BIT_CONFIG;  //(CAN_BASE + 0xac)
            uint32_t F_SEG_1     : 5;      /* F_Seg_1  (CAN_BASE + 0xac)                   */
            uint32_t             : 3;      /* Reserved                                     */
            uint32_t F_SEG_2     : 4;      /* F_Seg_2                                      */
            uint32_t             : 4;      /* Reserved                                     */
            uint32_t F_SJW       : 4;      /* Synchronization Jump Width (fast speed)      */
            uint32_t             : 4;      /* Reserved                                     */
            uint32_t F_PRESC     : 8;      /* Prescaler (fast speed)                       */
                
            //CAN_EALCAP_TYPE      EALCAP;      //(CAN_BASE + 0xb0)
            uint32_t ALC         : 5;       /* Arbitration lost capture                    */
            uint32_t KOER        : 3;       /* Kind of error                               */

            //Transmitter Delay Compensation Register TDC (CAN_BASE + 0xb1)
            uint32_t SSPOFF      : 7;       /* Secondary Sample Point OFFset                */
            uint32_t TDCEN       : 1;       /* Transmitter Delay Compensation ENable        */

            //CAN_ERROR_COUNT_TYPE  ECNT;       //(CAN_BASE + 0xb2)
            uint32_t RECNT       : 8;       /* Receive Error Count                          */
            uint32_t TECNT       : 8;       /* Transmit Error Count                         */

            //CAN_ACFCTRL_TYPE     ACFCTRL;     //(CAN_BASE + 0xb4)
            uint32_t ACFADR      : 4;       /* Acceptance filter address                   */
            uint32_t             : 1;       /* Reserved                                    */
            uint32_t SELMASK     : 1;       /* Select acceptance mask (1) or code (0)      */
            uint32_t             : 2;       /* Reserved                                    */
            uint32_t TIMEEN      : 1;       /* TIME-stamping ENable,0-disabled,1-enable    */
            uint32_t TIMEPOS     : 1;       /* TIME-stamping POSition,0-SOF,1-EOF          */
            uint32_t             : 6;       /* Reserved                                    */
            uint32_t ACF_EN      : 16;      /* Acceptance filter enable                    */

            //CAN_ACF_CONFIG_TYPE  ACF;         //(CAN_BASE + 0xb8)
            uint32_t ACF         : 31;      /* Filter data (code or mask) + AIDE + AIDEE   */
            //uint32_t ACF       : 29;      /* Filter data (code or mask) 29 bit           */
            //uint32_t AIDE      : 1;       /* Acceptance mask IDE bit value               */
            //uint32_t AIDEE     : 1;       /* Acceptance mask IDE bit check enable        */
            uint32_t             : 1;       /* Reserved                                    */

            //CAN_VER_TYPE         VER;         //(CAN_BASE + 0xbc)
            uint32_t VERSION     : 16;      /* CAN version                                 */

            //CAN_TBSLOT_TYPE      TBSLOT;      //(CAN_BASE + 0xbe)
            uint32_t TBPTR       : 6;       /* TB slot pointer                             */
            uint32_t TBF         : 1;       /* Set TB slot to "filled"                     */
            uint32_t TBE         : 1;       /* Set TB slot to "empty"                      */

            //CAN_TTCFG_TYPE       TTCFG;       //(CAN_BASE + 0xbf)
            uint32_t TTEN        : 1;       /* TTCAN: enable                              */
            uint32_t T_PRESC     : 2;       /* TTCAN: timer prescaler                     */
            uint32_t TTIF        : 1;       /* TTCAN: time trigger interrupt flag         */
            uint32_t TTIE        : 1;       /* TTCAN: time trigger interrupt enable       */
            uint32_t TEIF        : 1;       /* TTCAN: trigger error interrupt flag        */
            uint32_t WTIF        : 1;       /* TTCAN: watch trigger interrupt flag        */
            uint32_t WTIE        : 1;       /* TTCAN: watch trigger interrupt enable      */

            //CAN_REF_MSG_TYPE     REF_MSG;     //(CAN_BASE + 0xc0)
            uint32_t REF_MSG     : 32;      /* TTCAN: Reference message                   */
            //uint32_t REF_ID    : 29;      /* TTCAN: Reference message IDentifier        */
            //uint32_t           : 2;       /* Reserved                                   */
            //uint32_t REF_IDE   : 1;       /* TTCAN: Reference message IDE bit           */

            //CAN_TRIG_CFG_TYPE    TRIG_CFG;    //(CAN_BASE + 0xc4)
            uint32_t TTPTR       : 6;       /* TTCAN: trigger pointer to TB slot          */
            uint32_t             : 2;       /* Reserved                                   */
            uint32_t TTYPE       : 3;       /* TTCAN: Trigger Type                        */
            uint32_t             : 1;       /* Reserved                                   */
            uint32_t TEW         : 4;       /* TTCAN: Transmit Enable Window              */

            //CAN_TT_TRIG_TYPE     TT_TRIG;     //(CAN_BASE + 0xc6)
            uint32_t TT_TRIG     : 16;      /* TTCAN: Trigger Time                        */

            //CAN_TT_WTRIG_TYPE    TT_WTRIG;    //(CAN_BASE + 0xc8)
            uint32_t TT_WTRIG    : 16;      /* TTCAN: Watch Trigger Time                  */
            uint32_t             : 16;      /* Reserved                                   */
        } BIT;
    };
} ZN_CanType;

/*Configuration and Status Register CFG_STAT.Description of each bit value */
enum {                                                                             
    BUSOFF                           = 0x01,    /* bus off status                  */
    TACTIVE                          = 0x02,    /* transmission active status      */
    RACTIVE                          = 0x04,    /* reception active status         */
    TSSS                             = 0x08,    /* transmit STB - single shot mode */
    TPSS                             = 0x10,    /* transmit PTB - single shot mode */
    LBMI                             = 0x20,    /* loop-back mode: internal        */
    LBME                             = 0x40,    /* loop-back mode: external        */
    RESET                            = 0x80,    /* software reset                  */
};

/* Command Register TCMD.Description of each bit value*/
enum {
    TSA                              = 0x01,    /* transmit secondary abort                        */
    TSALL                            = 0x02,    /* transmit secondary enable - all messages        */
    TSONE                            = 0x04,    /* transmit secondary enable - one message         */
    TPA                              = 0x08,    /* transmit primary abort                          */
    TPE                              = 0x10,    /* transmit primary enable                         */
    STBY                             = 0x20,    /* transceiver standby mode                        */
    LOM                              = 0x40,    /* listen-only mode                                */
    TBSEL                            = 0x80,    /* transmit buffer selector (0 for PTB, 1 for STB) */
};

/*Transmit Control Register TCTRL. Description of some bit value*/
enum {                                                                                                                      
    TTTBM                            = 0x10,    /* TTCAN Transmit Buffer Mode                                               */
    TSMODE                           = 0x20,    /* transmit secondary: operation mode (FIFO (0) or priority decision (1))   */
    TSNEXT                           = 0x40,    /* transmit secondary: next message slot                                    */
};

/*Receive Control Register RCTRL. Description of some bit value*/
enum {
    RREL                             = 0x10,    /* reception buffer message slot release   */
    ROV                              = 0x20,    /* reception buffer overflow               */
    ROM                              = 0x40,    /* reception buffer overflow mode          */
};

/*Receive and Transmit Interrupt Enable Register RTIE(0xa4).Description of each bit value*/
enum {
    TSFF                             = 0x01,    /* transmit seconadary full flag               */
    EIE                              = 0x02,    /* error interrupt enable                      */
    TSIE                             = 0x04,    /* transmit secondary interrupt enable         */
    TPIE                             = 0x08,    /* transmit primary interrupt enable           */
    RAFIE                            = 0x10,    /* receive buffer almost full interrupt enable */
    RFIE                             = 0x20,    /* receive buffer full interrupt enable        */
    ROIE                             = 0x40,    /* receive buffer overflow interrupt enable    */
    RIE                              = 0x80,    /* receive buffer interrupt enable             */
};

/* Receive and Transmit Interrupt Flag Register RTIF(0xa5). Description of each bit value*/
enum {
    AIF                              = 0x01,    /* abort interrupt flag                        */
    EIF                              = 0x02,    /* error interrupt flag                        */
    TSIF                             = 0x04,    /* transmit secondary interrupt flag           */
    TPIF                             = 0x08,    /* transmit primary interrupt flag             */
    RAFIF                            = 0x10,    /* receive buffer almost full interrupt flag   */
    RFIF                             = 0x20,    /* receive buffer full interrupt flag          */
    ROIF                             = 0x40,    /* receive buffer overflow interrupt flag      */
    RIF                              = 0x80,    /* receive buffer interrupt flag               */
};

/* ERRor INTerrupt Enable and Flag Register ERRINT(0xa6).Description of each bit value*/
enum {
    BEIF                             = 0x01,    /* bus error interrupt flag           */
    BEIE                             = 0x02,    /* bus error interrupt enable         */
    ALIF                             = 0x04,    /* arbitration lost interrupt flag    */
    ALIE                             = 0x08,    /* arbitration lost interrupt enable  */
    EPIF                             = 0x10,    /* error passive interrupt flag       */
    EPIE                             = 0x20,    /* error passive interrupt enable     */
    EPASS                            = 0x40,    /* error passive mode                 */
    EWARN                            = 0x80,    /* error warning limit reached        */
};

enum {
    NOERROR                          = 0x00,    /* no error flag              */
    BIT_ERROR                        = 0x01,    /* bit error flag             */
    FORM_ERROR                       = 0x02,    /* form error flag            */
    STUFF_ERROR                      = 0x03,    /* stuff error flag           */
    ACK_ERROR                        = 0x04,    /* acknowledgement error flag */
    CRC_ERROR                        = 0x05,    /* crc error flag             */
    OTHER_ERROR                      = 0x06,    /* other error flag(dominant bits after own error flag, received active Error Flag too long,
                                                dominant bit during Passive-Error-Flag after ACK error) */
};

enum {
    SELMASK                          = 0x20,    /* select acceptance mask (1) or code (0) */
};                                              

enum {                                          
    TTEN                             = 0x01,    /* TTCAN: enable                         */
    TTIF                             = 0x08,    /* TTCAN: time trigger interrupt flag    */
    TTIE                             = 0x10,    /* TTCAN: time trigger interrupt enable  */
    TEIF                             = 0x20,    /* TTCAN: trigger error interrupt flag   */
    WTIF                             = 0x40,    /* TTCAN: watch trigger interrupt flag   */
    WTIE                             = 0x80,    /* TTCAN: watch trigger interrupt enable */
};

typedef enum
{
    TRANSMIT_PRIMARY = 0,          /* Transmit promary mode                               */
    TRANSMIT_SECONDARY,            /* Transmit secondary mode                             */
} TRANSMIT_TYPE;



#define CAN0_BASE        (CAN_BASE_ADDR)                     /* CAN0 module base address                  */
#define CAN0             ((ZN_CanType *) (CAN0_BASE))         /* CAN0 address                              */


#define CAN_RECEIVE_FIFO_COUNT       31          			 /* CAN receive fifo count                    */
#define CAN_TRANSMIT_FIFO_COUNT      32          			 /* CAN transmit fifo count (1 PTB + 31 STB)   */
#define CAN_ERROR_WARNING_LIMIT      0xB        			 /* Error Warning Limit = (EWL+1)*8           */
#define CAN_MAX_FILTER_NUM           16          			 /* CAN max filter number                     */


/**
 * can_reset
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  reset: 1 to reset CAN module, 0 to release reset
 * @return     none
 *
 * @brief      This function resets (if reset is 1) or releases reset (if reset is 0) for the provided CAN interface.
 */
__STATIC_INLINE void can_reset(ZN_CanType *CANx, uint8_t reset)
{
    CANx->BIT.RESET = reset;
}


/**
 * can_is_msg_in_rxbuff
 *
 * @param[in]  CANx: CAN Type pointer
 * @return     int32_t: receive buffer status as defined in the function
 *
 * @brief      This function returns the receive buffer status of the provided CAN interface as defined in the function.
 */
__STATIC_INLINE int32_t can_is_msg_in_rxbuff(ZN_CanType *CANx)
{
    /*Receive buffer STATus 
    00 - empty
    01 - > empty and < almost full (AFWL)
    10 -  almost full (programmable threshold by AFWL) but not full and no overflow
    11 - full (stays set in case of overflow – for overflow signaling see ROV)
    */
    return CANx->BIT.RSTAT;
}

/**
 * can_set_int_enable
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  intEn: 1 to enable Rx/Tx interrupt, 0 to disable
 * @param[in]  errIntEn: 1 to enable error interrupt, 0 to disable
 * @return     none
 *
 * @brief      This function enables or disables Rx/Tx interrupt and error interrupt for the provided CAN interface.
 */
__STATIC_INLINE void can_set_int_enable(ZN_CanType *CANx, uint8_t intEn, uint8_t errIntEn)
{
    CANx->REG.RTIE = intEn;
    CANx->REG.ERRINT = errIntEn;
}

/**
 * can_set_ewl
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  ewl: error warning limit value (0-15)
 * @return     none
 *
 * @brief      This function sets the error warning limit (EWL) for the provided CAN interface. EWL is the threshold
 *             for generating the error warning interrupt.
 */
__STATIC_INLINE void can_set_ewl(ZN_CanType *CANx, uint8_t ewl)
{
    CANx->BIT.EWL = ewl & 0xF;
}


/**
 * can_get_tts0
 *
 * @param[in]  CANx: CAN Type pointer
 * @return     uint32_t: Time Stamp of Transmission Request for Tx Mail Box 0
 *
 * @brief      This function returns the time stamp of transmission request for Tx Mail Box 0 of the provided CAN interface.
 */
__STATIC_INLINE uint32_t can_get_tts0(ZN_CanType *CANx)
{
    return (CANx->TBUF.TTS[0]);
}

/**
 * can_get_tts1
 *
 * @param[in]  CANx: CAN Type pointer
 * @return     uint32_t: Time Stamp of Transmission Request for Tx Mail Box 1
 *
 * @brief      This function returns the time stamp of transmission request for Tx Mail Box 1 of the provided CAN interface.
 */
__STATIC_INLINE uint32_t can_get_tts1(ZN_CanType *CANx)
{
    return (CANx->TBUF.TTS[1]);
}

#ifdef __cplusplus
}
#endif

#endif