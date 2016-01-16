/*******************************************************************************
* File Name: PC_PSoC_UART_tx.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PC_PSoC_UART_tx.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PC_PSoC_UART_tx_PC =   (PC_PSoC_UART_tx_PC & \
                                (uint32)(~(uint32)(PC_PSoC_UART_tx_DRIVE_MODE_IND_MASK << (PC_PSoC_UART_tx_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PC_PSoC_UART_tx_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PC_PSoC_UART_tx_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void PC_PSoC_UART_tx_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PC_PSoC_UART_tx_DR & (uint8)(~PC_PSoC_UART_tx_MASK));
    drVal = (drVal | ((uint8)(value << PC_PSoC_UART_tx_SHIFT) & PC_PSoC_UART_tx_MASK));
    PC_PSoC_UART_tx_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PC_PSoC_UART_tx_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PC_PSoC_UART_tx_DM_STRONG     Strong Drive 
*  PC_PSoC_UART_tx_DM_OD_HI      Open Drain, Drives High 
*  PC_PSoC_UART_tx_DM_OD_LO      Open Drain, Drives Low 
*  PC_PSoC_UART_tx_DM_RES_UP     Resistive Pull Up 
*  PC_PSoC_UART_tx_DM_RES_DWN    Resistive Pull Down 
*  PC_PSoC_UART_tx_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PC_PSoC_UART_tx_DM_DIG_HIZ    High Impedance Digital 
*  PC_PSoC_UART_tx_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PC_PSoC_UART_tx_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PC_PSoC_UART_tx__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PC_PSoC_UART_tx_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PC_PSoC_UART_tx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PC_PSoC_UART_tx_Read(void) 
{
    return (uint8)((PC_PSoC_UART_tx_PS & PC_PSoC_UART_tx_MASK) >> PC_PSoC_UART_tx_SHIFT);
}


/*******************************************************************************
* Function Name: PC_PSoC_UART_tx_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PC_PSoC_UART_tx_ReadDataReg(void) 
{
    return (uint8)((PC_PSoC_UART_tx_DR & PC_PSoC_UART_tx_MASK) >> PC_PSoC_UART_tx_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PC_PSoC_UART_tx_INTSTAT) 

    /*******************************************************************************
    * Function Name: PC_PSoC_UART_tx_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PC_PSoC_UART_tx_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PC_PSoC_UART_tx_INTSTAT & PC_PSoC_UART_tx_MASK);
		PC_PSoC_UART_tx_INTSTAT = maskedStatus;
        return maskedStatus >> PC_PSoC_UART_tx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
