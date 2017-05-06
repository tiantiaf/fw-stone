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
#include "Stone_Motor_Sequence.h"


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
    
    Stone_Motor[2] = 4;
    Stone_Motor[3] = 50;
}

void InitStoneInterrupt()
{
    uint16 timer_Period;
    
    /* Init Timer and PWM */
    Stone_PWM_Init();
    Stone_Timer_Init();
    
    timer_Period = Stone_Motor[2] * 1024;
    Stone_Timer_WritePeriod(timer_Period);
    
    Stone_Sequence_Init();
    
    /* Start Timer and PWM */
    Stone_Timer_Start();
    Stone_PWM_Start();
    
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

void Stone_Sequence_Init(void)
{
    uint8 offset = Stone_Motor[3] - 50;
    uint8 i = 0;
    
    for( i = 0; i < PERIOD_PER_CYCLE_RUN; i++)
    {
        switch((Test[i] - 1) / 5)
        {
            case 5:
            case 6:
               Motor_Running_Sequence[i] = Test[i] + (offset / 3);
               break;
            
            case 7:
            case 8:
               Motor_Running_Sequence[i] = Test[i] + (offset * 2) / 3;
               break;
            
            case 9:
               Motor_Running_Sequence[i] = Test[i] + offset;
               break;
            
            default:
               Motor_Running_Sequence[i] = Test[i];
               break;
        }
    } 
    
}

/* [] END OF FILE */
