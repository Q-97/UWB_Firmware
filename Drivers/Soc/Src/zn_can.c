/*****************************************************************************
 *  File: zn_can.c
 *
 *  Descirption: this file contains the functions support can operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-5-6
 *
 *****************************************************************************/

#include "zn_can.h"

static const uint8_t s_dlc2len[] = {0, 1, 2, 3, 4, 5, 6, 7, 
                                  8, 12, 16, 20, 24, 32, 48, 64};

static const uint8_t s_len2dlc[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,        /* 0 - 8 */
                                  9, 9, 9, 9,                        /* 9 - 12 */
                                  10, 10, 10, 10,                    /* 13 - 16 */
                                  11, 11, 11, 11,                    /* 17 - 20 */
                                  12, 12, 12, 12,                    /* 21 - 24 */ 
                                  13, 13, 13, 13, 13, 13, 13, 13,    /* 25 - 32 */      
                                  14, 14, 14, 14, 14, 14, 14, 14,    /* 33 - 40 */    
                                  14, 14, 14, 14, 14, 14, 14, 14,    /* 41 - 48 */
                                  15, 15, 15, 15, 15, 15, 15, 15,    /* 49 - 56 */
                                  15, 15, 15, 15, 15, 15, 15, 15};    /* 57 - 64 */

static CAN_Device s_canDevice = {0};

#define MAX_CAN_WAIT_TIMES 100000      // default wait times, or user define


/**
 * can_fd_dlc2len
 *
 * @param[in]  dlc: Data Length Code(Number of payload bytes)
 * @return     uint8_t: corresponding length of CAN FD frame data
 *
 * @brief      This function maps the provided Data Length Code (DLC) to the corresponding
 *             length of a CAN FD frame data.
 */
uint8_t can_fd_dlc2len(uint8_t dlc)
{
    return s_dlc2len[dlc & 0x0F];
}


/**
 * can_fd_len2dlc
 *
 * @param[in]  len: length of CAN FD frame data
 * @return     uint8_t: corresponding Data Length Code (DLC)
 *
 * @brief      This function maps the provided length of a CAN FD frame data to the corresponding
 *             Data Length Code (DLC).
 */
uint8_t can_fd_len2dlc(uint8_t len)
{
    if (len > 64)
    {
        return 0xF;
    }
    return s_len2dlc[len];
}

/**
 * can_standby
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  enable: 1 to enable CAN standby mode, 0 to disable
 * @return     int32_t: 0 if success, 1 if there is any transmission and cannot enter standby mode
 *
 * @brief      This function enables or disables CAN standby mode for the provided CAN interface.
 */
int32_t can_standby(ZN_CanType *CANx, uint8_t enable)
{
    int32_t err = 0;

    /* Using CAN standby mode or using other GPIO */
    if (enable)
    {
        /*If there is any transmission, can not entry standby mode */
        if (CANx->BIT.TPE != 1 && CANx->BIT.TSONE != 1 && CANx->BIT.TSALL != 1)
        {
            CANx->BIT.STBY = 1;
        }
        else
        {
            err = 1;
        }
    }
    else
    {
        CANx->BIT.STBY = 0;
    }

    return err;
}

/**
 * can_get_payload_size
 *
 * @param[in]  dlcValue: Data Length Code (DLC)
 * @return     uint8_t: payload size in bytes
 *
 * @brief      This function returns the payload size in bytes based on the provided Data Length Code (DLC).
 *             If DLC is less than or equal to 8, the DLC itself represents the payload size. Otherwise,
 *             the function switches on the DLC value and returns the corresponding payload size.
 */
uint8_t can_get_payload_size(uint8_t dlcValue)
{
    uint8_t ret = 0U;

    if (8U >= dlcValue)
    {
        ret = dlcValue;
    }
    else
    {
        switch (dlcValue)
        {
        case CAN_DLC_12_BYTES:
            ret = 12U;
            break;

        case CAN_DLC_16_BYTES:
            ret = 16U;
            break;

        case CAN_DLC_20_BYTES:
            ret = 20U;
            break;

        case CAN_DLC_24_BYTES:
            ret = 24U;
            break;

        case CAN_DLC_32_BYTES:
            ret = 32U;
            break;

        case CAN_DLC_48_BYTES:
            ret = 48U;
            break;

        case CAN_DLC_64_BYTES:
            ret = 64U;
            break;

        default:
            break;
        }
    }

    return ret;
}

/**
 * can_start_transmission
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  type: Transmit type (TRANSMIT_PRIMARY or TRANSMIT_SECONDARY)
 * @param[in]  mode: Send mode (0 to send all messages, 1 to send one message only)
 * @return     int32_t: 0 if success, 1 if CAN is in standby mode and cannot send message
 *
 * @brief      This function starts the transmission of CAN messages for the provided CAN interface.
 */
int32_t can_start_transmission(ZN_CanType *CANx, TRANSMIT_TYPE type, uint8_t mode)
{
    /*Can't send message when CAN is in standby mode(return or delay) */
    if (CANx->BIT.STBY)
    {
        return 1;
    }
    
    if (TRANSMIT_PRIMARY == type)
    {
        CANx->BIT.TPE = 1;
    }
    else
    {
        if (mode)
        {
            CANx->BIT.TSONE = 1;    // Send one message only
        }
        else
        {
            CANx->BIT.TSALL = 1;    // Send all messages
        }
    }

    return 0;
}

/**
 * can_abort_transmission
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  type: Transmit type (TRANSMIT_PRIMARY or TRANSMIT_SECONDARY)
 * @return     void
 *
 * @brief      This function aborts the transmission of CAN messages for the provided CAN interface.
 */
void can_abort_transmission(ZN_CanType *CANx, TRANSMIT_TYPE type)
{
    if (TRANSMIT_PRIMARY == type)
    {
        CANx->BIT.TPA = 1;
    }
    else
    {
        CANx->BIT.TSA = 1;
    }
}

/**
 * can_is_transmit_busy
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  type: Transmit type (TRANSMIT_PRIMARY or TRANSMIT_SECONDARY)
 * @return     int32_t: 1 if transmitting is not successful (for primary transmission) or transmission buffers are full (for secondary transmission), 0 otherwise
 * 
 * @brief      This function checks if transmitting is busy for the provided CAN interface and transmit type.
 */
int32_t can_is_transmit_busy(ZN_CanType *CANx, TRANSMIT_TYPE type)
{
    if (TRANSMIT_PRIMARY == type)
    {
        return (CANx->BIT.TPE == 1);    // Transmitting is not successful
    }
    else
    {
        return (CANx->BIT.TSSTAT == 3);    // Transmission buffers are full
    }
}

/**
 * can_is_transmit_idle
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  type: transmit type (TRANSMIT_PRIMARY or TRANSMIT_SECONDARY)
 * @return     int32_t: 1 if transmit buffer is idle, 0 if not idle
 *
 * @brief      This function checks if the transmit buffer of the provided CAN interface for the specified
 *             transmit type (primary or secondary) is idle or not. 
 */
int32_t can_is_transmit_idle(ZN_CanType *CANx, TRANSMIT_TYPE type)
{
    if (TRANSMIT_PRIMARY == type)
    {
        return (CANx->BIT.TPE == 0);    // PTB is empty
    }
    else
    {
        return (CANx->BIT.TSSTAT == 0);    // STB are empty
    }
}

/**
 * can_set_bitrate
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  config: CAN_BaudrateConfig pointer that contains the baudrate settings
 * @return     void
 *
 * @brief      This function sets the bit timing registers of the provided CAN interface based on the
 *             provided baudrate configuration. 
 */
void can_set_bitrate(ZN_CanType *CANx, const CAN_BaudrateConfig *config)
{
    CANx->BIT.RESET = 1;

    /*
    CAN/CAN-FD bautrate set formula:
    tSeg1 = (S_SEG_1 + 2); tSeg2 = (S_SEG_2 + 1).
    BandRate     = (40M / (S_PRESC + 1) / ((S_SEG_1 + 2) + (S_SEG_2 + 1)))
    SamplePoint = (tSeg1 / (tSeg1 + tSeg2)).
    */
    
    CANx->BIT.S_SEG_1 = config->S_SEG_1;
    CANx->BIT.S_SEG_2 = config->S_SEG_2;
    CANx->BIT.S_SJW   = config->S_SJW;
    CANx->BIT.S_PRESC = config->S_PRESC;
}

/**
 * canfd_set_data_bitrate
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  config: CAN_FDBaudrateConfig pointer that contains the data baudrate settings
 * @return     void
 *
 * @brief      This function sets the bit timing registers of the provided CAN-FD interface based on the
 *             provided data baudrate configuration. 
 */
void canfd_set_data_bitrate(ZN_CanType *CANx, const CAN_FDBaudrateConfig *config)
{
    CANx->BIT.RESET = 1;

    /*
    CAN-FD Nominal/Arbitration refer function can_set_bitrate.
    CAN-FD data bautrate set formula(data segment):
    tSeg1 = (S_SEG_1 + 2); tSeg2 = (S_SEG_2 + 1).
    BandRate     = (40M / (S_PRESC + 1) / ((S_SEG_1 + 2) + (S_SEG_2 + 1)))
    SamplePoint = (tSeg1 / (tSeg1 + tSeg2)).
    */

    CANx->BIT.F_SEG_1 = config->F_SEG_1;
    CANx->BIT.F_SEG_2 = config->F_SEG_2;
    CANx->BIT.F_SJW   = config->F_SJW;
    CANx->BIT.F_PRESC = config->F_PRESC;
}

/**
 * can_set_filter
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  index: Filter index (0 to 27)
 * @param[in]  code: Filter code (only the first 29 bits are valid)
 * @param[in]  mask: Filter mask (the bit to check, 1-indicating the mask check, 0-matching the corresponding bit)
 * @param[in]  enable: Filter enable (1 to enable, 0 to disable)
 * @return     int32_t: Return 0 if successful, otherwise return 1
 *
 * @brief      This function sets the acceptance filter for the provided CAN interface. 
 */
int32_t can_set_filter(ZN_CanType *CANx, uint8_t index, uint32_t code, uint32_t mask, uint8_t enable)
{
    int32_t ret = 0;

    if ((index >= CAN_MAX_FILTER_NUM) || (CANx->BIT.RESET == 0))  // Should set RESET = 1 first
    {
        ret = 1;
    }
    else
    {
        /*
        ACF_3, if SELMASK=1  bit6  1 -  acceptance filter accepts either standard or extended as defined by AIDE
                                   0 -  acceptance filter accepts both standard or extended frames
               If AIDEE=1     bit5  1 -  acceptance filter accepts only extended frames
                                   0 -  acceptance filter accepts only standard frames
        
        code:received ID, and only the first 29 bits are valid
        mask:the bit to check, 1 - indicating the mask check , 0 - matching the corresponding bit
        example :want to recieve ID (0x400-0x4FF) msg,mask others msg,code = 0x400,mask = 0x000000FF;
                 want only ID(400)msg,code = 0x400,mask = 0x00000000;
        */
        
        if (enable)
        {
            CANx->REG.ACFCTRL = index;
            CANx->BIT.ACF = code;
            CANx->REG.ACFCTRL = index | SELMASK;
            CANx->BIT.ACF = mask;
            CANx->BIT.ACF_EN |= (1 << index);
        }
        else
        {
            CANx->BIT.ACF_EN &= ~(uint32_t)(1 << index);
        }
    }

    return ret;
}

/**
 * can_msg_read
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[out] info: CAN message info structure
 * @return     int32_t: Return 0 if successful, otherwise return 1
 *
 * @brief      This function reads the CAN message from the receive buffer of the provided CAN interface. If there
 *             is no message in the receive buffer, it returns 1. Otherwise, it retrieves the message information
 *             from the receive buffer and stores it into the provided info structure. 
 */
int32_t can_msg_read(ZN_CanType *CANx, CAN_MSG_INFO *info)
{
    int32_t ret = 0;
     uint8_t dataLength = 0, i = 0;
    if (!can_is_msg_in_rxbuff(CANx))
    {
        ret = 1;
    }
    else
    {
        info->ID = CANx->RBUF.ID;
        info->ESI = CANx->RBUF.ESI;
        info->BRS = CANx->RBUF.BRS;
        info->FDF = CANx->RBUF.FDF;
        info->RTR = CANx->RBUF.RTR;
        info->IDE = CANx->RBUF.IDE;
        info->DLC = CANx->RBUF.DLC;

        if ((0 == info->RTR) && info->DLC)
        {
            dataLength = can_get_payload_size(info->DLC);

            for (i = 0; i < dataLength; i += 4)
            {
                info->Data[i >> 2] = CANx->RBUF.Data[i >> 2];
            }
        
        }
        info->RTS[0] = CANx->RBUF.RTS[0];
        info->RTS[1] = CANx->RBUF.RTS[1];
        CANx->BIT.RREL = 1;
    }

    return ret;
}

/**
 * can_set_msg_info
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  info: CAN message info structure
 * @param[in]  type: transmit type (primary or secondary)
 * @return     void
 *
 * @brief      This function sets the CAN message information in the transmit buffer of the provided CAN interface.
 */
void can_set_msg_info(ZN_CanType *CANx, const CAN_MSG_INFO *info, TRANSMIT_TYPE type)
{
    uint8_t dataLength = 0,i=0;
    if (TRANSMIT_PRIMARY == type)
    {
        CANx->BIT.TBSEL = 0;
    }
    else
    {
        CANx->BIT.TBSEL = 1;
    }

    CANx->TBUF.ID = (info->ID & CAN_INFO_ID_MASK);  // 
    CANx->TBUF.TTSEN = ((info->ID&CAN_INFO_TTSEN_MASK)>>CAN_INFO_TTSEN_POS);//ID bit31
    
    if (info->FDF && CANx->BIT.TDCEN)
    {
        /*if can type is FDF & TDCEN is enable,then brs is set 1*/
        CANx->TBUF.BRS = 1;
    }
    else
    {
        CANx->TBUF.BRS = 0;
    }
    CANx->TBUF.FDF = info->FDF;
    CANx->TBUF.RTR = info->RTR;
    CANx->TBUF.IDE = info->IDE;
    CANx->TBUF.DLC = info->DLC;  // (info->DLC > 8) ? 8 : info->DLC;

    if (info->RTR == 0 && info->DLC)
    {
        dataLength = can_get_payload_size(info->DLC);
        for (i = 0; i < dataLength; i += 4)
        {
            CANx->TBUF.Data[i >> 2] = *(uint32_t *)(&info->Data[i>>2]);
        }
    }

    if (TRANSMIT_SECONDARY == type)
    {
        CANx->BIT.TSNEXT = 1;
    }
}

/**
 * can_wait_transmission_idle
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  type: transmit type (primary or secondary)
 * @return     int32_t: 0 if transmission is successful, 1 if transmission is not successful after waiting for a
 *             maximum time
 *
 * @brief      This function waits for the CAN transmission to become idle by checking the TPE bit (for primary
 *             transmit) or the TSSTAT bits (for secondary transmit) in the provided CAN interface.
 */
int32_t can_wait_transmission_idle(ZN_CanType *CANx, TRANSMIT_TYPE type)
{
    uint32_t i = 0;
    int32_t ret = 0;

    if (TRANSMIT_PRIMARY == type)
    {
        do
        {
            if (CANx->BIT.TPE == 0)    // Transmission is successful
            {
                break;
            }
        } while (i++ < MAX_CAN_WAIT_TIMES);
    }
    else
    {
        do
        {
            if (CANx->BIT.TSSTAT != 3)    // Transmission buffers are not full
            {
                break;
            }
        } while (i++ < MAX_CAN_WAIT_TIMES);
    }

    if (i >= MAX_CAN_WAIT_TIMES)
    {
        ret = 1;
    }

    return ret;
}

/**
 * can_msg_send
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  info: pointer to CAN message information structure
 * @param[in]  type: transmit type (primary or secondary)
 * @return     int32_t: 0 if transmission is successful, -1 if transmission is not successful after waiting for a
 *             maximum time, -2 if transmission start failed
 *
 * @brief      This function sends a CAN message using the provided CAN interface and message information structure.
 */
int32_t can_msg_send(ZN_CanType *CANx, const CAN_MSG_INFO *info, TRANSMIT_TYPE type)
{
    int32_t ret = 0;

    if (!can_wait_transmission_idle(CANx, type))
    {
        can_set_msg_info(CANx, info, type);

        if (can_start_transmission(CANx, type, 0))
        {
            ret = -2;
        }
    }
    else  // If timeout, return error or abort transmission
    {
        ret = -1;
    }

    return ret;
}

/**
 * can_init
 *
 * @param[in]  CANx: CAN Type pointer
 * @param[in]  config: pointer to CAN configuration structure
 * @param[in]  baudrate: pointer to CAN baud rate configuration structure
 * @return     int32_t: 0 if initialization is successful, -1 otherwise
 *
 * @brief      This function initializes the CAN interface with the provided configuration and baud rate.
 */
int32_t can_init(ZN_CanType *CANx, CAN_Config *config, const CAN_BaudrateConfig *baudrate)
{

    int32_t ret = -1;
    CAN_FilterControl *filterList = NULL;
    if ((config != NULL) && (baudrate != NULL))
    {
        ret = 0;
        /*gpio->can*/
        pad_reg_write(CAN_TXD_PREG, 0x178);
        pad_reg_write(CAN_STBY_PREG, 0x178);
        pad_reg_write(CAN_RXD_PREG, 0x178);
        
        s_canDevice.errorFlag = 0;

        /* Set baudrate */
        can_set_bitrate(CANx, baudrate);

        /*Set filters(user define or use sample setting)*/
        if ((0 != config->filterEn) && (config->filterList != NULL))
        {
            filterList = config->filterList;
            for (int i = 0; i < config->filter_num; i++)
            {
                can_set_filter(CANx, filterList[i].index, filterList[i].code, filterList[i].mask, filterList[i].enable);
            }
        }
      
        
        /*Start synchronize */
        CANx->BIT.RESET = 0;
        CANx->BIT.AFWL = CAN_RECEIVE_FIFO_COUNT/2 - 1;
        CANx->BIT.EWL = CAN_ERROR_WARNING_LIMIT;

        /*Set work mode*/
        if (config->canMode == (uint32_t)CAN_MODE_MONITOR)
        {
            CANx->BIT.LOM = 1;
        }
        else if (config->canMode == (uint32_t)CAN_MODE_LOOPBACK_INTERNAL)
        {
            CANx->BIT.LBMI = 1;
        }
        else if (config->canMode == (uint32_t)CAN_MODE_LOOPBACK_EXTERNAL)
        {
            CANx->BIT.LBME = 1;
            CANx->BIT.SACK = 1;
        }
        else
        {
        }

        s_canDevice.autoReset = config->autoReset;
        CANx->BIT.TPSS = s_canDevice.TPSS = config->TPSS;  // 1->Single Shot mode
        CANx->BIT.TSSS = s_canDevice.TSSS = config->TSSS;  // 1->Single Shot mode
        CANx->BIT.TSMODE = config->TSMODE;  // 0->FIFO mode 1->priority decision mode
        CANx->BIT.ROM = config->ROM;        // 0->overwrite the oldest message 1->discard new message

        /*Time config*/
        CANx->BIT.TIMEEN = config->TIMEEN;
        CANx->BIT.TIMEPOS = config->TIMEPOS;
        // Enable interrupt
        if (config->interruptEnable)
        {
            //CANx->REG.RTIE = TSIE | TPIE | EIE | RIE;
            CANx->REG.RTIE = EIE | TSIE | TPIE | RAFIE | RFIE | ROIE | RIE;
            CANx->REG.ERRINT = BEIE | ALIE | EPIE;
            s_canDevice.interruptEnable = config->interruptEnable;
            s_canDevice.callbackFunc = config->callbackFunc;
            NVIC_EnableIRQ(CAN_IRQn);  
        }
    }

    return ret;
}

/**
 * canfd_init
 *
 * @param[in]   CANx: CAN device pointer
 * @param[in]   config: Configuration parameters pointer
 * @param[in]   baudrate: Baudrate configuration pointer
 * @param[in]   databaudrate: Data baudrate configuration pointer
 * @return      0 if successful, -1 if failed
 *
 * @brief       Initialize CAN-FD module with given configuration and baudrates
 */
int32_t canfd_init(ZN_CanType *CANx, CAN_Config *config, const CAN_BaudrateConfig *baudrate, const CAN_FDBaudrateConfig *databaudrate)
{

    int32_t ret = -1;
    
    CAN_FilterControl *filterList = NULL;
    if ((config != NULL) && (baudrate != NULL))
    {
        ret = 0;
        
        /*gpio->can*/
        pad_reg_write(CAN_TXD_PREG, 0x178);
        pad_reg_write(CAN_STBY_PREG, 0x178);
        pad_reg_write(CAN_RXD_PREG, 0x178);
        
        s_canDevice.errorFlag = 0;

        /* Set baudrate */
        can_set_bitrate(CANx, baudrate);
         if (config->fdModeEn)
         {
             CANx->BIT.FD_ISO = 1;
             canfd_set_data_bitrate(CANx, databaudrate);
             /*ISO 11898-1:2015 requires to use only F_PRESC=0 or 1 if that TDC is used.*/
             if ((config->tdcEnable) &&((0 == CANx->REG.F_PRESC || 1 == CANx->REG.F_PRESC)))
            {
                
                CANx->BIT.TDCEN = config->tdcEnable;
                CANx->BIT.SSPOFF = config->sspOffset;
            }
         }
        /* Set filters(user define or use sample setting) */
        if ((0 != config->filterEn)&& (config->filterList != NULL)) 
        {
            filterList = config->filterList;
            for (int i = 0; i < config->filter_num; i++)
            {
                can_set_filter(CANx, filterList[i].index, filterList[i].code, filterList[i].mask, filterList[i].enable);
            }
        }
       
        
        /* Start synchronize */
        CANx->BIT.RESET = 0;
        CANx->BIT.AFWL = CAN_RECEIVE_FIFO_COUNT/2 - 1;
        CANx->BIT.EWL = CAN_ERROR_WARNING_LIMIT;

        /* Set work mode */
        if (config->canMode == (uint32_t)CAN_MODE_MONITOR)
        {
            CANx->BIT.LOM = 1;
        }
        else if (config->canMode == (uint32_t)CAN_MODE_LOOPBACK_INTERNAL)
        {
            CANx->BIT.LBMI = 1;
        }
        else if (config->canMode == (uint32_t)CAN_MODE_LOOPBACK_EXTERNAL)
        {
            CANx->BIT.LBME = 1;
            CANx->BIT.SACK = 1;
        }
        else
        {
        }

        s_canDevice.autoReset = config->autoReset;
        CANx->BIT.TPSS = s_canDevice.TPSS = config->TPSS;  // 1->Single Shot mode
        CANx->BIT.TSSS = s_canDevice.TSSS = config->TSSS;  // 1->Single Shot mode
        CANx->BIT.TSMODE = config->TSMODE;  // 0->FIFO mode 1->priority decision mode
        CANx->BIT.ROM = config->ROM;        // 0->overwrite the oldest message 1->discard new message

        /*Time config*/
        CANx->BIT.TIMEEN = config->TIMEEN;
        CANx->BIT.TIMEPOS = config->TIMEPOS;

        /* Enable interrupt  */
        if (config->interruptEnable)
        {
            //CANx->REG.RTIE = TSIE | TPIE | EIE | RIE;
            CANx->REG.RTIE = EIE | TSIE | TPIE | RAFIE | RFIE | ROIE | RIE;
            CANx->REG.ERRINT = BEIE | ALIE | EPIE;
            s_canDevice.interruptEnable = config->interruptEnable;
            s_canDevice.callbackFunc = config->callbackFunc;
            NVIC_EnableIRQ(CAN_IRQn);  
        }
    }

    return ret;
}

/**
 * can0_handle_event
 *
 * @param[in]   CANx: CAN device pointer
 * @return      none
 *
 * @brief       Handle events for CAN module and call the callback function
 */
void can0_handle_event(ZN_CanType *CANx)
{
    NVIC_DisableIRQ(CAN_IRQn);
    uint8_t flag = CANx->REG.RTIF, errInt = CANx->REG.ERRINT, ttCfg = 0;
    CAN_Device *device = &s_canDevice;

    /*Clear flag*/
    CANx->REG.RTIF = flag;
    CANx->REG.ERRINT = errInt;


    /* Check error flag */
    if (flag & (EIF | ROIF | RFIF | RAFIF | AIF) || (errInt & (EPIF | ALIF | BEIF)))
    {
        if (flag & EIF)
        {
            /*Auto reset after bus off to active, or user define */
            if (device->autoReset && CANx->BIT.RESET && (CANx->BIT.BUSOFF == 0))
            {
                CANx->BIT.RESET = 0;
                if (device->TPSS)
                {
                    CANx->REG.CFG_STAT |= TPSS;
                }
                if (device->TSSS)
                {
                    CANx->REG.CFG_STAT |= TSSS;
                }
            }
        }

        device->errorFlag = flag | (errInt << 8);
    }

     device->callbackFunc((void *)CANx,(uint32_t)(flag | (errInt << 8) | (ttCfg << 16)), (uint32_t)CANx->BIT.KOER);
     NVIC_EnableIRQ(CAN_IRQn);  
    
}

/**
 * CAN_IRQHandler
 *
 * @param[in]   none
 * @return      none
 *
 * @brief       Interrupt handler for CAN module. Calls the can0_handle_event function with the CAN0 device pointer.
 */
void CAN_IRQHandler(void)
{
    can0_handle_event(CAN0); 
}