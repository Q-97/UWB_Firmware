/*****************************************************************************
* File: hal_mem.h
*
* Descirption: this file contains the functions support memory management.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _HAL_MEMORY_H
#define _HAL_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "zn_soc.h"

#define MAX_MEM_POOL_NUM    5
#define MAX_MEM_POOL_SIZE   256

typedef struct mem_pool
{
    uint8_t       alloc;
    uint8_t       len;
    uint8_t       index;
    uint8_t       buf[MAX_MEM_POOL_SIZE];
}hal_mem_pool_t;

void hal_mem_init(void);
uint8_t hal_mem_get_count(void);
hal_mem_pool_t *hal_mem_alloc(void);
void hal_mem_free(hal_mem_pool_t *mem_pool);

#ifdef __cplusplus
}
#endif

#endif
