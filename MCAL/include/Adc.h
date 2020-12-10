#ifndef ADC_H_
#define ADC_H_

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"

#include "Adc_cfg.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*Typdef For Adc Module Status */
typedef enum
{
    ADC_NOT_INITIALIZED,
    ADC_INITIALIZED
} Adc_ModuleStatusType;

/*Numeric ID For ADC Module.*/
typedef enum
{
    ADC_MODULE_0,
    ADC_MODULE_1
} Adc_ModuleType;

/*Type For seting the rate at which ADC module samples data*/
typedef enum
{
    ADC_SAMPLE_RATE_125K,/* 125K samples/second	*/
    ADC_SAMPLE_RATE_250K,/* 250K samples/second */
    ADC_SAMPLE_RATE_500K,/* 500K samples/second */
    ADC_SAMPLE_RATE_1M/* 1M samples/second */
} Adc_SampleRateType;

/*Numeric ID For Sequencer.*/
typedef enum
{
    SS0,
    SS1,
    SS2,
    SS3
} Adc_SampleSequnecerType;

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

/*Type for configuring the HW Event trigger for an ADC Channel group.*/
typedef enum
{
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

/*Type for configuring the streaming access mode buffer type.*/
typedef enum 
{
    ADC_STREAM_BUFFER_LINEAR,/*The ADC Driver stops the conversion as soon as the stream buffer is full (number of samples reached).*/
    ADC_STREAM_BUFFER_CIRCULAR/*The ADC Driver continues the conversion even if the stream buffer is full (number of samples reached).*/
}Adc_StreamBufferModeType;


typedef enum
{
    ADC_POLLING,
    ADC_INTERRUPTS
} Adc_ResultReadMode; /*type for method reading ADC Value*/


typedef struct {
	Adc_ModuleType AdcModule ; 
	Adc_SampleRateType SampleRate ; 
}Adc_AdcModuleConfig;

typedef struct {
	Adc_SampleSequnecerType SampleSequencer; 
	Adc_TriggerSourceType SequencerTriggerSource ; 
	Adc_HwTriggerSourceType HwTriggerSource ; 
	Adc_GroupConvModeType GroupConv ; 
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

typedef uint16 Adc_StreamNumSampleType  ;
typedef uint16 Adc_ValueGroupType;
typedef uint8 Adc_GroupType;

typedef uint8 Adc_GroupNumber ; 
typedef uint8 Adc_GroupChannelSize ;  
typedef struct 
{
		Adc_GroupNumber Num ; 
	Adc_GroupChannelSize size ; 
    Adc_ModuleType AdcModule ; 
    Adc_SampleSequncerConfig seqConfig ; 
    Adc_GroupConvModeType conversionMode ; 
    Adc_StreamBufferModeType bufferMode ; 
    Adc_ChannelType groupChannels[MAX_CHANNELS_PER_GROUP] ; 
}Adc_ConfigChannelGroup;

typedef struct
{
    Adc_AdcModuleConfig AdcConfiguredModules[CONFIG_ADC_MODULE];
  	Adc_SampleSequncerConfig AdcConfiguredSequncers[CONFIG_SAMPLE_SEQUNECERS];
    Adc_ConfigChannel AdcConfiguredChannels[CONFIG_ANALOG_CHANNELS];
    Adc_ConfigChannelGroup AdcConfiguredGroups [CONFIG_ADC_GROUPS] ; 
} Adc_ConfigType;

#endif
