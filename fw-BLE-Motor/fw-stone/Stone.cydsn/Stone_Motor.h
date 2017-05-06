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
#include "Stone_Motor_Sequence.h"
    
#define MOTOR_LENGTH     4 
    
#define MOTOR_ON		0x01
#define MOTOR_OFF       0x00
    
#define MOTOR_INACTIVE      0x00    
#define MOTOR_ACTIVE        0x01
#define MOTOR_DEFAULT       0x02
    
/* Define Location of Motor Register */
#define MOTOR_ON_INDEX      0x00
#define MOTOR_MODE_INDEX    0x01
#define MOTOR_TIME_INDEX    0x02
#define MOTOR_PWM_INDEX     0x03

extern volatile uint8 Stone_Motor[MOTOR_LENGTH];
extern const uint8 Test[PERIOD_PER_CYCLE_RUN];

void StoneUpdateMotor(void);

CY_ISR_PROTO(TRIGGER_ISR);
CY_ISR_PROTO(TC_ISR);
CY_ISR_PROTO(MS_ISR); 
    
#endif

 


/* [] END OF FILE */
