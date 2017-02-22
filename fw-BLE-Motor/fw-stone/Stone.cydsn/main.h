/********************************************************************************
*	Contains all macros and function declaration used in the main.c file 
********************************************************************************/
#if !defined(MAIN_H)
#define MAIN_H

#include <project.h>
#include "Stone_BLEApplications.h"
   
    
/* General Macros */
#define TRUE							1
#define FALSE							0
#define ZERO							0
#define TRANSFER_CMPLT      (0x00u)
#define TRANSFER_ERROR      (0xFFu)
    
/* Macros for LED ON and OFF values */
#define LED_ON							0x00
#define LED_OFF							0x01
    

    
/****************************************************************************/
	
/**************************Function Declarations*****************************/
CY_ISR_PROTO(MyISR);

#endif

/* [] END OF FILE */

