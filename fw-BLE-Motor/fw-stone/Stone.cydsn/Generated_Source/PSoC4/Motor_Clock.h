/*******************************************************************************
* File Name: Motor_Clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Motor_Clock_H)
#define CY_CLOCK_Motor_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Motor_Clock_StartEx(uint32 alignClkDiv);
#define Motor_Clock_Start() \
    Motor_Clock_StartEx(Motor_Clock__PA_DIV_ID)

#else

void Motor_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Motor_Clock_Stop(void);

void Motor_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Motor_Clock_GetDividerRegister(void);
uint8  Motor_Clock_GetFractionalDividerRegister(void);

#define Motor_Clock_Enable()                         Motor_Clock_Start()
#define Motor_Clock_Disable()                        Motor_Clock_Stop()
#define Motor_Clock_SetDividerRegister(clkDivider, reset)  \
    Motor_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define Motor_Clock_SetDivider(clkDivider)           Motor_Clock_SetDividerRegister((clkDivider), 1u)
#define Motor_Clock_SetDividerValue(clkDivider)      Motor_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Motor_Clock_DIV_ID     Motor_Clock__DIV_ID

#define Motor_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Motor_Clock_CTRL_REG   (*(reg32 *)Motor_Clock__CTRL_REGISTER)
#define Motor_Clock_DIV_REG    (*(reg32 *)Motor_Clock__DIV_REGISTER)

#define Motor_Clock_CMD_DIV_SHIFT          (0u)
#define Motor_Clock_CMD_PA_DIV_SHIFT       (8u)
#define Motor_Clock_CMD_DISABLE_SHIFT      (30u)
#define Motor_Clock_CMD_ENABLE_SHIFT       (31u)

#define Motor_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Motor_Clock_CMD_DISABLE_SHIFT))
#define Motor_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Motor_Clock_CMD_ENABLE_SHIFT))

#define Motor_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define Motor_Clock_DIV_FRAC_SHIFT (3u)
#define Motor_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define Motor_Clock_DIV_INT_SHIFT  (8u)

#else 

#define Motor_Clock_DIV_REG        (*(reg32 *)Motor_Clock__REGISTER)
#define Motor_Clock_ENABLE_REG     Motor_Clock_DIV_REG
#define Motor_Clock_DIV_FRAC_MASK  Motor_Clock__FRAC_MASK
#define Motor_Clock_DIV_FRAC_SHIFT (16u)
#define Motor_Clock_DIV_INT_MASK   Motor_Clock__DIVIDER_MASK
#define Motor_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Motor_Clock_H) */

/* [] END OF FILE */
