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










/**********************************************************************************************************************
 *  Start ADC HW
 *********************************************************************************************************************/



typedef struct 
{
/*0x000*/ volatile uint32 ADCACTSS	 ; /*ADC Active Sample Sequencer                          */ 					
/*0x004*/ volatile uint32 ADCRIS 	 ; /*ADC Raw Interrupt Status                             */
/*0x008*/ volatile uint32 ADCIM 	 ; /*ADC Interrupt Mask                                   */
/*0x00C*/ volatile uint32 ADCISC 	 ; /*ADC Interrupt Status and Clear                       */
/*0x010*/ volatile uint32 ADCOSTAT	 ; /*ADC Overflow Status                                  */
/*0x014*/ volatile uint32 ADCEMUX 	 ; /*ADC Event Multiplexer Select                         */
/*0x018*/ volatile uint32 ADCUSTAT	 ; /*ADC Underflow Status                                 */
/*0x01C*/ volatile uint32 ADCTSSEL	 ; /*ADC Trigger Source Select                            */
/*0x020*/ volatile uint32 ADCSSPRI	 ; /*ADC Sample Sequencer Priority                        */
/*0x024*/ volatile uint32 ADCSPC  	 ; /*ADC Sample Phase Control                             */
/*0x028*/ volatile uint32 ADCPSSI 	 ; /*cessor Sample Sequence Initiate                      */
/*0x030*/ volatile uint32 ADCSAC 	 ; /*ADC Sample Averaging Control                         */
/*0x034*/ volatile uint32 ADCDCISC	 ; /*ADC Digital Comparator Interrupt Status and Clear    */
/*0x038*/ volatile uint32 ADCCTL 	 ; /*ADC Control                                          */
/*0x040*/ volatile uint32 ADCSSMUX0  ; /*ADC Sample Sequence Input Multiplexer Select         */
/*0x044*/ volatile uint32 ADCSSCTL0  ; /*ADC Sample Sequence Control                          */
/*0x048*/ volatile uint32 ADCSSFIFO0 ; /*ADC Sample Sequence Result FIFO 0                    */
/*0x04C*/ volatile uint32 ADCSSFSTAT0; /*ADC Sample Sequence FIFO 0 Status                    */
/*0x050*/ volatile uint32 ADCSSOP0   ; /*ADC Sample Sequence 0 Operation                      */
/*0x054*/ volatile uint32 ADCSSDC0   ; /*ADC Sample Sequence 0 Digital Comparator Select      */
/*0x060*/ volatile uint32 ADCSSMUX1  ; /*ADC Sample Sequence Input Multiplexer Select         */
/*0x064*/ volatile uint32 ADCSSCTL1  ; /*ADC Sample Sequence Control                          */
/*0x068*/ volatile uint32 ADCSSFIFO1 ; /*ADC Sample Sequence Result FIFO 1                    */
/*0x06C*/ volatile uint32 ADCSSFSTAT1; /*ADC Sample Sequence FIFO 1 Status                    */
/*0x070*/ volatile uint32 ADCSSOP1   ; /*ADC Sample Sequence 1 Operation                      */
/*0x074*/ volatile uint32 ADCSSDC1   ; /*ADC Sample Sequence 1 Digital Comparator Select      */
/*0x080*/ volatile uint32 ADCSSMUX2  ; /*ADC Sample Sequence Input Multiplexer Select         */
/*0x084*/ volatile uint32 ADCSSCTL2  ; /*ADC Sample Sequence Control                          */
/*0x088*/ volatile uint32 ADCSSFIFO2 ; /*ADC Sample Sequence Result FIFO 2                    */
/*0x08C*/ volatile uint32 ADCSSFSTAT2; /*ADC Sample Sequence FIFO 2 Status                    */
/*0x090*/ volatile uint32 ADCSSOP2   ; /*ADC Sample Sequence 2 Operation                      */
/*0x094*/ volatile uint32 ADCSSDC2   ; /*ADC Sample Sequence 2 Digital Comparator Select      */
/*0x0A0*/ volatile uint32 ADCSSMUX3  ; /*ADC Sample Sequence Input Multiplexer Select         */
/*0x0A4*/ volatile uint32 ADCSSCTL3  ; /*ADC Sample Sequence Control                          */
/*0x0A8*/ volatile uint32 ADCSSFIFO3 ; /*ADC Sample Sequence Result FIFO 3                    */
/*0x0AC*/ volatile uint32 ADCSSFSTAT3; /*ADC Sample Sequence FIFO 3 Status                    */
/*0x0B0*/ volatile uint32 ADCSSOP3   ; /*ADC Sample Sequence 3 Operation                      */
/*0x0B4*/ volatile uint32 ADCSSDC3   ; /*ADC Sample Sequence 3 Digital Comparator Select      */
/*0xD00*/ volatile uint32 ADCDCRIC   ; /*ADC Digital Comparator Reset Initial Conditions      */
/*0xE00*/ volatile uint32 ADCDCCTL0  ; /*ADC Digital Comparator Control                       */
/*0xE04*/ volatile uint32 ADCDCCTL1  ; /*ADC Digital Comparator Control                       */
/*0xE08*/ volatile uint32 ADCDCCTL2  ; /*ADC Digital Comparator Control                       */
/*0xE0C*/ volatile uint32 ADCDCCTL3  ; /*ADC Digital Comparator Control                       */
/*0xE10*/ volatile uint32 ADCDCCTL4  ; /*ADC Digital Comparator Control                       */
/*0xE14*/ volatile uint32 ADCDCCTL5  ; /*ADC Digital Comparator Control                       */
/*0xE18*/ volatile uint32 ADCDCCTL6  ; /*ADC Digital Comparator Control                       */
/*0xE1C*/ volatile uint32 ADCDCCTL7  ; /*ADC Digital Comparator Control                       */
/*0xE40*/ volatile uint32 ADCDCCMP0  ; /*ADC Digital Comparator Range                         */
/*0xE44*/ volatile uint32 ADCDCCMP1  ; /*ADC Digital Comparator Range                         */
/*0xE48*/ volatile uint32 ADCDCCMP2  ; /*ADC Digital Comparator Range                         */
/*0xE4C*/ volatile uint32 ADCDCCMP3  ; /*ADC Digital Comparator Range                         */
/*0xE50*/ volatile uint32 ADCDCCMP4  ; /*ADC Digital Comparator Range                         */
/*0xE54*/ volatile uint32 ADCDCCMP5  ; /*ADC Digital Comparator Range                         */
/*0xE58*/ volatile uint32 ADCDCCMP6  ; /*ADC Digital Comparator Range                         */
/*0xE5C*/ volatile uint32 ADCDCCMP7  ; /*ADC Digital Comparator Range                         */
/*0xFC0*/ volatile uint32 ADCPP      ; /*ADC Peripheral Properties                            */
/*0xFC4*/ volatile uint32 ADCPC      ; /*ADC Peripheral Configuration                         */
/*0xFC8*/ volatile uint32 ADCCC      ;/*ADC Clock Configuration                              */
}Adc_Regs;

#define ADC0_BASE 0x40038000
#define ADC1_BASE 0x40039000
#define ADC0 ((Adc_Regs *)ADC0_BASE)
#define ADC1 ((Adc_Regs *)ADC1_BASE)

#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define MAXADC0SPD 8
#define MAXADC1SPD 10
/*12 bit ADC*/
#define ADC_12BIT_RESULT_MASK 0x00000FFF
#define ADC0_SAMPLE_RATE_MASK 0xFFFFFCFF
#define ADC1_SAMPLE_RATE_MASK 0xFFFFF3FF

#define EM3 12 
#define SEQ3_TRIG_REG_MASK 0xFFFF1FFF

/**********************************************************************************************************************
 *   END ADC HW
 *********************************************************************************************************************/



#endif
