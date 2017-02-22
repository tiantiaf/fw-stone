/*******************************************************************************
* File Name: Stone_Timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Stone_Timer.h"

static Stone_Timer_backupStruct Stone_Timer_backup;


/*******************************************************************************
* Function Name: Stone_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stone_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Stone_Timer_SaveConfig(void) 
{
    #if (!Stone_Timer_UsingFixedFunction)
        Stone_Timer_backup.TimerUdb = Stone_Timer_ReadCounter();
        Stone_Timer_backup.InterruptMaskValue = Stone_Timer_STATUS_MASK;
        #if (Stone_Timer_UsingHWCaptureCounter)
            Stone_Timer_backup.TimerCaptureCounter = Stone_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Stone_Timer_UDB_CONTROL_REG_REMOVED)
            Stone_Timer_backup.TimerControlRegister = Stone_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Stone_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stone_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Stone_Timer_RestoreConfig(void) 
{   
    #if (!Stone_Timer_UsingFixedFunction)

        Stone_Timer_WriteCounter(Stone_Timer_backup.TimerUdb);
        Stone_Timer_STATUS_MASK =Stone_Timer_backup.InterruptMaskValue;
        #if (Stone_Timer_UsingHWCaptureCounter)
            Stone_Timer_SetCaptureCount(Stone_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Stone_Timer_UDB_CONTROL_REG_REMOVED)
            Stone_Timer_WriteControlRegister(Stone_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Stone_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stone_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Stone_Timer_Sleep(void) 
{
    #if(!Stone_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Stone_Timer_CTRL_ENABLE == (Stone_Timer_CONTROL & Stone_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Stone_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Stone_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Stone_Timer_Stop();
    Stone_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Stone_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stone_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Stone_Timer_Wakeup(void) 
{
    Stone_Timer_RestoreConfig();
    #if(!Stone_Timer_UDB_CONTROL_REG_REMOVED)
        if(Stone_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Stone_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
