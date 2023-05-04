//|========================================================================|
//|Microcontroller ========/    STM32F103C6       \========================|
//|Driver ================/     RCC Drivers        \=======================|
//|File =================|      RCC_Drivers.c       |======================|
//|Author ================\     Abdallah Ahmed     /=======================|
//|Created on =============\      28/4/2023       /========================|
//|========================================================================|

// =======================================
// Includes
//========================================
#include "STM32F103C6_RCC_Driver.h"

const uint8_t APB_prescaler[8U]={0,0,0,0,1,2,3,4};
const uint8_t AHB_prescaler[16U]={0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};

GPIO_PinConfig_t PinConfig;


void MCAL_RCC_Init(RCC_Config *RCC_Configuration)
{
	if(RCC_Configuration->System_Clock_Switch == System_Clock_Switch_HSI)
	{
		//HSI selected as system clock
		RCC->CR &=RCC_Configuration->System_Clock_Switch;
		// wait until internal 8 MHz RC oscillator is stable.
		while(!(RCC->CR &(1<<1)));
	}
	else if(RCC_Configuration ->System_Clock_Switch == System_Clock_Switch_HSE)
	{
		//bypass the oscillator with an external clock
		RCC->CR |=(1<<18);
		// wait until the HSE oscillator is stable,it take 6 clock cycle
		//the clock is not released until this bit is set by hardware
		while(!(RCC->CR &(1<<17)));
		//HSE oscillator ON
		RCC->CR |=(1<<16);
		//HSE selected as system clock
		RCC->CFGR |=RCC_Configuration ->System_Clock_Switch;

		//  Clock security system enable
		RCC->CR |= (1<<19);
	}
	else if(RCC_Configuration ->System_Clock_Switch == System_Clock_Switch_PLL)
	{
		//PLL entry clock source(HSI/2 or HSE)
		if(RCC_Configuration->PLL_clock_source == PLL_clock_source_HSI_divider_2)
		{
			RCC->CFGR &= RCC_Configuration ->PLL_clock_source;
		}
		else if(RCC_Configuration->PLL_clock_source == PLL_clock_source_HSE)
		{
			if(RCC_Configuration->HSE_PLL_divider == HSE_PLL_divider_NONE)
			{
				RCC->CFGR &=RCC_Configuration->HSE_PLL_divider;
			}
			else if(RCC_Configuration->HSE_PLL_divider == HSE_PLL_divider_2)
			{
				RCC->CFGR |=RCC_Configuration->HSE_PLL_divider;
			}
			RCC->CFGR |= RCC_Configuration ->PLL_clock_source;

			//  Clock security system enable
			RCC->CR |= (1<<19);
		}
		//PLLMUL: PLL multiplication factor
		RCC->CFGR |=RCC_Configuration->PLL_multiplication;
		// PLL selected as system clock
		RCC->CFGR |=RCC_Configuration ->System_Clock_Switch;
	}
	// before enable PLL make sure that clock in APB1 ,APB2 , ADC ,Timer ,........ are configured
	/*
	    selection of HSI oscillator divided by 2 or HSE oscillator for PLL
		input clock, and multiplication factor) must be done before enabling the PLL. Once the PLL
		enabled, these parameters cannot be changed.
	 */

	// USB prescaler (divided by 1.5 , not divided)
	if(RCC_Configuration->USB_prescaler == USB_prescaler_oneANDhalf)
	{
		RCC->CFGR &=RCC_Configuration->USB_prescaler;
	}
	else if(RCC_Configuration->USB_prescaler == USB_prescaler_NONE)
	{
		RCC->CFGR |=RCC_Configuration->USB_prescaler;
	}


	// ADC prescaler(divided by 2,4,6,8)
	RCC->CFGR |=RCC_Configuration->ADC_prescaler;

	//HPRE: AHB prescaler
	RCC->CFGR |=RCC_Configuration->AHP_prescaler;

	//PPRE2: APB high-speed prescaler (APB2)
	RCC->CFGR |=RCC_Configuration->APB2_prescaler;

	//APB low-speed prescaler (APB1)
	RCC->CFGR |=RCC_Configuration->APB1_prescaler;

	if(RCC_Configuration ->System_Clock_Switch == System_Clock_Switch_PLL)
	{
		// enable PLL
		RCC->CR |= (1<<24);
		//PLL clock ready flag
		//Set by hardware to indicate that the PLL is locked
		while(!(RCC->CR &(1<<25)));
	}

	if(RCC_Configuration->MCO_Output_Select !=MCO_Output_NONE)
	{
		RCC->CFGR |=RCC_Configuration->MCO_Output_Select;
		// PORTA pin 8
		//MCO Clock output --> Alternate function push-pull
		PinConfig.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_50M;
		PinConfig.GPIO_PinNumber = GPIO_PIN_8;
		MCAL_GPIO_INIT(GPIOA, &PinConfig);
	}
}

void MCAL_RCC_DeInit(void)
{
	RCC->CR = 0x83 ;
	RCC->CFGR = 0x00;
	RCC->CIR = 0x00;
	RCC->APB2RSTR = 0x00;
	RCC->APB1RSTR = 0x00;
	RCC->AHBENR = 0x14;
	RCC->APB2ENR = 0x00;
	RCC->APB1ENR = 0x00;
	RCC->BDCR = 0x00;
	RCC->CSR = 0x00;

}


void MCAL_RCC_Enable_AHP_Peripheral(uint32_t Peripheral)
{
	RCC->AHBENR |=Peripheral;
}
void MCAL_RCC_Enable_APB1_Peripheral(uint32_t Peripheral)
{
	RCC->APB1ENR |=Peripheral;
}
void MCAL_RCC_Enable_APB2_Peripheral(uint32_t Peripheral)
{
	RCC->APB2ENR |=Peripheral;
}
void MCAL_RCC_Reset_APB1_Peripheral(uint32_t Peripheral)
{
	RCC->APB1RSTR |=Peripheral;
}
void MCAL_RCC_Reset_APB2_Peripheral(uint32_t Peripheral)
{
	RCC->APB2RSTR |=Peripheral;
}





uint32_t MCAL_RCC_GET_SysClockFreq(void)
{
	/*Bits 3:2 SWS: System clock switch status
Set and cleared by hardware to indicate which clock source is used as system clock.
00: HSI oscillator used as system clock
01: HSE oscillator used as system clock
10: PLL used as system clock
11: not applicable*/

	uint32_t SysClockFreq;
	switch( (RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		SysClockFreq = HSI_RCC_Clock;
		break;
	case 1:
		SysClockFreq = HSE_RCC_Clock;
		break;
	case 2:
		SysClockFreq = 16000000;
		break;
	}
	return SysClockFreq;
}
uint32_t MCAL_RCC_GET_HCLKFreq(void)
{
	/*Bits 7:4 HPRE: AHB prescaler
	Set and cleared by software to control the division factor of the AHB clock.
	0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512
	 */


	//Bits 7:4 HPRE: AHB prescaler
	return (MCAL_RCC_GET_SysClockFreq()>>AHB_prescaler[(RCC->CFGR >> 4) & 0b1111]);

}
uint32_t MCAL_RCC_GET_PCLK1Freq(void)
{
	/*Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB low-speed clock
	(PCLK1).
	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16
	 */


	//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return (MCAL_RCC_GET_HCLKFreq()>>APB_prescaler[(RCC->CFGR >> 8 ) & 0b111]); // divided by 2,4,8,16 according to the index of array
}
uint32_t MCAL_RCC_GET_PCLK2Freq(void)
{
	/*Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB high-speed clock
	(PCLK2).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16*/

	//Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return (MCAL_RCC_GET_HCLKFreq()>>APB_prescaler[(RCC->CFGR >> 11 ) & 0b111]);
}
