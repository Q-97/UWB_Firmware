#ifndef _AES_H
#define _AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zn_soc.h"

#define SE_INT_ENABLE             (SE_BASE_ADDR + 0x88)

#define SE_INT_KDF      (0x00000001)
#define SE_INT_CCM      (0x00000002)
#define SE_INT_ECB      (0x00000004)
#define SE_WAIT_TIMEOUT (250 * 1000) //1ms

#define AES_BLOCK_SIZE             16

void hal_uwb_write_tx_data(uint8_t* buffer, uint16_t len);
void hal_uwb_write_tx_frame_ctrl(uint16_t len);

void secure_sts_load_config(void);
void mac_data_encrypt(uint16_t payload_size, uint8_t header_size, uint16_t src_addr, uint8_t slot);
void mac_data_decrypt(uint8_t payload_size, uint8_t header_size, uint16_t src_addr, uint8_t slot);
void secure_aes_encode(unsigned char *in_data, unsigned char *out_data, unsigned int data_len, unsigned char *key_in, unsigned int key_len);

#ifdef __cplusplus
}
#endif

#endif