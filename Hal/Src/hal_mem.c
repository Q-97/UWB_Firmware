/*****************************************************************************
* File: mem.c
*
* Descirption: this file contains the functions support memory management.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <string.h>
#include <stdint.h>
#include "hal_mem.h"

static hal_mem_pool_t s_mem_pool[MAX_MEM_POOL_NUM];

void hal_mem_init(void)
{
    memset(&s_mem_pool[0], 0, sizeof(hal_mem_pool_t) * MAX_MEM_POOL_NUM);
}

uint8_t hal_mem_get_count(void)
{
    uint8_t idx;
    uint8_t mem_cnt = 0;

    for(idx = 0; idx < MAX_MEM_POOL_NUM; idx++)
    {
        if(s_mem_pool[idx].alloc)
        {
            mem_cnt++;
        }
    }

    return mem_cnt;
}

hal_mem_pool_t *hal_mem_alloc(void)
{
    uint8_t idx;

    for (idx = 0; idx < MAX_MEM_POOL_NUM; idx++)
    {
        if(1 != s_mem_pool[idx].alloc)
        {
            s_mem_pool[idx].len = 0;
            s_mem_pool[idx].index = idx;
            s_mem_pool[idx].alloc = 1;
            return &s_mem_pool[idx];
        }
    }

    return NULL;
}

void hal_mem_free(hal_mem_pool_t *mem_pool)
{
    if(mem_pool)
    {
        mem_pool->alloc = 0;
    }
    else
    {
        LOG_ERROR("Memsory pool is NULL!\n");
    }
}
