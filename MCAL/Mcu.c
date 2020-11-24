
#include "Mcu.h"
#include "tm4c123gh6pm_hw.h"

Mcu_statusType g_Mcu_Status = MCU_NOT_INITIALIZED;
Std_ReturnType Mcu_DistributePllClock( ){
	Std_ReturnType ret = E_NOT_OK ;
	
	/*Check iF Pll Status Is Activated and PLL Status Is Locked*/
	if((SYSCTL_RCC2_R & (1<<PWRDN2))==0)
	{
		if (SYSCTL_PLLSTAT_R==MCU_PLL_LOCKED)
		{
			/* select PLL as the source of system clock*/
			SYSCTL_RCC2_R &= ~(1 << BYPASS2); /* remove bypass and use the PLL */
		}
		
	}
	return ret ; 
}

Mcu_ResetType Mcu_GetResetReason(void){
	uint32 rescReg ; 
	Mcu_ResetType resetCause ; 
	  if (MCU_NOT_INITIALIZED == g_Mcu_Status)
		{
			resetCause = MCU_RESET_UNDEFINED ; 
		}
		else 
		{
			rescReg = SYSCTL_RESC_R ; 
		/*Clear Reset Cause*/
    SYSCTL_RESC_R = 0; /*Writing a 0 to any reset cause clears it.*/
			switch(rescReg)
			{
case REST_CAUSE_EXTERNAL_RESET:
resetCause = MCU_EXTERNAL_RESET;
break;
case REST_CAUSE_POWER_ON_RESET:
resetCause = MCU_POWER_ON_RESET;
break;
case REST_CAUSE_BROWN_OUT_RESET:
resetCause = MCU_BROWN_OUT_RESET;
break;
case REST_CAUSE_WDT0_RESET:
resetCause = MCU_WATCHDOG0_RESET;
break;
case REST_CAUSE_SOFTWARE_RESET:
resetCause = MCU_SW_RESET;
break;
case REST_CAUSE_WDT1_RESET:
resetCause = MCU_WATCHDOG1_RESET;
break;
case REST_CAUSE_MOSC_FAILURE_RESET:
resetCause = MCU_MOSC_FAILURE_RESET;
break;	
default:
		resetCause = MCU_RESET_UNDEFINED ; 
	break ; 
			}

			
			
		}
		return resetCause ; 
}
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
    /*Read Reset Cause */
    Mcu_RawResetType rawResetValue = SYSCTL_RESC_R;

    /*Clear Reset Cause*/
    SYSCTL_RESC_R = 0; /*Writing a 0 to any reset cause clears it.*/

    /*Return Reset Cause*/
    return rawResetValue;
}

Mcu_PllStatusType Mcu_GetPllStatus(void)
{
    Mcu_PllStatusType currentPllStatus;
    if (MCU_NOT_INITIALIZED == g_Mcu_Status)
    {
        currentPllStatus = MCU_PLL_STATUS_UNDEFINED;
    }
    else
    {
        currentPllStatus = ((SYSCTL_PLLSTAT_R == 0) ? MCU_PLL_UNLOCKED : MCU_PLL_LOCKED);
    }
    return currentPllStatus;
}
void Mcu_PerformReset( ){
	
    APINT = (APINT_VECTKEY << 16) | (1 << SYSRESREQ);
	
}
