/*****************************************************************************
 *  File: zn_dma.c
 *
 *  Descirption: this file contains the functions support dma operations.
 *
 *  Copyright (C) : 2023 ultraception.com
 *
 *  Author: wjy
 *  Mail:   
 *  Date:   2023-6-1
 *
 *****************************************************************************/

#include "zn_dma.h"

static DMA_CallbackType dma_callbackFunc = {(DMA_CallbackType)NULL};

/**
 * DMA0_IRQHandler
 *
 * @param none
 * @return none
 *
 * @brief Interrupt service routine for DMA0
 */
void DMA0_IRQHandler(void)
{
    uint32_t tmp32[3] = {0};
    
    /*read tfr interrupt status,then clear interrupt*/
    tmp32[0] = read_mreg32(DMAC_STATUSTFR(0));
    write_mreg32(DMAC_CLEARTFR(0), tmp32[0]);
    
    /*read block interrupt status,then clear interrupt*/
    tmp32[1] = read_mreg32(DMAC_STATUSBLOCK(0));
    write_mreg32(DMAC_CLEARBLOCK(0), tmp32[1]);
    
    /*read error interrupt status,then clear interrupt*/
    tmp32[2] = read_mreg32(DMAC_STATUSERR(0));
    write_mreg32(DMAC_CLEARERR(0), tmp32[2]);
    if (dma_callbackFunc)
    {
        dma_callbackFunc(tmp32);
    }
}

/**
 * dma_interrupt_en
 *
 * @param[in]  id: DMA channel ID
 * @param[in]  type: DMA interrupt type (TFR, BLOCK, ERROR)
 * @return 0 if successful, -1 if there is an interrupt pending
 *
 * @brief Enable DMA interrupts for a specific DMA channel and interrupt type
 */
int dma_interrupt_en(uint32_t id, DMA_IntType type)
{
    uint32_t tmp32 = 0;

    /*clear DMAC interrupt */
    write_mreg32(DMAC_CLEARTFR(id), DMAC_ALL_MASK);
    write_mreg32(DMAC_CLEARBLOCK(id), DMAC_ALL_MASK);
    write_mreg32(DMAC_CLEARSRCTRAN(id), DMAC_ALL_MASK);
    write_mreg32(DMAC_CLEARDSTTRAN(id), DMAC_ALL_MASK);
    write_mreg32(DMAC_CLEARERR(id), DMAC_ALL_MASK);
    
    /*check DMAC interrupt status */
    tmp32 = read_mreg32(DMAC_STATUSINT(id));

    if (tmp32 != 0)
    {
        return -1;
    }

    write_mreg32(DMAC_MASKTFR(id), (DMAC_ALL_MASK << 8));    // disable transfer int
    write_mreg32(DMAC_MASKBLOCK(id), (DMAC_ALL_MASK << 8));    // disable block int
    write_mreg32(DMAC_MASKSRCTRAN(id), (DMAC_ALL_MASK << 8)); // disable srctran int
    write_mreg32(DMAC_MASKDSTTRAN(id), (DMAC_ALL_MASK << 8)); // disable dsttran int
    write_mreg32(DMAC_MASKERR(id), (DMAC_ALL_MASK << 8));    // disable error int

    if ((type & DMAC_INTERRUPT_BLOCK) != 0)
    {
        write_mreg32(DMAC_MASKBLOCK(id), (DMAC_ALL_MASK | (DMAC_ALL_MASK << 8)));
    }

    if ((type & DMAC_INTERRUPT_TFR) != 0)
    {
        write_mreg32(DMAC_MASKTFR(id), (DMAC_ALL_MASK | (DMAC_ALL_MASK << 8)));
    }

    if ((type & DMAC_INTERRUPT_ERROR) != 0)
    {
        write_mreg32(DMAC_MASKERR(id), (DMAC_ALL_MASK | (DMAC_ALL_MASK << 8)));
    }
    
    return 0;
}


/**
 * dma_chan_config
 *
 * @param[in]  id: DMA channel ID
 * @param[in]  channel: pointer to DMA channel information structure
 * @param[in]  channel_number: DMA channel number (0-3)
 * @param[in]  BlockSize: DMA block size
 * @return 0 if successful, -1 if channel_number is invalid, -2 if BlockSize is too large, -3 if the channel is already in use
 *
 * @brief Configure a DMA channel with the provided information
 */
int dma_chan_config(uint32_t id, DMA_ChanInfo *channel, uint8_t channel_number, uint16_t BlockSize)
{
    uint32_t tmp32 = 0;
    uint32_t max_blk_size = 0;

    /*check if the channel exist*/
    if (channel_number > DMAC_NUM_CHANNELS-1)
    {
        return -1; /*channel is not 0,1,2,3*/
    }

    if (BlockSize > DMA_MAX_BLK_SIZE)
    {
        return -2;  /*Block Size too large*/
    }
        
    tmp32 = read_mreg32(DMAC_CHENREG(id));
    if ((tmp32 & (1 << channel_number)) != 0)
    {
        return -3;  /*this channel is used*/
    }

    write_mreg32(DMAC_SAR(id, channel_number), channel->sarx);
    write_mreg32(DMAC_DAR(id, channel_number), channel->darx);
    write_mreg32(DMAC_CTLH(id, channel_number), (uint32_t)(BlockSize));
    write_mreg32(DMAC_CTL(id, channel_number), channel->ctlLx);
    write_mreg32(DMAC_CFGH(id, channel_number), channel->cfgHx);
    write_mreg32(DMAC_CFG(id, channel_number), channel->cfgLx);
    write_mreg32(DMAC_LLP(id, channel_number), channel->llpx);
    
    return 0;
}

/**
 * dma_chan_start
 *
 * @param[in]  id: DMA channel ID
 * @param[in]  channel_number: DMA channel number (0-3)
 * @return none
 *
 * @brief Start a DMA channel
 */
void dma_chan_start(uint32_t id, uint8_t channel_number)
{
    write_mreg32(DMAC_CHENREG(id), read_mreg32(DMAC_CHENREG(id))|DMAC_CH_EN(channel_number));
}

/**
* dma_chan_close
*
* @param[in]  id: DMA channel ID
* @param[in]  channel_number: DMA channel number (0-3)
* @return none
*
* @brief Close a DMA channel
*/
void dma_chan_close(uint32_t id, uint8_t channel_number)
{
    //clear software request
    write_mreg32(DMAC_REQSRCREG(id), DMAC_SW_REQ_DIS(channel_number));
    write_mreg32(DMAC_REQDSTREG(id), DMAC_SW_REQ_DIS(channel_number));
    write_mreg32(DMAC_SGLRQSRCREG(id), DMAC_SW_REQ_DIS(channel_number));
    write_mreg32(DMAC_SGLRQDSTREG(id), DMAC_SW_REQ_DIS(channel_number));
    write_mreg32(DMAC_LSTSRCREG(id), DMAC_SW_REQ_DIS(channel_number));
    write_mreg32(DMAC_LSTDSTREG(id), DMAC_SW_REQ_DIS(channel_number));
    //disable DMAC cread_mreg32(DMAC_CHENREG(id))hannel
    write_mreg32(DMAC_CHENREG(id), read_mreg32(DMAC_CHENREG(id))|DMAC_CH_DIS(channel_number));
    //clear DMAC interrupt
    write_mreg32(DMAC_CLEARTFR(id), DMAC_INT_CLR(channel_number));
    write_mreg32(DMAC_CLEARBLOCK(id), DMAC_INT_CLR(channel_number));
    write_mreg32(DMAC_CLEARSRCTRAN(id), DMAC_INT_CLR(channel_number));
    write_mreg32(DMAC_CLEARDSTTRAN(id), DMAC_INT_CLR(channel_number));
    write_mreg32(DMAC_CLEARERR(id), DMAC_INT_CLR(channel_number));
    //disable DMAC interrupt
    write_mreg32(DMAC_MASKTFR(id), DMAC_INT_MASK(channel_number));
    write_mreg32(DMAC_MASKBLOCK(id), DMAC_INT_MASK(channel_number));
    write_mreg32(DMAC_MASKSRCTRAN(id), DMAC_INT_MASK(channel_number));
    write_mreg32(DMAC_MASKDSTTRAN(id), DMAC_INT_MASK(channel_number));
    write_mreg32(DMAC_MASKERR(id), DMAC_INT_MASK(channel_number));
}

/**
* dma_chan_set_fifo_mode
*
* @param[in]  id: DMA channel ID
* @param[in]  channel_number: DMA channel number (0-3)
* @return none
*
* @brief Set DMA channel to FIFO mode
*/
void dma_chan_set_fifo_mode(uint32_t id, uint8_t channel_number)
{
    uint32_t reg = 0;
    reg = read_mreg32(DMAC_CFGH(id, channel_number));
    write_mreg32(DMAC_CFGH(id, channel_number), reg | DMAC_CFG_FIFO_MODE_1);
}

/**
* dma_chan_check_done_poll
*
* @param[in]  id: DMA channel ID
* @param[in]  channel_number: DMA channel number (0-3)
* @return TRUE if DMA transfer is complete, FALSE otherwise
*
* @brief Check if DMA transfer is complete using polling
*/
BOOL_Type dma_chan_check_done_poll(uint32_t id, uint8_t channel_number)
{
    uint32_t timeout = 0;
    uint32_t tmp32 = 0;
    BOOL_Type ret = TRUE;
    tmp32 = read_mreg32(DMAC_RAWTFR(id));
    tmp32 &= (1 << channel_number);

    if (tmp32 != 0)
    {
        write_mreg32(DMAC_CLEARTFR(id), tmp32);
        tmp32 = read_mreg32(DMAC_STATUSBLOCK(id));
        if ((tmp32 & (1 << channel_number)) != 0)
        {              
           ret = FALSE;
        }
    }
    else
    {
        ret = FALSE;
    }
    
    return ret;
}
/**
* dma_init
*
* @param[in]  id: DMA channel ID
* @param[in]  config: pointer to DMA_ConfigType structure
* @return 0 if successful, non-zero otherwise
*
* @brief Initialize DMA controller
*/
int dma_init(uint32_t id, DMA_ConfigType *config)
{
    /*only one DMA controller, here id is 0*/
    
    /*enable DMAC*/
    write_mreg32(DMAC_DMACFGREG(id), DMAC_EN);
    
    /*enable DMAC to normal mode*/
    write_mreg32(DMAC_DMATESTREG(id), DMAC_NORMAL_MODE);

    /*clear software request*/
    write_mreg32(DMAC_REQSRCREG(id), (DMAC_ALL_MASK << 8));
    write_mreg32(DMAC_REQDSTREG(id), (DMAC_ALL_MASK << 8));
    write_mreg32(DMAC_SGLRQSRCREG(id), (DMAC_ALL_MASK << 8));
    write_mreg32(DMAC_SGLRQDSTREG(id), (DMAC_ALL_MASK << 8));
    write_mreg32(DMAC_LSTSRCREG(id), (DMAC_ALL_MASK << 8));
    write_mreg32(DMAC_LSTDSTREG(id), (DMAC_ALL_MASK << 8));

    /*disable DMAC  all channel*/
    write_mreg32(DMAC_CHENREG(id), (DMAC_ALL_MASK << 8));
    if (config->interruptEn)
    {    
        dma_callbackFunc = config->callBack;
        NVIC_EnableIRQ(config->irq);
        return dma_interrupt_en(id, config->interruptType);
    }
    return 0;
}

/**
* dma_chan_init
*
* @param[in]  id: DMA channel ID
* @param[in]  chConfig: pointer to DMA_ChConfigType structure
* @return 0 if successful, -1 if transfer direction is invalid
*
* @brief Initialize DMA channel with the provided configuration
*/
int dma_chan_init(uint32_t id, DMA_ChConfigType *chConfig)
{
    /*only one DMA controller, here id is 0*/
    DMA_ChanInfo channel_info = {0};
    uint8_t transferType = 0;
    channel_info.sarx = chConfig->srcAddr;
    channel_info.darx = chConfig->destAddr;
    channel_info.ctlHx = chConfig->blockCnt;
    channel_info.llpx = chConfig->llpx;
    switch (chConfig->transferDir)
    {
        case DMA_MEM_TO_MEM:
            channel_info.ctlLx |= DMAC_CTL_M2M_DW;
            channel_info.cfgLx |= (DMAC_CFG_HS_SRC_SOFTWARE | DMAC_CFG_HS_DST_SOFTWARE |
                                   DMAC_CFG_SRC_HS_POL_H | DMAC_CFG_SRC_HS_POL_H |
                                   DMAC_CFG_CH_PRIOR(chConfig->priority));

            break;
        case DMA_MEM_TO_UART0_TX:
        case DMA_MEM_TO_UART1_TX:
        case DMA_MEM_TO_I2C0_TX:
        case DMA_MEM_TO_I2C1_TX:
        case DMA_MEM_TO_SPI0_TX:
        case DMA_MEM_TO_SPI1_TX:
            channel_info.ctlLx |= DMAC_CTL_M2P_DW;
            channel_info.cfgLx |= (DMAC_CFG_HS_SRC_SOFTWARE | DMAC_CFG_HS_DST_HARDWARE |
                                   DMAC_CFG_SRC_HS_POL_H | DMAC_CFG_SRC_HS_POL_H |
                                   DMAC_CFG_CH_PRIOR(chConfig->priority));
            channel_info.cfgHx |= DMAC_CFG_DEST_PER(chConfig->transferDir);
            break;
        case DMA_UART0_RX_TO_MEM:
        case DMA_UART1_RX_TO_MEM:
        case DMA_I2C0_RX_TO_MEM:
        case DMA_I2C1_RX_TO_MEM:
        case DMA_SPI0_RX_TO_MEM:
        case DMA_SPI1_RX_TO_MEM:
            channel_info.ctlLx |= DMAC_CTL_P2M_DW;
            channel_info.cfgLx |= (DMAC_CFG_HS_SRC_HARDWARE | DMAC_CFG_HS_DST_SOFTWARE |
                                   DMAC_CFG_SRC_HS_POL_H | DMAC_CFG_SRC_HS_POL_H |
                                   DMAC_CFG_CH_PRIOR(chConfig->priority));
            channel_info.cfgHx = DMAC_CFG_SRC_PER(chConfig->transferDir);
            break;
        default:
            return -1;
            break;
    }

    channel_info.ctlLx |= (chConfig->srcMsize<<DMAC_CTL_SRC_MSIZE_POS) ;
    channel_info.ctlLx |= (chConfig->destMsize << DMAC_CTL_DEST_MSIZE_POS);
    channel_info.ctlLx |= (chConfig->srcAddrInc << DMAC_CTL_SINC_POS);
    channel_info.ctlLx |= (chConfig->destAddrInc << DMAC_CTL_DINC_POS);
    channel_info.ctlLx |= (chConfig->srcTrWidth << DMAC_CTL_SRC_TR_WIDTH_POS);
    channel_info.ctlLx |= (chConfig->destTrWidth << DMAC_CTL_DST_TR_WIDTH_POS);
    
    channel_info.cfgLx |= (DMAC_CFG_RELOAD_SRC(chConfig->srcReload) | DMAC_CFG_RELOAD_DST(chConfig->destReload));
    
    
    if (chConfig->interruptEn)
    {
        channel_info.ctlLx |= DMAC_CTL_INT_EN;
    }
    return dma_chan_config(id, &channel_info, chConfig->channel, chConfig->blockCnt);
}