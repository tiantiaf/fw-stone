/********************************************************************************
*	Contains all macros and function declaration used in the main.c file 
********************************************************************************/
#if !defined(MAIN_H)
#define MAIN_H

#include <project.h>
#include <BLEApplications.h>
/* General Macros */
#define TRUE							1
#define FALSE							0
#define ZERO							0
#define TRANSFER_CMPLT    (0x00u)
#define TRANSFER_ERROR    (0xFFu)
/****************************************************************************/
	
/**************************Function Declarations*****************************/
CY_ISR_PROTO(MyISR);

#endif

/* [] END OF FILE */

