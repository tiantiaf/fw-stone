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
 
#include "Stone_Motor.h"
#include <main.h> 

uint8 Stone_Motor_Mode[MOTOR_MODE_LENGTH];

void UpdateMotor(void)
{
    if (Stone_Motor_Mode[0] == 0x01)
    {
        Stone_Motor_Write(MOTOR_ON);
    }             
}

CY_ISR(TRIGGER_ISR) {
	Stone_Motor_Write(MOTOR_ON);
}

CY_ISR(TC_ISR) {
	Stone_Motor_Write(MOTOR_OFF);
}

CY_ISR(MS_ISR) {
    
}


/* [] END OF FILE */