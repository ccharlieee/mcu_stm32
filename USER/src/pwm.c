#include "pwm.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>

void pwm()    
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = TIM_TimeBaseInitStruct.TIM_Period/2;
	
	//step 1
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//step 2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//step 3
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//step 4
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	//step 5
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	//STEP 6
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//step 7
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	//step 8
	TIM_Cmd(TIM2, ENABLE);
}
