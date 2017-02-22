/*******************************************************************************
* File Name: Stone_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Stone_PWM.h"

static Stone_PWM_backupStruct Stone_PWM_backup;


/*******************************************************************************
* Function Name: Stone_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Stone_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Stone_PWM_SaveConfig(void) 
{

    #if(!Stone_PWM_UsingFixedFunction)
        #if(!Stone_PWM_PWMModeIsCenterAligned)
            Stone_PWM_backup.PWMPeriod = Stone_PWM_ReadPeriod();
        #endif /* (!Stone_PWM_PWMModeIsCenterAligned) */
        Stone_PWM_backup.PWMUdb = Stone_PWM_ReadCounter();
        #if (Stone_PWM_UseStatus)
            Stone_PWM_backup.InterruptMaskValue = Stone_PWM_STATUS_MASK;
        #endif /* (Stone_PWM_UseStatus) */

        #if(Stone_PWM_DeadBandMode == Stone_PWM__B_PWM__DBM_256_CLOCKS || \
            Stone_PWM_DeadBandMode == Stone_PWM__B_PWM__DBM_2_4_CLOCKS)
            Stone_PWM_backup.PWMdeadBandValue = Stone_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Stone_PWM_KillModeMinTime)
             Stone_PWM_backup.PWMKillCounterPeriod = Stone_PWM_ReadKillTime();
        #endif /* (Stone_PWM_KillModeMinTime) */

        #if(Stone_PWM_UseControl)
            Stone_PWM_backup.PWMControlRegister = Stone_PWM_ReadControlRegister();
        #endif /* (Stone_PWM_UseControl) */
    #endif  /* (!Stone_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Stone_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Stone_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Stone_PWM_RestoreConfig(void) 
{
        #if(!Stone_PWM_UsingFixedFunction)
            #if(!Stone_PWM_PWMModeIsCenterAligned)
                Stone_PWM_WritePeriod(Stone_PWM_backup.PWMPeriod);
            #endif /* (!Stone_PWM_PWMModeIsCenterAligned) */

            Stone_PWM_WriteCounter(Stone_PWM_backup.PWMUdb);

            #if (Stone_PWM_UseStatus)
                Stone_PWM_STATUS_MASK = Stone_PWM_backup.InterruptMaskValue;
            #endif /* (Stone_PWM_UseStatus) */

            #if(Stone_PWM_DeadBandMode == Stone_PWM__B_PWM__DBM_256_CLOCKS || \
                Stone_PWM_DeadBandMode == Stone_PWM__B_PWM__DBM_2_4_CLOCKS)
                Stone_PWM_WriteDeadTime(Stone_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Stone_PWM_KillModeMinTime)
                Stone_PWM_WriteKillTime(Stone_PWM_backup.PWMKillCounterPeriod);
            #endif /* (Stone_PWM_KillModeMinTime) */

            #if(Stone_PWM_UseControl)
                Stone_PWM_WriteControlRegister(Stone_PWM_backup.PWMControlRegister);
            #endif /* (Stone_PWM_UseControl) */
        #endif  /* (!Stone_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Stone_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Stone_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Stone_PWM_Sleep(void) 
{
    #if(Stone_PWM_UseControl)
        if(Stone_PWM_CTRL_ENABLE == (Stone_PWM_CONTROL & Stone_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            Stone_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Stone_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (Stone_PWM_UseControl) */

    /* Stop component */
    Stone_PWM_Stop();

    /* Save registers configuration */
    Stone_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Stone_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Stone_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Stone_PWM_Wakeup(void) 
{
     /* Restore registers values */
    Stone_PWM_RestoreConfig();

    if(Stone_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Stone_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
