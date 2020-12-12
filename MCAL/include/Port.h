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

#define PORTS_NUMBER 6
#define NUMBER_OF_CHANNELS_PER_PORT 8
#define GPIO_COMMIT_UNLOCKING_VALUE 0x4C4F434B

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef enum
{

    /*PORTA*/
    PA0 = 0,
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7,
    /*PORTB*/
    PB0 = 8,
    PB1,
    PB2,
    PB3,
    PB4,
    PB5,
    PB6,
    PB7,
    /*PORTC*/
    PC0 = 16,
    PC1,
    PC2,
    PC3,
    PC4,
    PC5,
    PC6,
    PC7,
    /*PORTD*/
    PD0 = 24,
    PD1,
    PD2,
    PD3,
    PD4,
    PD5,
    PD6,
    PD7,
    /*PORTE */
    PE0 = 32,
    PE1,
    PE2,
    PE3,
    PE4,
    PE5,
    /*PORTF*/
    PF0 = 40,
    PF1,
    PF2,
    PF3,
    PF4
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

typedef struct
{
    Port_PinType ChannelNumber;
    Port_PinDirectionType PinDirection;
    Port_PinModeType pinMode;
    Port_InternalAttachType ExtAttach;
    Port_PinInitialValueType pinInitialValue;
    Port_IntCtrType IntCtrl;
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
