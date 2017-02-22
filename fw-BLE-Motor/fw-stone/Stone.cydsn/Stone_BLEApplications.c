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

#include <main.h>
#include "Stone_BLEApplications.h"
#include "Stone_LED.h"
#include "Stone_Motor.h"

CYBLE_CONN_HANDLE_T  connectionHandle;

CYBLE_GATT_HANDLE_VALUE_PAIR_T      setHandle;
CYBLE_GATTS_HANDLE_VALUE_NTF_T      I2cHandle;

uint8 deviceConnected           = FALSE;
uint8 ledUpdateEnabled          = FALSE;
uint8 charNotificationEnabled   = FALSE;
uint8 restartAdvertisement      = FALSE;
uint32 negotiatedMtu            = 23;

uint8 stoneMotorUpdateEnable    = FALSE;

static uint8 isConnectionUpdateRequested = TRUE;
static CYBLE_GAP_CONN_UPDATE_PARAM_T ConnectionParam =
{
	CONN_PARAM_UPDATE_MIN_CONN_INTERVAL,
	CONN_PARAM_UPDATE_MAX_CONN_INTERVAL,
	CONN_PARAM_UPDATE_SLAVE_LATENCY,
	CONN_PARAM_UPDATE_SUPRV_TIMEOUT
};

uint8 busyStatus = 0;

void CustomEventHandler(uint32 event, void * eventParam)
{
    
    /* Local variable to store the data received as part of the Write request
	* events */
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch (event)
	{
        case CYBLE_EVT_STACK_ON:
    		restartAdvertisement = TRUE;
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;

    	case CYBLE_EVT_TIMEOUT:
            restartAdvertisement = TRUE;
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
    		break;
       
        /**********************************************************
		*                       GAP Events
		***********************************************************/
    	case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:

    		/* If the current BLE state is Disconnected, then the Advertisement
    		* Start Stop event implies that advertisement has stopped */
    		if (CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
    		{
    			/* Set restartAdvertisement flag to allow calling Advertisement
    			* API from main function */
    			restartAdvertisement = TRUE;
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);   
    		}
    		break;

    	case CYBLE_EVT_GAP_DEVICE_CONNECTED:
    		/* This event is received when device is connected over GAP layer */
    		break;

    	case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
    		restartAdvertisement = TRUE;
    		break;
            
        /**********************************************************
		*                       GATT Events
		***********************************************************/
        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
    		negotiatedMtu = (((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->mtu < CYBLE_GATT_MTU) ?
    			((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->mtu : CYBLE_GATT_MTU;
    		break;    
            
    	case CYBLE_EVT_GATT_CONNECT_IND:
    		connectionHandle = *(CYBLE_CONN_HANDLE_T  *)eventParam;
    		deviceConnected = TRUE;
    		break;

    	case CYBLE_EVT_GATT_DISCONNECT_IND:
    		deviceConnected = FALSE;
    		isConnectionUpdateRequested = TRUE;
    		break;

    	case CYBLE_EVT_GATTS_WRITE_REQ:
    		wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            /*
    		if (CYBLE_STONE_BLE_CTR_LED_CHAR_HANDLE == wrReqParam->handleValPair.attrHandle)
    		{
    			ledUpdateEnabled = TRUE;
    		}
            
            if (CYBLE_STONE_BLE_CTR_LED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE == wrReqParam->handleValPair.attrHandle)
            {
               
                charNotificationEnabled = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,FALSE, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
            }*/
          
    		CyBle_GattsWriteRsp(connectionHandle);
    		break;
            
        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
            
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            
            
            if (CYBLE_STONE_BLE_CTR_MOTOR_CHAR_HANDLE == wrReqParam->handleValPair.attrHandle)
            {
                Stone_Motor[MOTOR_ON_INDEX] = wrReqParam->handleValPair.value.val[MOTOR_ON_INDEX];
                Stone_Motor[MOTOR_MODE_INDEX] = wrReqParam->handleValPair.value.val[MOTOR_MODE_INDEX];
                
                stoneMotorUpdateEnable = TRUE;
            }
           
            if (CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE)
            {
                uint8 abc[4] = { 0,0,0,0 };
        		abc[MOTOR_ON_INDEX] = Stone_Motor[MOTOR_ON_INDEX];
        		abc[MOTOR_MODE_INDEX] = Stone_Motor[MOTOR_MODE_INDEX];
        		
                
                UpdateMotorCharacteristic(abc, 4);
        		
            }
            

    	case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
    		isConnectionUpdateRequested = FALSE;
    		break;

    	case CYBLE_EVT_STACK_BUSY_STATUS:
    		busyStatus = *(uint8*)eventParam;
    		break;

    	default:

    		break;
              
    }
        
}

void UpdateSettings(void)
{
    if (deviceConnected && isConnectionUpdateRequested)
	{
		isConnectionUpdateRequested = FALSE;

		CyBle_L2capLeConnectionParamUpdateRequest(connectionHandle.bdHandle, &ConnectionParam);
	}

}

void UpdateMotorCharacteristic(uint8* motorData, uint8 len)
{
    setHandle.attrHandle = CYBLE_STONE_BLE_CTR_MOTOR_CHAR_HANDLE;
	setHandle.value.val = motorData;
	setHandle.value.len = len;

	CyBle_GattsWriteAttributeValue(&setHandle, FALSE, &connectionHandle, FALSE);
	CyBle_ProcessEvents();
    
}


void UpdateLEDCharacteristic(uint8* ledData, uint8 len)
{
    setHandle.attrHandle = CYBLE_STONE_BLE_CTR_LED_CHAR_HANDLE;
	setHandle.value.val = ledData;
	setHandle.value.len = len;

	CyBle_GattsWriteAttributeValue(&setHandle, FALSE, &connectionHandle, FALSE);
	CyBle_ProcessEvents();
    
}










