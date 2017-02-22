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

#if !defined(STONE_MOTOR_SEQUENCE_H)
#define STONE_MOTOR_SEQUENCE_H
    

#include <main.h>

#define PERIOD_PER_CYCLE_RUN    64

const uint8 Test[PERIOD_PER_CYCLE_RUN] = {25, 25, 25, 25, 25, 25, 20, 20, 99, 99,
                                    50, 48, 46, 46, 45, 43, 43, 42, 40, 40,
                                    38, 38, 38, 36, 35, 33, 33, 31, 31,
                                    31, 30, 28, 28,
                                    25, 25, 20, 25, 40, 50, 60, 25, 25,
                                    25, 25, 25, 25, 25, 25, 20, 20, 20,
                                    25, 25, 25, 25, 25, 25, 20, 20, 20,
                                    20, 20, 20, 20 };

#endif
/* [] END OF FILE */
