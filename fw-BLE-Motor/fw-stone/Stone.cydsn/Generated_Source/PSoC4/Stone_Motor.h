/*******************************************************************************
* File Name: Stone_Motor.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Stone_Motor_H) /* Pins Stone_Motor_H */
#define CY_PINS_Stone_Motor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Stone_Motor_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Stone_Motor_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Stone_Motor_Read(void);
void    Stone_Motor_Write(uint8 value);
uint8   Stone_Motor_ReadDataReg(void);
#if defined(Stone_Motor__PC) || (CY_PSOC4_4200L) 
    void    Stone_Motor_SetDriveMode(uint8 mode);
#endif
void    Stone_Motor_SetInterruptMode(uint16 position, uint16 mode);
uint8   Stone_Motor_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Stone_Motor_Sleep(void); 
void Stone_Motor_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Stone_Motor__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Stone_Motor_DRIVE_MODE_BITS        (3)
    #define Stone_Motor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Stone_Motor_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Stone_Motor_SetDriveMode() function.
         *  @{
         */
        #define Stone_Motor_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Stone_Motor_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Stone_Motor_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Stone_Motor_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Stone_Motor_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Stone_Motor_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Stone_Motor_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Stone_Motor_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Stone_Motor_MASK               Stone_Motor__MASK
#define Stone_Motor_SHIFT              Stone_Motor__SHIFT
#define Stone_Motor_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Stone_Motor_SetInterruptMode() function.
     *  @{
     */
        #define Stone_Motor_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Stone_Motor_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Stone_Motor_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Stone_Motor_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Stone_Motor__SIO)
    #define Stone_Motor_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Stone_Motor__PC) && (CY_PSOC4_4200L)
    #define Stone_Motor_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Stone_Motor_USBIO_DISABLE              ((uint32)(~Stone_Motor_USBIO_ENABLE))
    #define Stone_Motor_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Stone_Motor_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Stone_Motor_USBIO_ENTER_SLEEP          ((uint32)((1u << Stone_Motor_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Stone_Motor_USBIO_SUSPEND_DEL_SHIFT)))
    #define Stone_Motor_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Stone_Motor_USBIO_SUSPEND_SHIFT)))
    #define Stone_Motor_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Stone_Motor_USBIO_SUSPEND_DEL_SHIFT)))
    #define Stone_Motor_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Stone_Motor__PC)
    /* Port Configuration */
    #define Stone_Motor_PC                 (* (reg32 *) Stone_Motor__PC)
#endif
/* Pin State */
#define Stone_Motor_PS                     (* (reg32 *) Stone_Motor__PS)
/* Data Register */
#define Stone_Motor_DR                     (* (reg32 *) Stone_Motor__DR)
/* Input Buffer Disable Override */
#define Stone_Motor_INP_DIS                (* (reg32 *) Stone_Motor__PC2)

/* Interrupt configuration Registers */
#define Stone_Motor_INTCFG                 (* (reg32 *) Stone_Motor__INTCFG)
#define Stone_Motor_INTSTAT                (* (reg32 *) Stone_Motor__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Stone_Motor_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Stone_Motor__SIO)
    #define Stone_Motor_SIO_REG            (* (reg32 *) Stone_Motor__SIO)
#endif /* (Stone_Motor__SIO_CFG) */

/* USBIO registers */
#if !defined(Stone_Motor__PC) && (CY_PSOC4_4200L)
    #define Stone_Motor_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Stone_Motor_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Stone_Motor_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Stone_Motor_DRIVE_MODE_SHIFT       (0x00u)
#define Stone_Motor_DRIVE_MODE_MASK        (0x07u << Stone_Motor_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Stone_Motor_H */


/* [] END OF FILE */
