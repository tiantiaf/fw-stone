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

#if !defined(STONE_MOTOR_H)
#define STONE_MOTOR_H
    
#include <main.h>
    
#define MOTOR_MODE_LENGTH     4 
    
#define MOTOR_ON		0x01
#define MOTOR_OFF       0x00

extern uint8 Stone_Motor_Mode[MOTOR_MODE_LENGTH];

void UpdateMotor(void);
CY_ISR_PROTO(TRIGGER_ISR);
CY_ISR_PROTO(TC_ISR);
CY_ISR_PROTO(MS_ISR);

#endif

/* [] END OF FILE */