#include "key_exti.h"
#include "led.h"
#include <stm32f10x_exti.h>
#include <misc.h>
#include "oled.h"
#include "delay.h"



void EXTI_KEY()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line10;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 15;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 15;
	
	//step 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO\
												, ENABLE);
	//step 2
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,  GPIO_PinSource10);
	//step 3
	EXTI_Init(&EXTI_InitStruct);
	//step 4
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
		delay_ms(20);
		led_flick();
	}
	hour = 0;
	min = 0;
	second = 0;
  
	EXTI_ClearITPendingBit(EXTI_Line10);
	
}
