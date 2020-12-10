#include "Mcu.h" 
#include "Adc.h" 

#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))

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
	Port_init() ; 
	
	while(1) ; 
}
