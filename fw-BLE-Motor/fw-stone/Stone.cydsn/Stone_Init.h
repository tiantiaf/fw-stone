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

#if !defined(STONE_INIT_H)
#define STONE_INIT_H

#include "main.h"
#include "Stone_Motor.h"
#include "Stone_Motor_Sequence.h"
    
void InitializeSystem(void);
void InitStoneInterrupt(void);
void StopStoneInterrupt(void);
void Stone_Sequence_Init(void);

extern volatile uint8 Stone_Motor[MOTOR_LENGTH];
extern uint8 Motor_Running_Sequence[PERIOD_PER_CYCLE_RUN];

#endif

/* [] END OF FILE */
