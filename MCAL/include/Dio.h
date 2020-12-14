/******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.h
 *
 * Description: Header file for Dio Module.
 *
 * Author: sayed mohsen
 ******************************************************************************/

#ifndef DIO_H
#define DIO_H

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "bit_math.h"
#include "Dio_cfg.h"


/*
 * Macros for Dio Status
 */
#define DIO_INITIALIZED (1U)
#define DIO_NOT_INITIALIZED (0U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef enum
{
  DIO_PORTA,
  DIO_PORTB,
  DIO_PORTC,
  DIO_PORTD,
  DIO_PORTE,
  DIO_PORTF
} Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;

/* Structure for Dio_ChannelGroup */
typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;

typedef struct
{
  /* Member contains the ID of the Port that this channel belongs to */
  Dio_PortType Port_Num;
  /* Member contains the ID of the Channel*/
  Dio_ChannelType Ch_Num;
} Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver */
typedef struct
{
  Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
  Dio_PortType ports[DIO_CONFIGURED_PORTS];
  Dio_ChannelGroupType groups[DIO_CONFIGURED_GROUPS];
} Dio_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for DIO read Channel API */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/* Function for DIO write Channel API */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Function for DIO read Port API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function for DIO write Port API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Function for DIO Initialization API */
void Dio_Init(Dio_ConfigType *ConfigPtr);

/* Function for DIO flip channel API */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern Dio_ConfigType Dio_Configuration;

#endif /* DIO_H */
