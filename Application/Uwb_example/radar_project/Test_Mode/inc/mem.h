/*****************************************************************************
* File: mem.h
*
* Descirption: this file contains the functions support memory management.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MAX_MEM_POOL_NUM    5
#define MAX_MEM_POOL_SIZE   256

typedef struct mem_pool
{
    uint8_t       alloc;
    uint8_t       len;
    uint8_t       index;
    uint8_t       buf[MAX_MEM_POOL_SIZE];
}mem_pool_t;

void mem_init(void);
uint8_t mem_get_count(void);
mem_pool_t *mem_alloc(void);
void mem_free(mem_pool_t *mem_pool);

#endif
