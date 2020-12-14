/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for Port Module.
 *
 * Author:	sayed mohsen
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_hw.h"

STATIC uint8 g_PortStatus = PORT_NOT_INITIALIZED;
STATIC Port_ConfigChannel *g_PortConfiguredChannels = NULL_PTR;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(Port_ConfigType *ConfigPtr)
{
	uint8 localPort;
	uint8 localPin;
	Port_PinModeType pinMode;
	Port_PinDirectionType pinDir;
	Port_InternalAttachType pinAttach;
	Port_PinInitialValueType pinInitialValue;
	Port_PinCurrentDriveType outputCurrentDrive;
	Port_PinExtIntCtrlType intCtrl;
	uint8 itr;
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR != ConfigPtr)
	{
		g_PortConfiguredChannels = ConfigPtr->port_channels;
		for (itr = 0; itr < PORT_CONFIGURED_CHANNLES; itr++)
		{
			/*Decode Configuration Structure*/
			localPort = g_PortConfiguredChannels[itr].ChannelNumber / NUMBER_OF_CHANNELS_PER_PORT;
			localPin = g_PortConfiguredChannels[itr].ChannelNumber % NUMBER_OF_CHANNELS_PER_PORT;
			pinDir = g_PortConfiguredChannels[itr].PinDirection;
			pinAttach = g_PortConfiguredChannels[itr].ExtAttach;
			pinInitialValue = g_PortConfiguredChannels[itr].pinInitialValue;
			outputCurrentDrive = g_PortConfiguredChannels[itr].currentDrive;
			intCtrl = g_PortConfiguredChannels[itr].intCtrl;

			/*Unlock Pin Functions*/
			GPIOLOCK(localPort) = GPIO_COMMIT_UNLOCKING_VALUE;
			GPIOCR(localPort) |= (1 << localPin);

			/*1- Set Pin Direction */
			GPIODIR(localPort) = (GPIODIR(localPort) & ~(1 << localPin)) | (pinDir << localPin);

			/*2- Set Pin initial Value*/
			if (PORT_PIN_OUT == pinDir)
			{
				GPIODATA(localPort) = (GPIODATA(localPort) & ~(1 << localPin)) | (pinInitialValue << localPin);
			}

			/*3-Set Pin Mode */
			if (PORT_MODE_DIO == pinMode)
			{
				GPIOAFSEL(localPort) &= ~(1 << localPin);
				GPIODEN(localPort) |= (1 << localPin);
			}
			else if (PORT_MODE_AIN == pinMode)
			{
				GPIOAFSEL(localPort) |= (1 << localPin);
				GPIOAMSEL(localPort) |= (1 << localPin);
			}
			else
			{
				GPIOAFSEL(localPort) |= (1 << localPin);
				/*Set Pin Alternating Function*/
				GPIOPCTL(localPort) |= (pinMode << (4 * localPin));
			}

			/*Set Pin Internal Attachment*/
			switch (pinAttach)
			{
			case PORT_INTERNALATTACH_NA: /*Pervent compiler Warning*/
				break;
			case PORT_INTERNALATTACH_PULLUPRES:
				GPIOPUR(localPort) |= (1 << localPin);
				break;
			case PORT_INTERNALATTACH_PULLDOWNRES:
				GPIOPDR(localPort) |= (1 << localPin);
				break;
			case PORT_INTERNALATTACH_OPENDRAIN:
				GPIOODR(localPort) |= (1 << localPin);
				break;
			}

			/*Set Output Drive Current*/
			switch (outputCurrentDrive)
			{
			case PORT_PIN_CURRENTDRIVE_2MA:
				GPIODR2R(localPort) |= (1 << localPin);
				break;
			case PORT_PIN_CURRENTDRIVE_4MA:
				GPIODR4R(localPort) |= (1 << localPin);
				break;
			case PORT_PIN_CURRRNTDRIVE_8MA:
				GPIODR8R(localPort) |= (1 << localPin);
				break;
			}

			if (PORT_PIN_INTDISABLE == intCtrl)
			{
				GPIOIM(localPort) &= ~(1 << localPin);
			}
			else
			{
				GPIOIM(localPort) |= (1 << localPin);
				switch (intCtrl)
				{
				case PORT_PIN_INTFALLINGEDGE:
					GPIOIEV(localPort) &= ~(1 << localPin);
					break;
				case PORT_PIN_INTRISINGEDGE:
					GPIOIEV(localPort) |= (1 << localPin);
					break;
				case PORT_PIN_INTBOTHEDGES:
					GPIOIBE(localPort) |= (1 << localPin);
					break;
				default:
					break;
				}
			}

		} //end For Loop
		g_PortStatus = PORT_INITIALIZED;
	}
}

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
}

/*Sets the port pin mode*/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	if (g_PortStatus == PORT_INITIALIZED)
	{
	}
}
