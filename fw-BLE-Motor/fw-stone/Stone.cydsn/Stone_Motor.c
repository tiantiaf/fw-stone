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

volatile uint8 Stone_Motor[MOTOR_LENGTH];
uint8 Motor_Running_Sequence[PERIOD_PER_CYCLE_RUN];
volatile uint8 Stone_Motor_Mode;

const uint8 Test[PERIOD_PER_CYCLE_RUN] = {  20, 25, 99, 99, 25, 20, 20, 20, 22, 22,
                                            22, 23, 23, 24, 24, 26, 26, 27, 28, 28, 
                                            29, 30, 30, 32, 35, 36, 37, 39, 42, 44, 
                                            46, 50,
                                            20, 25, 99, 99, 25, 20, 20, 20, 22, 22,
                                            22, 23, 23, 24, 24, 26, 26, 27, 28, 28, 
                                            29, 30, 30, 32, 35, 36, 37, 39, 42, 44, 
                                            46, 50, };

/*

const uint8 Test[PERIOD_PER_CYCLE_RUN] = {  20, 25, 99, 99, 25, 20, 20, 20, 22, 22,
                                            22, 23, 23, 24, 24, 26, 26, 27, 28, 28, 
                                            29, 30, 30, 32, 35, 36, 37, 39, 42, 44, 
                                            46, 50,
                                            20, 25, 99, 99, 25, 20, 20, 20, 22, 22,
                                            22, 23, 23, 24, 24, 26, 26, 27, 28, 28, 
                                            29, 30, 30, 32, 35, 36, 37, 39, 42, 44, 
                                            46, 50, };

const uint8 Test[PERIOD_PER_CYCLE_RUN] = {25, 25, 25, 25, 25, 25, 20, 20, 99, 99,
                                    50, 48, 46, 46, 45, 43, 43, 42, 40, 40,
                                    38, 38, 38, 36, 35, 33, 33, 31, 31,
                                    31, 30, 28, 28,
                                    25, 25, 20, 25, 40, 50, 60, 25, 25,
                                    25, 25, 25, 25, 25, 25, 20, 20, 20,
                                    25, 25, 25, 25, 25, 25, 20, 20, 20,
                                    20, 20, 20, 20 };*/

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
    
    if(ms_count == PERIOD_PER_CYCLE_RUN - 1)
    {
       ms_count = 0;
    }
    
    UpdateMotorPWM(ms_count);
    ms_count++;
     
}

void UpdateMotorPWM(uint8 index)
{
    Stone_PWM_WriteCompare(Motor_Running_Sequence[index]);
}

/* [] END OF FILE */
