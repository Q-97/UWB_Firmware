/**
 * @file frame_pack.c
 * @brief CIR data frame packing module (host protocol layer).
 */
#include "frame_pack.h"
#include "hal_uart.h"

/* --- Frame markers --- */
static const uint8_t FRAME_START[FRAME_HEADER_LEN] = {0xFF, 0x00, 0xFF, 0x00};
static const uint8_t FRAME_STOP [FRAME_FOOTER_LEN] = {0xF0, 0x00, 0xF0, 0x00};

/**
 * @brief  Convert int32 sample to int16 with saturation, little-endian.
 * @param  val  raw sample
 * @param  out  2-byte output buffer
 */
static void i32_to_i16_sat(int32_t val, uint8_t *out)
{
    int32_t clamped = val;

    if (clamped >  32767) clamped =  32767;
    if (clamped < -32768) clamped = -32768;

    out[0] = (uint8_t)(clamped & 0xFF);
    out[1] = (uint8_t)((clamped >> 8) & 0xFF);
}

uint16_t frame_pack_serialize(uint8_t ant_id,
                              const int32_t *buf_i, const int32_t *buf_q,
                              uint8_t tap_len,
                              uint8_t *out_frame, uint16_t out_max_len)
{
    uint16_t cir_len;
    uint16_t frame_len;
    uint16_t off;
    uint8_t  i;

    if ((NULL == out_frame) || (NULL == buf_i) || (NULL == buf_q) || (0 == tap_len))
    {
        return 0;
    }

    cir_len   = (uint16_t)tap_len * 4u;   /* I16 + Q16 per tap */
    frame_len = FRAME_HEADER_LEN + FRAME_ANTENNA_LEN + cir_len + FRAME_FOOTER_LEN;
    if (frame_len > out_max_len)
    {
        return 0;
    }

    off = 0;

    /* Frame header */
    for (i = 0; i < FRAME_HEADER_LEN; i++) { out_frame[off++] = FRAME_START[i]; }

    /* Antenna info: TX + RX */
    out_frame[off++] = FRAME_TX_ID;
    out_frame[off++] = ant_id;          /* ant 4~7 used directly as RX id */

    /* CIR payload: I/Q interleaved, int16 little-endian */
    for (i = 0; i < tap_len; i++)
    {
        i32_to_i16_sat(buf_i[i], &out_frame[off]);  off += 2;
        i32_to_i16_sat(buf_q[i], &out_frame[off]);  off += 2;
    }

    /* Frame footer */
    for (i = 0; i < FRAME_FOOTER_LEN; i++) { out_frame[off++] = FRAME_STOP[i]; }

    return frame_len;
}
