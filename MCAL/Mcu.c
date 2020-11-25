/********************************************************************************************************************
 *
 * Module: Microcontroller Unit Driver 
 *
 * File Name: Mcu.c
 *
 * Description:
 * The MCU driver provides services for basic microcontroller initialization, power down functionality, 
 * reset and microcontroller specific functions required from other MCAL software modules.
 *
 * Author: Sayed Mohsen
 *
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mcu.h"
#include "tm4c123gh6pm_hw.h"

/**********************************************************************************************************************
*  LOCAL CONSTANT MACROS 
*********************************************************************************************************************/

/*OSC Predefined Possible Clocks*/
#define PLL_CLOCK_400 (400000000UL)
#define PLL_CLOCK_200 (200000000UL)
#define PIOSC (16000000UL)		/* Internal oscillator freq */
#define PIOSC_DIV_4 (4000000UL) /* Internal oscillator freq divided by 4 */
#define LFIOSC (30000UL)		/* Internal 30K oscillator freq */
#define XTAL32K (32768UL)		/* external 32K oscillator freq */
#define MOSC_CLOCK (ATTACHED_EXTERNAL_CRYSTAL_VALUE)

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/*global Variable To Hold Module Status */
STATIC Mcu_statusType g_Mcu_Status = MCU_NOT_INITIALIZED;

/*global Variable To Hold Mcu Configurations */
STATIC const Mcu_ConfigType *g_Mcu_Configs = NULL_PTR;

/*Mcu Periphrals Clock Gates Registers Offsets*/
STATIC const uint32 g_RcgPreiphralOfsset[16] =
	{
		SYSCTL_RCGCWD_R_OFFSET,
		SYSCTL_RCGCTIMER_R_OFFSET,
		SYSCTL_RCGCGPIO_R_OFFSET,
		SYSCTL_RCGCDMA_R_OFFSET,
		SYSCTL_RCGCHIB_R_OFFSET,
		SYSCTL_RCGCUART_R_OFFSET,
		SYSCTL_RCGCSSI_R_OFFSET,
		SYSCTL_RCGCI2C_R_OFFSET,
		SYSCTL_RCGCUSB_R_OFFSET,
		SYSCTL_RCGCCAN_R_OFFSET,
		SYSCTL_RCGCADC_R_OFFSET,
		SYSCTL_RCGCACMP_R_OFFSET,
		SYSCTL_RCGCPWM_R_OFFSET,
		SYSCTL_RCGCQEI_R_OFFSET,
		SYSCTL_RCGCEEPROM_R_OFFSET,
		SYSCTL_RCGCWTIMER_R_OFFSET};

/*The main oscillator supports the use of a select number of crystals from 4 to 25 MHz */
static const unsigned long g_mainOscillatorAttachedCrystal[21] =
	{
		SYSCTL_RCC_XTAL_4MHZ,
		SYSCTL_RCC_XTAL_4_09MHZ,
		SYSCTL_RCC_XTAL_4_91MHZ,
		SYSCTL_RCC_XTAL_5MHZ,
		SYSCTL_RCC_XTAL_5_12MHZ,
		SYSCTL_RCC_XTAL_6MHZ,
		SYSCTL_RCC_XTAL_6_14MHZ,
		SYSCTL_RCC_XTAL_7_37MHZ,
		SYSCTL_RCC_XTAL_8MHZ,
		SYSCTL_RCC_XTAL_8_19MHZ,
		SYSCTL_RCC_XTAL_10MHZ,
		SYSCTL_RCC_XTAL_12MHZ,
		SYSCTL_RCC_XTAL_12_2MHZ,
		SYSCTL_RCC_XTAL_13_5MHZ,
		SYSCTL_RCC_XTAL_14_3MHZ,
		SYSCTL_RCC_XTAL_16MHZ,
		SYSCTL_RCC_XTAL_16_3MHZ,
		SYSCTL_RCC_XTAL_18MHZ,
		SYSCTL_RCC_XTAL_20MHZ,
		SYSCTL_RCC_XTAL_24MHZ,
		SYSCTL_RCC_XTAL_25MHZ,
};

/**********************************************************************************************************************
*  LOCAL MACROS FUNCTION
*********************************************************************************************************************/
#define Mcu_peripheralEnable(periphral, instance) (*((volatile uint32 *)(SYSCTL_RCGCBASE + g_RcgPreiphralOfsset[periphral])) |= (1 << instance))

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
STATIC void Mcu_InitPll(Mcu_ClockType ClockSetting)
{
	Mcu_OscClockValType oscClockVal;
	Mcu_SystemDivType sysDiv;

	/*1-bypass PLL while initializing*/
	SYSCTL_RCC2_R |= (1 << BYPASS2);

	/*2-Activate PLL*/
	SYSCTL_RCC2_R &= ~(1 << PWRDN2);

	if (g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].pllConfig.PllDiv == MCU_PLL_400Mhz)
	{
		SYSCTL_RCC2_R &= ~(1 << DIV400); /*Disable PLL Divisor */
		oscClockVal = PLL_CLOCK_400;
	}
	else if (g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].pllConfig.PllDiv == MCU_PLL_400MHZ_DIV_2)
	{
		SYSCTL_RCC2_R |= (1 << DIV400); /*Enable PLL Divisor */
		oscClockVal = PLL_CLOCK_200;
	}
	/*Set system clock divisor.*/
	sysDiv = (oscClockVal / g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].desiredClock) - 1;
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & 0xE03FFFFF) | (sysDiv << 22);

	/*wait PLL to lock.*/
	while ((SYSCTL_RIS_R & (1 << PLLLRIS)) == 0)
		; /* wait for PLLRIS bit */

	/* select PLL as the source of system clock*/
	SYSCTL_RCC2_R &= ~(1 << BYPASS2); /* remove bypass and use the PLL */
}

STATIC Mcu_OscClockValType Mcu_GetOscClockValue(Mcu_ClockType ClockSetting)
{
	Mcu_OscClockValType oscClockVal;
	if (CLOCK_SOURCE_MAIN_OSCILLATOR == g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].clockSource)
	{
		oscClockVal = ATTACHED_EXTERNAL_CRYSTAL_VALUE;
	}
	else if (CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR == g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].clockSource)
	{
		oscClockVal = PIOSC;
	}
	else if (CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR_DIVDED_4 == g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].clockSource)
	{
		oscClockVal = PIOSC_DIV_4;
	}
	else if (CLOCK_SOURCE_LOW_FREQUENCY_INTERNAL_OSCILLATOR == g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].clockSource)
	{
		oscClockVal = LFIOSC;
	}
	return oscClockVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************
 * Service name:Mcu_Init 
 * Syntax:void Mcu_Init( const Mcu_ConfigType* ConfigPtr ) 
 * Description:This service initializes the MCU driver.
 * Service ID[hex]:0x00 
 * Sync/Async:Synchronous 
 * Reentrancy:Non
 *  Reentrant Parameters (in):ConfigPtr Pointer to MCU driver configuration set. 
 * Parameters (in-out):None 
 * Parameters (out):None 
 * Return value:None 
 * ************************************************************************************************
*/
void Mcu_Init(const Mcu_ConfigType *ConfigPtr)
{
	uint8 itr;
	if (NULL_PTR != ConfigPtr)
	{
		/*Save Configurations Structure*/
		g_Mcu_Configs = ConfigPtr;

		/*Use RCC2 To Extend RCC Functions :Writing in RCC2 Overrides RCC*/
		SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;

		/*Set oscillator source Clock :PIOSC As Initial Value*/
		SYSCTL_RCC2_R = (SYSCTL_RCC2_R & 0xFFFFFF8F) | (CLOCK_SOURCE_PRECISION_INTERNAL_OSCILLATOR<< 4);

		/* Enable Periphrals Clock Gates*/
		for (itr = 0; itr < NUM_MCU_ACTIVATED_CLOCK_GATES; itr++)
		{
			Mcu_peripheralEnable(g_Mcu_Configs->perphClock[itr].perph, g_Mcu_Configs->perphClock[itr].instance);
		}
		g_Mcu_Status = MCU_INITIALIZED;
	}
}

/***********************************************************************************************************************
 * Service name:Mcu_InitRamSection
 * Syntax:Std_ReturnType Mcu_InitRamSection( Mcu_RamSectionType RamSection ) 
 * Description:This service initializes the RAM section wise.
 * Service ID[hex]:0x01
 * Sync/Async:Synchronous 
 * Reentrancy:Reentrant 
 * Parameters (in):RamSection :selects RAM memory section provided in configuration set 
 * Parameters (in-out):None
 *  Parameters (out):None 
 * Return value:Std_ReturnTypeE_OK: command has been accepted E_NOT_OK: command has not been accepted e.g. due to pa-rameter error 
******************************************************************************************************************************/
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
	Std_ReturnType ret = E_NOT_OK;
	uint32 size = g_Mcu_Configs->ramConfigArr[RamSection].ramSectionSize;
	uint32 *startAddress = g_Mcu_Configs->ramConfigArr[RamSection].ramSectionStartAddress;
	if (MCU_INITIALIZED == g_Mcu_Status)
	{
		if (RamSection <= CONFIGURED_RAM_SECTIONS)
		{
			while (size > 0)
			{
				*(startAddress++) = g_Mcu_Configs->ramConfigArr[RamSection].ramSectionDefaultValue;
				size = size - PLATFORM_WORD_LENGTH_BYTES;
			}
			ret = E_OK;
		}
	}
	return ret;
}

/********************************************************************************************************
 * Service name:Mcu_InitClock 
 * Syntax: Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting )
 * Description:This service initializes the PLL and other MCU specific clock options.
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous 
 * Reentrancy:Non Reentrant 
 * Parameters (in):ClockSetting
 * Parameters (in-out):None 
 * Parameters (out):None 
 * Return value: Std_ReturnType E_OK: Command has been accepted
 * 								 E_NOT_OK: Command has not been accepted 
 * *************************************************************************************************/

Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
	Mcu_OscClockValType oscClockVal;
	Mcu_SystemDivType sysDiv;
	Std_ReturnType ret;
	if (ClockSetting >= NUM_OF_CLOCK_SETTINGS)
	{
		ret = E_NOT_OK;
	}
	else if (g_Mcu_Status == MCU_NOT_INITIALIZED)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/*Set oscillator source Clock */
		SYSCTL_RCC2_R = (SYSCTL_RCC2_R & 0xFFFFFF8F) | (g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].clockSource << 4);
		oscClockVal = Mcu_GetOscClockValue(ClockSetting); /*Save Osc Clock*/
		/*
	 	 * The ARM® Cortex®-M4 Core or processor can be driven by
	 	 *	(1)Any clock source (MOSC,PIOSC,PIOSC/4,LFIOS,)
	 	 *	(2)Phase Locked Loop (PLL) clock generator.
		 */
		if (g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].pllConfig.pllUse == MCU_PLL_POWERED_ON)
		{
			/*init PLL */
			/*The output frequency of the PLL is always 400 MHz and it is independent on the input clock sources.*/
			Mcu_InitPll(ClockSetting);
		}
		else if (g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].pllConfig.pllUse == MCU_PLL_POWERD_OFF)
		{
			/*1-bypass PLL */
			SYSCTL_RCC2_R |= (1 << BYPASS2);

			/*Disable PLL*/
			SYSCTL_RCC2_R |= (1 << PWRDN2);

			/*Main OSC Setup */
			if (CLOCK_SOURCE_MAIN_OSCILLATOR == g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].clockSource)
			{
				Mcu_ExternalCrystalValueType xtal = g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].xtal; /*get Attached Crystal Value*/
				SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;															   /*Clear Attached Crystal Value*/
				SYSCTL_RCC_R |= g_mainOscillatorAttachedCrystal[xtal];										   /*Set external crystal value XTAL*/
				/*Enable Main Oscillator*/
				SYSCTL_RCC_R &= ~(1 << MOSCDIS);
			}
		}
		/*Set system clock divisor.*/
		sysDiv = (oscClockVal / g_Mcu_Configs->ConfiguredclockSettings[ClockSetting].desiredClock) - 1;
		SYSCTL_RCC2_R = (SYSCTL_RCC2_R & 0xE03FFFFF) | (sysDiv << 22);
	}
	return ret;
}

/******************************************************************************************************************
 * Service name: Mcu_DistributePllClock 
 * Syntax: Std_ReturnType Mcu_DistributePllClock(void) 
 * Description:This service activates the PLL clock to the MCU clock distribution.
 * Service ID[hex]:0x03 
 * Sync/Async:Synchronous 
 * Reentrancy:Non Reentrant
 *  Parameters (in):None 
 * Parameters (in-out):None 
 * Parameters (out):None
 *  Return value: Std_ReturnType E_OK: Command has been accepted E_NOT_OK: Command has not been accepted 
******************************************************************************************************************/
Std_ReturnType Mcu_DistributePllClock(void)
{
	/*If the function Mcu_DistributePllClock is called before PLL has locked,this function shall return E_NOT_OK immediately,*/
	Std_ReturnType ret = E_NOT_OK;

	/*Check iF Pll Status Is Activated and PLL Status Is Locked*/
	if ((SYSCTL_RCC2_R & (1 << PWRDN2)) == MCU_PLL_POWERED_ON)
	{
		if (SYSCTL_PLLSTAT_R == MCU_PLL_LOCKED)
		{
			/* remove bypass and activate the PLL clock to the MCU clock distribution*/
			SYSCTL_RCC2_R &= ~(1 << BYPASS2);
		}
	}
	return ret;
}

/********************************************************************************************************************
 * Service name:Mcu_GetPllStatus 
 * Syntax:Mcu_PllStatusType Mcu_GetPllStatus(void) 
 * Description:This service provides the lock status of the PLL.
 * Service ID[hex]:0x04 
 * Sync/Async:Synchronous 
 * Reentrancy:Reentrant 
 * Parameters (in):None 
 * Parameters (in-out):None 
 * Parameters (out):None 
 * Return value:Mcu_PllStatusType
********************************************************************************************************************/
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
	Mcu_PllStatusType currentPllStatus;
	if (MCU_NOT_INITIALIZED == g_Mcu_Status)
	{
		/* Function Shall Return MCU_PLL_STATUS_UNDEFINED if this function is called prior to calling of
		 * the function Mcu_Init.*/
		currentPllStatus = MCU_PLL_STATUS_UNDEFINED;
	}
	else
	{
		currentPllStatus = ((SYSCTL_PLLSTAT_R == 0) ? MCU_PLL_UNLOCKED : MCU_PLL_LOCKED);
	}
	return currentPllStatus;
}

/*********************************************************************************************************************
 * Service name:Mcu_GetResetReason  
 * Syntax:Mcu_ResetType Mcu_GetResetReason(void)
 * Description:The service reads the reset type from the hardware, if supported.
 * Service ID[hex]:0x05 
 * Sync/Async:Synchronous
 * Reentrancy:Reentrant 
 * Parameters (in):None
 * Parameters (in-out):None 
 * Parameters (out):None
 * Return value:Mcu_ResetType
 ***********************************************************************************************************************/

Mcu_ResetType Mcu_GetResetReason(void)
{
	uint32 rescReg;
	Mcu_ResetType resetCause;
	if (MCU_NOT_INITIALIZED == g_Mcu_Status)
	{
		/*The function Mcu_GetResetReason shall return MCU_RESET_UNDEFINED
		 *if this function is called prior to calling of the function Mcu_Init, and if supported by the hardware.
		 */
		resetCause = MCU_RESET_UNDEFINED;
	}
	else
	{
		/*read the reset reason from the hardware and return this reason if supported by the hardware.*/
		rescReg = SYSCTL_RESC_R;

		/*ensure that the reset reason is cleared once it has been read out to avoid multiple reset reasons*/
		SYSCTL_RESC_R = 0;

		switch (rescReg)
		{
		case REST_CAUSE_EXTERNAL_RESET:
			resetCause = MCU_EXTERNAL_RESET;
			break;
		case REST_CAUSE_POWER_ON_RESET:
			resetCause = MCU_POWER_ON_RESET;
			break;
		case REST_CAUSE_BROWN_OUT_RESET:
			resetCause = MCU_BROWN_OUT_RESET;
			break;
		case REST_CAUSE_WDT0_RESET:
			resetCause = MCU_WATCHDOG0_RESET;
			break;
		case REST_CAUSE_SOFTWARE_RESET:
			resetCause = MCU_SW_RESET;
			break;
		case REST_CAUSE_WDT1_RESET:
			resetCause = MCU_WATCHDOG1_RESET;
			break;
		case REST_CAUSE_MOSC_FAILURE_RESET:
			resetCause = MCU_MOSC_FAILURE_RESET;
			break;
		default:
			resetCause = MCU_RESET_UNDEFINED;
			break;
		}
	}
	return resetCause;
}
/*****************************************************************************************************************
 *  Service name:Mcu_GetResetRawValue 
 *  Syntax:Mcu_RawResetType Mcu_GetResetRawValue(void)
 *  Description:The service reads the reset type from the hardware register, if supported.
 *  Service ID[hex]:0x06 
 *  Sync/Async:Synchronous
 *  Reentrancy:Reentrant
 *  Parameters (in):None
 *  Parameters (in-out):None 
 *  Parameters (out):None
 *  Return value:Mcu_RawResetType
*****************************************************************************************************************/

Mcu_RawResetType Mcu_GetResetRawValue(void)
{
	/*read the reset reason from the hardware and return this reason if supported by the hardware.*/
	Mcu_RawResetType rawResetValue = SYSCTL_RESC_R;

	/*ensure that the reset reason is cleared once it has been read out to avoid multiple reset reasons*/
	SYSCTL_RESC_R = 0;

	/*Return Reset Cause*/
	return rawResetValue;
}

/***********************************************************************************************************
 * Service name:Mcu_PerformReset 
 * Syntax:void Mcu_PerformReset(void) 
 * Description:The service performs a microcontroller reset. 
 * Service ID[hex]:0x07 
 * Sync/Async:Synchronous 
 * Reentrancy:Non Reentrant 
 * Parameters (in):None
 * Parameters (in-out):None
 * Parameters (out):None
 * Return value:None
 * *****************************************************************************************************/
void Mcu_PerformReset(void)
{
	/*Raise A reset Request*/
	APINT = (APINT_VECTKEY << 16) | (1 << SYSRESREQ);
}
