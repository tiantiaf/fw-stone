/*******************************************************************************
* File Name: trigger_isr.h
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
#if !defined(CY_ISR_trigger_isr_H)
#define CY_ISR_trigger_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void trigger_isr_Start(void);
void trigger_isr_StartEx(cyisraddress address);
void trigger_isr_Stop(void);

CY_ISR_PROTO(trigger_isr_Interrupt);

void trigger_isr_SetVector(cyisraddress address);
cyisraddress trigger_isr_GetVector(void);

void trigger_isr_SetPriority(uint8 priority);
uint8 trigger_isr_GetPriority(void);

void trigger_isr_Enable(void);
uint8 trigger_isr_GetState(void);
void trigger_isr_Disable(void);

void trigger_isr_SetPending(void);
void trigger_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the trigger_isr ISR. */
#define trigger_isr_INTC_VECTOR            ((reg32 *) trigger_isr__INTC_VECT)

/* Address of the trigger_isr ISR priority. */
#define trigger_isr_INTC_PRIOR             ((reg32 *) trigger_isr__INTC_PRIOR_REG)

/* Priority of the trigger_isr interrupt. */
#define trigger_isr_INTC_PRIOR_NUMBER      trigger_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable trigger_isr interrupt. */
#define trigger_isr_INTC_SET_EN            ((reg32 *) trigger_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the trigger_isr interrupt. */
#define trigger_isr_INTC_CLR_EN            ((reg32 *) trigger_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the trigger_isr interrupt state to pending. */
#define trigger_isr_INTC_SET_PD            ((reg32 *) trigger_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the trigger_isr interrupt. */
#define trigger_isr_INTC_CLR_PD            ((reg32 *) trigger_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_trigger_isr_H */


/* [] END OF FILE */
