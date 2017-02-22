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

/* [] END OF FILE */
/********************************************************************************
* Contains all macros and function declaration used in the BLEApplications.c 
* file.
********************************************************************************/
#if !defined(BLEAPPLICATIONS_H)
#define BLEAPPLICATIONS_H
#include <project.h>

#define ENABLE_LOW_POWER_MODE
    
#define MODE0   						(0)
#define MODE1						    (1)
#define MODE2						    (2)
#define MODE3					        (3)
    
/**************************Function Declarations*****************************/
void CustomEventHandler(uint32 event, void * eventParam);
void UpdateConnectionParam();
void UpdateSettings();
void UpdateDataBack();
void HandleStatusLED(void);
void UpdateLEDCharacteristic(uint8* ledData, uint8 len);
void UpdateMotorCharacteristic(uint8* MotorData, uint8 len);
/****************************************************************************/


/* LED Blink rate values for different stages of BLE connection */
#ifdef ENABLE_LOW_POWER_MODE
#define	LED_ADV_BLINK_PERIOD_ON			5
#define LED_ADV_BLINK_PERIOD_OFF		20
#else
#define	LED_ADV_BLINK_PERIOD_ON			10000
#define LED_ADV_BLINK_PERIOD_OFF		15000
#endif


/****************************************************************************/

/* Minimum connection interval = CONN_PARAM_UPDATE_MIN_CONN_INTERVAL * 1.25 ms*/
#define CONN_PARAM_UPDATE_MIN_CONN_INTERVAL 50        	
/* Maximum connection interval = CONN_PARAM_UPDATE_MAX_CONN_INTERVAL * 1.25 ms */
#define CONN_PARAM_UPDATE_MAX_CONN_INTERVAL	52        	
/* Slave latency = Number of connection events */
#define CONN_PARAM_UPDATE_SLAVE_LATENCY		0          
/* Supervision timeout = CONN_PARAM_UPDATE_SUPRV_TIMEOUT * 10*/
#define CONN_PARAM_UPDATE_SUPRV_TIMEOUT		200   



/*****************************************************************************
* Extern variables
*****************************************************************************/
extern uint8 deviceConnected;
extern uint8 ledUpdateEnabled;
extern uint8 stoneMotorUpdateEnable;
    
    
#endif

