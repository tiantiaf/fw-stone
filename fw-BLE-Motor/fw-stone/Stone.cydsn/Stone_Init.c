/* ========================================
 *
 * Tiantian Feng, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "Stone_Init.h"
#include "Stone_Motor.h"


/*******************************************************************************
* Function Name: InitializeSystem
********************************************************************************
* Summary:
* Start the components and initialize system.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitializeSystem(void)
{
	/* Enable global interrupt mask */
	CyGlobalIntEnable; 
		
	/* Start BLE component and register the CustomEventHandler function. This 
	 * function exposes the events from BLE component for application use */
    CyBle_Start(CustomEventHandler);
    
    LED_Write(LED_ON);
    
    Motor_Write(MOTOR_OFF);
}

void InitStoneInterrupt()
{
    /* Init Timer and PWM */
    Stone_PWM_Init();
    Stone_Timer_Start(); // Configure and enable ms timer
    
    ms_isr_StartEx(MS_ISR);
    trigger_isr_StartEx(TRIGGER_ISR);
	tc_isr_StartEx(TC_ISR);   
}

void StopStoneInterrupt(void)
{
    ms_isr_Stop();
    trigger_isr_Stop();
	tc_isr_Stop();  
    
    /* Stop Timer and PWM */
    Stone_PWM_Stop();
    Stone_Timer_Stop(); // Configure and enable ms timer
}

/* [] END OF FILE */
