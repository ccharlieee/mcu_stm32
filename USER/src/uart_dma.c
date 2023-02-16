#include "uart_dma.h"

char tx_buf[BUFSIZE] = "hello world";
DMA_InitTypeDef DMA_InitStruct;
void uart_dma()
{
	GPIO_InitTypeDef GPIO_InitStructa9;
	GPIO_InitTypeDef GPIO_InitStructa10;
	USART_InitTypeDef USART_InitStruct;
	
	
	GPIO_InitStructa9.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructa9.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructa9.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructa10.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructa10.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructa10.GPIO_Speed = GPIO_Speed_50MHz;
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
		
	DMA_InitStruct.DMA_BufferSize = BUFSIZE ;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)tx_buf;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = USART1_DR_ADDR;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	//step 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//step 2
	GPIO_Init(GPIOA, &GPIO_InitStructa9);
	GPIO_Init(GPIOA, &GPIO_InitStructa10);
	//step 3
	USART_Init(USART1, &USART_InitStruct);
	//step 4
	DMA_Init(DMA1_Channel4, &DMA_InitStruct);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	//step 5
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//step 6
	USART_Cmd(USART1, ENABLE);
	DMA_Cmd(DMA1_Channel4, ENABLE);
}

void uart_dma_send(void)
{
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)tx_buf;	
	DMA_Init(DMA1_Channel4, &DMA_InitStruct);
	DMA_Cmd(DMA1_Channel4, ENABLE);
}
