#ifndef MCU_H_
#define MCU_H_

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*reset cause after reset. */

#define REST_CAUSE_EXTERNAL_RESET            (uint32)1
#define REST_CAUSE_POWER_ON_RESET            (uint32)2
#define REST_CAUSE_BROWN_OUT_RESET           (uint32)4
#define REST_CAUSE_WDT0_RESET                (uint32)8
#define REST_CAUSE_SOFTWARE_RESET            (uint32)16
#define REST_CAUSE_WDT1_RESET                (uint32)32
#define REST_CAUSE_MOSC_FAILURE_RESET        (uint32)65536

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
typedef enum 
{
	MCU_NOT_INITIALIZED,
	MCU_INITIALIZED,
}Mcu_statusType;


/*This type specifies the identification (ID) for a RAM section, which is configured in*/
typedef uint32  Mcu_RamSectionType ; 

/*This type specifies the reset reason in raw register format read from a reset status register.*/
typedef uint32 Mcu_RawResetType;

/*This is the type of the reset enumerator containing the subset of reset types That are supported by hardware.*/
typedef enum {
	
MCU_POWER_ON_RESET			,
MCU_WATCHDOG0_RESET         ,
MCU_WATCHDOG1_RESET         ,
MCU_BROWN_OUT_RESET ,
MCU_SW_RESET               ,
MCU_MOSC_FAILURE_RESET     ,
MCU_EXTERNAL_RESET ,
MCU_RESET_UNDEFINED			,
}Mcu_ResetType; 

/*Type Definitions For Current  PLL Status. */
typedef enum {
	MCU_PLL_LOCKED,/*The PLL is powered and locked.*/
	MCU_PLL_UNLOCKED,/*The PLL is unpowered or is not yet locked.*/
	MCU_PLL_STATUS_UNDEFINED /*if this function is called prior to calling of the init function*/
} Mcu_PllStatusType;


/*Type Definitions For Selecting the input source for the OSC. */
typedef enum {
	CLOCK_SOURCE_MAIN_OSCILLATOR,/*External, Default 16Mhz launchpad*/
	CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR,/*16MHZ*/
	CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR_DIVDED_4,/*4MHZ*/
	CLOCK_SOURCE_LOW_FREQUENCY_INTERNAL_OSCILLATOR,/*30-kHz internal oscillator*/
	CLOCK_SOURCE_HIBERNTION_OSCILLATOR =7/*32.768-kHz external oscillator*/
}Mcu_ClockType;


#endif 

