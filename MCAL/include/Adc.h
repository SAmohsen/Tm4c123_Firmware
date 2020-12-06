#ifndef ADC_H_
#define ADC_H_

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"

#define CONFIG_ANALOG_CHANNELS 2
#define CONFIG_SAMPLE_SEQUNECERS 2
#define CONFIG_ADC_MODULE 2
#define CONFIG_ADC_GROUPS 2 

typedef enum
{
    ADC_NOT_INITIALIZED,
    ADC_INITIALIZED
} Adc_ModuleStatusType;
typedef uint16 Adc_StreamNumSampleType  ;
typedef uint16 Adc_ValueGroupType;
typedef uint8 Adc_GroupType;
/*Numeric ID of an ADC channel.*/
typedef enum
{
    AIN0,  /*PE3 I Analog Analog-to-digital converter input 0.*/
    AIN1,  /*PE2 I Analog Analog-to-digital converter input 1.*/
    AIN2,  /*PE1 I Analog Analog-to-digital converter input 2.*/
    AIN3,  /*PE0 I Analog Analog-to-digital converter input 3.*/
    AIN4,  /*PD3 I Analog Analog-to-digital converter input 4.*/
    AIN5,  /*PD2 I Analog Analog-to-digital converter input 5.*/
    AIN6,  /*PD1 I Analog Analog-to-digital converter input 6.*/
    AIN7,  /*PD0 I Analog Analog-to-digital converter input 7.*/
    AIN8,  /*PE5 I Analog Analog-to-digital converter input 8.*/
    AIN9,  /*PE4 I Analog Analog-to-digital converter input 9.*/
    AIN10, /*PB4 I Analog Analog-to-digital converter input 10*/
    AIN11  /*PB5 I Analog Analog-to-digital converter input 11*/
} Adc_ChannelType;

/*Current status of the conversion of the requested ADC Channel group.*/
typedef enum
{
    ADC_IDLE,             /*The conversion of the specified group has not been started.- No result is available*/
    ADC_BUSY,             /*The conversion of the specified group has been started and is still going on. no result is available.*/
    ADC_COMPLETED,        /*A conversion round of the specified group has been finished.A result is available for all channels of the group.*/
    ADC_STREAM_COMPLETED, /*The result buffer is completely filled*/
} Adc_StatusType;

/*Type for configuring the trigger source for an ADC Channel group.*/
typedef enum
{
    ADC_TRIGG_SRC_SW, /*Group is triggered by a software API call.*/
    ADC_TRIGG_SRC_HW  /*Group is triggered by a hardware event.*/
} Adc_TriggerSourceType;

typedef enum
{
		NA,
    AnalogComparator0,
    AnalogComparator1,
    ExternalGPIO = 4,
    Timer,
    PWM_generator0,
    PWM_generator1,
    PWM_generator2,
    PWM_generator3,
} Adc_HwTriggerSourceType;

/*Type for configuring the conversion mode of an ADC Channel group.*/
typedef enum
{
    ADC_CONV_MODE_ONESHOT,   /*Exactly one conversion of each channel in an ADC channel group is performed after the configured trigger event.*/
    ADC_CONV_MODE_CONTINUOUS=0x0F /*Repeated conversions of each ADC channel in an ADC channel group are performed.*/
} Adc_GroupConvModeType;

typedef enum
{
    ADC_0,
    ADC_1
} Adc_ModuleType;

typedef enum
{
    SS3,
    SS2,
    SS1,
    SS0
} Adc_SampleSequnecerType;
typedef enum
{
    ADC_POLLING,
    ADC_INTERRUPTS
} Adc_ResultReadMode; /*type for method reading ADC Value*/

typedef enum
{
    ADC_SAMPLE_RATE_125K,
    ADC_SAMPLE_RATE_250K,
    ADC_SAMPLE_RATE_500K,
    ADC_SAMPLE_RATE_1M
} Adc_SampleRateType;

typedef struct {
	Adc_ModuleType AdcModule ; 
	Adc_SampleRateType SampleRate ; 
}Adc_AdcModuleConfig;
typedef struct {
	Adc_SampleSequnecerType SampleSequencer; 
	Adc_TriggerSourceType SequencerTriggerSource ; 
	Adc_HwTriggerSourceType HwTriggerSource ; 
}Adc_SampleSequncerConfig;

typedef struct
{
    Adc_SampleSequnecerType seq;
    Adc_ChannelType channel;
    Adc_StatusType status;
    Adc_TriggerSourceType trigger;
    Adc_GroupConvModeType mode;
    Adc_ModuleType AdcModule;
    Adc_ResultReadMode read;
} Adc_ConfigChannel;
typedef struct
{
    Adc_AdcModuleConfig AdcConfiguredModules[CONFIG_ADC_MODULE];
  	Adc_SampleSequncerConfig AdcConfiguredSequncers[CONFIG_SAMPLE_SEQUNECERS];
    Adc_ConfigChannel AdcConfiguredChannels[CONFIG_ANALOG_CHANNELS];
} Adc_ConfigType;
#endif
