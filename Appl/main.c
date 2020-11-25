#include "Mcu.h" 



int main(void){
	//Mcu_PerformReset(); 
	  Mcu_Init(&MCU_Configurations); 
	

	unsigned char c = Mcu_GetPllStatus() ; 
		
	  Mcu_InitClock(PLL_CLOCK_SETTINGS) ;
	
	c = Mcu_GetPllStatus() ; 
		
	Mcu_InitClock(MOSC_CLOCK_SETTINGS);
  
	
  
	while(1); 

}
