/*
 * STM32F103C6.h
 *
 *  Created on: Sep 15, 2022
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// --------------------------------------------------
//Includes
// --------------------------------------------------
#include <stdio.h>
#include <stdint.h>
//@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@

// --------------------------------------------------
//Base addresses for memories
// --------------------------------------------------
#define FLASH_MEMORY_BASE            	        0x08000000UL
#define SYSTEM_MEMORY_BASE           		    0x1FFFF000UL
#define SRAM_MEMORY_BASE             		    0x20000000UL
#define PERIEPHERALS_BASE            		    0x40000000UL
#define CORTEX_M3_INTERNAL_PERIEPHERALS_BASE    0xE0000000UL
#define NVIC_BASE                               0xE000E100UL

//#define NVIC_ISER0                              *(volatile uint32_t *)(NVIC_BASE+0x00)
//#define NVIC_ISER1                              *(volatile uint32_t *)(NVIC_BASE+0x04)
//#define NVIC_ISER2                              *(volatile uint32_t *)(NVIC_BASE+0x08)
//#define NVIC_ICER0                              *(volatile uint32_t *)(NVIC_BASE+0x80)
//#define NVIC_ICER1                              *(volatile uint32_t *)(NVIC_BASE+0x84)
//#define NVIC_ICER2                             *(volatile uint32_t *)(NVIC_BASE+0x88)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// --------------------------------------------------
//Base addresses for AHB Peripherals
// --------------------------------------------------
#define RCC_BASE                              	0x40021000UL

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// --------------------------------------------------
//Base addresses for ABB1 Peripherals
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define USART1_BASE							   0x40013800UL


// --------------------------------------------------
//Base addresses for ABB2 Peripherals
// --------------------------------------------------
#define GPIOA_BASE                             0x40010800UL    	  // GPIOA fully included in LQFP48 Package
#define GPIOB_BASE                             0x40010C00UL       // GPIOB fully included in LQFP48 Package
#define GPIOC_BASE                             0x40011000UL       // GPIOC Partial included in LQFP48 Package
#define GPIOD_BASE                             0x40011400UL       // GPIOD Partial included in LQFP48 Package
#define GPIOE_BASE                             0x40011800UL       // GPIOE not include in LQFP48 Package

#define EXTI_BASE                              0x40010400UL
#define AFIO_BASE                              0x40010000UL

#define USART2_BASE							   0x40004400UL
#define USART3_BASE                            0x40004800UL

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// Peripheral registers
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// GPIO Peripheral
typedef struct
{
	volatile uint32_t CRL  ;
	volatile uint32_t CRH  ;
	volatile uint32_t IDR  ;
	volatile uint32_t ODR  ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR  ;
	volatile uint32_t LCKR ;
}GPIO_TypeDef;

// AFIO Peripheral
typedef struct
{
	volatile uint32_t EVCR      ;
	volatile uint32_t MAPR      ;
	volatile uint32_t EXTICR[4] ;
	volatile uint32_t Reserved  ;
	volatile uint32_t MAPR2     ;
}AFIO_TypeDef;

// EXTRI Peripheral
typedef struct
{
	volatile uint32_t IMR   ;
	volatile uint32_t EMR   ;
	volatile uint32_t RTSR  ;
	volatile uint32_t FTSR  ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR    ;
}EXTRI_TypeDef;

// RCC Peripheral
typedef struct
{
	volatile uint32_t CR       ;
	volatile uint32_t CFGR     ;
	volatile uint32_t CIR      ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR   ;
	volatile uint32_t APB2ENR  ;
	volatile uint32_t APB1ENR  ;
	volatile uint32_t BDCR     ;
	volatile uint32_t CSR      ;
}RCC_TypeDef;

typedef struct
{
	// offset addresses 0x00 , 0x04 ,0x08
	volatile uint32_t ISER[3];

}NVIC_ISER_Typedef_t;

// note that offset address of ICER0 is 0x80
typedef struct
{
	// offset addresses 0x80 , 0x84 , 0x88
	volatile uint32_t ICER[3];
}NVIC_ICER_Typedef_t;


// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// USART registers
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
typedef struct
{
	volatile uint32_t SR    ;
	volatile uint32_t DR    ;
	volatile uint32_t BRR   ;
	volatile uint32_t CR1   ;
	volatile uint32_t CR2	;
	volatile uint32_t CR3   ;
	volatile uint32_t GTPR  ;

}USART_TypeDef;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// Peripheral Instants
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#define GPIOA          (( GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB          (( GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC          (( GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD          (( GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE          (( GPIO_TypeDef *)GPIOE_BASE)


#define RCC           (( RCC_TypeDef  *)RCC_BASE )

#define AFIO          (( AFIO_TypeDef *)AFIO_BASE)

#define EXTRI         (( EXTRI_TypeDef*)EXTI_BASE)


#define NVIC_ISER     ((NVIC_ISER_Typedef_t *)NVIC_BASE)
// The offset address of ICER0 is 0x80
#define NVIC_ICER     ( (NVIC_ICER_Typedef_t *)NVIC_BASE+0x80)

#define USART1        ( (USART_TypeDef *)USART1_BASE)
#define USART2        ( (USART_TypeDef *)USART2_BASE)
#define USART3        ( (USART_TypeDef *)USART3_BASE)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// IVT
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// EXTRI
#define EXTRI0_IRQ                    6
#define EXTRI1_IRQ                    7
#define EXTRI2_IRQ                    8
#define EXTRI3_IRQ                    9
#define EXTRI4_IRQ                    10
#define EXTRI5_IRQ                    23
#define EXTRI6_IRQ                    23
#define EXTRI7_IRQ                    23
#define EXTRI8_IRQ                    23
#define EXTRI9_IRQ                    23
#define EXTRI10_IRQ                   40
#define EXTRI11_IRQ                   40
#define EXTRI12_IRQ                   40
#define EXTRI13_IRQ                   40
#define EXTRI14_IRQ                   40
#define EXTRI15_IRQ                   40
// USART
#define USART1_IRQ					  37
#define USART2_IRQ					  38
#define USART3_IRQ					  39

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// Clock Enable Macros
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

#define RCC_AFIO_CLK_EN()      				(RCC->APB2ENR |=1<<0)
#define RCC_GPIOA_CLK_EN()   			    (RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()    			    (RCC->APB2ENR |=1<<3)
#define RCC_GPIOC_CLK_EN()    			    (RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()     				(RCC->APB2ENR |=1<<5)
#define RCC_GPIOE_CLK_EN()     				(RCC->APB2ENR |=1<<6)
// clock enable USART
#define RCC_USART1_CLK_EN()    				(RCC->APB2ENR |=1<<14)
#define RCC_USART2_CLK_EN()    				(RCC->APB1ENR |=1<<17)
#define RCC_USART3_CLK_EN()    				(RCC->APB1ENR |=1<<18)
// RCC Reset USART
#define RCC_USART1_Reset()     				(RCC->APB2RSTR |=1<<14)
#define RCC_USART2_Reset()     				(RCC->APB1RSTR |=1<<17)
#define RCC_USART3_Reset()     				(RCC->APB1RSTR |=1<<18)
// ========================================
// NVIC IRQ Enable and disable
// ===========================================
#define NVIC_IRQ6_EXTRI0_Enable          			  (NVIC_ISER->ISER[0] |= 1<<EXTRI0_IRQ       )
#define NVIC_IRQ7_EXTRI1_Enable     			      (NVIC_ISER->ISER[0] |= 1<<EXTRI1_IRQ       )
#define NVIC_IRQ8_EXTRI2_Enable       			      (NVIC_ISER->ISER[0] |= 1<<EXTRI2_IRQ       )
#define NVIC_IRQ9_EXTRI3_Enable         			  (NVIC_ISER->ISER[0] |= 1<<EXTRI3_IRQ       )
#define NVIC_IRQ10_EXTRI4_Enable        			  (NVIC_ISER->ISER[0] |= 1<<EXTRI4_IRQ       )
#define NVIC_IRQ23_EXTRI5_9_Enable                    (NVIC_ISER->ISER[0] |= 1<<EXTRI5_IRQ       )
#define NVIC_IRQ40_EXTRI10_15_Enable      		      (NVIC_ISER->ISER[1] |= 1<<(EXTRI10_IRQ-32) ) // 40 - 32 = 8
#define NVIC_IRQ37_USART1_Enable					  (NVIC_ISER->ISER[1] |= 1<<(USART1_IRQ -32) ) // 37 - 32 = 5
#define NVIC_IRQ38_USART2_Enable					  (NVIC_ISER->ISER[1] |= 1<<(USART2_IRQ -32) ) // 38 - 32 = 6
#define NVIC_IRQ39_USART3_Enable					  (NVIC_ISER->ISER[1] |= 1<<(USART3_IRQ -32) ) // 39 - 32 = 7



#define NVIC_IRQ6_EXTRI0_Disable          		      (NVIC_ICER->ICER[0] |= 1<<EXTRI0_IRQ   	 )
#define NVIC_IRQ7_EXTRI1_Disable     			      (NVIC_ICER->ICER[0] |= 1<<EXTRI1_IRQ 		 )
#define NVIC_IRQ8_EXTRI2_Disable       			      (NVIC_ICER->ICER[0] |= 1<<EXTRI2_IRQ 		 )
#define NVIC_IRQ9_EXTRI3_Disable         			  (NVIC_ICER->ICER[0] |= 1<<EXTRI3_IRQ 	     )
#define NVIC_IRQ10_EXTRI4_Disable        			  (NVIC_ICER->ICER[0] |= 1<<EXTRI4_IRQ       )
#define NVIC_IRQ23_EXTRI5_9_Disable                   (NVIC_ICER->ICER[0] |= 1<<EXTRI5_IRQ       )
#define NVIC_IRQ40_EXTRI10_15_Disable      		      (NVIC_ICER->ICER[1] |= 1<<(EXTRI10_IRQ-32) ) // 40 - 32 = 8
#define NVIC_IRQ37_USART1_Disable			          (NVIC_ICER->ICER[1] |= 1<<(USART1_IRQ -32) ) // 37 - 32 = 5
#define NVIC_IRQ38_USART2_Disable					  (NVIC_ICER->ICER[1] |= 1<<(USART2_IRQ -32) ) // 38 - 32 = 6
#define NVIC_IRQ39_USART3_Disable					  (NVIC_ICER->ICER[1] |= 1<<(USART3_IRQ -32) ) // 39 - 32 = 7

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@






#endif /* INC_STM32F103C6_H_ */
