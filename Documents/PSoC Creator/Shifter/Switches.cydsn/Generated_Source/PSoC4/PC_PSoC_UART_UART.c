/*******************************************************************************
* File Name: PC_PSoC_UART_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PC_PSoC_UART_PVT.h"
#include "PC_PSoC_UART_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if(PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const PC_PSoC_UART_UART_INIT_STRUCT PC_PSoC_UART_configUart =
    {
        PC_PSoC_UART_UART_SUB_MODE,
        PC_PSoC_UART_UART_DIRECTION,
        PC_PSoC_UART_UART_DATA_BITS_NUM,
        PC_PSoC_UART_UART_PARITY_TYPE,
        PC_PSoC_UART_UART_STOP_BITS_NUM,
        PC_PSoC_UART_UART_OVS_FACTOR,
        PC_PSoC_UART_UART_IRDA_LOW_POWER,
        PC_PSoC_UART_UART_MEDIAN_FILTER_ENABLE,
        PC_PSoC_UART_UART_RETRY_ON_NACK,
        PC_PSoC_UART_UART_IRDA_POLARITY,
        PC_PSoC_UART_UART_DROP_ON_PARITY_ERR,
        PC_PSoC_UART_UART_DROP_ON_FRAME_ERR,
        PC_PSoC_UART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        PC_PSoC_UART_UART_MP_MODE_ENABLE,
        PC_PSoC_UART_UART_MP_ACCEPT_ADDRESS,
        PC_PSoC_UART_UART_MP_RX_ADDRESS,
        PC_PSoC_UART_UART_MP_RX_ADDRESS_MASK,
        (uint32) PC_PSoC_UART_SCB_IRQ_INTERNAL,
        PC_PSoC_UART_UART_INTR_RX_MASK,
        PC_PSoC_UART_UART_RX_TRIGGER_LEVEL,
        PC_PSoC_UART_UART_INTR_TX_MASK,
        PC_PSoC_UART_UART_TX_TRIGGER_LEVEL,
        (uint8) PC_PSoC_UART_UART_BYTE_MODE_ENABLE,
        (uint8) PC_PSoC_UART_UART_CTS_ENABLE,
        (uint8) PC_PSoC_UART_UART_CTS_POLARITY,
        (uint8) PC_PSoC_UART_UART_RTS_POLARITY,
        (uint8) PC_PSoC_UART_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PSoC_UART_UartInit(const PC_PSoC_UART_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (PC_PSoC_UART_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (PC_PSoC_UART_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1) */

            /* Configure pins */
            PC_PSoC_UART_SetPins(PC_PSoC_UART_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            PC_PSoC_UART_scbMode       = (uint8) PC_PSoC_UART_SCB_MODE_UART;
            PC_PSoC_UART_scbEnableWake = (uint8) config->enableWake;
            PC_PSoC_UART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            PC_PSoC_UART_rxBuffer      =         config->rxBuffer;
            PC_PSoC_UART_rxDataBits    = (uint8) config->dataBits;
            PC_PSoC_UART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            PC_PSoC_UART_txBuffer      =         config->txBuffer;
            PC_PSoC_UART_txDataBits    = (uint8) config->dataBits;
            PC_PSoC_UART_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(PC_PSoC_UART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                PC_PSoC_UART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (PC_PSoC_UART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (PC_PSoC_UART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                PC_PSoC_UART_CTRL_REG  = PC_PSoC_UART_GET_CTRL_OVS(config->oversample);
            }

            PC_PSoC_UART_CTRL_REG     |= PC_PSoC_UART_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             PC_PSoC_UART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             PC_PSoC_UART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            PC_PSoC_UART_UART_CTRL_REG = PC_PSoC_UART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            PC_PSoC_UART_UART_RX_CTRL_REG = PC_PSoC_UART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        PC_PSoC_UART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        PC_PSoC_UART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        PC_PSoC_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        PC_PSoC_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(PC_PSoC_UART_UART_PARITY_NONE != config->parity)
            {
               PC_PSoC_UART_UART_RX_CTRL_REG |= PC_PSoC_UART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    PC_PSoC_UART_UART_RX_CTRL_PARITY_ENABLED;
            }

            PC_PSoC_UART_RX_CTRL_REG      = PC_PSoC_UART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                PC_PSoC_UART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                PC_PSoC_UART_GET_UART_RX_CTRL_ENABLED(config->direction);

            PC_PSoC_UART_RX_FIFO_CTRL_REG = PC_PSoC_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            PC_PSoC_UART_RX_MATCH_REG     = PC_PSoC_UART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                PC_PSoC_UART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            PC_PSoC_UART_UART_TX_CTRL_REG = PC_PSoC_UART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                PC_PSoC_UART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(PC_PSoC_UART_UART_PARITY_NONE != config->parity)
            {
               PC_PSoC_UART_UART_TX_CTRL_REG |= PC_PSoC_UART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    PC_PSoC_UART_UART_TX_CTRL_PARITY_ENABLED;
            }

            PC_PSoC_UART_TX_CTRL_REG      = PC_PSoC_UART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                PC_PSoC_UART_GET_UART_TX_CTRL_ENABLED(config->direction);

            PC_PSoC_UART_TX_FIFO_CTRL_REG = PC_PSoC_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1)
            PC_PSoC_UART_UART_FLOW_CTRL_REG = PC_PSoC_UART_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            PC_PSoC_UART_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            PC_PSoC_UART_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            PC_PSoC_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (PC_PSoC_UART_ISR_NUMBER);
            CyIntSetPriority(PC_PSoC_UART_ISR_NUMBER, PC_PSoC_UART_ISR_PRIORITY);
            (void) CyIntSetVector(PC_PSoC_UART_ISR_NUMBER, &PC_PSoC_UART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(PC_PSoC_UART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (PC_PSoC_UART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(PC_PSoC_UART_RX_WAKE_ISR_NUMBER, PC_PSoC_UART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(PC_PSoC_UART_RX_WAKE_ISR_NUMBER, &PC_PSoC_UART_UART_WAKEUP_ISR);
        #endif /* (PC_PSoC_UART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            PC_PSoC_UART_INTR_I2C_EC_MASK_REG = PC_PSoC_UART_NO_INTR_SOURCES;
            PC_PSoC_UART_INTR_SPI_EC_MASK_REG = PC_PSoC_UART_NO_INTR_SOURCES;
            PC_PSoC_UART_INTR_SLAVE_MASK_REG  = PC_PSoC_UART_NO_INTR_SOURCES;
            PC_PSoC_UART_INTR_MASTER_MASK_REG = PC_PSoC_UART_NO_INTR_SOURCES;
            PC_PSoC_UART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            PC_PSoC_UART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            PC_PSoC_UART_rxBufferHead     = 0u;
            PC_PSoC_UART_rxBufferTail     = 0u;
            PC_PSoC_UART_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            PC_PSoC_UART_txBufferHead = 0u;
            PC_PSoC_UART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PSoC_UART_UartInit(void)
    {
        /* Configure UART interface */
        PC_PSoC_UART_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        PC_PSoC_UART_UART_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        PC_PSoC_UART_UART_RX_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_UART_RX_CTRL;
        PC_PSoC_UART_RX_CTRL_REG      = PC_PSoC_UART_UART_DEFAULT_RX_CTRL;
        PC_PSoC_UART_RX_FIFO_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_RX_FIFO_CTRL;
        PC_PSoC_UART_RX_MATCH_REG     = PC_PSoC_UART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        PC_PSoC_UART_UART_TX_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_UART_TX_CTRL;
        PC_PSoC_UART_TX_CTRL_REG      = PC_PSoC_UART_UART_DEFAULT_TX_CTRL;
        PC_PSoC_UART_TX_FIFO_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1)
        PC_PSoC_UART_UART_FLOW_CTRL_REG = PC_PSoC_UART_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(PC_PSoC_UART_SCB_IRQ_INTERNAL)
        CyIntDisable    (PC_PSoC_UART_ISR_NUMBER);
        CyIntSetPriority(PC_PSoC_UART_ISR_NUMBER, PC_PSoC_UART_ISR_PRIORITY);
        (void) CyIntSetVector(PC_PSoC_UART_ISR_NUMBER, &PC_PSoC_UART_SPI_UART_ISR);
    #endif /* (PC_PSoC_UART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(PC_PSoC_UART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (PC_PSoC_UART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(PC_PSoC_UART_RX_WAKE_ISR_NUMBER, PC_PSoC_UART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(PC_PSoC_UART_RX_WAKE_ISR_NUMBER, &PC_PSoC_UART_UART_WAKEUP_ISR);
    #endif /* (PC_PSoC_UART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        PC_PSoC_UART_INTR_I2C_EC_MASK_REG = PC_PSoC_UART_UART_DEFAULT_INTR_I2C_EC_MASK;
        PC_PSoC_UART_INTR_SPI_EC_MASK_REG = PC_PSoC_UART_UART_DEFAULT_INTR_SPI_EC_MASK;
        PC_PSoC_UART_INTR_SLAVE_MASK_REG  = PC_PSoC_UART_UART_DEFAULT_INTR_SLAVE_MASK;
        PC_PSoC_UART_INTR_MASTER_MASK_REG = PC_PSoC_UART_UART_DEFAULT_INTR_MASTER_MASK;
        PC_PSoC_UART_INTR_RX_MASK_REG     = PC_PSoC_UART_UART_DEFAULT_INTR_RX_MASK;
        PC_PSoC_UART_INTR_TX_MASK_REG     = PC_PSoC_UART_UART_DEFAULT_INTR_TX_MASK;

    #if(PC_PSoC_UART_INTERNAL_RX_SW_BUFFER_CONST)
        PC_PSoC_UART_rxBufferHead     = 0u;
        PC_PSoC_UART_rxBufferTail     = 0u;
        PC_PSoC_UART_rxBufferOverflow = 0u;
    #endif /* (PC_PSoC_UART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(PC_PSoC_UART_INTERNAL_TX_SW_BUFFER_CONST)
        PC_PSoC_UART_txBufferHead = 0u;
        PC_PSoC_UART_txBufferTail = 0u;
    #endif /* (PC_PSoC_UART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: PC_PSoC_UART_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_PSoC_UART_UartPostEnable(void)
{
#if (PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG)

#if (PC_PSoC_UART_TX_SCL_MISO_PIN)
    if (PC_PSoC_UART_CHECK_TX_SCL_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_TX_SCL_MISO_HSIOM_REG, PC_PSoC_UART_TX_SCL_MISO_HSIOM_MASK,
                                       PC_PSoC_UART_TX_SCL_MISO_HSIOM_POS, PC_PSoC_UART_HSIOM_UART_SEL);
    }
#endif /* (PC_PSoC_UART_TX_SCL_MISO_PIN_PIN) */

#if (PC_PSoC_UART_RTS_SS0_PIN)
    if (PC_PSoC_UART_CHECK_RTS_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_RTS_SS0_HSIOM_REG, PC_PSoC_UART_RTS_SS0_HSIOM_MASK,
                                       PC_PSoC_UART_RTS_SS0_HSIOM_POS, PC_PSoC_UART_HSIOM_UART_SEL);
    }
#endif /* (PC_PSoC_UART_RTS_SS0_PIN) */

#else
#if (PC_PSoC_UART_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_TX_HSIOM_REG, PC_PSoC_UART_TX_HSIOM_MASK,
                                   PC_PSoC_UART_TX_HSIOM_POS, PC_PSoC_UART_HSIOM_UART_SEL);
#endif /* (PC_PSoC_UART_UART_TX_PIN) */

#if (PC_PSoC_UART_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_RTS_HSIOM_REG, PC_PSoC_UART_RTS_HSIOM_MASK,
                                   PC_PSoC_UART_RTS_HSIOM_POS, PC_PSoC_UART_HSIOM_UART_SEL);
#endif /* (PC_PSoC_UART_UART_RTS_PIN) */

#endif /* (PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: PC_PSoC_UART_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PC_PSoC_UART_UartStop(void)
{
#if(PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (PC_PSoC_UART_TX_SCL_MISO_PIN)
        if (PC_PSoC_UART_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_TX_SCL_MISO_HSIOM_REG, PC_PSoC_UART_TX_SCL_MISO_HSIOM_MASK,
                                           PC_PSoC_UART_TX_SCL_MISO_HSIOM_POS, PC_PSoC_UART_HSIOM_GPIO_SEL);
        }
    #endif /* (PC_PSoC_UART_TX_SCL_MISO_PIN_PIN) */

    #if (PC_PSoC_UART_RTS_SS0_PIN)
        if (PC_PSoC_UART_CHECK_RTS_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            PC_PSoC_UART_uart_rts_spi_ss0_Write(PC_PSoC_UART_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_RTS_SS0_HSIOM_REG, PC_PSoC_UART_RTS_SS0_HSIOM_MASK,
                                           PC_PSoC_UART_RTS_SS0_HSIOM_POS, PC_PSoC_UART_HSIOM_GPIO_SEL);
        }
    #endif /* (PC_PSoC_UART_SS0_PIN) */

#else
    #if (PC_PSoC_UART_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_TX_HSIOM_REG, PC_PSoC_UART_TX_HSIOM_MASK,
                                       PC_PSoC_UART_TX_HSIOM_POS, PC_PSoC_UART_HSIOM_GPIO_SEL);
    #endif /* (PC_PSoC_UART_UART_TX_PIN) */

    #if (PC_PSoC_UART_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        PC_PSoC_UART_rts_Write(PC_PSoC_UART_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        PC_PSoC_UART_SET_HSIOM_SEL(PC_PSoC_UART_RTS_HSIOM_REG, PC_PSoC_UART_RTS_HSIOM_MASK,
                                       PC_PSoC_UART_RTS_HSIOM_POS, PC_PSoC_UART_HSIOM_GPIO_SEL);
    #endif /* (PC_PSoC_UART_UART_RTS_PIN) */

#endif /* (PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (PC_PSoC_UART_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    PC_PSoC_UART_UART_RX_CTRL_REG &= (uint32) ~PC_PSoC_UART_UART_RX_CTRL_SKIP_START;
#endif /* (PC_PSoC_UART_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: PC_PSoC_UART_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void PC_PSoC_UART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = PC_PSoC_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~PC_PSoC_UART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & PC_PSoC_UART_RX_MATCH_ADDR_MASK)); /* Set address  */

    PC_PSoC_UART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: PC_PSoC_UART_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void PC_PSoC_UART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = PC_PSoC_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~PC_PSoC_UART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << PC_PSoC_UART_RX_MATCH_MASK_POS));

    PC_PSoC_UART_RX_MATCH_REG = matchReg;
}


#if(PC_PSoC_UART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 PC_PSoC_UART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != PC_PSoC_UART_SpiUartGetRxBufferSize())
        {
            rxData = PC_PSoC_UART_SpiUartReadRxData();
        }

        if (PC_PSoC_UART_CHECK_INTR_RX(PC_PSoC_UART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            PC_PSoC_UART_ClearRxInterruptSource(PC_PSoC_UART_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 PC_PSoC_UART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (PC_PSoC_UART_CHECK_RX_SW_BUFFER)
        {
            PC_PSoC_UART_DisableInt();
        }
        #endif

        if (0u != PC_PSoC_UART_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (PC_PSoC_UART_CHECK_RX_SW_BUFFER)
            {            
                PC_PSoC_UART_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = PC_PSoC_UART_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = PC_PSoC_UART_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (PC_PSoC_UART_CHECK_RX_SW_BUFFER)
            {
                PC_PSoC_UART_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (PC_PSoC_UART_GetRxInterruptSource() & PC_PSoC_UART_INTR_RX_ERR);
        PC_PSoC_UART_ClearRxInterruptSource(PC_PSoC_UART_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: PC_PSoC_UART_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   PC_PSoC_UART_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   PC_PSoC_UART_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PC_PSoC_UART_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                PC_PSoC_UART_UART_FLOW_CTRL_REG |= (uint32)  PC_PSoC_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                PC_PSoC_UART_UART_FLOW_CTRL_REG &= (uint32) ~PC_PSoC_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: PC_PSoC_UART_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PC_PSoC_UART_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = PC_PSoC_UART_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~PC_PSoC_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (PC_PSoC_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            PC_PSoC_UART_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1) */

#endif /* (PC_PSoC_UART_UART_RX_DIRECTION) */


#if(PC_PSoC_UART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PSoC_UART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            PC_PSoC_UART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PSoC_UART_UartPutCRLF(uint32 txDataByte)
    {
        PC_PSoC_UART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        PC_PSoC_UART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        PC_PSoC_UART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: PC_PSoC_UARTSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PC_PSoC_UART_UartEnableCts(void)
        {
            PC_PSoC_UART_UART_FLOW_CTRL_REG |= (uint32)  PC_PSoC_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: PC_PSoC_UART_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PC_PSoC_UART_UartDisableCts(void)
        {
            PC_PSoC_UART_UART_FLOW_CTRL_REG &= (uint32) ~PC_PSoC_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: PC_PSoC_UART_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   PC_PSoC_UART_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   PC_PSoC_UART_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PC_PSoC_UART_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                PC_PSoC_UART_UART_FLOW_CTRL_REG |= (uint32)  PC_PSoC_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                PC_PSoC_UART_UART_FLOW_CTRL_REG &= (uint32) ~PC_PSoC_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(PC_PSoC_UART_CY_SCBIP_V0 || PC_PSoC_UART_CY_SCBIP_V1) */

#endif /* (PC_PSoC_UART_UART_TX_DIRECTION) */


#if(PC_PSoC_UART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PSoC_UART_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        PC_PSoC_UART_UART_RX_CTRL_REG |= PC_PSoC_UART_UART_RX_CTRL_SKIP_START;

    #if(PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(PC_PSoC_UART_MOSI_SCL_RX_WAKE_PIN)
            (void) PC_PSoC_UART_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt();
        #endif /* (PC_PSoC_UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(PC_PSoC_UART_UART_RX_WAKE_PIN)
            (void) PC_PSoC_UART_rx_wake_ClearInterrupt();
        #endif /* (PC_PSoC_UART_UART_RX_WAKE_PIN) */
    #endif /* (PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(PC_PSoC_UART_UART_RX_WAKEUP_IRQ)
        PC_PSoC_UART_RxWakeClearPendingInt();
        PC_PSoC_UART_RxWakeEnableInt();
    #endif /* (PC_PSoC_UART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PC_PSoC_UART_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(PC_PSoC_UART_UART_RX_WAKEUP_IRQ)
        PC_PSoC_UART_RxWakeDisableInt();
    #endif /* (PC_PSoC_UART_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (PC_PSoC_UART_UART_WAKE_ENABLE_CONST) */


#if(PC_PSoC_UART_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: PC_PSoC_UART_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(PC_PSoC_UART_UART_WAKEUP_ISR)
    {
    #ifdef PC_PSoC_UART_UART_WAKEUP_ISR_ENTRY_CALLBACK
        PC_PSoC_UART_UART_WAKEUP_ISR_EntryCallback();
    #endif /* PC_PSoC_UART_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by PC_PSoC_UART_UartRestoreConfig() call.
        */
    #if(PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(PC_PSoC_UART_MOSI_SCL_RX_WAKE_PIN)
            (void) PC_PSoC_UART_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt();
        #endif /* (PC_PSoC_UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(PC_PSoC_UART_UART_RX_WAKE_PIN)
            (void) PC_PSoC_UART_rx_wake_ClearInterrupt();
        #endif /* (PC_PSoC_UART_UART_RX_WAKE_PIN) */
    #endif /* (PC_PSoC_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef PC_PSoC_UART_UART_WAKEUP_ISR_EXIT_CALLBACK
        PC_PSoC_UART_UART_WAKEUP_ISR_ExitCallback();
    #endif /* PC_PSoC_UART_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (PC_PSoC_UART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
