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

uint8 Stone_Motor_Mode[MOTOR_MODE_LENGTH];

void UpdateMotorPWM(uint8 index);

void StoneUpdateMotor()
{
    /* Mode 0, just on and off */
    if (Stone_Motor_Mode[MODE0] == MOTOR_ON)
    {
        Motor_Write(MOTOR_ON);
        //InitStoneInterrupt();
        
    } else {
        Motor_Write(MOTOR_OFF);
        //StopStoneInterrupt();
    }
}

CY_ISR(TRIGGER_ISR) {
	Motor_Write(MOTOR_ON);
}

CY_ISR(TC_ISR) {
	Motor_Write(MOTOR_OFF);
}

CY_ISR(MS_ISR) {
    
    switch(status)
    {
        case MOTOR_ACTIVE:
            
            if(ms_count == 0)
            {
               status = MOTOR_ACTIVE;
               ms_count = PERIOD_PER_CYCLE_RUN - 1;
            }
            
            UpdateMotorPWM(ms_count);
            ms_count--;
        	
            break;
        
        case MOTOR_DEFAULT:
            break;
    
    }
      
}

void UpdateMotorPWM(uint8 index)
{
    Stone_PWM_WriteCompare(Test[index]);
}

/* [] END OF FILE */
