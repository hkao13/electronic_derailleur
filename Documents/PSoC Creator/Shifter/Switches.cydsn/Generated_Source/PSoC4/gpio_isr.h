/*******************************************************************************
* File Name: gpio_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_gpio_isr_H)
#define CY_ISR_gpio_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void gpio_isr_Start(void);
void gpio_isr_StartEx(cyisraddress address);
void gpio_isr_Stop(void);

CY_ISR_PROTO(gpio_isr_Interrupt);

void gpio_isr_SetVector(cyisraddress address);
cyisraddress gpio_isr_GetVector(void);

void gpio_isr_SetPriority(uint8 priority);
uint8 gpio_isr_GetPriority(void);

void gpio_isr_Enable(void);
uint8 gpio_isr_GetState(void);
void gpio_isr_Disable(void);

void gpio_isr_SetPending(void);
void gpio_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the gpio_isr ISR. */
#define gpio_isr_INTC_VECTOR            ((reg32 *) gpio_isr__INTC_VECT)

/* Address of the gpio_isr ISR priority. */
#define gpio_isr_INTC_PRIOR             ((reg32 *) gpio_isr__INTC_PRIOR_REG)

/* Priority of the gpio_isr interrupt. */
#define gpio_isr_INTC_PRIOR_NUMBER      gpio_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable gpio_isr interrupt. */
#define gpio_isr_INTC_SET_EN            ((reg32 *) gpio_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the gpio_isr interrupt. */
#define gpio_isr_INTC_CLR_EN            ((reg32 *) gpio_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the gpio_isr interrupt state to pending. */
#define gpio_isr_INTC_SET_PD            ((reg32 *) gpio_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the gpio_isr interrupt. */
#define gpio_isr_INTC_CLR_PD            ((reg32 *) gpio_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_gpio_isr_H */


/* [] END OF FILE */
