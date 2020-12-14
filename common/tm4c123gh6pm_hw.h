#ifndef TM4C123GH6PM_HW_H_
#define TM4C123GH6PM_HW_H_

#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"




/**********************************************************************************************************************
 *   GPIO HW
 *********************************************************************************************************************/

#define DIO_PORTS_NUMBER 6
#define PORTS_NUMBER 6

#define PORTA_BASE_ADDRESS    (0x40004000)
#define PORTB_BASE_ADDRESS    (0x40005000)
#define PORTC_BASE_ADDRESS    (0x40006000)
#define PORTD_BASE_ADDRESS    (0x40007000)
#define PORTE_BASE_ADDRESS    (0x40024000)
#define PORTF_BASE_ADDRESS    (0x40025000)


typedef struct {
    /* 0x3FC */ volatile unsigned long GPIODATA ;
    /* 0x400 */ volatile unsigned long GPIODIR  ;
    /* 0x404 */ volatile unsigned long GPIOIS   ;
    /* 0x408 */ volatile unsigned long GPIOIBE  ;
    /* 0x40C */ volatile unsigned long GPIOIEV  ;
    /* 0x410 */ volatile unsigned long GPIOIM   ;
    /* 0x414 */ volatile unsigned long GPIORIS  ;
    /* 0x418 */ volatile unsigned long GPIOMIS  ;
    /* 0x41C */ volatile unsigned long GPIOICR  ;
    /* 0x420 */ volatile unsigned long GPIOAFSEL;
     /*gap*/        unsigned long  RESERVED1[55];
    /* 0x500 */ volatile unsigned long GPIODR2R ;
    /* 0x504 */ volatile unsigned long GPIODR4R ;
    /* 0x508 */ volatile unsigned long GPIODR8R ;
    /* 0x50C */ volatile unsigned long GPIOODR  ;
    /* 0x510 */ volatile unsigned long GPIOPUR  ;
    /* 0x514 */ volatile unsigned long GPIOPDR  ;
    /* 0x518 */ volatile unsigned long GPIOSLR  ;
    /* 0x51C */ volatile unsigned long GPIODEN  ;
    /* 0x520 */ volatile unsigned long GPIOLOCK ;
    /* 0x524 */ volatile unsigned long GPIOCR   ;
		/*0x528*/   volatile unsigned long GPIOAMSEL ; 
		/*0x52C*/ volatile unsigned long GPIOPCTL ; 
		/*0x530*/ volatile unsigned long GPIOADCCTL ; 
}GPIO_typedef;

#define  GPIO_DATA_REGISTER_OFFSET         0x3FC 
#define  GPIO_DIR_REGISTER_OFFSET          0x400 
#define  GPIO_IS_REGISTER_OFFSET           0x404 
#define  GPIO_IBE_REGISTER_OFFSET          0x408 
#define  GPIO_IEV_REGISTER_OFFSET          0x40C 
#define  GPIO_IM_REGISTER_OFFSET           0x410 
#define  GPIO_RIS_REGISTER_OFFSET          0x414 
#define  GPIO_MIS_REGISTER_OFFSET          0x418 
#define  GPIO_ICR_REGISTER_OFFSET          0x41C 
#define  GPIO_AFSEL_REGISTER_OFFSET        0x420 
#define  GPIO_DR2R_REGISTER_OFFSET         0x500 
#define  GPIO_DR4R_REGISTER_OFFSET         0x504 
#define  GPIO_DR8R_REGISTER_OFFSET         0x508 
#define  GPIO_ODR_REGISTER_OFFSET          0x50C 
#define  GPIO_PUR_REGISTER_OFFSET          0x510 
#define  GPIO_PDR_REGISTER_OFFSET          0x514 
#define  GPIO_SLR_REGISTER_OFFSET          0x518 
#define  GPIO_DEN_REGISTER_OFFSET          0x51C 
#define  GPIO_LOCK_REGISTER_OFFSET         0x520 
#define  GPIO_CR_REGISTER_OFFSET           0x524 
#define  GPIO_AMSEL_REGISTER_OFFSET        0x528 
#define  GPIO_PCTL _REGISTER_OFFSET	       0x52C
#define  GPIO_ADCCTL_REGISTER_OFFSET	     0x530

		
		
#define GPIODATA(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DATA_REGISTER_OFFSET))
#define GPIODIR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DIR_REGISTER_OFFSET))
#define GPIODATA(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DATA_REGISTER_OFFSET))
#define GPIOCR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_CR_REGISTER_OFFSET))
#define GPIOAFSEL(PORT_ID)(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_AFSEL_REGISTER_OFFSET))
#define GPIOPUR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_PUR_REGISTER_OFFSET))
#define GPIOPDR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_PDR_REGISTER_OFFSET))
#define GPIODEN(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DEN_REGISTER_OFFSET))
#define GPIOLOCK(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_LOCK_REGISTER_OFFSET))
#define GPIOAMSEL(PORT_ID)(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_AMSEL_REGISTER_OFFSET))
#define GPIOCR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_CR_REGISTER_OFFSET))
#define GPIOODR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_ODR_REGISTER_OFFSET))
#define ADCCTL(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_ADCCTL_REGISTER_OFFSET))
#define GPIOPCTL(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_ADCCTL_REGISTER_OFFSET))
#define GPIODR2R(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DR2R_REGISTER_OFFSET))
#define GPIODR4R(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DR4R_REGISTER_OFFSET))
#define GPIODR8R(PORT_ID) (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DR8R_REGISTER_OFFSET))
#define GPIOIBE(PORT_ID)	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_IBE_REGISTER_OFFSET))
#define GPIOIEV(PORT_ID)	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_IEV_REGISTER_OFFSET))
#define GPIOIM(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_IM_REGISTER_OFFSET))

extern const uint32 GPIOPortsBaseAddress[DIO_PORTS_NUMBER] ;
/**********************************************************************************************************************
 *  End Gpio HW
 *********************************************************************************************************************/


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


#define ADC0_ACTSS_R (*((volatile unsigned long *)0x40038000))
#define ADC0_SSMUX1_R (*((volatile unsigned long *)0x40038060))
#define ADC0_SSFIFO1_R (*((volatile unsigned long *)0x40038068))
#define ADC0_ISC_R (*((volatile unsigned long *)0x4003800C))


#define ADCSSMUX0_OFFSET 0x040
#define ADCSSMUX1_OFFSET 0x060
#define ADCSSMUX2_OFFSET 0x080
#define ADCSSMUX3_OFFSET 0x0A0


#define SSCTL0_OFFSET (0x044)
#define SSCTL1_OFFSET (0x064)
#define SSCTL2_OFFSET (0x084)
#define SSCTL3_OFFSET (0x0A4)



#define ADC_SSFIFO0_OFFSET_REG 0x048
#define ADC_SSFIFO1_OFFSET_REG 0x068
#define ADC_SSFIFO2_OFFSET_REG 0x088
#define ADC_SSFIFO3_OFFSET_REG 0x0A8

#define ADCSSFIFO(ADC_MODULE,SEQ) (*(volatile uint32 *)(adcModules[ADC_MODULE] + adc_ssfifo[SEQ]))
#define ADCACTSS(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0x000))
#define ADCEMUX(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0x014))
#define ADCSSMUX(ADC_MODULE,SEQ) (*(volatile uint32 *)(adcModules[ADC_MODULE] + adc_ssmuxRegs[SEQ]))
#define ADCPSSI(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0x028))
#define SSCTL(ADC_MODULE,SEQ) (*(volatile uint32 *)(adcModules[ADC_MODULE] + adc_ssctrlRegs[SEQ]))
#define ADCPC(ADC_MODULE) (*(volatile uint32 *)(adcModules[ADC_MODULE] + 0xFC4))
	
extern	const uint32  adc_ssctrlRegs[4] ; 
extern	const	uint32  adc_ssmuxRegs[4] ;
extern	const uint32 adcModules[2] ;
extern	const	uint32  adc_ssfifo[4] ;
/**********************************************************************************************************************
 *   END ADC HW
 *********************************************************************************************************************/



#endif
