/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for Port Module.
 *
 * Author:  sayed mohsen
 ******************************************************************************/

#include "Port.h"

/* PB structure used with Port_Init API */
 Port_ConfigType Port_Configuration =
 {																	 
			{
				   /*Channnel--Direction--InitialValue--PinMode--internalAttach--CurrentDrive---ExtInterrupt      */
					{PORT_PA1,PORT_PIN_OUT,PIN_INITIAL_LOW,PORT_MODE_DIO,PORT_INTERNALATTACH_NA,PORT_PIN_CURRENTDRIVE_2MA,PORT_PIN_INTDISABLE},
					{PORT_PA1,PORT_PIN_IN,PIN_INITIAL_NA,PORT_MODE_DIO,PORT_INTERNALATTACH_NA,PORT_PIN_CURRENTDRIVE_2MA,PORT_PIN_INTDISABLE},
					{PORT_PA1,PORT_PIN_OUT,PIN_INITIAL_LOW,PORT_MODE_DIO,PORT_INTERNALATTACH_NA,PORT_PIN_CURRENTDRIVE_2MA,PORT_PIN_INTDISABLE},
			}
	
	};
