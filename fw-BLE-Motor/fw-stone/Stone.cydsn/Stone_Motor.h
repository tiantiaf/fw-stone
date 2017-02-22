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
#if !defined(Stone_Motor_H)
#define Stone_Motor_H

#include <main.h>
    
#define MOTOR_MODE_LENGTH     4 
    
#define MOTOR_ON		0x01
#define MOTOR_OFF       0x00
    
#define MOTOR_INACTIVE      0x00    
#define MOTOR_ACTIVE        0x01
#define MOTOR_DEFAULT       0x02

extern uint8 Stone_Motor_Mode[MOTOR_MODE_LENGTH];

void StoneUpdateMotor(void);

CY_ISR_PROTO(TRIGGER_ISR);
CY_ISR_PROTO(TC_ISR);
CY_ISR_PROTO(MS_ISR); 
    
#endif

 


/* [] END OF FILE */
