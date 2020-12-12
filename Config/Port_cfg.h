/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for Port Module.
 *
 * Author:  sayed mohsen
 ******************************************************************************/
#ifndef PORT_CFG_H
#define PORT_CFG_H

/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNLES              (3U)




#define portConf_INT0_CHANNEL_ID_INDX 0X00
#define portConf_INT0_CHANNEL_CHANNEL_NUMBER PORT_PIN0
#define portConf_INT0_CHANNEL_PORT_NUMBER  PORTD_ID
#define portConf_INT0_CHANNEL_CHANNEL_DIRECTION PORT_PIN_IN
#define portConf_INT0_CHANNEL_INPUT_PIN_MODE	Enable_Pull_up


#define portConf_LED_CHANNEL_ID_INDX 0X01
#define portConf_LED_CHANNEL_CHANNEL_NUMBER PORT_PIN2
#define portConf_LED_CHANNEL_PORT_NUMBER  PORTB_ID
#define portConf_LED_CHANNEL_CHANNEL_DIRECTION PORT_PIN_OUT
#define portConf_LED_CHANNEL_INPUT_PIN_MODE	initial_Low


#define portConf_ADC_CHANNEL_ID_INDX 0X02
#define portConf_ADC_CHANNEL_CHANNEL_NUMBER PORT_PIN2
#define portConf_ADC_CHANNEL_PORT_NUMBER  PORTA_ID
#define portConf_ADC_CHANNEL_CHANNEL_DIRECTION PORT_PIN_IN
#define portConf_ADC_CHANNEL_INPUT_PIN_MODE	Disable_Pull_up

#endif



