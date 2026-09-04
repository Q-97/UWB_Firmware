
/*****************************************************************************
* File: zn_radar_reg.h
*
* Descirption: this file contains the functions support radar driver regs.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2026 - 6
*****************************************************************************/
#ifndef __ZN_RADAR_REG_H
#define __ZN_RADAR_REG_H

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************/
// Description: Bit definitions for register radar fast cmd
//******************************************************************************/
#define RADAR_FAST_CMD_ID                         (0x00)
#define RADAR_FAST_CMD_OFF_BIT_OFFSET             (1U)                
#define RADAR_FAST_CMD_OFF_BIT_LEN                (1U)                
#define RADAR_FAST_CMD_OFF_BIT_MASK               0x02U  

#define RADAR_FAST_CMD_EN_BIT_OFFSET              (0U)                
#define RADAR_FAST_CMD_EN_BIT_LEN                 (1U)                
#define RADAR_FAST_CMD_EN_BIT_MASK                0x01U

//******************************************************************************/
// Description: Bit definitions for register radar system control register0
//******************************************************************************/
#define RADAR_SYS_CTRL_REG0_ID                    (0x04)

#define RADAR_SYS_CTRL_PULSEPERIOD_BIT_OFFSET         (16U)                
#define RADAR_SYS_CTRL_PULSEPERIOD_BIT_LEN            (8U)                
#define RADAR_SYS_CTRL_PULSEPERIOD_BIT_MASK           0x00FF0000U  

#define RADAR_SYS_CTRL_CHUNKNUM_BIT_OFFSET         (8U)                
#define RADAR_SYS_CTRL_CHUNKNUM_BIT_LEN            (8U)                
#define RADAR_SYS_CTRL_CHUNKNUM_BIT_MASK           0x0000FF00U  

#define RADAR_SYS_CTRL_DT_BIT_OFFSET             (0U)                
#define RADAR_SYS_CTRL_DT_BIT_LEN                (8U)                
#define RADAR_SYS_CTRL_DT_BIT_MASK               0xFFU

//******************************************************************************/
// Description: Bit definitions for register radar system control register1
//******************************************************************************/
#define RADAR_SYS_CTRL_REG1_ID                       (0x08)

#define RADAR_SYS_CTRL_CHUNKT_BIT_OFFSET             (0U)                
#define RADAR_SYS_CTRL_CHUNKT_BIT_LEN                (32U)                
#define RADAR_SYS_CTRL_CHUNKT_BIT_MASK               0xFFFFFFFFU

//******************************************************************************/
// Description: Bit definitions for register radar system control register2
//******************************************************************************/
#define RADAR_SYS_CTRL_REG2_ID                       (0x0C)

#define RADAR_SYS_CTRL_PULSENUM_BIT_OFFSET             (0U)                
#define RADAR_SYS_CTRL_PULSENUM_BIT_LEN                (16U)                
#define RADAR_SYS_CTRL_PULSENUM_BIT_MASK               0x0000FFFFU

//******************************************************************************/
// Description: Bit definitions for register radar TX register
//******************************************************************************/
#define RADAR_TX_REG_ID                    (0x10)

#define RADAR_TX_REG_CLK500M_SEL_BIT_OFFSET         (11U)                
#define RADAR_TX_REG_CLK500M_SEL_BIT_LEN            (1U)                
#define RADAR_TX_REG_CLK500M_SEL_BIT_MASK           0x00001000U  

#define RADAR_TX_REG_PULSE_POSITION_BIT_OFFSET         (10U)                
#define RADAR_TX_REG_PULSE_POSITION_BIT_LEN            (2U)                
#define RADAR_TX_REG_PULSE_POSITION_BIT_MASK           0x00000C00U  

#define RADAR_TX_REG_PULSE_TYPE_BIT_OFFSET             (9U)                
#define RADAR_TX_REG_PULSE_TYPE_BIT_LEN                (1U)                
#define RADAR_TX_REG_PULSE_TYPE_BIT_MASK               0x00000200U 

#define RADAR_TX_REG_SWFLG_BIT_OFFSET             (8U)                
#define RADAR_TX_REG_SWFLG_BIT_LEN                (1U)                
#define RADAR_TX_REG_SWFLG_BIT_MASK               0x00000100U 

#define RADAR_TX_REG_SWDELAY_BIT_OFFSET             (0U)                
#define RADAR_TX_REG_SWDELAY_BIT_LEN                (8U)                
#define RADAR_TX_REG_SWDELAY_BIT_MASK               0x000000FFU 

//******************************************************************************/
// Description: Bit definitions for register radar rx peak detection registion
//******************************************************************************/
#define RADAR_RX_PEAK_DETECTION_ID                    (0x14)

#define RADAR_PEAK_DETECTION_PHASE_OFFSET_BIT_OFFSET         (25U)                
#define RADAR_PEAK_DETECTION_PHASE_OFFSET_BIT_LEN            (5U)                
#define RADAR_PEAK_DETECTION_PHASE_OFFSET_BIT_MASK           0x3E000000U  

#define RADAR_PEAK_DETECTION_DIS_OFFSET_BIT_OFFSET         (17U)                
#define RADAR_PEAK_DETECTION_DIS_OFFSET_BIT_LEN            (8U)                
#define RADAR_PEAK_DETECTION_DIS_OFFSET_BIT_MASK           0x01FE0000U  

#define RADAR_PEAK_DETECTION_THRESHOLD_BIT_OFFSET             (9U)                
#define RADAR_PEAK_DETECTION_THRESHOLD_BIT_LEN                (8U)                
#define RADAR_PEAK_DETECTION_THRESHOLD_BIT_MASK               0x0001FE00U 

#define RADAR_PEAK_DETECTION_PHASEEN_BIT_OFFSET             (8U)                
#define RADAR_PEAK_DETECTION_PHASEEN_BIT_LEN                (1U)                
#define RADAR_PEAK_DETECTION_PHASEEN_BIT_MASK               0x00000100U 

#define RADAR_PEAK_DETECTION_WINDOW_BIT_OFFSET             (6U)                
#define RADAR_PEAK_DETECTION_WINDOW_BIT_LEN                (2U)                
#define RADAR_PEAK_DETECTION_WINDOW_BIT_MASK               0x000000C0U 

#define RADAR_PEAK_DETECTION_OFFSET_BIT_OFFSET             (1U)                
#define RADAR_PEAK_DETECTION_OFFSET_BIT_LEN                (5U)                
#define RADAR_PEAK_DETECTION_OFFSET_BIT_MASK               0x0000003EU 

#define RADAR_PEAK_DETECTION_EN_BIT_OFFSET             (0U)                
#define RADAR_PEAK_DETECTION_EN_BIT_LEN                (1U)                
#define RADAR_PEAK_DETECTION_EN_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar rx control register
//******************************************************************************/
#define RADAR_RX_CTRL_ID                    (0x18)

#define RADAR_TAP_LEN_BIT_OFFSET         (8U)                
#define RADAR_TAP_LEN_BIT_LEN            (6U)                
#define RADAR_TAP_LEN_BIT_MASK           0x00003F00U  

#define RADAR_ACC_AVEG_NUM_OFFSET_BIT_OFFSET         (2U)                
#define RADAR_ACC_AVEG_NUM_OFFSET_BIT_LEN            (4U)                
#define RADAR_ACC_AVEG_NUM_OFFSET_BIT_MASK           0x0000003CU  

#define RADAR_ACC_AVEG_EN_BIT_OFFSET             (1U)                
#define RADAR_ACC_AVEG_EN_BIT_LEN                (1U)                
#define RADAR_ACC_AVEG_EN_BIT_MASK               0x00000002U 

#define RADAR_ADC_SEL_BIT_OFFSET             (0U)                
#define RADAR_ADC_SEL_BIT_LEN                (1U)                
#define RADAR_ADC_SEL_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar rx memory store register
//******************************************************************************/
#define RADAR_RX_STORE_CTRL_ID                    (0x1C)

#define RADAR_BIT_WIDTH_BIT_OFFSET         (2U)                
#define RADAR_BIT_WIDTH_BIT_LEN            (3U)                
#define RADAR_BIT_WIDTH_BIT_MASK           0x0000001CU  

#define RADAR_STORE_SEQ_MODE_BIT_OFFSET         (1U)                
#define RADAR_STORE_SEQ_MODE_BIT_LEN            (1U)                
#define RADAR_STORE_SEQ_MODE_BIT_MASK           0x00000002U  

#define RADAR_STORE_MODE_BIT_OFFSET             (0U)                
#define RADAR_STORE_MODE_BIT_LEN                (1U)                
#define RADAR_STORE_MODE_BIT_MASK               0x00000001U 


//******************************************************************************/
// Description: Bit definitions for register radar rx ce control register
//******************************************************************************/
#define RADAR_CE_REG_ID                    (0x20)

#define RADAR_CE_TAP_LEN_BIT_OFFSET         (15U)                
#define RADAR_CE_TAP_LEN_BIT_LEN            (5U)                
#define RADAR_CE_TAP_LEN_BIT_MASK           0x000F8000U  

#define RADAR_CE_PULSE_NUM_BIT_OFFSET         (1U)                
#define RADAR_CE_PULSE_NUM_BIT_LEN            (14U)                
#define RADAR_CE_PULSE_NUM_BIT_MASK           0x00007FFEU  

#define RADAR_CE_MODE_BIT_OFFSET             (0U)                
#define RADAR_CE_MODE_BIT_LEN                (1U)                
#define RADAR_CE_MODE_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar rx ce control register1
//******************************************************************************/
#define RADAR_CE_REG1_ID                    (0x24)

#define RADAR_CE_GAP_PULSE_NUM_BIT_OFFSET         (22U)                
#define RADAR_CE_GAP_PULSE_NUM_BIT_LEN            (4U)                
#define RADAR_CE_GAP_PULSE_NUM_BIT_MASK           0x03C00000U  

#define RADAR_MODE1_PEAK_THRESHOLD_BIT_OFFSET             (0U)                
#define RADAR_MODE1_PEAK_THRESHOLD_BIT_LEN                (22U)                
#define RADAR_MODE1_PEAK_THRESHOLD_BIT_MASK               0x003FFFFFU 

//******************************************************************************/
// Description: Bit definitions for register radar interrutpt raw  register
//******************************************************************************/
#define RADAR_INT_RAW_ID                    (0x28)

#define RADAR_AVGE_DONE_RAW_BIT_OFFSET         (4U)                
#define RADAR_AVGE_DONE_RAW_BIT_LEN            (1U)                
#define RADAR_AVGE_DONE_RAW_BIT_MASK           0x00000010U  

#define RADAR_OVER_FLOW_ERR_RAW_BIT_OFFSET         (3U)                
#define RADAR_OVER_FLOW_ERR_RAW_BIT_LEN            (1U)                
#define RADAR_OVER_FLOW_ERR_RAW_BIT_MASK           0x00000008U  

#define RADAR_CONLLISION_ERR_RAW_BIT_OFFSET             (2U)                
#define RADAR_CONLLISION_ERR_RAW_BIT_LEN                (1U)                
#define RADAR_CONLLISION_ERR_RAW_BIT_MASK               0x00000004U 

#define RADAR_RADAR_DONE_PULSE_RAW_BIT_OFFSET             (1U)                
#define RADAR_RADAR_DONE_PULSE_RAW_BIT_LEN                (1U)                
#define RADAR_RADAR_DONE_PULSE_RAW_BIT_MASK               0x00000002U 

#define RADAR_CHUNK_DONE_PULSE_RAW_BIT_OFFSET             (0U)                
#define RADAR_CHUNK_DONE_PULSE_RAW_BIT_LEN                (1U)                
#define RADAR_CHUNK_DONE_PULSE_RAW_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar interrutpt mask register
//******************************************************************************/
#define RADAR_INT_MASK_ID                    (0x30)

#define RADAR_AVGE_DONE_MASK_BIT_OFFSET         (4U)                
#define RADAR_AVGE_DONE_MASK_BIT_LEN            (1U)                
#define RADAR_AVGE_DONE_MASK_BIT_MASK           0x00000010U  

#define RADAR_OVER_FLOW_ERR_MASK_BIT_OFFSET         (3U)                
#define RADAR_OVER_FLOW_ERR_MASK_BIT_LEN            (1U)                
#define RADAR_OVER_FLOW_ERR_MASK_BIT_MASK           0x00000008U  

#define RADAR_CONLLISION_ERR_MASK_BIT_OFFSET             (2U)                
#define RADAR_CONLLISION_ERR_MASK_BIT_LEN                (1U)                
#define RADAR_CONLLISION_ERR_MASK_BIT_MASK               0x00000004U 

#define RADAR_RADAR_DONE_PULSE_MASK_BIT_OFFSET             (1U)                
#define RADAR_RADAR_DONE_PULSE_MASK_BIT_LEN                (1U)                
#define RADAR_RADAR_DONE_PULSE_MASK_BIT_MASK               0x00000002U 

#define RADAR_CHUNK_DONE_PULSE_MASK_BIT_OFFSET             (0U)                
#define RADAR_CHUNK_DONE_PULSE_MASK_BIT_LEN                (1U)                
#define RADAR_CHUNK_DONE_PULSE_MASK_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar interrutpt status register
//******************************************************************************/
#define RADAR_INT_STATUS_ID                    (0x34)

#define RADAR_AVGE_DONE_STATUS_BIT_OFFSET         (4U)                
#define RADAR_AVGE_DONE_STATUS_BIT_LEN            (1U)                
#define RADAR_AVGE_DONE_STATUS_BIT_MASK           0x00000010U  

#define RADAR_OVER_FLOW_ERR_STATUS_BIT_OFFSET         (3U)                
#define RADAR_OVER_FLOW_ERR_STATUS_BIT_LEN            (1U)                
#define RADAR_OVER_FLOW_ERR_STATUS_BIT_MASK           0x00000008U  

#define RADAR_CONLLISION_ERR_STATUS_BIT_OFFSET             (2U)                
#define RADAR_CONLLISION_ERR_STATUS_BIT_LEN                (1U)                
#define RADAR_CONLLISION_ERR_STATUS_BIT_MASK               0x00000004U 

#define RADAR_RADAR_DONE_PULSE_STATUS_BIT_OFFSET             (1U)                
#define RADAR_RADAR_DONE_PULSE_STATUS_BIT_LEN                (1U)                
#define RADAR_RADAR_DONE_PULSE_STATUS_BIT_MASK               0x00000002U 

#define RADAR_CHUNK_DONE_PULSE_STATUS_BIT_OFFSET             (0U)                
#define RADAR_CHUNK_DONE_PULSE_STATUS_BIT_LEN                (1U)                
#define RADAR_CHUNK_DONE_PULSE_STATUS_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar extend control
//******************************************************************************/
#define RADAR_EXTEND_CTRL_REG_ID                    (0x38)

#define RADAR_RX_EXTEND_FLIP_GAP_BIT_OFFSET         (12U)                
#define RADAR_RX_EXTEND_FLIP_GAP_BIT_LEN            (5U)                
#define RADAR_RX_EXTEND_FLIP_GAP_BIT_MASK           0x0001F000U  

#define RADAR_RX_EXTEND_DELAY_BIT_OFFSET         (4U)                
#define RADAR_RX_EXTEND_DELAY_BIT_LEN            (6U)                
#define RADAR_RX_EXTEND_DELAY_BIT_MASK           0x000003F0U  

#define RADAR_PULSE_EXTEND_BIT_OFFSET             (0U)                
#define RADAR_PULSE_EXTEND_BIT_LEN                (1U)                
#define RADAR_PULSE_EXTEND_BIT_MASK               0x00000001U 

//******************************************************************************/
// Description: Bit definitions for register radar extend sequence register
//******************************************************************************/
#define RADAR_EXTEND_SEQ_REG_ID                    (0x3C)


#define RADAR_EXTEND_SEQ_BIT_OFFSET             (0U)                
#define RADAR_EXTEND_SEQ_BIT_LEN                (16U)                
#define RADAR_EXTEND_SEQ_BIT_MASK               0x0000FFFFU 


//******************************************************************************/
// Description: Bit definitions for register radar acc data output disable register
//******************************************************************************/
#define ACC_DATA_DISABLE_REG_ID                    (0x40)


#define RADAR_P2S_EN_BIT_OFFSET             (1U)                
#define RADAR_P2S_EN_BIT_LEN                (1U)                
#define RADAR_P2S_EN_BIT_MASK               0x00000002U 

#define RADAR_ACC_DATA_DISABLE_BIT_OFFSET             (0U)                
#define RADAR_ACC_DATA_DISABLE_BIT_LEN                (1U)                
#define RADAR_ACC_DATA_DISABLE_BIT_MASK               0x00000001U 



#endif