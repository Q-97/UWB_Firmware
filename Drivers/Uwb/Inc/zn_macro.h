/*****************************************************************************
* File: zn_macro.h
*
* Descirption: this file contains the functions support driver macor.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#ifndef _ZN_MACRO_H_
#define _ZN_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ZN_SUCCESS (0)
#define ZN_ERROR   (-1)

#define FCS_LEN                         (2)
#define RX_BUFFER_MAX_LEN               (1023)
#define TX_BUFFER_MAX_LEN               (1024)

// fast commands
#define CMD_CLR_IRQS      (0x12)   // Clear IRQ
#define CMD_CCA_TX_W4R    (0x11)   // Open Rx after CCA TX
#define CMD_DTX_W4R       (0xD )   // Open Rx after delayed tx
#define CMD_TX_W4R        (0xC )   // Open RX after immediate tx
#define CMD_CCA_TX        (0xB )   // cca tx
#define CMD_DRX           (0x4 )   // Enable RX @ time specified in DX_TIME register
#define CMD_DTX           (0x3 )   // Start delayed TX (RMARKER will be @ time set in DX_TIME register)
#define CMD_RX            (0x2 )   // Enable RX
#define CMD_TX            (0x1 )   // Start TX
#define CMD_TXRXOFF       (0x0 )   // Turn off TX or RX, clear any TX/RX events and put ZN into IDLE

// Defined constants for "mode" bitmask parameter passed into zn_start_tx() function.
#define ZN_START_TX_IMMEDIATE      0x00    // Send the frame immediately
#define ZN_START_TX_DELAYED        0x01    // Send the frame at specified time (time must be less that half period away)
#define ZN_RX_EN_AFTER_TX          0x02    // Enable rx after immediately tx done with delayed time
#define ZN_RX_EN_AFTER_TX_DELAY    0x03    // Enable rx after delay tx done with delayed time
#define ZN_START_TX_CCA            0x04    // Send the frame with cca
#define ZN_RX_EN_AFTER_TX_CCA      0x05    // Enable rx after cca tx done


// Defined constants for "mode" bitmask parameter passed into zn_rx_enable() function.
#define ZN_START_RX_IMMEDIATE      0x00    // Enable the receiver immediately
#define ZN_START_RX_DELAYED        0x01    // Set up delayed RX, if "late" error triggers, then the RX will be enabled immediately

// Call-back data RX frames flags
#define ZN_CB_DATA_RX_FLAG_RNG 0x1 // Ranging bit
#define ZN_CB_DATA_RX_FLAG_ND  0x2 // No data mode
#define ZN_CB_DATA_RX_FLAG_CIA 0x4 // CIA done
#define ZN_CB_DATA_RX_FLAG_CER 0x8 // CIA error


#define DBL_BUFF_OFF             0x0
#define DBL_BUFF_ACCESS_BUFFER_A 0x1
#define DBL_BUFF_ACCESS_BUFFER_B 0x3

#define FLASH_VGA_ADDR   (QSPI_END_ADDR - 0x1000)

/* User defined RX timeouts (frame wait timeout and preamble detect timeout) mask. */
#define SYS_STATUS_ALL_RX_TO     (SYS_STATUS_RXRFTO_BIT_MASK | SYS_STATUS_RXPTO_BIT_MASK | SYS_STATUS_RXSFDTO_BIT_MASK)


/* All RX errors mask. */
#define SYS_STATUS_ALL_RX_ERR    (SYS_STATUS_RXPHE_BIT_MASK | SYS_STATUS_RXFCE_BIT_MASK | SYS_STATUS_RXRFSL_BIT_MASK \
                                  | SYS_STATUS_AFFREJ_BIT_MASK | SYS_STATUS_RXSTSE_BIT_MASK)

/* All RX events after a correct packet reception mask. */
#define SYS_STATUS_ALL_RX_GOOD   (SYS_STATUS_RXFCG_BIT_MASK | SYS_STATUS_RXPRD_BIT_MASK \
                                  | SYS_STATUS_RXSFDD_BIT_MASK | SYS_STATUS_RXPHD_BIT_MASK | SYS_STATUS_RXCIADONE_BIT_MASK)

/* All TX events mask. */
#define SYS_STATUS_ALL_TX        (SYS_STATUS_AAT_BIT_MASK | SYS_STATUS_TXFRB_BIT_MASK | SYS_STATUS_TXPRS_BIT_MASK \
                                  | SYS_STATUS_TXPHS_BIT_MASK | SYS_STATUS_TXDONE_BIT_MASK )


#ifdef __cplusplus
}
#endif

#endif

