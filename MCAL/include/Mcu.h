/********************************************************************************************************************
 *
 * Module: Microcontroller Unit Driver 
 *
 * File Name: Mcu.h
 *
 * Description:
 * The MCU driver provides services for basic microcontroller initialization, power down functionality, 
 * reset and microcontroller specific functions required from other MCAL software modules.
 *
 * Author: Sayed Mohsen
 *
 **********************************************************************************************************************/


#ifndef MCU_H_
#define MCU_H_


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Mcu_cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*reset cause after reset. */
#define REST_CAUSE_EXTERNAL_RESET (uint32)1
#define REST_CAUSE_POWER_ON_RESET (uint32)2
#define REST_CAUSE_BROWN_OUT_RESET (uint32)4
#define REST_CAUSE_WDT0_RESET (uint32)8
#define REST_CAUSE_SOFTWARE_RESET (uint32)16
#define REST_CAUSE_WDT1_RESET (uint32)32
#define REST_CAUSE_MOSC_FAILURE_RESET (uint32)65536

/* Main OSC Clock Source Predefined Set Value :Mask*/
#define SYSCTL_RCC_XTAL_4MHZ    0x00000180  // 4 MHz
#define SYSCTL_RCC_XTAL_4_09MHZ 0x000001C0  // 4.096 MHz
#define SYSCTL_RCC_XTAL_4_91MHZ 0x00000200  // 4.9152 MHz
#define SYSCTL_RCC_XTAL_5MHZ    0x00000240  // 5 MHz
#define SYSCTL_RCC_XTAL_5_12MHZ 0x00000280  // 5.12 MHz
#define SYSCTL_RCC_XTAL_6MHZ    0x000002C0  // 6 MHz
#define SYSCTL_RCC_XTAL_6_14MHZ 0x00000300  // 6.144 MHz
#define SYSCTL_RCC_XTAL_7_37MHZ 0x00000340  // 7.3728 MHz
#define SYSCTL_RCC_XTAL_8MHZ    0x00000380  // 8 MHz
#define SYSCTL_RCC_XTAL_8_19MHZ 0x000003C0  // 8.192 MHz
#define SYSCTL_RCC_XTAL_10MHZ   0x00000400  // 10 MHz
#define SYSCTL_RCC_XTAL_12MHZ   0x00000440  // 12 MHz
#define SYSCTL_RCC_XTAL_12_2MHZ 0x00000480  // 12.288 MHz
#define SYSCTL_RCC_XTAL_13_5MHZ 0x000004C0  // 13.56 MHz
#define SYSCTL_RCC_XTAL_14_3MHZ 0x00000500  // 14.31818 MHz
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540  // 16 MHz
#define SYSCTL_RCC_XTAL_16_3MHZ 0x00000580  // 16.384 MHz
#define SYSCTL_RCC_XTAL_18MHZ   0x000005C0  // 18.0 MHz (USB)
#define SYSCTL_RCC_XTAL_20MHZ   0x00000600  // 20.0 MHz (USB)
#define SYSCTL_RCC_XTAL_24MHZ   0x00000640  // 24.0 MHz (USB)
#define SYSCTL_RCC_XTAL_25MHZ   0x00000680  // 25.0 MHz (USB)


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*Typdef For Mcu Module Status */
typedef enum
{
	MCU_NOT_INITIALIZED,
	MCU_INITIALIZED,
} Mcu_statusType;

/*Typdef For Required Mcu Bus Clock*/
typedef uint32 Mcu_BusClockType ; 

/*Typdef For BusClock Divisor Type*/
typedef uint32 Mcu_SystemDivType ; 

/*Typedef For Mcu  Clock Type*/
typedef uint32 Mcu_ClockType;

/*This type specifies the reset reason in raw register format read from a reset status register.*/
typedef uint32 Mcu_RawResetType;

/*Osc Clock Source Value*/
typedef uint32 Mcu_OscClockValType ; 

/*Type Definitions For Selecting the input source for the OSC. */
typedef enum
{
	CLOCK_SOURCE_MAIN_OSCILLATOR,						 /*External, Default 16Mhz launchpad*/
	CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR,			 /*16MHZ*/
	CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR_DIVDED_4, /*4MHZ*/
	CLOCK_SOURCE_LOW_FREQUENCY_INTERNAL_OSCILLATOR,		 /*30-kHz internal oscillator*/
	CLOCK_SOURCE_HIBERNTION_OSCILLATOR = 7				 /*32.768-kHz external oscillator*/
}Mcu_OscClockSourceType ;

/*Type Definition For Main OSC Attached Crystal Clock Source Value*/
typedef enum 
{
	XTAL_4MHZ  ,  
	XTAL_4_09MHZ ,
	XTAL_4_91MHZ ,
	XTAL_5MHZ    ,
	XTAL_5_12MHZ ,
	XTAL_6MHZ    ,
	XTAL_6_14MHZ ,
	XTAL_7_37MHZ ,
	XTAL_8MHZ    ,
	XTAL_8_19MHZ ,
	XTAL_10MHZ   ,
	XTAL_12MHZ   ,
	XTAL_12_2MHZ ,
	XTAL_13_5MHZ ,
	XTAL_14_3MHZ ,
	XTAL_16MHZ  ,
	XTAL_16_3MHZ,
	XTAL_18MHZ  ,
	XTAL_20MHZ  ,
	XTAL_24MHZ ,
	XTAL_25MHZ,
}Mcu_ExternalCrystalValueType;

/*This is the type of the reset enumerator containing the subset of reset types That are supported by hardware.*/
typedef enum
{
	MCU_POWER_ON_RESET,
	MCU_WATCHDOG0_RESET,
	MCU_WATCHDOG1_RESET,
	MCU_BROWN_OUT_RESET,
	MCU_SW_RESET,
	MCU_MOSC_FAILURE_RESET,
	MCU_EXTERNAL_RESET,
	MCU_RESET_UNDEFINED,
} Mcu_ResetType;

/*Type Defintion For Mcu Periphrals*/
typedef enum
{
	SYSCTL_WD,
	SYSCTL_TIMER,
	SYSCTL_GPIO,
	SYSCTL_CDMA,
	SYSCTL_CHIB,
	SYSCTL_CUART,
	SYSCTL_CSSI,
	SYSCTL_CI2C,
	SYSCTL_CUSB,
	SYSCTL_CCAN,
	SYSCTL_CADC,
	SYSCTL_CACMP,
	SYSCTL_CPWM,
	SYSCTL_CQEI,
	SYSCTL_CEEPROM,
	SYSCTL_CWTIMER,
} Mcu_PeriphralType;

/*instance For For each Periphral ..Ex =Uart0*/
typedef uint8 Mcu_periphralInstanceType;

/*Periphral Clock Configurations*/
typedef struct
{
	Mcu_PeriphralType perph;
	Mcu_periphralInstanceType instance;
} Mcu_periphralClockSettingsType;

/*Type Definitions For  PLL USage .*/
typedef enum
{
	MCU_PLL_POWERED_ON,/*Use PLL*/
	MCU_PLL_POWERD_OFF /*Dpnt USe PLL*/
} Mcu_PllUsageType;

/*Type Definitions For Current  PLL Status. */
typedef enum
{
	MCU_PLL_LOCKED,			 /*The PLL is powered and locked.*/
	MCU_PLL_UNLOCKED,		 /*The PLL is unpowered or is not yet locked.*/
	MCU_PLL_STATUS_UNDEFINED /*if this function is called prior to calling of the init function*/
} Mcu_PllStatusType;

/*Typedef For Pll Divisor*/
typedef enum {
	NA,/*in Case Pll Powered Off*/
	MCU_PLL_400Mhz ,/*the output frequency of the PLL is always 400 MHz and it is independent on the input clock sources.*/
	MCU_PLL_400MHZ_DIV_2 /* the output frequency of 400 MHz is pre-divided by 2 (becomes 200 MHz)*/
}Mcu_PllDevisorType;

/*Pll Configurations*/
typedef struct
{
	Mcu_PllUsageType pllUse;
	Mcu_PllDevisorType PllDiv;
} Mcu_PllConfigType;

/*This type specifies the identification (ID) for a RAM section, which is configured in*/
typedef uint32 Mcu_RamSectionType;

/*RAM Config*/
typedef struct
{
	uint32 * ramSectionStartAddress;
	uint32   ramSectionSize;
	uint32 	ramSectionDefaultValue;
} Mcu_RamSectionConfigType;

/*Mcu Clock Config*/
typedef struct 
{
	Mcu_OscClockSourceType clockSource ; 
	Mcu_ExternalCrystalValueType xtal ;
	Mcu_PllConfigType pllConfig ; 
	Mcu_BusClockType desiredClock ; 
}Mcu_ClockConfigType;

typedef struct
{
	Mcu_RamSectionConfigType ramConfigArr[CONFIGURED_RAM_SECTIONS]; 
	Mcu_periphralClockSettingsType *perphClock; 
	Mcu_ClockConfigType ConfiguredclockSettings[NUM_OF_CLOCK_SETTINGS];
} Mcu_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Mcu_Init(const Mcu_ConfigType *ConfigPtr);
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection);
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);
Mcu_ResetType Mcu_GetResetReason(void);
Mcu_RawResetType Mcu_GetResetRawValue(void);
Std_ReturnType Mcu_DistributePllClock(void) ; 
Mcu_PllStatusType Mcu_GetPllStatus(void);
void Mcu_PerformReset(void);

#endif
/**********************************************************************************************************************
 *  END OF FILE: MCU_H.h
 *********************************************************************************************************************/
