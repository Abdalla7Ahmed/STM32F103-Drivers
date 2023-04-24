/*
 * RCC Driver
 *
 *  Created on: ١٩‏/٠٩‏/٢٠٢٢
 *      Author: Abdallah Ahmed Mohammed
 */

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_

// Includes
#include "STM32F103C6.h"
#include "STM32F103C6_GPIO_Driver.h"

// The HSI clock signal is generated from an internal 8 MHz RC Oscillator and can be used
// directly as a system clock or divided by 2 to be used as PLL input.
#define HSI_RCC_Clock                 (uint32_t)8000000
// set the frequency of external Oscillator
#define HSE_RCC_Clock                 (uint32_t)16000000



typedef struct
{
	// Specify the clock source which will be output from MCO pin
	//this parameter must be set based on @ref MCO_Output_define(SYSCLK , HSI , HSE , PLL clock divided by 2 )
	uint32_t MCO_Output_Select	;
	//generate 48 MHz USB clock
	//this parameter must be set based on @ref USB prescaler_define(divided by 1.5 ,  not divided)
	uint32_t USB_prescaler;

	// define the PLL multiplication factor.
	//this parameter must be set based on @ref PLL_input_clock_MUL_define
	uint32_t PLL_multiplication;
	//  Specify HSE divider for PLL entry
	//this parameter must be set based on @ref HSE_PLL_divider_define(not divided , divided by 2)
	uint32_t HSE_PLL_divider;

	// Specify PLL entry clock source
	//this parameter must be set based on @ref PLL_clock_source_define(HSI  / 2 , HSE )
	uint32_t  PLL_clock_source;

	// Specify ADC prescaler
	//this parameter must be set based on @ref ADC_prescaler_define(PCLK2 divided by 2,4,6,8)
	uint32_t ADC_prescaler;

	// Specify APB high-speed prescaler (APB2)
	//this parameter must be set based on @ref APB2_prescaler_define(HCLK divided by 2,4,8,16,not divided)
	uint32_t APB2_prescaler;

	// Specify APB low-speed prescaler (APB1)
	//this parameter must be set based on @ref APB1_prescaler_define(HCLK divided by 2,4,8,16,not divided)
	uint32_t APB1_prescaler;

	// Specify AHB prescaler
	//this parameter must be set based on @ref AHP_prescaler_define(SYSCLK divided by 2,4,8,16,64,128,256,512,not divided)
	uint32_t AHP_prescaler;

	// Specify System clock switch
	//this parameter must be set based on @ref System_Clock_Switch_define(HSI,HSE,PLL)
	uint32_t System_Clock_Switch;

}RCC_Config;





//@ref MCO_Output_define
#define MCO_Positon												24U
#define MCO_Output_NONE								 			(uint32_t)(0x0<<MCO_Positon)
#define MCO_Output_SYSCLK										(uint32_t)(0x4<<MCO_Positon)	// System clock (SYSCLK) selected
#define MCO_Output_HSI											(uint32_t)(0x5<<MCO_Positon)	// HSI clock selected
#define MCO_Output_HSE 											(uint32_t)(0x6<<MCO_Positon)	// HSE clock selected
#define MCO_Output_PLL_Divided_by_2								(uint32_t)(0x7<<MCO_Positon)	//  PLL clock divided by 2 selected


//@ref USB_prescaler_define
#define USBPRE_Position											22U
#define USB_prescaler_oneANDhalf								(uint32_t)(~(0x1<<USBPRE_Position))
#define USB_prescaler_NONE										(uint32_t)(0x1<<USBPRE_Position)


//@ref PLL_input_clock_MUL_define
#define PLLMUL_Position											18U
#define PLL_input_clock_MUL_2									(uint32_t)(0x0<<PLLMUL_Position)
#define PLL_input_clock_MUL_3									(uint32_t)(0x1<<PLLMUL_Position)
#define PLL_input_clock_MUL_4									(uint32_t)(0x2<<PLLMUL_Position)
#define PLL_input_clock_MUL_5									(uint32_t)(0x3<<PLLMUL_Position)
#define PLL_input_clock_MUL_6									(uint32_t)(0x4<<PLLMUL_Position)
#define PLL_input_clock_MUL_7									(uint32_t)(0x5<<PLLMUL_Position)
#define PLL_input_clock_MUL_8									(uint32_t)(0x6<<PLLMUL_Position)
#define PLL_input_clock_MUL_9									(uint32_t)(0x7<<PLLMUL_Position)
#define PLL_input_clock_MUL_10									(uint32_t)(0x8<<PLLMUL_Position)
#define PLL_input_clock_MUL_11									(uint32_t)(0x9<<PLLMUL_Position)
#define PLL_input_clock_MUL_12									(uint32_t)(0xA<<PLLMUL_Position)
#define PLL_input_clock_MUL_13									(uint32_t)(0xB<<PLLMUL_Position)
#define PLL_input_clock_MUL_14									(uint32_t)(0xC<<PLLMUL_Position)
#define PLL_input_clock_MUL_15									(uint32_t)(0xD<<PLLMUL_Position)
#define PLL_input_clock_MUL_16									(uint32_t)(0xE<<PLLMUL_Position)
#define PLL_input_clock_MUL_17									(uint32_t)(0xF<<PLLMUL_Position)


//@ref HSE_PLL_divider_define
#define PLLXTPRE_Position										17U
#define HSE_PLL_divider_NONE									(uint32_t)(~(0x0<<PLLXTPRE_Position))
#define HSE_PLL_divider_2										(uint32_t)(0x1<<PLLXTPRE_Position)

//@ref PLL_clock_source_define
#define PLLSRC_Position											16U
#define PLL_clock_source_HSI_divider_2							(uint32_t)(~(0x1<<PLLSRC_Position))
#define PLL_clock_source_HSE									(uint32_t)(0x1<<PLLSRC_Position)

//@ref ADC_prescaler_define
#define ADCPRE_Position											14U
#define ADC_prescaler_2											(uint32_t)(0x0<<ADCPRE_Position)
#define ADC_prescaler_4											(uint32_t)(0x1<<ADCPRE_Position)
#define ADC_prescaler_6											(uint32_t)(0x2<<ADCPRE_Position)
#define ADC_prescaler_8											(uint32_t)(0x3<<ADCPRE_Position)


//@ref APB2_prescaler_define
#define PPRE2_Position											11U
#define APB2_prescaler_NONE										(uint32_t)(0x0<<PPRE2_Position)
#define APB2_prescaler_2										(uint32_t)(0x4<<PPRE2_Position)
#define APB2_prescaler_4										(uint32_t)(0x5<<PPRE2_Position)
#define APB2_prescaler_8										(uint32_t)(0x6<<PPRE2_Position)
#define APB2_prescaler_16										(uint32_t)(0x7<<PPRE2_Position)

//@ref APB1_prescaler_define
#define PPRE1_Position											8U
#define APB1_prescaler_NONE										(uint32_t)(0x0<<PPRE1_Position)
#define APB1_prescaler_2										(uint32_t)(0x4<<PPRE1_Position)
#define APB1_prescaler_4										(uint32_t)(0x5<<PPRE1_Position)
#define APB1_prescaler_8										(uint32_t)(0x6<<PPRE1_Position)
#define APB1_prescaler_16										(uint32_t)(0x7<<PPRE1_Position)


//@ref AHP_prescaler_define
#define HPRE_Position											4U
#define AHP_prescaler_NONE										(uint32_t)(0x0<<HPRE_Position)
#define AHP_prescaler_2											(uint32_t)(0x8<<HPRE_Position)
#define AHP_prescaler_4											(uint32_t)(0x9<<HPRE_Position)
#define AHP_prescaler_8											(uint32_t)(0xA<<HPRE_Position)
#define AHP_prescaler_16										(uint32_t)(0xB<<HPRE_Position)
#define AHP_prescaler_64										(uint32_t)(0xC<<HPRE_Position)
#define AHP_prescaler_128										(uint32_t)(0xD<<HPRE_Position)
#define AHP_prescaler_256										(uint32_t)(0xE<<HPRE_Position)
#define AHP_prescaler_512										(uint32_t)(0xF<<HPRE_Position)


//@ref System_Clock_Switch_define
#define SW_Position												0U
#define System_Clock_Switch_HSI									(uint32_t)(~(0x1<<SW_Position))
#define System_Clock_Switch_HSE									(uint32_t)(0x1<<SW_Position)
#define System_Clock_Switch_PLL									(uint32_t)(0x2<<SW_Position)




//APB2 peripheral reset register (RCC_APB2RSTR)
#define Timer11_Reset											(uint32_t)(1<<21)
#define Timer10_Reset											(uint32_t)(1<<20)
#define Timer9_Reset											(uint32_t)(1<<19)
#define ADC3_Reset												(uint32_t)(1<<15)
#define USART1_Reset											(uint32_t)(1<<14)
#define Timer8_Reset											(uint32_t)(1<<13)
#define SPI1_Reset												(uint32_t)(1<<12)
#define Timer1_Reset											(uint32_t)(1<<11)
#define ADC2_Reset												(uint32_t)(1<<10)
#define ADC1_Reset												(uint32_t)(1<<9)
#define GPIOG_Reset												(uint32_t)(1<<8)
#define GPIOF_Reset												(uint32_t)(1<<7)
#define GPIOE_Reset												(uint32_t)(1<<6)
#define GPIOD_Reset												(uint32_t)(1<<5)
#define GPIOC_Reset												(uint32_t)(1<<4)
#define GPIOB_Reset												(uint32_t)(1<<3)
#define GPIOA_Reset												(uint32_t)(1<<2)
#define AFIO_Reset												(uint32_t)(1<<0)

//APB1 peripheral reset register (RCC_APB1RSTR)
#define DAC_Reset												(uint32_t)(1<<29)
#define PWR_Reset												(uint32_t)(1<<28)
#define BKP_Reset												(uint32_t)(1<<27)
#define CAN_Reset												(uint32_t)(1<<25)
#define USB_Reset												(uint32_t)(1<<23)
#define I2C1_Reset												(uint32_t)(1<<22)
#define I2C2_Reset												(uint32_t)(1<<21)
#define UART5_Reset												(uint32_t)(1<<20)
#define UART4_Reset												(uint32_t)(1<<19)
#define USART3_Reset											(uint32_t)(1<<18)
#define USART2_Reset											(uint32_t)(1<<17)
#define SPI3_Reset												(uint32_t)(1<<15)
#define SPI2_Reset												(uint32_t)(1<<14)
#define WWDG_Reset												(uint32_t)(1<<11)
#define TIM14_Reset												(uint32_t)(1<<8)
#define TIM13_Reset												(uint32_t)(1<<7)
#define TIM12_Reset												(uint32_t)(1<<6)
#define TIM7_Reset												(uint32_t)(1<<5)
#define TIM6_Reset												(uint32_t)(1<<4)
#define TIM5_Reset												(uint32_t)(1<<3)
#define TIM4_Reset												(uint32_t)(1<<2)
#define TIM3_Reset												(uint32_t)(1<<1)
#define TIM2_Reset												(uint32_t)(1<<0)

// AHB peripheral clock enable register (RCC_AHBENR)
#define SDIO_Enable												(uint32_t)(1<<10)
#define FSMC_Enable												(uint32_t)(1<<8)
#define CRC_Enable												(uint32_t)(1<<6)
#define FLITF_Enable											(uint32_t)(1<<4)
#define SRAM_Enable												(uint32_t)(1<<2)
#define DMA2_Enable												(uint32_t)(1<<1)
#define DMA1_Enable												(uint32_t)(1<<0)

//APB2 peripheral clock enable register (RCC_APB2ENR)
#define Timer11_Enable											(uint32_t)(1<<21)
#define Timer10_Enable											(uint32_t)(1<<20)
#define Timer9_Enable											(uint32_t)(1<<19)
#define ADC3_Enable												(uint32_t)(1<<15)
#define USART1_Enable											(uint32_t)(1<<14)
#define Timer8_Enable											(uint32_t)(1<<13)
#define SPI1_Enable												(uint32_t)(1<<12)
#define Timer1_Enable											(uint32_t)(1<<11)
#define ADC2_Enable												(uint32_t)(1<<10)
#define ADC1_Enable												(uint32_t)(1<<9)
#define GPIOG_Enable											(uint32_t)(1<<8)
#define GPIOF_Enable											(uint32_t)(1<<7)
#define GPIOE_Enable											(uint32_t)(1<<6)
#define GPIOD_Enable											(uint32_t)(1<<5)
#define GPIOC_Enable				 							(uint32_t)(1<<4)
#define GPIOB_Enable											(uint32_t)(1<<3)
#define GPIOA_Enable											(uint32_t)(1<<2)
#define AFIO_Enable												(uint32_t)(1<<0)


// APB1 peripheral clock enable register (RCC_APB1ENR)
#define DAC_Enable												(uint32_t)(1<<29)
#define PWR_Enable												(uint32_t)(1<<28)
#define BKP_Enable												(uint32_t)(1<<27)
#define CAN_Enable												(uint32_t)(1<<25)
#define USB_Enable												(uint32_t)(1<<23)
#define I2C1_Enable												(uint32_t)(1<<22)
#define I2C2_Enable												(uint32_t)(1<<21)
#define UART5_Enable											(uint32_t)(1<<20)
#define UART4_Enable											(uint32_t)(1<<19)
#define USART3_Enable											(uint32_t)(1<<18)
#define USART2_Enable											(uint32_t)(1<<17)
#define SPI3_Enable												(uint32_t)(1<<15)
#define SPI2_Enable												(uint32_t)(1<<14)
#define WWDG_Enable												(uint32_t)(1<<11)
#define TIM14_Enable											(uint32_t)(1<<8)
#define TIM13_Enable											(uint32_t)(1<<7)
#define TIM12_Enable											(uint32_t)(1<<6)
#define TIM7_Enable												(uint32_t)(1<<5)
#define TIM6_Enable												(uint32_t)(1<<4)
#define TIM5_Enable												(uint32_t)(1<<3)
#define TIM4_Enable												(uint32_t)(1<<2)
#define TIM3_Enable												(uint32_t)(1<<1)
#define TIM2_Enable												(uint32_t)(1<<0)

// APIS

void MCAL_RCC_Init(RCC_Config *RCC_Configuration);
void MCAL_RCC_DeInit(void);
void MCAL_RCC_Enable_AHP_Peripheral(uint32_t Peripheral);
void MCAL_RCC_Enable_APB1_Peripheral(uint32_t Peripheral);
void MCAL_RCC_Enable_APB2_Peripheral(uint32_t Peripheral);
void MCAL_RCC_Reset_APB1_Peripheral(uint32_t Peripheral);
void MCAL_RCC_Reset_APB2_Peripheral(uint32_t Peripheral);
uint32_t MCAL_RCC_GET_SysClockFreq(void);
uint32_t MCAL_RCC_GET_HCLKFreq(void);
uint32_t MCAL_RCC_GET_PCLK1Freq(void);
uint32_t MCAL_RCC_GET_PCLK2Freq(void);



#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
