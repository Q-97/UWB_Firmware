/*****************************************************************************
*  File: hal_dca.h
*
*  Description: this file contains the functions support dca operations.
*
* Copyright (C) : 2025 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2025 - 5
*****************************************************************************/
#include "hal_dca.h"


void hal_dca_write(uint32_t addr, uint32_t data)
{
    dca_write(addr, data);
}

uint32_t hal_dca_read(uint32_t addr)
{
    return dca_read(addr);
}