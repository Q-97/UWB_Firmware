/*****************************************************************************
 *  File: hal_gp_timer.c
 *
 * Descirption: this file contains the functions support sleep operations.
 *
 *  Copyright (C) : 2025 ultraception.com
 *
 *  Author: sxg
 *  Mail:   
 *  Date:   2025-5-12
 *
 *****************************************************************************/

#include "hal_sleep.h"
#include "hal_uwb.h"
#include "hal_gp_timer.h"

static uint32_t g_sleep_us = 0;

static void wakeup_source_set(wakeup_cfg_t * wakeup_config)
{
    uint8_t value = dca_read(AON_WKUP_CFG) & 0x8f;
    
    value |= wakeup_config->wakeup_src.mask;
    dca_write(AON_WKUP_CFG, value);
    
    dca_write(WAKEUP_CONFIG, wakeup_config->wakeup_mode.mask);
    
    value = dca_read(AON_WKUP_STATUS) & 0x1f;
    value |= wakeup_config->wakeup_level.mask;
    dca_write(AON_WKUP_STATUS, value);
    
}

static void retention_config(retention_cfg_t * ret_config)
{
    uint8_t value = 0;
    uint8_t size  = 0;
    
    dca_write(AON_RESETN_CFG,0x19);
    dca_write(AON_SPI0_CSN_CFG,0x19);
    dca_write(AON_SPI1_CSN_CFG,0x19);
    dca_write(AON_BOOT0_CFG,0x19);
    dca_write(AON_BOOT1_CFG,0x19);
    dca_write(AON_CAN_RXD_CFG,0x19);
    if(ret_config->ret_en)
    {
        value = (ret_config->ret_size > 32) ? 0x00 : 0x80;
        dca_write(AON_MEM_LDO_CONFIG,value);

        size = ret_config->ret_size / 16;
        value = (1 << size) - 1;
        dca_write(AON_SRAM_CODE_PD,value);
        dca_write(AON_ANA_CFG,0x0);       // bg off
        if(ret_config->boot_en)
        {
            dca_write(AON_BOOT_RETENTION,0x80|((CODE_SRAM_ADDR-0x1FFE0000)>>10));
            dca_write(AON_CFG, (dca_read(AON_CFG) & (~(0x07 << 2)))); 
        }
        else
        {
            dca_write(AON_BOOT_RETENTION, 0x00);
            dca_write(AON_CFG, (dca_read(AON_CFG) & (~(0x07 << 2))) | (3<<2)); 
        }
    }
    else
    {
        dca_write(AON_MEM_LDO_CONFIG,0xc0); // mem ldo2 off, mem ldo off, ldo2:high 96k,lod: low 32k
        dca_write(AON_SRAM_CODE_PD,0x0);   // ds or sd sel,0: sd, 1: sd, each bit response 16k
        dca_write(AON_ANA_CFG,0x0);       // bg off
        dca_write(AON_BOOT_RETENTION,0x00);
        dca_write(AON_CFG, (dca_read(AON_CFG) & (~(0x07 << 2))) | (3<<2)); 
    }
}

static void auto_sleep_config(uint8_t clk_sel, uint32_t time_us, uint8_t count_mode, uint32_t count_load)
{
    uint32_t cur_count = 0;
    uint32_t count     = US_TO_32K_COUNT(time_us);
    
    if(EXTERNAL_XO_CLK == clk_sel)
    {
        if((dca_read(AON_XO_CFG) & 0x0b) != 0x0b)
        {
            dca_write(AON_XO_CFG, 0x0b);
            mdelay(500);
        }
        
    }
    else
    {
        if((dca_read(AON_XO_CFG) & 0x08) != 0x08)
        {
            dca_write(AON_XO_CFG, 0x08);
            mdelay(1);
        }
    }
    
    
    if(MODE_NOT_CLEAR == count_mode)
    {
        while(0x08 != (dca_read(AON_SLP_CNT_CONTRL) & 0x08));
        dca_write(AON_SLP_CNT_CONTRL, 0x04); /*when write 1, clear SLP_CNT_VALID*/
        cur_count = dca_read(AON_SLP_LOAD_READ_CNT3) << 24;
        cur_count |=  dca_read(AON_SLP_LOAD_READ_CNT2) << 16;
        cur_count |=  dca_read(AON_SLP_LOAD_READ_CNT1) << 8;
        cur_count |=  dca_read(AON_SLP_LOAD_READ_CNT0);
        dca_write(AON_SLP_CNT_CONTRL, 0x00);
        
        
        count += cur_count;
        dca_write(AON_SLEEP_CNT_BYTE3, count >> 24);
        dca_write(AON_SLEEP_CNT_BYTE2, (count >> 16) & 0xFF);
        dca_write(AON_SLEEP_CNT_BYTE1, (count >> 8) & 0xFF);
        dca_write(AON_SLEEP_CNT_BYTE0, count & 0xFF);
    }
    else if(MODE_CLEAR == count_mode)
    {
        dca_write(AON_SLP_CNT_CONTRL, 0x01);/*clear sleep couter */
        dca_write(AON_SLP_CNT_CONTRL, 0x00);
        dca_write(AON_SLEEP_CNT_BYTE3, count >> 24);
        dca_write(AON_SLEEP_CNT_BYTE2, (count >> 16) & 0xFF);
        dca_write(AON_SLEEP_CNT_BYTE1, (count >> 8) & 0xFF);
        dca_write(AON_SLEEP_CNT_BYTE0, count & 0xFF);
    }
    else if(MODE_RELOAD == count_mode)
    {
        dca_write(AON_SLP_CNT_CONTRL, 0x02);/*load SLP_LOAD_READ_CNT to SLP_CNT*/
        dca_write(AON_SLP_LOAD_READ_CNT3, count_load >> 24);
        dca_write(AON_SLP_LOAD_READ_CNT2, (count_load >> 16) & 0xff);
        dca_write(AON_SLP_LOAD_READ_CNT1, (count_load >> 8) & 0xff);
        dca_write(AON_SLP_LOAD_READ_CNT0, count_load & 0xff);
        dca_write(AON_SLP_CNT_CONTRL, 0x00);
        
        count += count_load;
        dca_write(AON_SLEEP_CNT_BYTE3, count >> 24);
        dca_write(AON_SLEEP_CNT_BYTE2, (count >> 16) & 0xFF);
        dca_write(AON_SLEEP_CNT_BYTE1, (count >> 8) & 0xFF);
        dca_write(AON_SLEEP_CNT_BYTE0, count & 0xFF);       
    }
}

static void clear_sleep_flag(void)
{
    dca_clear_bit(AON_CFG,5);  //clear deepsleep_en
    dca_clear_bit(AON_CFG,1);  //clear WAKE_CNT en
    dca_clear_bit(AON_CFG,0);  //clear sleep en
    dca_clear_bit(AON_WKUP_CFG,6);//clear can rxd wakeup enable
    dca_clear_bit(AON_WKUP_CFG,5);//clear spi1 cs wakeup enable
    dca_clear_bit(AON_WKUP_CFG,4);//clear spi0 cs wakeup enable
    dca_set_bit(AON_WKUP_STATUS,0);  //Write 1 to clear wakeup_flag
}


ERROR_Type hal_sleep_go_sleep(hal_sleep_t *sleep_config)
{
    if(NULL == sleep_config)
    {
        LOG_ERROR("null pointer error");
        return ERROR;
    }
    
    clear_sleep_flag();
    retention_config(&sleep_config->ret_cfg);
    wakeup_source_set(&sleep_config->wakeup_cofig);
    
    if(AUTO_SLEEP == sleep_config->sleep_type)
    {
        auto_sleep_config(sleep_config->clk_sel, sleep_config->time_us, sleep_config->sleep_cnt_mode, sleep_config->count_load);
        dca_clear_bit(AON_CFG, 5);
        dca_set_bit(AON_CFG, 1);
    }
    else
    {
        dca_set_bit(AON_CFG, 5);
        dca_clear_bit(AON_CFG, 1);
    }

    dca_write(AON_CFG, dca_read(AON_CFG) | 0x01); 
    
    __asm("wfi");
    
    return SUCCESS;
}

uint8_t hal_sleep_get_wakeup_status(void)
{
    uint8_t status = 0;
    
    status = dca_read(AON_WKUP_STATUS);
    
    status = (status >> 1) & 0x0f;

    return status;
}

uint32_t hal_sleep_get_cur_counter(void)
{
    uint32_t sleep_cnt_raw = 0;

    sleep_cnt_raw = dca_read(AON_SLP_LOAD_READ_CNT3)<<24;
    sleep_cnt_raw |=  dca_read(AON_SLP_LOAD_READ_CNT2)<<16;
    sleep_cnt_raw |=  dca_read(AON_SLP_LOAD_READ_CNT1)<<8;
    sleep_cnt_raw |=  dca_read(AON_SLP_LOAD_READ_CNT0);
    
    return sleep_cnt_raw;
}

uint8_t hal_sleep_get_retention_en(void)
{
    uint8_t status = 0;
    
    status = dca_read(AON_BOOT_RETENTION);
    
    status = (status >> 7) & 0x01;

    return status;
}

void hal_standby_with_sleep(void)
{
    memcpy((uint8_t *)STACK_BACK, (uint8_t *)(*(uint32_t *)CUR_SP_ADDR), ((*(uint32_t *)TOP_SP_ADDR) - (*(uint32_t *)CUR_SP_ADDR)));
    write_mreg32(SLEEP_FLAG_ADDR, SLEEP_FLAG_VAL);
    
    hal_sleep_t sleep_config = {0};
    sleep_config.sleep_type = AUTO_SLEEP;
    sleep_config.clk_sel = INTERNAL_RC_CLK;
    sleep_config.sleep_cnt_mode = 0;
    sleep_config.latch_en = FALSE;
    sleep_config.time_us = g_sleep_us;
    sleep_config.ret_cfg.ret_en = TRUE;
    sleep_config.ret_cfg.ret_size = 128;
    sleep_config.ret_cfg.boot_en = TRUE;
    hal_sleep_go_sleep(&sleep_config);

    return;
}

void hal_store_stack_and_sleep(uint32_t sleep_us)
{
    g_sleep_us = sleep_us;
    __asm volatile
    (
        "ISB                            \n\t"
        "LDR     R0, =LABEL             \n\t"
        "PUSH    {R0}                   \n\t"
        "MRS     R0,  XPSR              \n\t"
        "PUSH    {R0}                   \n\t"
        "STMDB   SP!, {R0-R12, R14}     \n\t"
        "LDR     R0,  =0x1FFE0008       \n\t"
        "STR     R13,[R0]               \n\t"
        "B       hal_standby_with_sleep \n\t"
        "LABEL:                         \n\t"
    );

    return;
}

void hal_restore_stack(void)
{
    write_mreg32(SLEEP_FLAG_ADDR, 0x00);
    memcpy((uint8_t *)(*(uint32_t *)CUR_SP_ADDR), (uint8_t *)STACK_BACK, ((*(uint32_t *)TOP_SP_ADDR) - (*(uint32_t *)CUR_SP_ADDR)));
    __asm volatile
    (
        "ISB                           \n\t"
        "LDR     R0, =0x1FFE0008       \n\t"
        "LDR     SP, [R0]              \n\t"
        "LDMIA   SP!, {R0-R12, R14}    \n\t"
        "POP     {R0}                  \n\t"
        "MSR     XPSR, R0              \n\t"
        "POP     {R0}                  \n\t"
        "MOV     PC, R0                \n\t"
    );

    return;
}