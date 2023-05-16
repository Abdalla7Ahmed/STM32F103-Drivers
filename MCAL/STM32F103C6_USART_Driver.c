//|========================================================================|
//|Microcontroller ========/    STM32F103C6       \========================|
//|Driver ================/    	UART Drivers       \=======================|
//|File =================|      UART_Drivers.c      |======================|
//|Author ================\     Abdallah Ahmed     /=======================|
//|Created on =============\       1/10/2022      /========================|
//|========================================================================|



// Includes
#include "STM32F103C6_USART_Driver.h"
//========================================

// ===================================Generic Variables =========================
UART_Config Global_UART_Config[3]  = {0};

DMA1_PinConfig_t DMA_UART_Config;

UART_Config UART_DMA_Config;
// ===========================================================================

// ===================================Generic Macros =========================

#define UART1_INDEX						0
#define UART2_INDEX						1
#define UART3_INDEX						2

// ===========================================================================




// ===================================Generic functions =========================
void MCAL_UART_GPIO_set_pins(USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t PinCfg ;

	if ( USARTx == USART1 )
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_INPUT;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if (Global_UART_Config[UART1_INDEX].HWFlowCtrl==USART_FlowCtrl_CTS_Enable  || Global_UART_Config[UART1_INDEX].HWFlowCtrl ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}


		if (Global_UART_Config[UART1_INDEX].HWFlowCtrl  == USART_FlowCtrl_RTS_Enable|| Global_UART_Config[UART1_INDEX].HWFlowCtrl ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);

		}
	}
	else if ( USARTx == USART2 )
	{
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS


		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_INPUT;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if (Global_UART_Config[UART2_INDEX].HWFlowCtrl  ==USART_FlowCtrl_CTS_Enable  || Global_UART_Config[UART2_INDEX].HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}

		if (Global_UART_Config[UART2_INDEX].HWFlowCtrl  ==USART_FlowCtrl_RTS_Enable || Global_UART_Config[UART2_INDEX].HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}
	}
	else if ( USARTx == USART3 )
	{
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_INPUT;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		if (Global_UART_Config[UART3_INDEX].HWFlowCtrl  ==USART_FlowCtrl_CTS_Enable  || Global_UART_Config[UART3_INDEX].HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
		if (Global_UART_Config[UART3_INDEX].HWFlowCtrl  ==USART_FlowCtrl_RTS_Enable || Global_UART_Config[UART3_INDEX].HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable )
		{
			//PA14 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
	}

}



/**===================================================================
 * @Fn				- MCAL_UART_Init
 * @brief 			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration
 * @retval 			- none
 * Note				- Support for Now Asynchronous mode & Clock 8 MHZ S
======================================================================**/
void MCAL_UART_Init(USART_TypeDef *USARTx,UART_Config *UART_Config)
{
	if(USARTx == USART1)
	{
	 	RCC_USART1_CLK_EN();
	 	Global_UART_Config[UART1_INDEX] = *UART_Config;
	}
	else if(USARTx == USART2)
	{
	 	RCC_USART2_CLK_EN();
	 	Global_UART_Config[UART2_INDEX] = *UART_Config;
	}
	else if(USARTx == USART3)
	{
	 	RCC_USART3_CLK_EN();
	 	Global_UART_Config[UART3_INDEX] = *UART_Config;
	}

	uint32_t pclk,BRR;
	// Enable the USART by writing the UE bit in USART_CR1 register to 1
	USARTx->CR1 |=1<<13;
	// select the mode
	USARTx->CR1 |=UART_Config->USART_Mode;
	// Program the M bit in USART_CR1 to define the word length.
	USARTx->CR1 |=UART_Config->PayLoad_Length;
	//Configuration of parity control bit fields
	// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->parity ;
	//Program the number of stop bits in USART_CR2.
	USARTx->CR2 |=UART_Config->stopBits;
	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->HWFlowCtrl ;
	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2, 3
	//PCLK2 for USART1
	if(USARTx==USART1)  	{pclk=MCAL_RCC_GET_PCLK2Freq();}
	else 				    {pclk=MCAL_RCC_GET_PCLK1Freq();}
	BRR = UART_BRR_Register(pclk, UART_Config->Baud_rate);
	USARTx->BRR = BRR ;

	if (UART_Config->IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |=UART_Config->IRQ_Enable;
		if		(USARTx==USART1)  		 {NVIC_IRQ37_USART1_Enable;}
		else if (USARTx==USART2)		 {NVIC_IRQ38_USART2_Enable;}
		else if (USARTx==USART3)		 {NVIC_IRQ39_USART3_Enable;}
	}

	// set pins of GPIO
	MCAL_UART_GPIO_set_pins(USARTx);
}
/**===================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_UART_DeInit(USART_TypeDef *USARTx)
{
	if		(USARTx==USART1)  		{RCC_USART1_Reset();	NVIC_IRQ37_USART1_Disable;}
	else if (USARTx==USART2)		{RCC_USART2_Reset();	NVIC_IRQ38_USART2_Disable;}
	else if (USARTx==USART3)		{RCC_USART3_Reset();	NVIC_IRQ39_USART3_Disable;}
}



/**===================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_UART_SendData(USART_TypeDef *USARTx,uint16_t *pTxBuffer,enum polling_mecism pollingEn)
{
	if (pollingEn==Enable) {while(!(USARTx->SR & 1<<7));}
	uint8_t Index ;
	Index = (USARTx == USART1)?UART1_INDEX :(USARTx == USART2)?UART2_INDEX:UART3_INDEX;

	if(Global_UART_Config[Index].PayLoad_Length == USART_Payload_Length_9B)
	{
		/*When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
		because it is replaced by the parity.
		When receiving with the parity enabled, the value read in the MSB bit is the received parity
		bit*/
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}
}
void MCAL_UART_WAIT_TC (USART_TypeDef *USARTx )
{
	// wait till TC flag is set in the SR
	while( ! (USARTx->SR & 1<<6 ));
}
/**===================================================================
 * @Fn				- MCAL_UART_ReceiveData
 * @brief 			- Receive the buffer
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- Global_UART_Config[UART_number]: All UART Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx,uint16_t *pRxBuffer,enum polling_mecism pollingEn)
{
	uint8_t Index ;
	Index = (USARTx == USART1)?UART1_INDEX :(USARTx == USART2)?UART2_INDEX:UART3_INDEX;
	if (pollingEn==Enable) {while(!(USARTx->SR & 1<<5));}
	if(Global_UART_Config[Index].PayLoad_Length == USART_Payload_Length_9B)
	{
		if(Global_UART_Config[Index].parity == USART_Paratiy_NONE)
		{
			//no parity So all 9bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->DR ;
		}
		else
		{
			//Parity is used, so, 8bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
		}
	}
	else
	{
		if(Global_UART_Config[Index].parity == USART_Paratiy_NONE)
		{
			//no parity So all 8bit are considered data
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
		}
		else
		{
			//Parity is used, so,7 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0x7F );
		}

	}
}




/**================================================================
 * @Fn		  - MCAL_USART_send_string
 * @brief 	  - Send string
 * @param[in] - pointer to the string
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_USART_send_string(USART_TypeDef *USARTx,uint8_t *string)
{
	uint8_t i=0;
	while(string[i] !=0)  MCAL_UART_SendData(USARTx,&string[i++],Enable);
}

/**================================================================
 * @Fn		  - MCAL_USART_send_number
 * @brief 	  - Send string
 * @param[in] - pointer to the number
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_USART_send_number(USART_TypeDef *USARTx,uint32_t *number)
{
	uint8_t counter=0;
	uint8_t number_array[10];
	while((*number) != 0)
	{
		number_array[counter] = ((*number)%10) +'0';
		(*number) /=10;
		counter ++;
	}
	for(int i=counter-1;i>=0;i--)
	{
		MCAL_UART_SendData(USARTx,&number_array[i],Enable);
	}

}
/**================================================================
 * @Fn		  - MCAL_USART_receive_string
 * @brief 	  - Receive string
 * @param[in] - pointer to the string
 * @param[in] - defaultStop
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_USART_receive_string(USART_TypeDef *USARTx,uint8_t *buffer,uint8_t defaultStop)
{
	uint8_t i=0;
	MCAL_UART_ReceiveData(USARTx,&buffer[i],Enable);
	while(buffer[i] != defaultStop)
	{
		i++;
		MCAL_UART_ReceiveData(USARTx,&buffer[i],Enable);
	}
	buffer[i] ='\0';
}
/**================================================================
 * @Fn		  - MCAL_USART_receive_number
 * @brief 	  - Receive number
 * @param[in] - pointer to the number
 * @param[in] - defaultStop
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_USART_receive_number(USART_TypeDef *USARTx,uint8_t *number,uint8_t defaultStop)
{
	uint32_t counter=0;
	MCAL_UART_ReceiveData(USARTx,&number[counter],Enable);
	while(number[counter]!=defaultStop)
	{
		counter ++;
		MCAL_UART_ReceiveData(USARTx,&number[counter],Enable);
	}
	number[counter] = '\0';
}


/**===================================================================
 * @Fn				- MCAL_USART_DMA_Init
 * @brief 			- initialize UART by using DMA 
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- none
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_USART_DMA_Init(USART_TypeDef *USARTx)
{


	UART_DMA_Config.Baud_rate = USART_BaudRate_115200;
	UART_DMA_Config.HWFlowCtrl = USART_FlowCtrl_NONE ;
	UART_DMA_Config.IRQ_Enable = USART_IRQ_Enable_NONE;
	UART_DMA_Config.P_IRQ_CallBack = NULL ;
	UART_DMA_Config.parity =USART_Paratiy_NONE ;
	UART_DMA_Config.PayLoad_Length = USART_Payload_Length_8B;
	UART_DMA_Config.stopBits = USART_StopBits_ONE;
	UART_DMA_Config.USART_Mode =USART_Mode_TX_RX ;
	MCAL_UART_Init(USARTx,&UART_DMA_Config);

}

/**===================================================================
 * @Fn				- MCAL_UART_DMA_SendData
 * @brief 			- send the data by using DMA  
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer the address of source ,the DMA will send the data from this buffer
 * @retval 			- Number_Data_Transfer
 * Note				- P_IRQ_DMA_CallBack pointer to function that will be called after interrupt is happened 
======================================================================**/
void MCAL_UART_DMA_SendData(USART_TypeDef *USARTx,uint8_t *pTxBuffer,uint16_t Number_Data_Transfer,void(* P_IRQ_DMA_CallBack)(void))
{



	//	Bit 7 DMAT: DMA enable transmitter
	//	This bit is set/reset by software
	//	1: DMA mode is enabled for transmission
	//	0: DMA mode is disabled for transmission
	//	This bit is not available for UART5
	USARTx->CR3 |=(1<<7);


	// disable circular mode . when the transmission is complete , DMA is stopped
	DMA_UART_Config.Circular_mode = Circular_mode_Disable;
	// read from memory and then by using DMA transmit it in DR register
	DMA_UART_Config.Data_transfer_Direction = Data_Dir_Read_from_memory;
	// increase the size of buffer only to transmit new data every transfer
	DMA_UART_Config.Increment = Increment_memory;
	// enable transmit error and transmit complete interrupt
	DMA_UART_Config.Interrupt_enable = Interrupt_enable_TCIE | Interrupt_enable_TEIE ;
	// Disable memory to memory mode
	DMA_UART_Config.MEM2MEM = MEM2MEM_Disable ;
	// the number of data transfer is the number of times that DMA will transfer
	DMA_UART_Config.Number_Data_TX = Number_Data_Transfer;
	// set the priority high
	DMA_UART_Config.Priority_level = Priority_level_High ;
	// the address of buffer is the source according to DMA
	DMA_UART_Config.Memory_Address = (uint32_t)pTxBuffer;
	// support only 8 bit transfer
	DMA_UART_Config.Memory_size = Memory_size_8bits ;
	// support only 8 bit transfer
	DMA_UART_Config.Peripheral_size = Peripheral_size_8bits ;
	// Set the c function which will be called once the IRQ happen
	DMA_UART_Config.P_DMA1_CallBack = (void *)P_IRQ_DMA_CallBack;

	if(USARTx==USART1)
	{
		// the address of DR register is the destination of DMA
		DMA_UART_Config.Peripheral_Address = (uint32_t) (USART1_BASE + 0x4 );
		// channel 4 USART1_TX
		DMA_UART_Config.Peripheral = Peripheral_USART1_TX;
	}
	else if (USARTx==USART2)
	{
		// the address of DR register is the destination of DMA
		DMA_UART_Config.Peripheral_Address = (uint32_t)(USART2_BASE + 0x4 );
		// channel 7 USART2_TX
		DMA_UART_Config.Peripheral = Peripheral_USART2_TX;

	}
	else if (USARTx==USART3)
	{
		// the address of DR register is the destination of DMA
		DMA_UART_Config.Peripheral_Address = (uint32_t) (USART3_BASE + 0x4 );
		// channel 2 USART3_TX
		DMA_UART_Config.Peripheral = Peripheral_USART3_TX;
	}

	MCAL_DMA1_Init(&DMA_UART_Config);
}

/**===================================================================
 * @Fn				- MCAL_UART_DMA_ReceiveData
 * @brief 			- receive the data by using DMA  
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer the address of destination ,the data will saved in this buffer
 * @retval 			- Number_Data_Transfer
 * Note				- P_IRQ_DMA_CallBack pointer to function that will be called after interrupt is happened 
======================================================================**/
void MCAL_UART_DMA_ReceiveData(USART_TypeDef *USARTx,uint8_t *pRxBuffer,uint16_t Number_Data_Transfer,void(* P_IRQ_DMA_CallBack)(void))
{
//	Bit 6 DMAR: DMA enable receiver
//	This bit is set/reset by software
//	1: DMA mode is enabled for reception
//	0: DMA mode is disabled for reception
//	This bit is not available for UART5
	USARTx->CR3 |=(1<<6);


	// disable circular mode . when the transmission is complete , DMA is stopped
	DMA_UART_Config.Circular_mode = Circular_mode_Disable;
	// read from DR register
	DMA_UART_Config.Data_transfer_Direction = Data_Dir_Read_from_memory;
	// increase the size of buffer only to receive new data every transfer
	DMA_UART_Config.Increment = Increment_Peripheral;
	// enable transmit error and transmit complete interrupt
	DMA_UART_Config.Interrupt_enable = Interrupt_enable_TCIE | Interrupt_enable_TEIE ;
	// Disable memory to memory mode
	DMA_UART_Config.MEM2MEM = MEM2MEM_Disable ;
	// the number of data transfer is the number of times that DMA will transfer
	DMA_UART_Config.Number_Data_TX = Number_Data_Transfer;
	// set the priority high
	DMA_UART_Config.Priority_level = Priority_level_High ;
	// the address of buffer is the destination according to DMA
	DMA_UART_Config.Peripheral_Address = (uint32_t)pRxBuffer;
	// support only 8 bit transfer
	DMA_UART_Config.Memory_size = Memory_size_8bits ;
	// support only 8 bit transfer
	DMA_UART_Config.Peripheral_size = Peripheral_size_8bits ;
	// Set the c function which will be called once the IRQ happen
	DMA_UART_Config.P_DMA1_CallBack = (void *)P_IRQ_DMA_CallBack;

	if(USARTx==USART1)
	{
		// the address of DR register is the source of DMA
		DMA_UART_Config.Memory_Address = (uint32_t) (USART1_BASE + 0x4 );
		// channel 5 USART1_RX
		DMA_UART_Config.Peripheral = Peripheral_USART1_RX;
	}
	else if (USARTx==USART2)
	{
		// the address of DR register is the source of DMA
		DMA_UART_Config.Memory_Address = (uint32_t)(USART2_BASE + 0x4 );
		// channel 6 USART2_RX
		DMA_UART_Config.Peripheral = Peripheral_USART2_RX;

	}
	else if (USARTx==USART3)
	{
		// the address of DR register is the source of DMA
		DMA_UART_Config.Memory_Address = (uint32_t) (USART3_BASE + 0x4 );
		// channel 3 USART3_RX
		DMA_UART_Config.Peripheral = Peripheral_USART3_RX;
	}

	MCAL_DMA1_Init(&DMA_UART_Config);

}


//ISR
void USART1_IRQHandler (void)
{
	Global_UART_Config[0].P_IRQ_CallBack();
}

void USART2_IRQHandler (void)
{
	Global_UART_Config[1].P_IRQ_CallBack();
}
void USART3_IRQHandler (void)
{
	Global_UART_Config[2].P_IRQ_CallBack();
}

