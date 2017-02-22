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

#include <main.h> 
#include "Stone_LED.h"

uint8 LED_Mode[LED_MODE_LENGTH];

void UpdateLED(void)
{
    
    if (LED_Mode[MODE0] == 0x01)
    {
        LED_Write(0);
        
    } else {
        LED_Write(1);
    }
                
}


/* [] END OF FILE */
