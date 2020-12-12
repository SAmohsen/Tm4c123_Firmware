#include "Mcu.h"
#include "Mcu_cfg.h"



const Mcu_ConfigType MCU_Configurations =
{

    /*MOSC Clock Configurations Mode B*/
    .ConfiguredclockSettings[MOSC_CLOCK_SETTINGS].clockSource = CLOCK_SOURCE_MAIN_OSCILLATOR , 
    .ConfiguredclockSettings[MOSC_CLOCK_SETTINGS].xtal = XTAL_16MHZ ,
    .ConfiguredclockSettings[MOSC_CLOCK_SETTINGS].desiredClock=16000000UL ,
    .ConfiguredclockSettings[MOSC_CLOCK_SETTINGS].pllConfig.pllUse=MCU_PLL_POWERD_OFF , 
    .ConfiguredclockSettings[MOSC_CLOCK_SETTINGS].pllConfig.PllDiv=NA ,

	 /*MODE A */
    .ConfiguredclockSettings[PLL_CLOCK_SETTINGS].clockSource = CLOCK_SOURCE_MAIN_OSCILLATOR , 
    .ConfiguredclockSettings[PLL_CLOCK_SETTINGS].xtal = XTAL_16MHZ ,
    .ConfiguredclockSettings[PLL_CLOCK_SETTINGS].desiredClock=40000000UL ,
    .ConfiguredclockSettings[PLL_CLOCK_SETTINGS].pllConfig.pllUse=MCU_PLL_POWERED_ON , 
    .ConfiguredclockSettings[PLL_CLOCK_SETTINGS].pllConfig.PllDiv=MCU_PLL_400MHZ_DIV_2 ,

	
    /*Ram Sections Configurations*/
    .ramConfigArr[RAM_SECTION1].ramSectionStartAddress = RAM_SECTION1_START_ADDR , 
    .ramConfigArr[RAM_SECTION1].ramSectionDefaultValue = RAM_SECTION1_DEFAULT_VAL , 
    .ramConfigArr[RAM_SECTION1].ramSectionSize = RAM_SECTION1_SIZE_BYTES , 


    /*Enable Periphral Clocks*/

    /*Enable Clock gate ADC0*/
    .perphClock[0].perph = MCU_CADC, 
    .perphClock[0].instance= 1,

    /*Enable Clock gate ADC0*/
    .perphClock[1].perph = MCU_CADC, 
    .perphClock[1].instance= 0,

	/*Enable Clock Gate GPIOA*/
    .perphClock[2].perph = MCU_GPIO, 
    .perphClock[2].instance= 0,
	
	/*Enable Clock Gate GPIOE*/
    .perphClock[3].perph =MCU_GPIO , 
    .perphClock[3].instance= 4,
	
	/*Enable Clock Gate GPIOF*/
    .perphClock[4].perph = MCU_GPIO, 
    .perphClock[4].instance= 5,
    
};
