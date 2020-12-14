#include "Adc.h"


Adc_ConfigType adc_Configs = 
{
	{
		ADC_MODULE_0 , 
		ADC_SAMPLE_RATE_1M , 
		ADC_MODULE_1 , 
		ADC_SAMPLE_RATE_250K , 
	}	
	,
	{
		{
			0,
			4,
			ADC_MODULE_0,
			{
				SS1,
				ADC_TRIGG_SRC_SW,/*SequencerTriggerSource*/
				FALSE ,/*HwTriggerSource*/
				ADC_CONV_MODE_ONESHOT	/*GroupConv*/
			},
			ADC_STREAM_BUFFER_LINEAR,/*bufferMode*/
			{
	  AIN0, 
    AIN1,  
    AIN2,  
    AIN3,  
			}
		}
		,
		{
			1,
			4,
			ADC_MODULE_1,
			{
				SS2,
				ADC_TRIGG_SRC_SW,
				FALSE ,
				ADC_CONV_MODE_ONESHOT	
			},
			ADC_STREAM_BUFFER_LINEAR,
			{
				 AIN7, 
    AIN8,  
    AIN9,  
    AIN10,  
			}
		}
	}
};
