#ifndef TM4C123GH6PM_HW_H_
#define TM4C123GH6PM_HW_H_

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"
/**********************************************************************************************************************
 *  Start System Control HW
 *********************************************************************************************************************/


/*Run Mode Clock Gating Control*/
#define SYSCTL_RCGCBASE   0x400fe600


#define SYSCTL_RCGCWD_R_OFFSET         0x00
#define SYSCTL_RCGCTIMER_R_OFFSET      0x04
#define SYSCTL_RCGCGPIO_R_OFFSET       0x08
#define SYSCTL_RCGCDMA_R_OFFSET        0x0C
#define SYSCTL_RCGCHIB_R_OFFSET        0x14
#define SYSCTL_RCGCUART_R_OFFSET       0x18
#define SYSCTL_RCGCSSI_R_OFFSET        0x1C
#define SYSCTL_RCGCI2C_R_OFFSET        0x20
#define SYSCTL_RCGCUSB_R_OFFSET        0x28
#define SYSCTL_RCGCCAN_R_OFFSET        0x34
#define SYSCTL_RCGCADC_R_OFFSET        0x38
#define SYSCTL_RCGCACMP_R_OFFSET       0x3C
#define SYSCTL_RCGCPWM_R_OFFSET        0x40
#define SYSCTL_RCGCQEI_R_OFFSET        0x44
#define SYSCTL_RCGCEEPROM_R_OFFSET     0x58
#define SYSCTL_RCGCWTIMER_R_OFFSET     0x5C
	


#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC_XTAL_M       0x000007C0  // Crystal Value
#define MOSCDIS 0


#define SYSCTL_RCC2_R				(*((volatile  unsigned long *)0x400FE070))
#define PWRDN2 13
#define BYPASS2 11
#define DIV400 30 
#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2

#define SYSCTL_RIS_R            (*((volatile  unsigned long*)0x400FE050))
#define PLLLRIS 6

#define SYSCTL_PLLSTAT_R        (*((volatile  unsigned long *)0x400FE168))
#define SYSCTL_RESC_R           (*((volatile unsigned long *)0x400FE05C))
	
typedef struct
{
    uint32 MEMA : 1;
    uint32 BUSA : 1;
    uint32 : 1;
    uint32 USGA : 1;
    uint32 : 3;
    uint32 SVCA : 1;
    uint32 MON : 1;
    uint32 : 1;
    uint32 PNDSV : 1;
    uint32 TICK : 1;
    uint32 USAGEP : 1;
    uint32 MEMP : 1;
    uint32 BUSP : 1;
    uint32 SVC : 1;
    uint32 MEM : 1;
    uint32 BUS : 1;
    uint32 USAGE : 1;
    uint32 :13;
} SYSHNDCTRL_Bits;

typedef union
{

    SYSHNDCTRL_Bits Bits;
    uint32 Reg;
} SYSHNDCTRL_Tag;

typedef struct
{
    uint32 VECACT : 8;
    uint32 : 3;
    uint32 RETBASE : 1;
    uint32 VECPEND : 8;
    uint32 : 2;
    uint32 ISRPEND : 1;
    uint32 ISRPRE : 1;
    uint32 : 1;
    uint32 PENDSTCLR : 1;
    uint32 PENDSTSET : 1;
    uint32 UNPENDSV : 1;
    uint32 PENDSV : 1;
    uint32 : 2;
    uint32 NMISET : 1;

} INTCTRL_BITS;

typedef union
{

    INTCTRL_BITS Bits;
    uint32 Reg;
} INTCTRL_Tag;
#define INTCTRL (*(volatile INTCTRL_Tag *)0xE000ED04)

#define SYSHNDCTRL (*((volatile SYSHNDCTRL_Tag *)0xE000ED24))
#define SYSTICK_CTRL_R (*((volatile unsigned long *)0xE000E010))
/*
 * An interrupt is generated to the NVIC when SysTick counts to 0.
 */
#define SYSTICK_INTEN 1
#define ENDIANESS 15 
#define SYSCTRL  (*((volatile unsigned long *)0xE000ED10))
#define SEVONPEND 4 
#define SLEEPEXIT 1 

#define VTABLE (*(volatile uint32 *)0xE000ED08)
#define APINT (*(volatile uint32 *)0xE000ED0C)

#define NVIC_APINT_VECTKEY_M 0xFFFF0000 // Register Key
#define APINT_VECTKEY 0x05FA            // Vector key

#define SYSRESREQ 2

/**********************************************************************************************************************
 *   END System Control HW
 *********************************************************************************************************************/





/*===========================================================*
 * GPIO REGISTERS                                            *
 *========================================================== */
typedef struct
{
    uint32 GPIODATA    ;
    uint32 GPIODIR     ;
    uint32 GPIOIS      ;
    uint32 GPIOIBE     ;
    uint32 GPIOIEV     ;
    uint32 GPIOIM      ;
    uint32 GPIORIS     ;
    uint32 GPIOMIS     ;
    uint32 GPIOICR     ;
      uint32 GPIOAFSEL   ; /*offset : 0x420+4 byte = 0x424 end:0x424*/

    uint8 Reserved[0xDC];/*500-424 = DC byte 0r 37 uint32 */
    
    uint32 GPIODR2R    ; /*offset : 0x500 */
    uint32 GPIODR4R    ;
    uint32 GPIODR8R    ;
    uint32 GPIOODR     ;
    uint32 GPIOPUR     ;
    uint32 GPIOPDR     ;
    uint32 GPIOSLR     ;
    uint32 GPIODEN     ;
    uint32 GPIOLOCK    ;
    uint32 GPIOCR      ;
    uint32 GPIOAMSEL   ;
    uint32 GPIOPCTL    ;
    uint32 GPIOADCCTL  ;
    uint32 GPIODMACTL  ;
}PORT_Registers;

#define PORTA_REG     (*((volatile PORT_Registers*)0x400043FC))
#define PORTB_REG     (*((volatile PORT_Registers*)0x400053FC))
#define PORTC_REG     (*((volatile PORT_Registers*)0x400063FC))
#define PORTD_REG     (*((volatile PORT_Registers*)0x400073FC))
#define PORTE_REG     (*((volatile PORT_Registers*)0x400243FC))
#define PORTF_REG     (*((volatile PORT_Registers*)0x400253FC))













#endif
