//|========================================================================|
//|Microcontroller ========/    STM32F103C6       \========================|
//|Driver ================/     EXTRI Drivers      \=======================|
//|File =================|      EXTRI_Drivers.h     |======================|
//|Author ================\     Abdallah Ahmed     /=======================|
//|Created on =============\       3/5/2023       /========================|
//|========================================================================|



#include "STM32F103C6_DMA_Driver.h"


// ===================================Generic Variables =========================
DMA1_PinConfig_t G_DMA1_Config;
static void(* GP_DMA1_CallBack[7])(DMA1_Interrupt_Source source) = {NULL} ;


// ===================================Generic Macros =========================
#define CCRx_Offset(channel_Number)				 (0x08 + 0d20 × (channel_Number – 1))  // not used
#define CNDTRx_Offset(channel_Number)			 (0x0C + 0d20 × (channel_Number – 1))  // not used
#define CMARx_Offset(channel_Number)			 (0x14 + 0d20 × (channel_Number – 1))  // not used

#define Channel_1								 0
#define Channel_2								 1
#define Channel_3								 2
#define Channel_4								 3
#define Channel_5								 4
#define Channel_6								 5
#define Channel_7								 6



// ===================================Generic functions =========================
uint8_t Get_Channel(uint8_t Peripheral)
{
	uint8_t return_Value = 0;
	switch (Peripheral)
	{
	case Peripheral_ADC1:
	case Peripheral_TIM2_CH3 :
	case Peripheral_TIM4_CH1 :
	case Memory_TO_Memory_CH1:
		return_Value = Channel_1;
		break;
	case Peripheral_USART3_TX:
	case Peripheral_TIM1_CH1:
	case Peripheral_TIM2_UP:
	case Peripheral_TIM3_CH3:
	case Peripheral_SPI1_RX	:
	case Memory_TO_Memory_CH2:
		return_Value = Channel_2;
		break ;
	case Peripheral_USART3_RX:
	case Peripheral_TIM1_CH2:
	case Peripheral_TIM3_CH4:
	case Peripheral_TIM3_UP:
	case Peripheral_SPI1_TX:
	case Memory_TO_Memory_CH3:
		return_Value = Channel_3;
		break ;
	case Peripheral_USART1_TX:
	case Peripheral_TIM1_CH4:
	case Peripheral_TIM1_TRIG:
	case Peripheral_TIM1_COM:
	case Peripheral_TIM4_CH2:
	case Memory_TO_Memory_CH4:
		return_Value = Channel_4;
		break ;
	case Peripheral_USART1_RX:
	case Peripheral_TIM1_UP:
	case Peripheral_SPI_I2S2_TX:
	case Peripheral_TIM2_CH1:
	case Peripheral_TIM4_CH3:
	case Peripheral_I2C2_RX:
	case Memory_TO_Memory_CH5:
		return_Value = Channel_5;
		break ;
	case Peripheral_USART2_RX:
	case Peripheral_TIM1_CH3:
	case Peripheral_TIM3_CH1:
	case Peripheral_TIM3_TRIG:
	case Peripheral_I2C1_TX:
	case Memory_TO_Memory_CH6:
		return_Value = Channel_6;
		break;
	case Peripheral_USART2_TX:
	case Peripheral_TIM2_CH2:
	case Peripheral_TIM2_CH4:
	case Peripheral_TIM4_UP:
	case Peripheral_I2C1_RX:
	case Memory_TO_Memory_CH7:
		return_Value = Channel_7;
		break;
	}

	return return_Value;
}


/**===================================================================
 * @Fn				- MCAL_DMA1_Init
 * @brief 			- Initializes the DMA1
 * @param [in] 		- DMA1_PinConfig_t : the configuration of DMA
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_DMA1_Init(DMA1_PinConfig_t *DMA_Config)
{

	G_DMA1_Config = *DMA_Config;

	volatile uint32_t *CCRx   = NULL;

	if(Channel_1 == Get_Channel(DMA_Config->Peripheral))
	{
		CCRx   = &DMA1->CCR1;
	}
	else if(Channel_2 == Get_Channel(DMA_Config->Peripheral))
	{
		CCRx   = &DMA1->CCR2;
	}
	else if(Channel_3 == Get_Channel(DMA_Config->Peripheral))
	{
		CCRx   = &DMA1->CCR3;
	}
	else if(Channel_4 == Get_Channel(DMA_Config->Peripheral))
	{
		CCRx   = &DMA1->CCR4;
	}
	else if(Channel_5 == Get_Channel(DMA_Config->Peripheral))
	{
		CCRx   = &DMA1->CCR5;
	}
	else if(Channel_6 == Get_Channel(DMA_Config->Peripheral) )
	{
		CCRx   = &DMA1->CCR6;
	}
	else if(Channel_7 == Get_Channel(DMA_Config->Peripheral))
	{
		CCRx   = &DMA1->CCR7;
	}

	// Disable DMA1 if it enable
	*CCRx &=DMA1_disable;

	RCC_DMA1_CLK_EN();
	// Memory to memory mode
	if(MEM2MEM_Disable !=DMA_Config->MEM2MEM)
	{
		if(Circular_mode_Enable !=DMA_Config->Circular_mode)
		{
			*CCRx |=DMA_Config->MEM2MEM;
		}
		else
		{
			//The transfer stops once the DMA_CNDTRx register reaches zero.
			//Memory to Memory mode may not be used at the same time as Circular mode.
		}

	}
	else
	{
		*CCRx &=DMA_Config->MEM2MEM;
	}
	// Priority level
	if(Priority_level_Low !=DMA_Config->Priority_level)
	{
		*CCRx |=DMA_Config->Priority_level;
	}
	else
	{
		*CCRx &=DMA_Config->Priority_level;
	}

	// Memory size
	if(Memory_size_8bits !=DMA_Config->Memory_size)
	{
		*CCRx |=DMA_Config->Memory_size;
	}
	else
	{
		*CCRx &=DMA_Config->Memory_size;
	}

	//Peripheral size
	if(Peripheral_size_8bits !=DMA_Config->Peripheral_size)
	{
		*CCRx |=DMA_Config->Peripheral_size;
	}
	else
	{
		*CCRx &=DMA_Config->Peripheral_size;
	}

	//Increment configuration
	if(Increment_NONE !=DMA_Config->Increment)
	{
		*CCRx |=DMA_Config->Increment;
	}
	else
	{
		*CCRx &=DMA_Config->Increment;
	}

	// Circular mode
	if(Circular_mode_Disable !=DMA_Config->Circular_mode)
	{
		*CCRx |=DMA_Config->Circular_mode;
	}
	else
	{
		*CCRx &=DMA_Config->Circular_mode;
	}

	// Data transfer direction
	if(Data_Dir_Read_from_peripheral !=DMA_Config->Data_transfer_Direction)
	{
		*CCRx |=DMA_Config->Data_transfer_Direction;
	}
	else
	{
		*CCRx &=DMA_Config->Data_transfer_Direction;
	}

	//Interrupt configuration
	if(Interrupt_enable_NONE !=DMA_Config->Interrupt_enable)
	{
		*CCRx |=DMA_Config->Interrupt_enable;
	}
	else
	{
		*CCRx &=DMA_Config->Interrupt_enable;
	}

	if(Interrupt_enable_NONE !=DMA_Config->Interrupt_enable)
	{
		if(Channel_1 == Get_Channel(DMA_Config->Peripheral))
		{
			GP_DMA1_CallBack[Channel_1] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ11_DMA1_CH1_interrupt_Enable	;
		}

		else if(Channel_2 == Get_Channel(DMA_Config->Peripheral))
		{
			GP_DMA1_CallBack[Channel_2] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ12_DMA1_CH2_interrupt_Enable	;
		}
		else if(Channel_3 == Get_Channel(DMA_Config->Peripheral))
		{
			GP_DMA1_CallBack[Channel_3] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ13_DMA1_CH3_interrupt_Enable	;
		}
		else if(Channel_4 ==  Get_Channel(DMA_Config->Peripheral))
		{
			GP_DMA1_CallBack[Channel_4] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ14_DMA1_CH4_interrupt_Enable	;
		}
		else if(Channel_5 == Get_Channel(DMA_Config->Peripheral))
		{
			GP_DMA1_CallBack[Channel_5] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ15_DMA1_CH5_interrupt_Enable	;
		}
		else if(Channel_6 == Get_Channel(DMA_Config->Peripheral))

		{
			GP_DMA1_CallBack[Channel_6] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ16_DMA1_CH6_interrupt_Enable	;
		}
		else if(Channel_7 == Get_Channel(DMA_Config->Peripheral))
		{
			GP_DMA1_CallBack[Channel_7] = DMA_Config->P_DMA1_CallBack;
			NVIC_IRQ17_DMA1_CH7_interrupt_Enable	;
		}
	}

	// set the number of data transfer , peripheral address , memory address and then start
	MCAL_DMA1_Start(DMA_Config->Number_Data_TX,DMA_Config->Peripheral_Address,DMA_Config->Memory_Address);


}


/**===================================================================
 * @Fn				- MCAL_DMA1_Deinit
 * @brief 			- De-Initializes the DMA1
 * @param [in] 		- none
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_DMA1_Deinit(void)
{

	RCC_DMA1_Reset();
	if(Channel_1 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF1_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF1_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF1_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF1_Pos);

			NVIC_IRQ11_DMA1_CH1_interrupt_Disable	;
		}
		DMA1->CNDTR1 = 0x00;
		DMA1->CPAR1  = 0x00;
		DMA1->CMAR1  = 0x00;
		DMA1->CCR1   = 0x00;
	}

	else if(Channel_2 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF3_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF3_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF3_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF3_Pos);

			NVIC_IRQ12_DMA1_CH2_interrupt_Disable	;
		}
		DMA1->CNDTR2 = 0x00;
		DMA1->CPAR2  = 0x00;
		DMA1->CMAR2  = 0x00;
		DMA1->CCR2   = 0x00;
	}
	else if(Channel_3 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF3_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF3_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF3_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF3_Pos);

			NVIC_IRQ13_DMA1_CH3_interrupt_Disable	;
		}
		DMA1->CNDTR3 = 0x00;
		DMA1->CPAR3  = 0x00;
		DMA1->CMAR3  = 0x00;
		DMA1->CCR3   = 0x00;

	}
	else if(Channel_4 ==  Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF4_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF4_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF4_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF4_Pos);

			NVIC_IRQ14_DMA1_CH4_interrupt_Disable	;
		}
		DMA1->CNDTR4 = 0x00;
		DMA1->CPAR4  = 0x00;
		DMA1->CMAR4  = 0x00;
		DMA1->CCR4   = 0x00;
	}
	else if(Channel_5 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF5_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF5_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF5_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF5_Pos);

			NVIC_IRQ15_DMA1_CH5_interrupt_Disable	;
		}
		DMA1->CNDTR5 = 0x00;
		DMA1->CPAR5  = 0x00;
		DMA1->CMAR5  = 0x00;
		DMA1->CCR5   = 0x00;
	}
	else if(Channel_6 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF6_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF6_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF6_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF6_Pos);

			NVIC_IRQ16_DMA1_CH6_interrupt_Disable	;
		}
		DMA1->CNDTR6 = 0x00;
		DMA1->CPAR6  = 0x00;
		DMA1->CMAR6  = 0x00;
		DMA1->CCR6   = 0x00;
	}
	else if(Channel_7 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		if(Interrupt_enable_NONE !=G_DMA1_Config.Interrupt_enable)
		{
			//  Clears the corresponding flag in the DMA_ISR register
			DMA1->ISR &=~(0x1<<IFCR_CGIF7_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTCIF7_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CHTIF7_Pos);
			DMA1->ISR &=~(0x1<<IFCR_CTEIF7_Pos);

			NVIC_IRQ17_DMA1_CH7_interrupt_Disable	;
		}
		DMA1->CNDTR7 = 0x00;
		DMA1->CPAR7  = 0x00;
		DMA1->CMAR7  = 0x00;
		DMA1->CCR7   = 0x00;
	}

}




/**===================================================================
 * @Fn				- MCAL_DMA1_Start
 * @brief 			- start the transfer of data
 * @param [in] 		- Number_Data_TX :- Number of data to be transferred (0 up to 65535)
 * @param [in] 		- Peripheral_Address :- Base address of the peripheral
 * @param [in] 		- Memory_Address :- Base address of the memory
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_DMA1_Start(uint16_t Number_Data_TX , uint32_t Peripheral_Address,uint32_t Memory_Address)
{

	if(Channel_1 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR1 &= DMA1_disable;
		DMA1->CNDTR1 = Number_Data_TX;
		DMA1->CPAR1  = Peripheral_Address;
		DMA1->CMAR1  = Memory_Address;
		DMA1->CCR1 |= DMA1_enable;
	}

	else if(Channel_2 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR2 &= DMA1_disable;
		DMA1->CNDTR2 = Number_Data_TX;
		DMA1->CPAR2  = Peripheral_Address;
		DMA1->CMAR2  = Memory_Address;
		DMA1->CCR2 |= DMA1_enable;

	}
	else if(Channel_3 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR3 &= DMA1_disable;
		DMA1->CNDTR3 = Number_Data_TX;
		DMA1->CPAR3  = Peripheral_Address;
		DMA1->CMAR3  = Memory_Address;
		DMA1->CCR3 |= DMA1_enable;
	}
	else if(Channel_4 ==  Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR4 &= DMA1_disable;
		DMA1->CNDTR4 = Number_Data_TX;
		DMA1->CPAR4  = Peripheral_Address;
		DMA1->CMAR4  = Memory_Address;
		DMA1->CCR4 |= DMA1_enable;

	}
	else if(Channel_5 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR5 &= DMA1_disable;
		DMA1->CNDTR5 = Number_Data_TX;
		DMA1->CPAR5  = Peripheral_Address;
		DMA1->CMAR5  = Memory_Address;
		DMA1->CCR5 |= DMA1_enable;

	}
	else if(Channel_6 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR6 &= DMA1_disable;
		DMA1->CNDTR6 = Number_Data_TX;
		DMA1->CPAR6  = Peripheral_Address;
		DMA1->CMAR6  = Memory_Address;
		DMA1->CCR6 |= DMA1_enable;
	}
	else if(Channel_7 == Get_Channel(G_DMA1_Config.Peripheral))
	{
		DMA1->CCR7 &= DMA1_disable;
		DMA1->CNDTR7 = Number_Data_TX;
		DMA1->CPAR7  = Peripheral_Address;
		DMA1->CMAR7  = Memory_Address;
		DMA1->CCR7 |= DMA1_enable;

	}

}






// =========================== ISR =====================================
void DMA1_Channel1_IRQHandler(void)
{
	DMA1_Interrupt_Source source;

	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF1_Pos)  ) >> ISR_GIF1_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF1_Pos) ) >> ISR_TCIF1_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF1_Pos) ) >> ISR_HTIF1_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF1_Pos) ) >> ISR_TEIF1_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_1])
	{
		GP_DMA1_CallBack[Channel_1](source);
	}
	//NVIC_IRQ11_DMA1_CH1_interrupt_Disable;
	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->IFCR |=(0x1<<IFCR_CGIF1_Pos);
	DMA1->IFCR |=(0x1<<IFCR_CTCIF1_Pos);
	DMA1->IFCR |=(0x1<<IFCR_CHTIF1_Pos);
	DMA1->IFCR |=(0x1<<IFCR_CTEIF1_Pos);
}
void DMA_Channel2_IRQHandler(void)
{
	DMA1_Interrupt_Source source;
	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF2_Pos)  ) >> ISR_GIF2_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF2_Pos) ) >> ISR_TCIF2_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF2_Pos) ) >> ISR_HTIF2_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF2_Pos) ) >> ISR_TEIF2_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_2])
	{
		GP_DMA1_CallBack[Channel_2](source);
	}

	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->ISR &=~(0x1<<IFCR_CGIF2_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTCIF2_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CHTIF2_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTEIF2_Pos);
}
void DMA1_Channel3_IRQHandler(void)
{
	DMA1_Interrupt_Source source;

	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF3_Pos)  ) >> ISR_GIF3_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF3_Pos) ) >> ISR_TCIF3_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF3_Pos) ) >> ISR_HTIF3_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF3_Pos) ) >> ISR_TEIF3_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_3])
	{
		GP_DMA1_CallBack[Channel_3](source);
	}

	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->ISR &=~(0x1<<IFCR_CGIF3_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTCIF3_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CHTIF3_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTEIF3_Pos);
}
void DMA1_Channel4_IRQHandler(void)
{
	DMA1_Interrupt_Source source;
	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF4_Pos)  ) >> ISR_GIF4_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF4_Pos) ) >> ISR_TCIF4_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF4_Pos) ) >> ISR_HTIF4_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF4_Pos) ) >> ISR_TEIF4_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_4])
	{
		GP_DMA1_CallBack[Channel_4](source);
	}

	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->ISR &=~(0x1<<IFCR_CGIF4_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTCIF4_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CHTIF4_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTEIF4_Pos);
}
void DMA1_Channel5_IRQHandler(void)
{
	DMA1_Interrupt_Source source;

	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF5_Pos)  ) >> ISR_GIF5_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF5_Pos) ) >> ISR_TCIF5_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF5_Pos) ) >> ISR_HTIF5_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF5_Pos) ) >> ISR_TEIF5_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_5])
	{
		GP_DMA1_CallBack[Channel_5](source);
	}

	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->ISR &=~(0x1<<IFCR_CGIF5_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTCIF5_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CHTIF5_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTEIF5_Pos);
}
void DMA1_Channel6_IRQHandler(void)
{
	DMA1_Interrupt_Source source;

	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF6_Pos)  ) >> ISR_GIF6_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF6_Pos) ) >> ISR_TCIF6_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF6_Pos) ) >> ISR_HTIF6_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF6_Pos) ) >> ISR_TEIF6_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_6])
	{
		GP_DMA1_CallBack[Channel_6](source);
	}

	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->ISR &=~(0x1<<IFCR_CGIF6_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTCIF6_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CHTIF6_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTEIF6_Pos);
}
void DMA1_Channel7_IRQHandler(void)
{
	DMA1_Interrupt_Source source;

	source.GIFx  = (  (  (DMA1->ISR) & (1<<ISR_GIF7_Pos)  ) >> ISR_GIF7_Pos);
	source.TCIFx = (  (  (DMA1->ISR) & (1<<ISR_TCIF7_Pos) ) >> ISR_TCIF7_Pos);
	source.HTIFx = (  (  (DMA1->ISR) & (1<<ISR_HTIF7_Pos) ) >> ISR_HTIF7_Pos);
	source.TEIFx = (  (  (DMA1->ISR) & (1<<ISR_TEIF7_Pos) ) >> ISR_TEIF7_Pos);

	if(NULL != GP_DMA1_CallBack[Channel_7])
	{
		GP_DMA1_CallBack[Channel_7](source);
	}

	//  Clears the corresponding flag in the DMA_ISR register
	DMA1->ISR &=~(0x1<<IFCR_CGIF7_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTCIF7_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CHTIF7_Pos);
	DMA1->ISR &=~(0x1<<IFCR_CTEIF7_Pos);
}

