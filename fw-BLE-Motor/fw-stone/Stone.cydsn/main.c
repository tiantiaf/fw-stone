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
#include "Stone_Motor.h"
#include "Stone_BLEApplications.h"
#include "Stone_Init.h"
#include "Stone_LED.h"


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitializeSystem();
    
    
    for(;;)
    {
        /* Place your application code here. */
        /*Process event callback to handle BLE events. The events generated and 
		* used for this application are inside the 'CustomEventHandler' routine*/
        CyBle_ProcessEvents();
		
		if(TRUE == deviceConnected)
		{
            /*Process event callback to handle BLE events. The events generated and 
    		* used for this application are inside the 'CustomEventHandler' routine*/
            CyBle_ProcessEvents();
			
            
			if(TRUE == stoneMotorUpdateEnable)
			{
                StoneUpdateMotor();
                stoneMotorUpdateEnable = FALSE;
			}
		}
    }
}


/* [] END OF FILE */
