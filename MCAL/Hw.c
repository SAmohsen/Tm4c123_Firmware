
#include "tm4c123gh6pm_hw.h"

/*GPIO PORTS Base Addresses */
const uint32 GPIOPortsBaseAddress[DIO_PORTS_NUMBER] =
	{
		PORTA_BASE_ADDRESS,
		PORTB_BASE_ADDRESS,
		PORTC_BASE_ADDRESS,
		PORTD_BASE_ADDRESS,
		PORTE_BASE_ADDRESS,
		PORTF_BASE_ADDRESS};

const uint32 adc_ssctrlRegs[4] =
	{
		SSCTL0_OFFSET,
		SSCTL1_OFFSET,
		SSCTL2_OFFSET,
		SSCTL3_OFFSET};
uint32 const adc_ssmuxRegs[4] =
	{
		ADCSSMUX0_OFFSET,
		ADCSSMUX1_OFFSET,
		ADCSSMUX2_OFFSET,
		ADCSSMUX3_OFFSET};

const uint32 adcModules[2] =
	{
		ADC0_BASE,
		ADC1_BASE};

uint32 const adc_ssfifo[4] =
	{
		ADC_SSFIFO0_OFFSET_REG,
		ADC_SSFIFO1_OFFSET_REG,
		ADC_SSFIFO2_OFFSET_REG,
		ADC_SSFIFO3_OFFSET_REG};