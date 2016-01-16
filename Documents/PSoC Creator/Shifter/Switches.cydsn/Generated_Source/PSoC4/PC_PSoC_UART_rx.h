/*******************************************************************************
* File Name: PC_PSoC_UART_rx.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PC_PSoC_UART_rx_H) /* Pins PC_PSoC_UART_rx_H */
#define CY_PINS_PC_PSoC_UART_rx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PC_PSoC_UART_rx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PC_PSoC_UART_rx_Write(uint8 value) ;
void    PC_PSoC_UART_rx_SetDriveMode(uint8 mode) ;
uint8   PC_PSoC_UART_rx_ReadDataReg(void) ;
uint8   PC_PSoC_UART_rx_Read(void) ;
uint8   PC_PSoC_UART_rx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PC_PSoC_UART_rx_DRIVE_MODE_BITS        (3)
#define PC_PSoC_UART_rx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PC_PSoC_UART_rx_DRIVE_MODE_BITS))

#define PC_PSoC_UART_rx_DM_ALG_HIZ         (0x00u)
#define PC_PSoC_UART_rx_DM_DIG_HIZ         (0x01u)
#define PC_PSoC_UART_rx_DM_RES_UP          (0x02u)
#define PC_PSoC_UART_rx_DM_RES_DWN         (0x03u)
#define PC_PSoC_UART_rx_DM_OD_LO           (0x04u)
#define PC_PSoC_UART_rx_DM_OD_HI           (0x05u)
#define PC_PSoC_UART_rx_DM_STRONG          (0x06u)
#define PC_PSoC_UART_rx_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PC_PSoC_UART_rx_MASK               PC_PSoC_UART_rx__MASK
#define PC_PSoC_UART_rx_SHIFT              PC_PSoC_UART_rx__SHIFT
#define PC_PSoC_UART_rx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PC_PSoC_UART_rx_PS                     (* (reg32 *) PC_PSoC_UART_rx__PS)
/* Port Configuration */
#define PC_PSoC_UART_rx_PC                     (* (reg32 *) PC_PSoC_UART_rx__PC)
/* Data Register */
#define PC_PSoC_UART_rx_DR                     (* (reg32 *) PC_PSoC_UART_rx__DR)
/* Input Buffer Disable Override */
#define PC_PSoC_UART_rx_INP_DIS                (* (reg32 *) PC_PSoC_UART_rx__PC2)


#if defined(PC_PSoC_UART_rx__INTSTAT)  /* Interrupt Registers */

    #define PC_PSoC_UART_rx_INTSTAT                (* (reg32 *) PC_PSoC_UART_rx__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PC_PSoC_UART_rx_DRIVE_MODE_SHIFT       (0x00u)
#define PC_PSoC_UART_rx_DRIVE_MODE_MASK        (0x07u << PC_PSoC_UART_rx_DRIVE_MODE_SHIFT)


#endif /* End Pins PC_PSoC_UART_rx_H */


/* [] END OF FILE */
