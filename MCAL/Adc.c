#include "Adc.h"
#include "tm4c123gh6pm_hw.h"

/*global Variable To Hold Module Status */
STATIC Adc_ModuleStatusType g_Adc_Status = ADC_NOT_INITIALIZED;

/*global Variable To Hold Adc Configurations */
STATIC const Adc_ConfigChannel *g_AdcConfiguredChannels = NULL_PTR;

/*
The TM4C123GH6PM microcontroller contains two identical Analog-to-Digital Converter modules.
These two modules, ADC0 and ADC1, share the same 12 analog input channels.

	**/
	
STATIC Adc_ValueGroupType* g_DataBufferPtr[CONFIG_ADC_GROUPS];


void Adc_Init( const Adc_ConfigType* ConfigPtr) 
{
	uint8 itr ; 
	if (NULL_PTR != ConfigPtr)
	{
		/*Init ADC Modules With Required Sample Rate*/
		for (itr =0 ; itr <CONFIG_ADC_MODULE ; itr++)
		{
			if(ADC_0 == (ConfigPtr->AdcConfiguredModules[itr]).AdcModule)
			{
				SYSCTL_RCGC0_R = (SYSCTL_RCGC0_R & ADC0_SAMPLE_RATE_MASK) |((ConfigPtr->AdcConfiguredModules[itr]).SampleRate<<MAXADC0SPD);
			}
			else if (ADC_1 == (ConfigPtr->AdcConfiguredModules[itr]).AdcModule)
			{
				SYSCTL_RCGC0_R = (SYSCTL_RCGC0_R & ADC1_SAMPLE_RATE_MASK) |((ConfigPtr->AdcConfiguredModules[itr]).SampleRate<<MAXADC1SPD);
			}
		}
		
		
		/*Init Sequencers */
		
		
		g_Adc_Status = ADC_INITIALIZED ; 
	}
}

Std_ReturnType Adc_SetupResultBuffer( Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr) 
{
	Std_ReturnType ret = E_NOT_OK ; 
	if (ADC_INITIALIZED == g_Adc_Status)
	{
		if (CONFIG_ADC_GROUPS > Group )
		{
			g_DataBufferPtr[Group] = DataBufferPtr ;  
			ret = E_OK ; 
		}
	}
	return ret ; 
}




















#if 0
#define SEQ3 3
void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
	uint8 itr = 0 ; 
	if (NULL_PTR != ConfigPtr)
	{
		SYSCTL_RCGC0_R = (SYSCTL_RCGC0_R & ADC0_SAMPLE_RATE_MASK) | (ConfigPtr->Rate << MAXADC0SPD);

		ADC0->ADCACTSS &= ~(1 << SEQ3);
		ADC0->ADCSSCTL3 |= 6;
	for (itr =0 ; itr <CONFIG_SAMPLE_SEQUNECERS;itr++)
		{
		/*Set Triggering Source For Each Sequencer*/
		switch (ConfigPtr->AdcConfiguredSequncers[itr].SampleSequencer)
		{
			case SS3  :
					ADC0->ADCEMUX =(ADC0->ADCEMUX & SEQ3_TRIG_REG_MASK) |(ConfigPtr->AdcConfiguredSequncers[itr].SequencerTriggerSource<<EM3) ; 
				break ; 
			case SS2  :
						break ; 				
			case SS1  :
				break ; 
			case SS0	:		
				break ; 
			default :
				break ; 
		}
	}
		ADC0->ADCACTSS |= (1 << SEQ3);
		g_AdcConfiguredChannels = ConfigPtr->AdcConfiguredChannels;
		g_Adc_Status = ADC_INITIALIZED;
	}
}

/*Busy Wait*/
Adc_ValueGroupType Adc_ReadChannel(uint8 AnalogChannelId)
{
	Adc_ValueGroupType adcResult = 0;

	if (ADC_INITIALIZED == g_Adc_Status)
	{
		/*Set Input Channel*/
		ADC0->ADCSSMUX3 = g_AdcConfiguredChannels[AnalogChannelId].channel;

		/*Intiate Sequencer*/
		ADC0->ADCPSSI |= (1 << g_AdcConfiguredChannels[AnalogChannelId].seq);

		/*wait for conversion*/
		while ((ADC0->ADCRIS & (1 << g_AdcConfiguredChannels[AnalogChannelId].seq)) == 0)
			;

		/*Clear Flag*/
		ADC0->ADCISC |= (1 << g_AdcConfiguredChannels[AnalogChannelId].seq);

		/*Read Result*/
		adcResult = ADC0->ADCSSFIFO3 & ADC_12BIT_RESULT_MASK;
	}
	return adcResult;
}
#endif 
