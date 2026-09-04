/*****************************************************************************
 *  File: hal_otp.c
 *
 * Descirption: this file contains the functions support otp operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************
* OTP memory map:
* addr     BYTE[3]        BYTE[2]         BYTE[1]         BYTE[0]           programmed by 
*  0       otp_key_3      otp_key_2       otp_key_1       otp_key_0         Customer
*  1       otp_key_7      otp_key_6       otp_key_5       otp_key_4         Customer
*  2       otp_key_11     otp_key_10      otp_key_9       otp_key_8         Customer
*  3       otp_key_15     otp_key_14      otp_key_13      otp_key_12        Customer
*  4       otp_key_19     otp_key_18      otp_key_17      otp_key_16        Customer
*  5       otp_key_23     otp_key_22      otp_key_21      otp_key_20        Customer
*  6       otp_key_27     otp_key_26      otp_key_25      otp_key_24        Customer
*  7       otp_key_31     otp_key_30      otp_key_29      otp_key_28        Customer
*  8       otp_key_mask   Reserved        Reserved        Reserved          Reserved(only BYTE[3] Customer)     
*  9       Reserved       Reserved        Reserved        Reserved          Ultraception
*  ...     Reserved       Reserved        Reserved        Reserved          Ultraception 
*  31      Reserved       Reserved        Reserved        Reserved          Ultraception 
*  32                                                                       Customer
*  ...                                                                      ...
*  255                                                                      Customer
*  otp_key_mask[7]: when set to 1, otp key can not be programmed and read.
*  otp memory only can program once, ech bit can only programmed 0-1,can not programmed 1-0.
*************************************************************************************************************/
#include "hal_otp.h"

void hal_otp_write(uint16_t addr, uint32_t* data, uint8_t len)
{
    zn_otp_write(addr, data, len);
}

void hal_otp_read(uint16_t addr, uint32_t* data, uint8_t len)
{
    zn_otp_read(addr, data, len);
}

BOOL_Type hal_opt_key_locked(void)
{
    uint32_t data = 0;
    
    zn_otp_read(8, &data, 1);
    
    if(data & 0x80000000)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ERROR_Type hal_otp_key_write(uint32_t* key)
{
    uint32_t data = 0;
    
    zn_otp_read(8, &data, 1);
    
    if(data & 0x80000000)
    {
        LOG_ERROR("otp key locked, can not write");
        return ERROR;
    }
    else
    {
        zn_otp_write(0, key, 8);
    }
    
    return SUCCESS;
}

ERROR_Type hal_otp_key_read(uint32_t* key)
{
    uint32_t data = 0;
    
    zn_otp_read(8, &data, 1);
    
    if(data & 0x80000000)
    {
        LOG_ERROR("otp key locked, can not read");
        return ERROR;
    }
    else
    {
        zn_otp_read(0, key, 8);
    }
    
    return SUCCESS;
}

