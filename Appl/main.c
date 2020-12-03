#include "Mcu.h" 
#include "Dio.h"
#include "Port.h"


int main(void){
	  Mcu_Init(&MCU_Configurations);
Port_init(&portConfigs) ; 	
Dio_WriteChannel(Dio_PortF_Pin_PF2,STD_HIGH);
	

	while(1); 

}
