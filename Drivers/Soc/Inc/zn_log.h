/*****************************************************************************
* File: log.h
*
* Descirption: this file contains the functions support log.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>


typedef enum log_level
{
    LOG_LEVEL_OFF   = -3,
    LOG_LEVEL_NEC   = -2,
    LOG_LEVEL_ERROR = -1,
    LOG_LEVEL_WARN  = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_DEBUG = 2,
    LOG_LEVEL_ALL   = 3,
}log_level_t;

extern volatile int32_t g_log_level;

#define LOG_DEBUG(format,...)    \
do {                            \
    if (g_log_level >= LOG_LEVEL_DEBUG) {    \
        printf(""format"\r\n", ##__VA_ARGS__);    \
    }    \
} while(0)

#define LOG_INFO(format,...)    \
do {                            \
    if (g_log_level >= LOG_LEVEL_INFO) {    \
        printf(""format"\r\n", ##__VA_ARGS__);    \
    }    \
} while(0)
 
#define LOG_WARN(format,...)    \
do {                            \
    if (g_log_level >= LOG_LEVEL_WARN) {    \
        printf("[WARN ] [%s] [%d] "format"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);    \
    }    \
} while(0)
 
#define LOG_ERROR(format,...)    \
do {                            \
    if (g_log_level >= LOG_LEVEL_ERROR) {    \
        printf("[ERROR] [%s] [%d] "format"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);    \
    }    \
} while(0)

#define LOG_NEC(format,...)        \
do {                            \
    if (g_log_level >= LOG_LEVEL_NEC) {    \
        printf(""format"\r\n", ##__VA_ARGS__);    \
    }    \
} while(0)

#define LOG_DEBUG_ARRAY(arr, size, elem_format)  \
do {  \
    if (g_log_level >= LOG_LEVEL_DEBUG){ \
        printf("%s=", #arr); \
        printf(" ["); \
        for (int i = 0; i < (size); i++) { \
            printf(elem_format, (arr)[i]); \
        } \
        printf("]\n"); \
    }  \
} while(0)

#define DOT_TIME()              \
        printf("[TIME ] [%s] [%d] [%d]\r\n", __FILE__, __LINE__, xTaskGetTickCount());


void set_log_level(log_level_t level);
#ifdef __cplusplus
}
#endif

#endif
