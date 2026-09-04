#ifndef FRAME_PACK_H
#define FRAME_PACK_H
#include <stdint.h>

#define FRAME_HEADER_LEN    4
#define FRAME_ANTENNA_LEN   2
#define FRAME_FOOTER_LEN    4
#define FRAME_TX_ID         1      /* 按你的协议定义修改 */

uint16_t frame_pack_serialize(uint8_t ant_id,
                              const int32_t *buf_i, const int32_t *buf_q,
                              uint8_t tap_len,
                              uint8_t *out_frame, uint16_t out_max_len);


#endif