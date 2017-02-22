/*******************************************************************************
* File Name: Stone_Motor.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Stone_Motor.h"

static Stone_Motor_BACKUP_STRUCT  Stone_Motor_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Stone_Motor_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Stone_Motor_SUT.c usage_Stone_Motor_Sleep_Wakeup
*******************************************************************************/
void Stone_Motor_Sleep(void)
{
    #if defined(Stone_Motor__PC)
        Stone_Motor_backup.pcState = Stone_Motor_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Stone_Motor_backup.usbState = Stone_Motor_CR1_REG;
            Stone_Motor_USB_POWER_REG |= Stone_Motor_USBIO_ENTER_SLEEP;
            Stone_Motor_CR1_REG &= Stone_Motor_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Stone_Motor__SIO)
        Stone_Motor_backup.sioState = Stone_Motor_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Stone_Motor_SIO_REG &= (uint32)(~Stone_Motor_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Stone_Motor_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Stone_Motor_Sleep() for an example usage.
*******************************************************************************/
void Stone_Motor_Wakeup(void)
{
    #if defined(Stone_Motor__PC)
        Stone_Motor_PC = Stone_Motor_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Stone_Motor_USB_POWER_REG &= Stone_Motor_USBIO_EXIT_SLEEP_PH1;
            Stone_Motor_CR1_REG = Stone_Motor_backup.usbState;
            Stone_Motor_USB_POWER_REG &= Stone_Motor_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Stone_Motor__SIO)
        Stone_Motor_SIO_REG = Stone_Motor_backup.sioState;
    #endif
}


/* [] END OF FILE */
