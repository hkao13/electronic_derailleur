/*******************************************************************************
* File Name: hbridge_driver.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the hbridge_driver
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_hbridge_driver_H)
#define CY_TCPWM_hbridge_driver_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} hbridge_driver_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  hbridge_driver_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define hbridge_driver_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define hbridge_driver_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define hbridge_driver_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define hbridge_driver_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define hbridge_driver_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define hbridge_driver_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define hbridge_driver_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define hbridge_driver_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define hbridge_driver_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define hbridge_driver_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define hbridge_driver_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define hbridge_driver_TC_RUN_MODE                    (0lu)
#define hbridge_driver_TC_COUNTER_MODE                (0lu)
#define hbridge_driver_TC_COMP_CAP_MODE               (2lu)
#define hbridge_driver_TC_PRESCALER                   (0lu)

/* Signal modes */
#define hbridge_driver_TC_RELOAD_SIGNAL_MODE          (0lu)
#define hbridge_driver_TC_COUNT_SIGNAL_MODE           (3lu)
#define hbridge_driver_TC_START_SIGNAL_MODE           (0lu)
#define hbridge_driver_TC_STOP_SIGNAL_MODE            (0lu)
#define hbridge_driver_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define hbridge_driver_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define hbridge_driver_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define hbridge_driver_TC_START_SIGNAL_PRESENT        (0lu)
#define hbridge_driver_TC_STOP_SIGNAL_PRESENT         (0lu)
#define hbridge_driver_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define hbridge_driver_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define hbridge_driver_PWM_KILL_EVENT                 (0lu)
#define hbridge_driver_PWM_STOP_EVENT                 (0lu)
#define hbridge_driver_PWM_MODE                       (4lu)
#define hbridge_driver_PWM_OUT_N_INVERT               (0lu)
#define hbridge_driver_PWM_OUT_INVERT                 (0lu)
#define hbridge_driver_PWM_ALIGN                      (0lu)
#define hbridge_driver_PWM_RUN_MODE                   (0lu)
#define hbridge_driver_PWM_DEAD_TIME_CYCLE            (0lu)
#define hbridge_driver_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define hbridge_driver_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define hbridge_driver_PWM_COUNT_SIGNAL_MODE          (3lu)
#define hbridge_driver_PWM_START_SIGNAL_MODE          (0lu)
#define hbridge_driver_PWM_STOP_SIGNAL_MODE           (0lu)
#define hbridge_driver_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define hbridge_driver_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define hbridge_driver_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define hbridge_driver_PWM_START_SIGNAL_PRESENT       (0lu)
#define hbridge_driver_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define hbridge_driver_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define hbridge_driver_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define hbridge_driver_TC_PERIOD_VALUE                (65535lu)
#define hbridge_driver_TC_COMPARE_VALUE               (65535lu)
#define hbridge_driver_TC_COMPARE_BUF_VALUE           (65535lu)
#define hbridge_driver_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define hbridge_driver_PWM_PERIOD_VALUE               (65535lu)
#define hbridge_driver_PWM_PERIOD_BUF_VALUE           (65535lu)
#define hbridge_driver_PWM_PERIOD_SWAP                (0lu)
#define hbridge_driver_PWM_COMPARE_VALUE              (65535lu)
#define hbridge_driver_PWM_COMPARE_BUF_VALUE          (65535lu)
#define hbridge_driver_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define hbridge_driver__LEFT 0
#define hbridge_driver__RIGHT 1
#define hbridge_driver__CENTER 2
#define hbridge_driver__ASYMMETRIC 3

#define hbridge_driver__X1 0
#define hbridge_driver__X2 1
#define hbridge_driver__X4 2

#define hbridge_driver__PWM 4
#define hbridge_driver__PWM_DT 5
#define hbridge_driver__PWM_PR 6

#define hbridge_driver__INVERSE 1
#define hbridge_driver__DIRECT 0

#define hbridge_driver__CAPTURE 2
#define hbridge_driver__COMPARE 0

#define hbridge_driver__TRIG_LEVEL 3
#define hbridge_driver__TRIG_RISING 0
#define hbridge_driver__TRIG_FALLING 1
#define hbridge_driver__TRIG_BOTH 2

#define hbridge_driver__INTR_MASK_TC 1
#define hbridge_driver__INTR_MASK_CC_MATCH 2
#define hbridge_driver__INTR_MASK_NONE 0
#define hbridge_driver__INTR_MASK_TC_CC 3

#define hbridge_driver__UNCONFIG 8
#define hbridge_driver__TIMER 1
#define hbridge_driver__QUAD 3
#define hbridge_driver__PWM_SEL 7

#define hbridge_driver__COUNT_UP 0
#define hbridge_driver__COUNT_DOWN 1
#define hbridge_driver__COUNT_UPDOWN0 2
#define hbridge_driver__COUNT_UPDOWN1 3


/* Prescaler */
#define hbridge_driver_PRESCALE_DIVBY1                ((uint32)(0u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY2                ((uint32)(1u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY4                ((uint32)(2u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY8                ((uint32)(3u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY16               ((uint32)(4u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY32               ((uint32)(5u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY64               ((uint32)(6u << hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_PRESCALE_DIVBY128              ((uint32)(7u << hbridge_driver_PRESCALER_SHIFT))

/* TCPWM set modes */
#define hbridge_driver_MODE_TIMER_COMPARE             ((uint32)(hbridge_driver__COMPARE         <<  \
                                                                  hbridge_driver_MODE_SHIFT))
#define hbridge_driver_MODE_TIMER_CAPTURE             ((uint32)(hbridge_driver__CAPTURE         <<  \
                                                                  hbridge_driver_MODE_SHIFT))
#define hbridge_driver_MODE_QUAD                      ((uint32)(hbridge_driver__QUAD            <<  \
                                                                  hbridge_driver_MODE_SHIFT))
#define hbridge_driver_MODE_PWM                       ((uint32)(hbridge_driver__PWM             <<  \
                                                                  hbridge_driver_MODE_SHIFT))
#define hbridge_driver_MODE_PWM_DT                    ((uint32)(hbridge_driver__PWM_DT          <<  \
                                                                  hbridge_driver_MODE_SHIFT))
#define hbridge_driver_MODE_PWM_PR                    ((uint32)(hbridge_driver__PWM_PR          <<  \
                                                                  hbridge_driver_MODE_SHIFT))

/* Quad Modes */
#define hbridge_driver_MODE_X1                        ((uint32)(hbridge_driver__X1              <<  \
                                                                  hbridge_driver_QUAD_MODE_SHIFT))
#define hbridge_driver_MODE_X2                        ((uint32)(hbridge_driver__X2              <<  \
                                                                  hbridge_driver_QUAD_MODE_SHIFT))
#define hbridge_driver_MODE_X4                        ((uint32)(hbridge_driver__X4              <<  \
                                                                  hbridge_driver_QUAD_MODE_SHIFT))

/* Counter modes */
#define hbridge_driver_COUNT_UP                       ((uint32)(hbridge_driver__COUNT_UP        <<  \
                                                                  hbridge_driver_UPDOWN_SHIFT))
#define hbridge_driver_COUNT_DOWN                     ((uint32)(hbridge_driver__COUNT_DOWN      <<  \
                                                                  hbridge_driver_UPDOWN_SHIFT))
#define hbridge_driver_COUNT_UPDOWN0                  ((uint32)(hbridge_driver__COUNT_UPDOWN0   <<  \
                                                                  hbridge_driver_UPDOWN_SHIFT))
#define hbridge_driver_COUNT_UPDOWN1                  ((uint32)(hbridge_driver__COUNT_UPDOWN1   <<  \
                                                                  hbridge_driver_UPDOWN_SHIFT))

/* PWM output invert */
#define hbridge_driver_INVERT_LINE                    ((uint32)(hbridge_driver__INVERSE         <<  \
                                                                  hbridge_driver_INV_OUT_SHIFT))
#define hbridge_driver_INVERT_LINE_N                  ((uint32)(hbridge_driver__INVERSE         <<  \
                                                                  hbridge_driver_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define hbridge_driver_TRIG_RISING                    ((uint32)hbridge_driver__TRIG_RISING)
#define hbridge_driver_TRIG_FALLING                   ((uint32)hbridge_driver__TRIG_FALLING)
#define hbridge_driver_TRIG_BOTH                      ((uint32)hbridge_driver__TRIG_BOTH)
#define hbridge_driver_TRIG_LEVEL                     ((uint32)hbridge_driver__TRIG_LEVEL)

/* Interrupt mask */
#define hbridge_driver_INTR_MASK_TC                   ((uint32)hbridge_driver__INTR_MASK_TC)
#define hbridge_driver_INTR_MASK_CC_MATCH             ((uint32)hbridge_driver__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define hbridge_driver_CC_MATCH_SET                   (0x00u)
#define hbridge_driver_CC_MATCH_CLEAR                 (0x01u)
#define hbridge_driver_CC_MATCH_INVERT                (0x02u)
#define hbridge_driver_CC_MATCH_NO_CHANGE             (0x03u)
#define hbridge_driver_OVERLOW_SET                    (0x00u)
#define hbridge_driver_OVERLOW_CLEAR                  (0x04u)
#define hbridge_driver_OVERLOW_INVERT                 (0x08u)
#define hbridge_driver_OVERLOW_NO_CHANGE              (0x0Cu)
#define hbridge_driver_UNDERFLOW_SET                  (0x00u)
#define hbridge_driver_UNDERFLOW_CLEAR                (0x10u)
#define hbridge_driver_UNDERFLOW_INVERT               (0x20u)
#define hbridge_driver_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define hbridge_driver_PWM_MODE_LEFT                  (hbridge_driver_CC_MATCH_CLEAR        |   \
                                                         hbridge_driver_OVERLOW_SET           |   \
                                                         hbridge_driver_UNDERFLOW_NO_CHANGE)
#define hbridge_driver_PWM_MODE_RIGHT                 (hbridge_driver_CC_MATCH_SET          |   \
                                                         hbridge_driver_OVERLOW_NO_CHANGE     |   \
                                                         hbridge_driver_UNDERFLOW_CLEAR)
#define hbridge_driver_PWM_MODE_ASYM                  (hbridge_driver_CC_MATCH_INVERT       |   \
                                                         hbridge_driver_OVERLOW_SET           |   \
                                                         hbridge_driver_UNDERFLOW_CLEAR)

#if (hbridge_driver_CY_TCPWM_V2)
    #if(hbridge_driver_CY_TCPWM_4000)
        #define hbridge_driver_PWM_MODE_CENTER                (hbridge_driver_CC_MATCH_INVERT       |   \
                                                                 hbridge_driver_OVERLOW_NO_CHANGE     |   \
                                                                 hbridge_driver_UNDERFLOW_CLEAR)
    #else
        #define hbridge_driver_PWM_MODE_CENTER                (hbridge_driver_CC_MATCH_INVERT       |   \
                                                                 hbridge_driver_OVERLOW_SET           |   \
                                                                 hbridge_driver_UNDERFLOW_CLEAR)
    #endif /* (hbridge_driver_CY_TCPWM_4000) */
#else
    #define hbridge_driver_PWM_MODE_CENTER                (hbridge_driver_CC_MATCH_INVERT       |   \
                                                             hbridge_driver_OVERLOW_NO_CHANGE     |   \
                                                             hbridge_driver_UNDERFLOW_CLEAR)
#endif /* (hbridge_driver_CY_TCPWM_NEW) */

/* Command operations without condition */
#define hbridge_driver_CMD_CAPTURE                    (0u)
#define hbridge_driver_CMD_RELOAD                     (8u)
#define hbridge_driver_CMD_STOP                       (16u)
#define hbridge_driver_CMD_START                      (24u)

/* Status */
#define hbridge_driver_STATUS_DOWN                    (1u)
#define hbridge_driver_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   hbridge_driver_Init(void);
void   hbridge_driver_Enable(void);
void   hbridge_driver_Start(void);
void   hbridge_driver_Stop(void);

void   hbridge_driver_SetMode(uint32 mode);
void   hbridge_driver_SetCounterMode(uint32 counterMode);
void   hbridge_driver_SetPWMMode(uint32 modeMask);
void   hbridge_driver_SetQDMode(uint32 qdMode);

void   hbridge_driver_SetPrescaler(uint32 prescaler);
void   hbridge_driver_TriggerCommand(uint32 mask, uint32 command);
void   hbridge_driver_SetOneShot(uint32 oneShotEnable);
uint32 hbridge_driver_ReadStatus(void);

void   hbridge_driver_SetPWMSyncKill(uint32 syncKillEnable);
void   hbridge_driver_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   hbridge_driver_SetPWMDeadTime(uint32 deadTime);
void   hbridge_driver_SetPWMInvert(uint32 mask);

void   hbridge_driver_SetInterruptMode(uint32 interruptMask);
uint32 hbridge_driver_GetInterruptSourceMasked(void);
uint32 hbridge_driver_GetInterruptSource(void);
void   hbridge_driver_ClearInterrupt(uint32 interruptMask);
void   hbridge_driver_SetInterrupt(uint32 interruptMask);

void   hbridge_driver_WriteCounter(uint32 count);
uint32 hbridge_driver_ReadCounter(void);

uint32 hbridge_driver_ReadCapture(void);
uint32 hbridge_driver_ReadCaptureBuf(void);

void   hbridge_driver_WritePeriod(uint32 period);
uint32 hbridge_driver_ReadPeriod(void);
void   hbridge_driver_WritePeriodBuf(uint32 periodBuf);
uint32 hbridge_driver_ReadPeriodBuf(void);

void   hbridge_driver_WriteCompare(uint32 compare);
uint32 hbridge_driver_ReadCompare(void);
void   hbridge_driver_WriteCompareBuf(uint32 compareBuf);
uint32 hbridge_driver_ReadCompareBuf(void);

void   hbridge_driver_SetPeriodSwap(uint32 swapEnable);
void   hbridge_driver_SetCompareSwap(uint32 swapEnable);

void   hbridge_driver_SetCaptureMode(uint32 triggerMode);
void   hbridge_driver_SetReloadMode(uint32 triggerMode);
void   hbridge_driver_SetStartMode(uint32 triggerMode);
void   hbridge_driver_SetStopMode(uint32 triggerMode);
void   hbridge_driver_SetCountMode(uint32 triggerMode);

void   hbridge_driver_SaveConfig(void);
void   hbridge_driver_RestoreConfig(void);
void   hbridge_driver_Sleep(void);
void   hbridge_driver_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define hbridge_driver_BLOCK_CONTROL_REG              (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define hbridge_driver_BLOCK_CONTROL_PTR              ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define hbridge_driver_COMMAND_REG                    (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define hbridge_driver_COMMAND_PTR                    ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define hbridge_driver_INTRRUPT_CAUSE_REG             (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define hbridge_driver_INTRRUPT_CAUSE_PTR             ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define hbridge_driver_CONTROL_REG                    (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__CTRL )
#define hbridge_driver_CONTROL_PTR                    ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__CTRL )
#define hbridge_driver_STATUS_REG                     (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__STATUS )
#define hbridge_driver_STATUS_PTR                     ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__STATUS )
#define hbridge_driver_COUNTER_REG                    (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__COUNTER )
#define hbridge_driver_COUNTER_PTR                    ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__COUNTER )
#define hbridge_driver_COMP_CAP_REG                   (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__CC )
#define hbridge_driver_COMP_CAP_PTR                   ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__CC )
#define hbridge_driver_COMP_CAP_BUF_REG               (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__CC_BUFF )
#define hbridge_driver_COMP_CAP_BUF_PTR               ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__CC_BUFF )
#define hbridge_driver_PERIOD_REG                     (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__PERIOD )
#define hbridge_driver_PERIOD_PTR                     ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__PERIOD )
#define hbridge_driver_PERIOD_BUF_REG                 (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define hbridge_driver_PERIOD_BUF_PTR                 ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define hbridge_driver_TRIG_CONTROL0_REG              (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define hbridge_driver_TRIG_CONTROL0_PTR              ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define hbridge_driver_TRIG_CONTROL1_REG              (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define hbridge_driver_TRIG_CONTROL1_PTR              ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define hbridge_driver_TRIG_CONTROL2_REG              (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define hbridge_driver_TRIG_CONTROL2_PTR              ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define hbridge_driver_INTERRUPT_REQ_REG              (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR )
#define hbridge_driver_INTERRUPT_REQ_PTR              ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR )
#define hbridge_driver_INTERRUPT_SET_REG              (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR_SET )
#define hbridge_driver_INTERRUPT_SET_PTR              ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR_SET )
#define hbridge_driver_INTERRUPT_MASK_REG             (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR_MASK )
#define hbridge_driver_INTERRUPT_MASK_PTR             ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR_MASK )
#define hbridge_driver_INTERRUPT_MASKED_REG           (*(reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR_MASKED )
#define hbridge_driver_INTERRUPT_MASKED_PTR           ( (reg32 *) hbridge_driver_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define hbridge_driver_MASK                           ((uint32)hbridge_driver_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define hbridge_driver_RELOAD_CC_SHIFT                (0u)
#define hbridge_driver_RELOAD_PERIOD_SHIFT            (1u)
#define hbridge_driver_PWM_SYNC_KILL_SHIFT            (2u)
#define hbridge_driver_PWM_STOP_KILL_SHIFT            (3u)
#define hbridge_driver_PRESCALER_SHIFT                (8u)
#define hbridge_driver_UPDOWN_SHIFT                   (16u)
#define hbridge_driver_ONESHOT_SHIFT                  (18u)
#define hbridge_driver_QUAD_MODE_SHIFT                (20u)
#define hbridge_driver_INV_OUT_SHIFT                  (20u)
#define hbridge_driver_INV_COMPL_OUT_SHIFT            (21u)
#define hbridge_driver_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define hbridge_driver_RELOAD_CC_MASK                 ((uint32)(hbridge_driver_1BIT_MASK        <<  \
                                                                            hbridge_driver_RELOAD_CC_SHIFT))
#define hbridge_driver_RELOAD_PERIOD_MASK             ((uint32)(hbridge_driver_1BIT_MASK        <<  \
                                                                            hbridge_driver_RELOAD_PERIOD_SHIFT))
#define hbridge_driver_PWM_SYNC_KILL_MASK             ((uint32)(hbridge_driver_1BIT_MASK        <<  \
                                                                            hbridge_driver_PWM_SYNC_KILL_SHIFT))
#define hbridge_driver_PWM_STOP_KILL_MASK             ((uint32)(hbridge_driver_1BIT_MASK        <<  \
                                                                            hbridge_driver_PWM_STOP_KILL_SHIFT))
#define hbridge_driver_PRESCALER_MASK                 ((uint32)(hbridge_driver_8BIT_MASK        <<  \
                                                                            hbridge_driver_PRESCALER_SHIFT))
#define hbridge_driver_UPDOWN_MASK                    ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                            hbridge_driver_UPDOWN_SHIFT))
#define hbridge_driver_ONESHOT_MASK                   ((uint32)(hbridge_driver_1BIT_MASK        <<  \
                                                                            hbridge_driver_ONESHOT_SHIFT))
#define hbridge_driver_QUAD_MODE_MASK                 ((uint32)(hbridge_driver_3BIT_MASK        <<  \
                                                                            hbridge_driver_QUAD_MODE_SHIFT))
#define hbridge_driver_INV_OUT_MASK                   ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                            hbridge_driver_INV_OUT_SHIFT))
#define hbridge_driver_MODE_MASK                      ((uint32)(hbridge_driver_3BIT_MASK        <<  \
                                                                            hbridge_driver_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define hbridge_driver_CAPTURE_SHIFT                  (0u)
#define hbridge_driver_COUNT_SHIFT                    (2u)
#define hbridge_driver_RELOAD_SHIFT                   (4u)
#define hbridge_driver_STOP_SHIFT                     (6u)
#define hbridge_driver_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define hbridge_driver_CAPTURE_MASK                   ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                  hbridge_driver_CAPTURE_SHIFT))
#define hbridge_driver_COUNT_MASK                     ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                  hbridge_driver_COUNT_SHIFT))
#define hbridge_driver_RELOAD_MASK                    ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                  hbridge_driver_RELOAD_SHIFT))
#define hbridge_driver_STOP_MASK                      ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                  hbridge_driver_STOP_SHIFT))
#define hbridge_driver_START_MASK                     ((uint32)(hbridge_driver_2BIT_MASK        <<  \
                                                                  hbridge_driver_START_SHIFT))

/* MASK */
#define hbridge_driver_1BIT_MASK                      ((uint32)0x01u)
#define hbridge_driver_2BIT_MASK                      ((uint32)0x03u)
#define hbridge_driver_3BIT_MASK                      ((uint32)0x07u)
#define hbridge_driver_6BIT_MASK                      ((uint32)0x3Fu)
#define hbridge_driver_8BIT_MASK                      ((uint32)0xFFu)
#define hbridge_driver_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define hbridge_driver_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define hbridge_driver_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(hbridge_driver_QUAD_ENCODING_MODES     << hbridge_driver_QUAD_MODE_SHIFT))       |\
         ((uint32)(hbridge_driver_CONFIG                  << hbridge_driver_MODE_SHIFT)))

#define hbridge_driver_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(hbridge_driver_PWM_STOP_EVENT          << hbridge_driver_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(hbridge_driver_PWM_OUT_INVERT          << hbridge_driver_INV_OUT_SHIFT))         |\
         ((uint32)(hbridge_driver_PWM_OUT_N_INVERT        << hbridge_driver_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(hbridge_driver_PWM_MODE                << hbridge_driver_MODE_SHIFT)))

#define hbridge_driver_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(hbridge_driver_PWM_RUN_MODE         << hbridge_driver_ONESHOT_SHIFT))
            
#define hbridge_driver_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(hbridge_driver_PWM_ALIGN            << hbridge_driver_UPDOWN_SHIFT))

#define hbridge_driver_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(hbridge_driver_PWM_KILL_EVENT      << hbridge_driver_PWM_SYNC_KILL_SHIFT))

#define hbridge_driver_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(hbridge_driver_PWM_DEAD_TIME_CYCLE  << hbridge_driver_PRESCALER_SHIFT))

#define hbridge_driver_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(hbridge_driver_PWM_PRESCALER        << hbridge_driver_PRESCALER_SHIFT))

#define hbridge_driver_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(hbridge_driver_TC_PRESCALER            << hbridge_driver_PRESCALER_SHIFT))       |\
         ((uint32)(hbridge_driver_TC_COUNTER_MODE         << hbridge_driver_UPDOWN_SHIFT))          |\
         ((uint32)(hbridge_driver_TC_RUN_MODE             << hbridge_driver_ONESHOT_SHIFT))         |\
         ((uint32)(hbridge_driver_TC_COMP_CAP_MODE        << hbridge_driver_MODE_SHIFT)))
        
#define hbridge_driver_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(hbridge_driver_QUAD_PHIA_SIGNAL_MODE   << hbridge_driver_COUNT_SHIFT))           |\
         ((uint32)(hbridge_driver_QUAD_INDEX_SIGNAL_MODE  << hbridge_driver_RELOAD_SHIFT))          |\
         ((uint32)(hbridge_driver_QUAD_STOP_SIGNAL_MODE   << hbridge_driver_STOP_SHIFT))            |\
         ((uint32)(hbridge_driver_QUAD_PHIB_SIGNAL_MODE   << hbridge_driver_START_SHIFT)))

#define hbridge_driver_PWM_SIGNALS_MODES                                                              \
        (((uint32)(hbridge_driver_PWM_SWITCH_SIGNAL_MODE  << hbridge_driver_CAPTURE_SHIFT))         |\
         ((uint32)(hbridge_driver_PWM_COUNT_SIGNAL_MODE   << hbridge_driver_COUNT_SHIFT))           |\
         ((uint32)(hbridge_driver_PWM_RELOAD_SIGNAL_MODE  << hbridge_driver_RELOAD_SHIFT))          |\
         ((uint32)(hbridge_driver_PWM_STOP_SIGNAL_MODE    << hbridge_driver_STOP_SHIFT))            |\
         ((uint32)(hbridge_driver_PWM_START_SIGNAL_MODE   << hbridge_driver_START_SHIFT)))

#define hbridge_driver_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(hbridge_driver_TC_CAPTURE_SIGNAL_MODE  << hbridge_driver_CAPTURE_SHIFT))         |\
         ((uint32)(hbridge_driver_TC_COUNT_SIGNAL_MODE    << hbridge_driver_COUNT_SHIFT))           |\
         ((uint32)(hbridge_driver_TC_RELOAD_SIGNAL_MODE   << hbridge_driver_RELOAD_SHIFT))          |\
         ((uint32)(hbridge_driver_TC_STOP_SIGNAL_MODE     << hbridge_driver_STOP_SHIFT))            |\
         ((uint32)(hbridge_driver_TC_START_SIGNAL_MODE    << hbridge_driver_START_SHIFT)))
        
#define hbridge_driver_TIMER_UPDOWN_CNT_USED                                                          \
                ((hbridge_driver__COUNT_UPDOWN0 == hbridge_driver_TC_COUNTER_MODE)                  ||\
                 (hbridge_driver__COUNT_UPDOWN1 == hbridge_driver_TC_COUNTER_MODE))

#define hbridge_driver_PWM_UPDOWN_CNT_USED                                                            \
                ((hbridge_driver__CENTER == hbridge_driver_PWM_ALIGN)                               ||\
                 (hbridge_driver__ASYMMETRIC == hbridge_driver_PWM_ALIGN))               
        
#define hbridge_driver_PWM_PR_INIT_VALUE              (1u)
#define hbridge_driver_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_hbridge_driver_H */

/* [] END OF FILE */
