#include "Mcu.h"
#include "Adc.h"

#include "tm4c123gh6pm.h"
extern void Adc_Init(Adc_ConfigType *ConfigPtr);
extern Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);
extern void Adc_StartGroupConversion(Adc_GroupType Group);

#define GPIO_PORTE_DIR_R (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R (*((volatile unsigned long *)0x40024528))
#define ENABLE_REG_BASE ((volatile uint32 *)0xE000E100) /*EN0*/
#define IRQ_SET_ENABLE(ENn, IRQ_BIT) (*(ENABLE_REG_BASE + ENn) |= (1 << IRQ_BIT))
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
#define ADC0_IM_R (*((volatile unsigned long *)0x40038008))

void _init()
{
	/*Analog input on PE4*/
	GPIO_PORTE_DIR_R &= ~0x04;
	GPIO_PORTE_AFSEL_R |= 0x04;
	GPIO_PORTE_DEN_R &= ~0x04;
	GPIO_PORTE_AMSEL_R |= 0x04;
	uint32 ENn;
	uint32 irqEnOffset;

	SYSCTL->RCGCADC |= 1; /* enable clock to ADC0 */
						  /*Get Offset Of ENn Register Which Irq resident in */
	ENn = 15 / PLATFORM_WORD_LENGTH;

	/*Get Offset Of irqNum in ENn Register */
	irqEnOffset = 15 % PLATFORM_WORD_LENGTH;

	/*Enable Interrupt*/
	IRQ_SET_ENABLE(ENn, irqEnOffset);
	ADC0_IM_R = 0xFFFFFFFF;
}

uint16 buf[4];

int main(void)
{
	Mcu_Init(&MCU_Configurations);
	Mcu_InitClock(PLL_CLOCK_SETTINGS);
	SYSCTL_RCGCGPIO_R = 0xFFFFFFFF;
	_init();
	Adc_Init(&adc_Configs);
	Adc_SetupResultBuffer(0, buf);
	Adc_StartGroupConversion(0);
	while (1)
		;
}

#if 0

/* p7_2.c: Convert on-chip temperature */
/* This program converts the on-chip temperature sensor output using sample sequencer 3
and timer trigger at 1 Hz. */
#include "TM4C123GH6PM.h"
volatile int temperature;
extern void Adc_Init(Adc_ConfigType *ConfigPtr) ;

#define GPIO_PORTE_DIR_R (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R (*((volatile unsigned long *)0x40024528))


void Port_init()
{
	/*Analog input on PE4*/
	GPIO_PORTE_DIR_R &= ~0x04;     
  GPIO_PORTE_AFSEL_R |= 0x04;     
  GPIO_PORTE_DEN_R &= ~0x04;      
  GPIO_PORTE_AMSEL_R |= 0x04;     
}

/*
The TM4C123GH6PM microcontroller contains two identical Analog-to-Digital Converter modules.
These two modules, ADC0 and ADC1, share the same 12 analog input channels.
	**/
#define ADC0_BASE 0x40038000
#define ADC1_BASE 0x40039000
static uint32  adcModules[2]=
{
	ADC0_BASE, 
	ADC1_BASE
};
#define ADCSSMUX0_OFFSET 0x040
#define ADCSSMUX1_OFFSET 0x060
#define ADCSSMUX2_OFFSET 0x080
#define ADCSSMUX3_OFFSET 0x0A0

static uint32 const adc_ssmuxRegs [4]=
{
	ADCSSMUX0_OFFSET,
	ADCSSMUX1_OFFSET,
	ADCSSMUX2_OFFSET,
	ADCSSMUX3_OFFSET
};
STATIC Adc_ValueGroupType* g_DataBufferPtr[CONFIG_ADC_GROUPS];

#define ADCACTSS(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0x000))
#define ADCEMUX(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0x014))
#define ADCSSMUX(ADC_MODULE, SEQ) (*(volatile uint32 *)(adcModules[ADC_MODULE] + adc_ssmuxRegs[SEQ]))
#define ADC0_ACTSS_R (*((volatile unsigned long *)0x40038000))
#define ADC0_SSMUX1_R (*((volatile unsigned long *)0x40038060))
int main(void)
{

//Mcu_Init(&MCU_Configurations);
	//Mcu_InitClock(PLL_CLOCK_SETTINGS);
	SYSCTL->RCGCADC |= 1; /* enable clock to ADC0 */
		Adc_Init(&adc_Configs); 

/* enable clocks */
SYSCTL->RCGCADC |= 1; /* enable clock to ADC0 */
SYSCTL->RCGCWTIMER |= 1; /* enable clock to WTimer Block 0 */

/* initialize ADC0 */
ADC0->ACTSS &= ~8; /* disable SS3 during configuration */
			ADCEMUX(0)=2;

ADC0->EMUX &= ~0xF000;
ADC0->EMUX |= 0x5000; /* timer trigger conversion seq 0 */
ADC0->SSMUX3 = 0; /* get input from channel 0 */
ADC0->SSCTL3 |= 0x0E; /* take chip temperature, set flag at 1st sample */
ADCACTSS(0)|= 8; /* enable ADC0 sequencer 3 */
/* initialize wtimer 0 to trigger ADC at 1 sample/sec */
WTIMER0->CTL = 0; /* disable WTimer before initialization */
WTIMER0->CFG = 0x04; /* 32-bit option */
WTIMER0->TAMR = 0x02; /* periodic mode and down-counter */
WTIMER0->TAILR = 16000000; /* WTimer A interval load value reg (1 s) */
WTIMER0->CTL |= 0x20; /* timer triggers ADC */
WTIMER0->CTL |= 0x01; /* enable WTimer A after initialization */
while(1)
{
while((ADC0->RIS & 8) == 0) ; /* wait for conversion complete */
temperature = 147 - (247 * ADC0->SSFIFO3) / 4096;
ADC0->ISC = 8; /* clear completion flag */
}
}















extern void Adc_Init(Adc_ConfigType *ConfigPtr) ;

#define GPIO_PORTE_DIR_R (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R (*((volatile unsigned long *)0x40024528))


void Port_init()
{
	/*Analog input on PE4*/
	GPIO_PORTE_DIR_R &= ~0x04;     
  GPIO_PORTE_AFSEL_R |= 0x04;     
  GPIO_PORTE_DEN_R &= ~0x04;      
  GPIO_PORTE_AMSEL_R |= 0x04;     
}

int main(void){
	Mcu_Init(&MCU_Configurations);
	Mcu_InitClock(PLL_CLOCK_SETTINGS);
	Port_init() ; 
	Adc_Init(&adc_Configs); 
	
	while(1) ; 
}
#endif
