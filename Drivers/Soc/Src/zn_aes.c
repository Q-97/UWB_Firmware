/*****************************************************************************
* File: secure_zn2014.c
*
* Descirption: this file contains the functions support security.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <string.h>
#include "zn_regs.h"
#include "zn_aes.h"
#include "zn_interface.h"

static uint32_t key[4] = {0x1d177b4c, 0xcf72304f, 0xcc82ba7d, 0x1ec0998}; // key for ccm* and aes module ,user can modify

void hal_uwb_write_tx_data(uint8_t* buffer, uint16_t len)
{
    zn_write_tx_data(len, buffer, 0);
}
void hal_uwb_write_tx_frame_ctrl(uint16_t len)
{
    zn_write_tx_frame_ctrl(len + 2, 0, 0);
}

static void key_print(uint32_t *key, uint8_t len)
{
    uint8_t offset = 0;
    uint8_t idx = 0;
    uint8_t data;

    for(idx = 0; idx < len; idx++)
    {
        for(offset = 0; offset < 4; offset++)
        {
            data = (uint8_t)((key[idx] >> 8 * offset) & 0xff);
            printf("%x", data);
        }
    }
    printf("\r\n");
}

static void wait_done(uint32_t state_mask)
{
    uint32_t status = 0;
    uint32_t now    = 0; 
    uint32_t last   = zn_get_sys_time();

    do
    {
        status = read_mreg32(SE_INT_RAW);
        now = zn_get_sys_time();

        if(now > last)
        {
            if ((now - last) >= SE_WAIT_TIMEOUT)
            {
                break;
            }
        }
        else
        {
            if ((0xffffffff - last + now) >= SE_WAIT_TIMEOUT)
            {
                break;
            }
        }
    } while(!(status & state_mask));

    write_mreg32(SE_INT_RAW , state_mask);
}

static void wait_kdf_done(void)
{
    wait_done(SE_INT_KDF);
}

static void wait_aes_done(void)
{
    wait_done(SE_INT_CCM);
}

static void wait_ecb_done(void)
{
    wait_done(SE_INT_ECB);
}

static void secure_byte_convert(uint32_t *data, uint8_t len)
{
    uint32_t convert_data = 0;
    uint8_t  idx          = 0;

    for(idx = 0; idx < len; idx++)
    {
        convert_data = ((data[idx] & 0xff) << 24) | ((data[idx] & 0xff00) << 8) | ((data[idx] & 0xff0000) >> 8) | ((data[idx] & 0xff000000) >> 24);
        data[idx] = convert_data;
    }
}

void secure_sts_load_config(void)
{
    zn_write_32bit_reg(STS_LOAD_ID, 0x00000000);
}

//Data encrypt and decrypt use ccm* following the fira mac protocol specification 
void mac_data_encrypt(uint16_t payload_size, uint8_t header_size, uint16_t src_addr, uint8_t slot)
{
    uint32_t nonce[4]  = {0x00000000, 0x0000000, 0x00000000, 0x00000600};
    uint32_t reg_value = 0x00c0000;

    nonce[1] = ((uint32_t)src_addr & 0xff00) << 16;
    nonce[2] = src_addr & 0x00ff;
    nonce[3] |= slot;

    reg_value |= (uint32_t)payload_size << 8 | header_size;
    
    write_mreg32(KDFFREEKEY_REG_0, key[0]);
    write_mreg32(KDFFREEKEY_REG_1, key[1]);
    write_mreg32(KDFFREEKEY_REG_2, key[2]);
    write_mreg32(KDFFREEKEY_REG_3, key[3]);

    write_mreg32(NONCE_REG_0, nonce[0]);
    write_mreg32(NONCE_REG_1, nonce[1]);
    write_mreg32(NONCE_REG_2, nonce[2]);
    write_mreg32(NONCE_REG_3, nonce[3]);

    write_mreg32(DATA_CONTROL_REG, 0x04000400); //src tx buff dst tx buff
    write_mreg32(DATA_SIZE_REG, reg_value);     //tag size 8

    write_mreg32(AES_CONTROLLER_REG, 0x00000000);
    write_mreg32(SE_INT_MASK, 0x00000002);
    write_mreg32(SE_INT_ENABLE, 0x00000002);
    write_mreg32(CCM_CONTROLLER_REG, 0x00000013);

    wait_aes_done();
}

void mac_data_decrypt(uint8_t payload_size, uint8_t header_size, uint16_t src_addr, uint8_t slot)
{
    uint32_t nonce[4]  = {0x00000000, 0x0000000, 0x00000000, 0x00000600};
    uint32_t reg_value = 0x00c0000;

    nonce[1] = ((uint32_t)src_addr & 0xff00) << 16;
    nonce[2] = src_addr & 0x00ff;
    nonce[3] |= slot;

    reg_value |= (uint32_t)payload_size << 8 | header_size;
    
    write_mreg32(KDFFREEKEY_REG_0, key[0]);
    write_mreg32(KDFFREEKEY_REG_1, key[1]);
    write_mreg32(KDFFREEKEY_REG_2, key[2]);
    write_mreg32(KDFFREEKEY_REG_3, key[3]);

    write_mreg32(NONCE_REG_0, nonce[0]);
    write_mreg32(NONCE_REG_1, nonce[1]);
    write_mreg32(NONCE_REG_2, nonce[2]);
    write_mreg32(NONCE_REG_3, nonce[3]);

    write_mreg32(DATA_CONTROL_REG, 0x08000800); //src rx buff dst rx buff
    write_mreg32(DATA_SIZE_REG, reg_value);     //tag size 8

    write_mreg32(AES_CONTROLLER_REG, 0x00000000);
    write_mreg32(SE_INT_MASK, 0x00000002);
    write_mreg32(SE_INT_ENABLE, 0x00000002);
    write_mreg32(CCM_CONTROLLER_REG, 0x00000011);

    wait_aes_done();
}

void secure_aes_encode(unsigned char *in_data, unsigned char *out_data, unsigned int data_len, unsigned char *key_in, unsigned int key_len)
{
    uint32_t key[4]     = {0};
    uint32_t payload[4] = {0};

    memcpy((uint8_t *)key, key_in, AES_BLOCK_SIZE);
    memcpy((uint8_t *)payload, in_data, AES_BLOCK_SIZE);

    write_mreg32(KDFFREEKEY_REG_0, key[0]);
    write_mreg32(KDFFREEKEY_REG_1, key[1]);
    write_mreg32(KDFFREEKEY_REG_2, key[2]);
    write_mreg32(KDFFREEKEY_REG_3, key[3]);

    write_mreg32(NONCE_REG_0, payload[0]);
    write_mreg32(NONCE_REG_1, payload[1]);
    write_mreg32(NONCE_REG_2, payload[2]);
    write_mreg32(NONCE_REG_3, payload[3]);

    write_mreg32(AES_CONTROLLER_REG, 0x00000000);
    write_mreg32(SE_INT_ENABLE, 0x00000004);
    write_mreg32(SE_INT_MASK, 0x00000004);
    write_mreg32(ECBCONTROLREG, 0x00000043);

    wait_ecb_done();

    out_data[0] = read_mreg32(KDFKEYOUT_REG_0);
    out_data[1] = read_mreg32(KDFKEYOUT_REG_1);
    out_data[2] = read_mreg32(KDFKEYOUT_REG_2);
    out_data[3] = read_mreg32(KDFKEYOUT_REG_3);
}