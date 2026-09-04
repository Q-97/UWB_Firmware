#ifndef __CALI_REG_H__
#define __CALI_REG_H__

#include "stdint.h"


typedef struct {
    uint32_t baseAddress; // Base address for the register
    uint32_t baseOffset; // Bit offset for the field
    uint32_t baseLength; // Length of the field in bits
} FileConfig;

#endif