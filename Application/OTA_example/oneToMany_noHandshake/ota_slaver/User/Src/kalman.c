/*****************************************************************************
* File: kalman.c
*
* Descirption: this file contains the functions support kalman filter.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <stdint.h>
#include <math.h>

#define  MAX_SUPPORT_DEV_NUM   8
#define  MAX_AOA_MUM           2

const float q   = 0.02;
const float r   = 5;
const float thr = 86;

float x[MAX_SUPPORT_DEV_NUM] = {0};
float p[MAX_SUPPORT_DEV_NUM] = {1.0};

uint8_t kalman_flag = 0;

float kalman_core(uint8_t idx, float distance)
{
    float x_;
    float p_;
    float kg;

    if(!kalman_flag)
    {
        x[idx] = distance;
        kalman_flag = 1;
    }
    else
    {
        x_ = x[idx];
        p_ = p[idx] + q;
        kg = p_ / (p_ + r);
        x[idx] = x_ + kg * (distance - x_);
        p[idx] = (1 - kg) * p_;
        if(fabs(x[idx] - distance) >= thr)
        {
            x[idx] = distance;
        }
    }

    return x[idx];
}

const double aoa_q = 1.0;
const double aoa_r = 5;
const double aoa_thr = 10.0;

double aoa_x[MAX_AOA_MUM][MAX_SUPPORT_DEV_NUM] = {{0},{0}};
double aoa_p[MAX_AOA_MUM][MAX_SUPPORT_DEV_NUM] = {{1.0},{1.0}};
uint8_t aoa_flag = 0;

void kalman_aoa(uint8_t aoaidx, uint8_t idx, double aoa, double *rlt)
{
    float x_;
    float p_;
    float kg;

    if(aoa_flag == 0)
    {
         aoa_x[aoaidx][idx] = aoa;
         aoa_flag = 1;
    }
    else
    {
        x_ = aoa_x[aoaidx][idx];
        p_ = aoa_p[aoaidx][idx] + aoa_q;
        kg = p_ / (p_ + aoa_q);
        aoa_x[aoaidx][idx] = x_ + kg * (aoa - x_);
        aoa_p[aoaidx][idx] = (1 - kg) * p_;
        if(fabs(aoa_x[aoaidx][idx] - aoa) >= aoa_thr)
        {
            aoa_x[aoaidx][idx] = aoa;
        }
    }

    *rlt = aoa_x[aoaidx][idx];
}
