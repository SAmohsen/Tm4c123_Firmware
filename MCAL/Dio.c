/******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.c
 *
 * Description: Source file for Dio Module.
 *
 * Author: sayed mohsen
 ******************************************************************************/

#include "Dio.h"
#include "tm4c123gh6pm_hw.h"

STATIC Dio_ConfigChannel *Dio_PortChannels = NULL_PTR;
STATIC Dio_PortType *Dio_Ports = NULL_PTR;
STATIC Dio_ChannelGroupType *Dio_ChannelGroups = NULL_PTR;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

/*GPIO PORTS Base Addresses */
static const uint32 GPIOPortsBaseAddress[DIO_PORTS_NUMBER] =
	{
		PORTA_BASE_ADDRESS,
		PORTB_BASE_ADDRESS,
		PORTC_BASE_ADDRESS,
		PORTD_BASE_ADDRESS,
		PORTE_BASE_ADDRESS,
		PORTF_BASE_ADDRESS};

#define GPIODATA(DIO_PORT) (*(volatile uint32 *)(GPIOPortsBaseAddress[DIO_PORT] + GPIO_DATA_REGISTER_OFFSET))

/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(Dio_ConfigType *ConfigPtr)
{
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR != ConfigPtr)
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_Status = DIO_INITIALIZED;
		Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
		Dio_Ports = ConfigPtr->ports;
		Dio_ChannelGroups = ConfigPtr->groups;
	}
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	if (Level == STD_HIGH)
	{
		/* Write Logic High */
		GPIODATA(Dio_PortChannels[ChannelId].Port_Num) |= (1 << Dio_PortChannels[ChannelId].Ch_Num);
	}
	else if (Level == STD_LOW)
	{
		/* Write Logic Low */
		GPIODATA(Dio_PortChannels[ChannelId].Port_Num) &= ~(1 << Dio_PortChannels[ChannelId].Ch_Num);
	}
}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType ChannelLevel;
	/* Read the required channel */
	ChannelLevel = READ_BIT(GPIODATA(Dio_PortChannels[ChannelId].Port_Num), Dio_PortChannels[ChannelId].Ch_Num);
	return ChannelLevel;
}
/************************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a value of the port.
************************************************************************************/

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	GPIODATA(Dio_Ports[PortId]) = Level;
}

/************************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to Return the level of all channels of that port..
************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	/*read required port */
	Dio_PortLevelType PortLevel = GPIODATA(Dio_Ports[PortId]);
	return PortLevel;
}

/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to flip the level of a channel and return the level of the channel after flip.
************************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType ChannelLevel = STD_LOW;

	/* Read the required channel and write the required level */
	if (BIT_IS_SET(GPIODATA(Dio_PortChannels[ChannelId].Port_Num), Dio_PortChannels[ChannelId].Ch_Num))
	{
		CLR_BIT(GPIODATA(Dio_PortChannels[ChannelId].Port_Num), Dio_PortChannels[ChannelId].Ch_Num);
		ChannelLevel = STD_LOW;
	}
	else if (BIT_IS_CLEAR(GPIODATA(Dio_PortChannels[ChannelId].Port_Num), Dio_PortChannels[ChannelId].Ch_Num))
	{
		SET_BIT(GPIODATA(Dio_PortChannels[ChannelId].Port_Num), Dio_PortChannels[ChannelId].Ch_Num);
		ChannelLevel = STD_HIGH;
	}

	return ChannelLevel;
}

/************************************************************************************
* Service Name: Dio_ReadChannelGroup
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to  read a subset of the adjoining bits of a port.
************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
	Dio_PortLevelType groupLevel;
	groupLevel = ((GPIODATA(ChannelGroupIdPtr->PortIndex)) & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
	return groupLevel;
}

/************************************************************************************
* Service Name: Dio_WriteChannelGroup
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
* 					Level -Value to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to set a subset of the adjoining bits of a port to a specified level.
************************************************************************************/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level)
{

	GPIODATA(ChannelGroupIdPtr->PortIndex) = ((GPIODATA(ChannelGroupIdPtr->PortIndex)) & (~(ChannelGroupIdPtr->mask))) | (Level << ChannelGroupIdPtr->offset);
}
