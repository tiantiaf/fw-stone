/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include <main.h>
#include "Stone_Motor.h"
#include "Stone_Motor_Sequence.h"
#include "Stone_Init.h"

uint8 status = MOTOR_INACTIVE;
uint16 ms_count = PERIOD_PER_CYCLE_RUN - 1;

uint8 Stone_Motor[MOTOR_LENGTH];

volatile uint8 Stone_Motor_Mode;

void UpdateMotorPWM(uint8 index);

void StoneUpdateMotor()
{
    /* Mode 0, just on and off */
    if (Stone_Motor[MOTOR_ON_INDEX] == MOTOR_ON)
    {
        Stone_Motor_Mode = Stone_Motor[MOTOR_MODE_INDEX];
        
        /* If Motor is set to be on, we decide which mode we want to be */
        switch(Stone_Motor_Mode)
        {
            case MODE0:
                Motor_Write(MOTOR_ON);
                break;
            
            case MODE1:
                InitStoneInterrupt();
                break;    
                
            default:
                break;
                
        }
        
    } else {
        Motor_Write(MOTOR_OFF);
        Stone_Motor_Mode = 0;
        StopStoneInterrupt();
    }
    
}

CY_ISR(TRIGGER_ISR) {
	Motor_Write(MOTOR_ON);
}

CY_ISR(TC_ISR) {
	Motor_Write(MOTOR_OFF);
}

CY_ISR(MS_ISR) {
    
    if(ms_count == 0)
    {
       ms_count = PERIOD_PER_CYCLE_RUN - 1;
    }
    
    UpdateMotorPWM(ms_count);
    ms_count--;
     
}

void UpdateMotorPWM(uint8 index)
{
    Stone_PWM_WriteCompare(Test[index]);
}

/* [] END OF FILE */
