/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for Port Module.
 *
 * Author:  sayed mohsen
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "bit_math.h"
#include "Port_Cfg.h"

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED (1U)
#define PORT_NOT_INITIALIZED (0U)

#define NUMBER_OF_CHANNELS_PER_PORT 8
#define GPIO_COMMIT_UNLOCKING_VALUE 0x4C4F434B

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef enum
{

    /*PORTA*/
    PORT_PA0 = 0,
    PORT_PA1,
    PORT_PA2,
    PORT_PA3,
    PORT_PA4,
    PORT_PA5,
    PORT_PA6,
    PORT_PA7,
    /*PORTB*/
    PORT_PB0 = 8,
    PORT_PB1,
    PORT_PB2,
    PORT_PB3,
    PORT_PB4,
    PORT_PB5,
    PORT_PB6,
    PORT_PB7,
    /*PORTC*/
    PORT_PC0 = 16,
    PORT_PC1,
    PORT_PC2,
    PORT_PC3,
    PORT_PC4,
    PORT_PC5,
    PORT_PC6,
    PORT_PC7,
    /*PORTD*/
    PORT_PD0 = 24,
    PORT_PD1,
    PORT_PD2,
    PORT_PD3,
    PORT_PD4,
    PORT_PD5,
    PORT_PD6,
    PORT_PD7,
    /*PORTE */
    PORT_PE0 = 32,
    PORT_PE1,
    PORT_PE2,
    PORT_PE3,
    PORT_PE4,
    PORT_PE5,
    /*PORTF*/
    PORT_PF0 = 40,
    PORT_PF1,
    PORT_PF2,
    PORT_PF3,
    PORT_PF4
} Port_PinType;
typedef enum
{
    PORT_PORTA,
    PORT_PORTB,
    PORT_PORTC,
    PORT_PORTD,
    PORT_PORTE,
    PORT_PORTF
} Port_PortType;
/*
I/O pins on Stellaris and Tiva  microcontrollers have a wide range of alternative functions:

�  UART                           Universal asynchronous receiver/transmitter

�  SSI                                Synchronous serial interface

�  I2C                                Inter-integrated circuit

�  Timer                            Periodic interrupts, input capture, and output compare

�  PWM                            Pulse width modulation

�  ADC                              Analog to digital converter, measure analog signals

�  Analog Comparator      Compare two analog signals

�  QEI                              Quadrature encoder interface

�  USB                              Universal serial bus

�  Ethernet                        High-speed network

�  CAN                             Controller area network

*/
typedef enum
{
    PORT_MODE_DIO,
    PORT_MODE_UART_TX,
    PORT_MODE_UART_RX,
    PORT_MODE_SSI_CLK,
    PORT_MODE_SSI_FSS,
    PORT_MODE_SSI_RX,
    PORT_MODE_SSI_TX,
    PORT_MODE_I2C_SCL,
    PORT_MODE_I2C_SDA,
    PORT_MODE_PWM,
    PORT_MODE_CCP,
    PORT_MODE_AIN,
    PORT_MODE_CAN_RX,
    PORT_MODE_CAN_TX
} Port_PinModeType;

typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
} Port_PinDirectionType;

typedef enum
{
    PORT_INTERNALATTACH_NA,
    PORT_INTERNALATTACH_PULLUPRES,
    PORT_INTERNALATTACH_PULLDOWNRES,
    PORT_INTERNALATTACH_OPENDRAIN,

} Port_InternalAttachType;
typedef enum
{
    PIN_INITIAL_NA,
    PIN_INITIAL_LOW = 0,
    PIN_INITIAL_HIGH
} Port_PinInitialValueType;
typedef enum
{
    PORT_INTDISABLE,
    PORT_INTFALLINGEDGE,
    PORT_INTRISINGEDGE,
    PORT_INTBOTHEDGES
} Port_IntCtrType;
typedef enum
{
    PORT_PIN_DIGITAL,
    PORT_PIN_ANALOG
} Port_PinGpioMode;
typedef enum
{
    PORT_PIN_CURRENTDRIVE_2MA,
	  PORT_PIN_CURRENTDRIVE_4MA,
	  PORT_PIN_CURRRNTDRIVE_8MA
} Port_PinCurrentDriveType;

typedef enum {
	  PORT_PIN_INTDISABLE,
    PORT_PIN_INTFALLINGEDGE,
    PORT_PIN_INTRISINGEDGE,
    PORT_PIN_INTBOTHEDGES
}Port_PinExtIntCtrlType;

typedef struct
{
    Port_PinType ChannelNumber;
    Port_PinDirectionType PinDirection;
	Port_PinInitialValueType pinInitialValue;
    Port_PinModeType pinMode;
    Port_InternalAttachType ExtAttach;
		Port_PinCurrentDriveType currentDrive ; 
		Port_PinExtIntCtrlType intCtrl ; 
} Port_ConfigChannel;

/*Type of the external data structure containing the initialization data for this module. */
typedef struct
{
    Port_ConfigChannel port_channels[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Initializes the Port Driver module */
void Port_Init(Port_ConfigType *ConfigPtr);

/* Sets the port pin direction */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

/*Sets the port pin mode*/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Port and other modules */
extern  Port_ConfigType Port_Configuration;

#endif /* PORT_H */
