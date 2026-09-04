/*****************************************************************************
 *  File: hal_adc.c
 *
 * Descirption: this file contains the functions support adc operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/
/*************************************************************************************************************
* The adc read data of the vbat, vtestp and temperature is linear relationship.
* Flowing is the test data : 
************************************************************************************************************
* vbat(voltage)    adc_out(dec)      vtestp(voltage)    adc_out(dec)   temperature(℃)    adc_out(dec)
*     3.8             725               0.25               16             -40                725
*     3.75            703               0.3                88             -20                671  
*     3.7             695               0.35               156            -10                646
*     3.65            682               0.4                225              0                618
*     3.6             667               0.5                365             10                591
*     3.55            653               0.55               434             20                562
*     3.5             631               0.6                506             30                537
*     3.45            615               0.65               574             40                510
*     3.35            585               0.7                645             50                481
*     3.3             570               0.75               713             60                453 
*     3.25            563               0.8                783             70                424 
*     3.2             549               0.85               855             80                396
*     3.15            537               0.9                923             90                368
*     3.1             524               0.95               991             100               340
*     3.05            503               1                  1023            110               310 
*     3               494                                                  120               280 
*     2.95            481                                                  130               258
*     2.9             467                                                  140               231 
*     2.85            452
*     2.8             438
*     2.75            423
*     2.7             408
*     2.65            393
*     2.6             378
*
* we can get the linear equation from these test datas above.
* vbat ≈ (adc_out + 413) / 300
* old: vtetp ≈ (adc_out + 310) / 1360;   new: vtetp ≈ (adc_out + 335) / 1425;
* tempterature ≈ (612 - agcout) / 2.5
************************************************************************************************************/
#include "hal_adc.h"

float adc_cali_val = 0;

void hal_adc_cali_init(void)
{
    adc_cali_val += 603 - zn_read_vbat_voltage(TYPE_VBAT);
    adc_cali_val += 603 - zn_read_vbat_voltage(TYPE_VBAT);
    adc_cali_val += 603 - zn_read_vbat_voltage(TYPE_VBAT);
    adc_cali_val /= 3;
}

double hal_adc_get_cur_vbat_voltage(void)
{
    uint16_t val  = 0;
    double   vbat = 0.0;
    
    val = zn_read_vbat_voltage(TYPE_VBAT);
    
    vbat = (val + 413) / 300.0;
    
    return vbat;
}

double hal_adc_get_cur_vtestp_voltage(void)
{
    uint16_t val   = 0;
    double   vtesp = 0.0;
    
    val = zn_read_vbat_voltage(TYPE_ATESTP);
    
    vtesp = (val + 335 + adc_cali_val) / 1425.0;
    
    return vtesp;
}

double hal_adc_get_cur_temperature(void)
{
    uint16_t val         = 0;
    double   temperature = 0.0;
    
    val = zn_read_vbat_voltage(TYPE_TEMPERATURE);
    
    temperature = (612 - val) / 2.5;
    
    return temperature;
}
