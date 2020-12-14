#include "Adc.h"
#include "tm4c123gh6pm_hw.h"

/*global Variable To Hold Adc Configurations */
STATIC uint8 g_SeqConfiguredGroup[ADC_HW_UNITS] = {0};
STATIC Adc_ConfigChannelGroup *g_AdcConfiguredChannels = NULL_PTR;
STATIC Adc_ValueGroupType *g_DataBufferPtr[CONFIG_ADC_GROUPS];
STATIC Adc_ValueGroupType *g_DataBufferPtr[CONFIG_ADC_GROUPS];

/*
The TM4C123GH6PM microcontroller contains two identical Analog-to-Digital Converter modules.
These two modules, ADC0 and ADC1, share the same 12 analog input channels.
	**/

uint32 x;

STATIC void __sequencerConfig(Adc_ConfigChannelGroup *groups)
{
	uint8 itr;
	uint8 itr2;
	for (itr = 0; itr < CONFIG_ADC_GROUPS; itr++)
	{
		/*Disable Sequencers At Begaining*/
		ADCACTSS(groups[itr].AdcModule) &= ~(1 << groups[itr].seqConfig.SampleSequencer);
		/*Set Sequncer Trigger */
		if (ADC_TRIGG_SRC_SW == groups[itr].seqConfig.SequencerTriggerSource)
		{
			ADCEMUX(groups[itr].AdcModule) = (groups[itr].seqConfig.GroupConv << (groups[itr].seqConfig.SampleSequencer * 4));
		}
		else if (ADC_TRIGG_SRC_HW == groups[itr].seqConfig.SequencerTriggerSource)
		{
			ADCEMUX(groups[itr].AdcModule) = (groups[itr].seqConfig.HwTriggerSource << (groups[itr].seqConfig.SampleSequencer * 4));
		}

		/*Clear To Set Channels*/
		ADCSSMUX(groups[itr].AdcModule, groups[itr].seqConfig.SampleSequencer) = 0;
		/*Set Channels*/
		for (itr2 = 0; itr2 < groups[itr].size; itr2++)
		{
			ADCSSMUX(groups[itr].AdcModule, groups[itr].seqConfig.SampleSequencer) |= (groups[itr].groupChannels[itr2] << itr2 * 4);
			SSCTL(groups[itr].AdcModule, groups[itr].seqConfig.SampleSequencer) |= (6 << itr2 * 4);
		}
		/*Enable Sequencers */
		ADCACTSS(groups[itr].AdcModule) |= (1 << groups[itr].seqConfig.SampleSequencer);
	}
}

void Adc_Init(Adc_ConfigType *ConfigPtr)
{
	uint8 itr;
	/*Init ADC Modules With Required Sample Rate*/
	for (itr = 0; itr < CONFIG_ADC_MODULE; itr++)
	{
		ADCPC((ConfigPtr->AdcConfiguredModules[itr]).AdcModule) = (ConfigPtr->AdcConfiguredModules[itr]).SampleRate;

		//		if (ADC_MODULE_0 == (ConfigPtr->AdcConfiguredModules[itr]).AdcModule)
		//		{
		//			SYSCTL_RCGC0_R = (SYSCTL_RCGC0_R & ADC0_SAMPLE_RATE_MASK) | ((ConfigPtr->AdcConfiguredModules[itr]).SampleRate << MAXADC0SPD);
		//		}
		//		else if (ADC_MODULE_1 == (ConfigPtr->AdcConfiguredModules[itr]).AdcModule)
		//		{
		//			SYSCTL_RCGC0_R = (SYSCTL_RCGC0_R & ADC1_SAMPLE_RATE_MASK) | ((ConfigPtr->AdcConfiguredModules[itr]).SampleRate << MAXADC1SPD);
		//		}
	}
	__sequencerConfig(ConfigPtr->AdcConfiguredGroups);
	g_AdcConfiguredChannels = ConfigPtr->AdcConfiguredGroups;
}
void Adc_StartGroupConversion(Adc_GroupType Group)
{
	uint8 seq = g_AdcConfiguredChannels[Group].seqConfig.SampleSequencer;
	ADCPSSI(g_AdcConfiguredChannels[Group].AdcModule) |= (1 << seq);
}
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr)
{
	Std_ReturnType ret = E_NOT_OK;

	g_DataBufferPtr[Group] = DataBufferPtr;
	if (g_AdcConfiguredChannels[Group].AdcModule == ADC_MODULE_0)
	{
		g_SeqConfiguredGroup[g_AdcConfiguredChannels[Group].seqConfig.SampleSequencer] = g_AdcConfiguredChannels[Group].Num;
	}
	else if (g_AdcConfiguredChannels[Group].AdcModule == ADC_MODULE_1)
	{
		g_SeqConfiguredGroup[g_AdcConfiguredChannels[Group].seqConfig.SampleSequencer + 4] = g_AdcConfiguredChannels[Group].Num;
	}
	return ret;
}
void ADC0SS0_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC0_SEQ0_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_0, SS0);
	}
}

void ADC0SS2_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC0_SEQ2_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_0, SS2);
	}
}
void ADC0SS1_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC0_SEQ1_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_0, SS1);
	}
}
void ADC0SS3_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC0_SEQ3_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_0, SS3);
	}
}
void ADC1SS1_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC1_SEQ0_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_1, SS0);
	}
}
void ADC1SS0_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC1_SEQ1_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_1, SS1);
	}
}
void ADC1SS2_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC1_SEQ2_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_1, SS2);
	}
}
void ADC1SS3_Handler(void)
{
	Adc_GroupType groupId = g_SeqConfiguredGroup[ADC1_SEQ3_HW];

	for (uint8 itr = 0; itr < g_AdcConfiguredChannels[groupId].size; itr++)
	{
		(*(g_DataBufferPtr[groupId] + itr)) = ADCSSFIFO(ADC_MODULE_1, SS3);
	}
}

#if 0 
/*global Variable To Hold Module Status */
STATIC Adc_ModuleStatusType g_Adc_Status = ADC_NOT_INITIALIZED;

/*global Variable To Hold Adc Configurations */
STATIC const Adc_ConfigChannel *g_AdcConfiguredChannels = NULL_PTR;

/*
The TM4C123GH6PM microcontroller contains two identical Analog-to-Digital Converter modules.
These two modules, ADC0 and ADC1, share the same 12 analog input channels.

	**/
#define ADC0_BASE 0x40038000
#define ADC1_BASE 0x40039000
static uint32 const adcModules[2]=
{
	ADC0_BASE, 
	ADC1_BASE
};
STATIC Adc_ValueGroupType* g_DataBufferPtr[CONFIG_ADC_GROUPS];

#define ADCACTSS(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0x000))

static inline SeqSetChannels()
void Adc_Init( const Adc_ConfigType* ConfigPtr) 
{
	uint8 itr ;
	Adc_SampleSequnecerType seq ; 
	 Adc_ModuleType adcModule ; 
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
		for(itr=0;itr <CONFIG_ADC_GROUPS ; itr++)
		{
			/*Disable Sequncer Befor Configuring it*/
			adcModule = ConfigPtr->AdcConfiguredGroups[itr].AdcModule ; 
			seq = ConfigPtr->AdcConfiguredGroups[itr].seq.SampleSequencer ; 
			ADCACTSS(adcModule) &=~(1<<seq) ;


			/*Set Sequncer Channels*/


			/*Set Conversion Mode Type*/







			/*Enable Sample Sequncer After Config*/
			ADCACTSS(adcModule) |=(1<<seq) ;

		}
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

#endif
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
