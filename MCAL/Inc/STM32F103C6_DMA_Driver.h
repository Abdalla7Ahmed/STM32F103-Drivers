//|========================================================================|
//|Microcontroller ========/    STM32F103C6       \========================|
//|Driver ================/     EXTRI Drivers      \=======================|
//|File =================|      EXTRI_Drivers.h     |======================|
//|Author ================\     Abdallah Ahmed     /=======================|
//|Created on =============\       3/5/2023       /========================|
//|========================================================================|

#ifndef INC_STM32F103C6_DMA_DRIVER_H_
#define INC_STM32F103C6_DMA_DRIVER_H_

#include "STM32F103C6.h"



typedef struct
{
	uint8_t GIFx:1	   ;		//Channel x global interrupt flag
	uint8_t TCIFx:1    ;		//Channel x transfer complete flag
	uint8_t HTIFx:1	   ;		// Channel x half transfer flag
	uint8_t TEIFx:1    ;		// Channel x transfer error flag
	uint8_t Reserved:4 ;

}DMA1_Interrupt_Source;

typedef struct
{
	// enable Memory to memory mode
	// the parameters can be set based on @ref MEM2MEM_define
	uint16_t MEM2MEM;
	// set the priority to corresponding channel
	// the parameters can be set based on @ref Priority_level_define
	uint16_t Priority_level ;
	// set the memory size bits
	// the parameters can be set based on @ref Memory_size_define
	uint16_t Memory_size	;
	// set the Peripheral size bits
	// the parameters can be set based on @ref Peripheral_size_define
	uint16_t Peripheral_size	;
	// set the memory and Peripheral increment type
	// the parameters can be set based on @ref Increment_define
	uint16_t Increment ;
	// set this parameters whether it in  Circular mode or not
	// the parameters can be set based on @ref Circular_mode_define
	uint16_t Circular_mode;
	// set the direction of data transfer
	// the parameters can be set based on @ref Data_Dir_define
	uint16_t Data_transfer_Direction;
	// set the type of interrupt which will enable
	// the parameters can be set based on @ref Interrupt_enable_define
	uint16_t Interrupt_enable;
	// set the Peripheral which will be a source or destination
	// the parameters can be set based on @ref Peripheral_define
	uint8_t Peripheral;
	// Number of data to be transferred (0 up to 65535)
	uint16_t Number_Data_TX;
	//Base address of the peripheral data register from/to which the data will be read/written.
	uint32_t Peripheral_Address;
	//Base address of the memory area from/to which the data will be read/written.
	uint32_t Memory_Address;
	// Set the c function which will be called once the IRQ happened.
	void(* P_DMA1_CallBack)(DMA1_Interrupt_Source source);
}DMA1_PinConfig_t;




// @ref MEM2MEM_define
#define MEM2MEM_POS											14
#define MEM2MEM_Disable										(uint16_t)(~((0x1<<MEM2MEM_POS)))
#define MEM2MEM_Enable										(uint16_t)(0x1<<MEM2MEM_POS)


// @ref Priority_level_define
#define PL_POS												12
#define Priority_level_Low									(uint16_t)(~((0x11<<PL_POS)))
#define Priority_level_Medium								(uint16_t)(0x1<<PL_POS)
#define Priority_level_High									(uint16_t)(0x2<<PL_POS)
#define Priority_level_VeryHigh								(uint16_t)(0x3<<PL_POS)

// @ref Memory_size_define
#define MSIZE_POS											10
#define Memory_size_8bits									(uint16_t)(~(0x11<<MSIZE_POS))
#define Memory_size_16bits									(uint16_t)(0x1<<MSIZE_POS)
#define Memory_size_32bits									(uint16_t)(0x2<<MSIZE_POS)


// @ref Peripheral_size_define
#define PSIZE_POS											8
#define Peripheral_size_8bits								(uint16_t)(~(0x11<<PSIZE_POS))
#define Peripheral_size_16bits								(uint16_t)(0x1<<PSIZE_POS)
#define Peripheral_size_32bits								(uint16_t)(0x2<<PSIZE_POS)

//@ref Increment_define
#define MINC_POS											7
#define PINC_POS											6
#define Increment_NONE										(uint16_t)(~(0x1<<MINC_POS) & ~(0x1<<PINC_POS))
#define Increment_memory									(uint16_t)(0x1<<MINC_POS)
#define Increment_Peripheral								(uint16_t)(0x1<<PINC_POS)
#define Increment_memoryANDPeripheral				 		(uint16_t)((0x1<<MINC_POS) | (0x1<<PINC_POS))

//@ref Circular_mode_define
#define CIRC_POS											5
#define Circular_mode_Disable								(uint16_t)(~(0x1<<CIRC_POS))
#define Circular_mode_Enable								(uint16_t)(0x1<<CIRC_POS)

//@ref Data_Dir_define
#define DIR_POS											    4
#define Data_Dir_Read_from_peripheral						(uint16_t)(~(0x1<<DIR_POS))
#define Data_Dir_Read_from_memory							(uint16_t)(0x1<<DIR_POS)


//@ref Interrupt_enable_define
#define TEIE_POS											 3
#define HTIE_POS											 2
#define TCIE_POS											 1
#define Interrupt_enable_NONE								(uint16_t)(~(0x1<<TEIE_POS) & ~(0x1<<HTIE_POS) & ~(0x1<<TCIE_POS))
#define Interrupt_enable_TEIE								(uint16_t)(0x1<<TEIE_POS)
#define Interrupt_enable_HTIE								(uint16_t)(0x1<<HTIE_POS)
#define Interrupt_enable_TCIE								(uint16_t)(0x1<<TCIE_POS)



// Enable & Disable DMA1
#define EN_Pos												0
#define DMA1_disable										(uint16_t)(~(0x1<<EN_Pos))
#define DMA1_enable											(uint16_t)(0x1<<EN_Pos)


//@ref Peripheral_define
// channel 1
#define Peripheral_ADC1										0
#define Peripheral_TIM2_CH3									1
#define Peripheral_TIM4_CH1									2
// channel 2
#define Peripheral_USART3_TX								3
#define Peripheral_TIM1_CH1									4
#define Peripheral_TIM2_UP									5
#define Peripheral_TIM3_CH3									6
#define Peripheral_SPI1_RX									7
// channel 3
#define Peripheral_USART3_RX								8
#define Peripheral_TIM1_CH2									9
#define Peripheral_TIM3_CH4									10
#define Peripheral_TIM3_UP									11
#define Peripheral_SPI1_TX									12
// channel 4
#define Peripheral_USART1_TX								13
#define Peripheral_TIM1_CH4									14
#define Peripheral_TIM1_TRIG								15
#define Peripheral_TIM1_COM									16
#define Peripheral_TIM4_CH2									17
// channel 5
#define Peripheral_USART1_RX								18
#define Peripheral_TIM1_UP									19
#define Peripheral_SPI_I2S2_TX								20
#define Peripheral_TIM2_CH1									21
#define Peripheral_TIM4_CH3									22
#define Peripheral_I2C2_RX									23
// channel 6
#define Peripheral_USART2_RX								24
#define Peripheral_TIM1_CH3									25
#define Peripheral_TIM3_CH1									26
#define Peripheral_TIM3_TRIG								27
#define Peripheral_I2C1_TX									28
// channel 7
#define Peripheral_USART2_TX								29
#define Peripheral_TIM2_CH2									30
#define Peripheral_TIM2_CH4									31
#define Peripheral_TIM4_UP									32
#define Peripheral_I2C1_RX									33

// if the data transfer from memory to memory , no requist need
#define Memory_TO_Memory_CH1								34
#define Memory_TO_Memory_CH2								35
#define Memory_TO_Memory_CH3								36
#define Memory_TO_Memory_CH4								37
#define Memory_TO_Memory_CH5								38
#define Memory_TO_Memory_CH6								39
#define Memory_TO_Memory_CH7								40

// ISR register bit definition
#define ISR_GIF1_Pos										(uint8_t)(0)
#define ISR_TCIF1_Pos										(uint8_t)(1)
#define ISR_HTIF1_Pos										(uint8_t)(2)
#define ISR_TEIF1_Pos										(uint8_t)(3)

#define ISR_GIF2_Pos										(uint8_t)(4)
#define ISR_TCIF2_Pos										(uint8_t)(5)
#define ISR_HTIF2_Pos										(uint8_t)(6)
#define ISR_TEIF2_Pos										(uint8_t)(7)

#define ISR_GIF3_Pos										(uint8_t)(8)
#define ISR_TCIF3_Pos										(uint8_t)(9)
#define ISR_HTIF3_Pos										(uint8_t)(10)
#define ISR_TEIF3_Pos										(uint8_t)(11)

#define ISR_GIF4_Pos										(uint8_t)(12)
#define ISR_TCIF4_Pos										(uint8_t)(13)
#define ISR_HTIF4_Pos										(uint8_t)(14)
#define ISR_TEIF4_Pos										(uint8_t)(15)

#define ISR_GIF5_Pos										(uint8_t)(16)
#define ISR_TCIF5_Pos										(uint8_t)(17)
#define ISR_HTIF5_Pos										(uint8_t)(18)
#define ISR_TEIF5_Pos										(uint8_t)(19)

#define ISR_GIF6_Pos										(uint8_t)(20)
#define ISR_TCIF6_Pos										(uint8_t)(21)
#define ISR_HTIF6_Pos										(uint8_t)(22)
#define ISR_TEIF6_Pos										(uint8_t)(23)

#define ISR_GIF7_Pos										(uint8_t)(24)
#define ISR_TCIF7_Pos										(uint8_t)(25)
#define ISR_HTIF7_Pos										(uint8_t)(26)
#define ISR_TEIF7_Pos										(uint8_t)(27)


// IFCR register bit definition
#define IFCR_CGIF1_Pos										(uint8_t)(0)
#define IFCR_CTCIF1_Pos										(uint8_t)(1)
#define IFCR_CHTIF1_Pos										(uint8_t)(2)
#define IFCR_CTEIF1_Pos										(uint8_t)(3)

#define IFCR_CGIF2_Pos										(uint8_t)(4)
#define IFCR_CTCIF2_Pos										(uint8_t)(5)
#define IFCR_CHTIF2_Pos										(uint8_t)(6)
#define IFCR_CTEIF2_Pos										(uint8_t)(7)

#define IFCR_CGIF3_Pos										(uint8_t)(8)
#define IFCR_CTCIF3_Pos										(uint8_t)(9)
#define IFCR_CHTIF3_Pos										(uint8_t)(10)
#define IFCR_CTEIF3_Pos										(uint8_t)(11)

#define IFCR_CGIF4_Pos										(uint8_t)(12)
#define IFCR_CTCIF4_Pos										(uint8_t)(13)
#define IFCR_CHTIF4_Pos										(uint8_t)(14)
#define IFCR_CTEIF4_Pos										(uint8_t)(15)

#define IFCR_CGIF5_Pos										(uint8_t)(16)
#define IFCR_CTCIF5_Pos										(uint8_t)(17)
#define IFCR_CHTIF5_Pos										(uint8_t)(18)
#define IFCR_CTEIF5_Pos										(uint8_t)(19)

#define IFCR_CGIF6_Pos										(uint8_t)(20)
#define IFCR_CTCIF6_Pos										(uint8_t)(21)
#define IFCR_CHTIF6_Pos										(uint8_t)(22)
#define IFCR_CTEIF6_Pos										(uint8_t)(23)

#define IFCR_CGIF7_Pos										(uint8_t)(24)
#define IFCR_CTCIF7_Pos										(uint8_t)(25)
#define IFCR_CHTIF7_Pos										(uint8_t)(26)
#define IFCR_CTEIF7_Pos										(uint8_t)(27)

void MCAL_DMA1_Init(DMA1_PinConfig_t *DMA_Config);
void MCAL_DMA1_Deinit(void);
void MCAL_DMA1_Start(uint16_t Number_Data_TX , uint32_t Peripheral_Address,uint32_t Memory_Address);





#endif /* INC_STM32F103C6_DMA_DRIVER_H_ */
