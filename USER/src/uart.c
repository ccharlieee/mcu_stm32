#include "uart.h"


void uart_init()
{
	GPIO_InitTypeDef GPIO_InitStructa9;
	GPIO_InitTypeDef GPIO_InitStructa10;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
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
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0xF;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0xF;
	//step 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	//step 2
	GPIO_Init(GPIOA, &GPIO_InitStructa9);
	GPIO_Init(GPIOA, &GPIO_InitStructa10);
	//step 3
	USART_Init(USART1, &USART_InitStruct);
	//step 4
	NVIC_Init(&NVIC_InitStruct);
	//step 5
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//step 6
	USART_Cmd(USART1, ENABLE);
}


void pputc(char ch)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, ch);
	
}	

void printText(char* buf)
{
	while(*buf != '\0')
	{
		pputc(*buf);
		buf++;
	}
}

void USART1_IRQHandler()
{
	char data;	

	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART1);

		USART_SendData(USART1, data);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
		
}
