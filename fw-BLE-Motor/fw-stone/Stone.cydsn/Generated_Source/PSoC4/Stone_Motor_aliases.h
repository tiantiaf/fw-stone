/*******************************************************************************
* File Name: Stone_Motor.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Stone_Motor_ALIASES_H) /* Pins Stone_Motor_ALIASES_H */
#define CY_PINS_Stone_Motor_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Stone_Motor_0			(Stone_Motor__0__PC)
#define Stone_Motor_0_PS		(Stone_Motor__0__PS)
#define Stone_Motor_0_PC		(Stone_Motor__0__PC)
#define Stone_Motor_0_DR		(Stone_Motor__0__DR)
#define Stone_Motor_0_SHIFT	(Stone_Motor__0__SHIFT)
#define Stone_Motor_0_INTR	((uint16)((uint16)0x0003u << (Stone_Motor__0__SHIFT*2u)))

#define Stone_Motor_INTR_ALL	 ((uint16)(Stone_Motor_0_INTR))


#endif /* End Pins Stone_Motor_ALIASES_H */


/* [] END OF FILE */
