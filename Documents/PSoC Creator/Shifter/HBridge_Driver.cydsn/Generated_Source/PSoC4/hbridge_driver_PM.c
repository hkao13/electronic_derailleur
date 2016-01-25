/*******************************************************************************
* File Name: hbridge_driver_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "hbridge_driver.h"

static hbridge_driver_BACKUP_STRUCT hbridge_driver_backup;


/*******************************************************************************
* Function Name: hbridge_driver_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void hbridge_driver_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: hbridge_driver_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void hbridge_driver_Sleep(void)
{
    if(0u != (hbridge_driver_BLOCK_CONTROL_REG & hbridge_driver_MASK))
    {
        hbridge_driver_backup.enableState = 1u;
    }
    else
    {
        hbridge_driver_backup.enableState = 0u;
    }

    hbridge_driver_Stop();
    hbridge_driver_SaveConfig();
}


/*******************************************************************************
* Function Name: hbridge_driver_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void hbridge_driver_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: hbridge_driver_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void hbridge_driver_Wakeup(void)
{
    hbridge_driver_RestoreConfig();

    if(0u != hbridge_driver_backup.enableState)
    {
        hbridge_driver_Enable();
    }
}


/* [] END OF FILE */
