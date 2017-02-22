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

#if !defined(STONE_LED_H)
#define STONE_LED_H
    
#include <main.h>
    
#define LED_MODE_LENGTH     4  
    
void UpdateLED(void);

extern uint8 LED_Mode[LED_MODE_LENGTH];
  
#endif

/* [] END OF FILE */
