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
#include <BLEApplications.h>

/*****************************************************************************
* Function Prototypes
*****************************************************************************/
static void InitializeSystem(void);
static void UpdateLED(void);

extern uint8 LED_Mode[LED_MODE_LENGTH];

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitializeSystem();
    
    LED1_Write(1);
    LED2_Write(1);
    
    
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
			
			/* Update LED mode */
			if(TRUE == ledUpdateEnabled)
			{
                UpdateLED();
				ledUpdateEnabled = FALSE;
			}
		}
    }
}

/*******************************************************************************
* Function Name: InitializeSystem
********************************************************************************
* Summary:
* Start the components and initialize system.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitializeSystem(void)
{
	/* Enable global interrupt mask */
	CyGlobalIntEnable; 
		
	/* Start BLE component and register the CustomEventHandler function. This 
	 * function exposes the events from BLE component for application use */
    CyBle_Start(CustomEventHandler);	
    
    PWM_1_Init();
    
	
}

void UpdateLED(void)
{
    PWM_1_Stop();
    
    if (LED_Mode[MODE0] == 0x01)
    {
        //LED1_Write(0);
        
    } else {
        //LED1_Write(1);
    }
    
    if (LED_Mode[MODE1] == 0x02)
    {
        //LED2_Write(0);
    } else {
        //LED2_Write(1);
    }
    
    if (LED_Mode[MODE2] <= 100)
    {
        PWM_1_WriteCompare(LED_Mode[MODE2]);
    }
    
    PWM_1_Start();
                
}

/* [] END OF FILE */
