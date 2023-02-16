#include "led.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

static int led_flag =0;//³õÊ¼µÆÃð
void led_init()
{
	  GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}

void led_off()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void led_on()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void led_flick()
{
	
	if(led_flag == 0)
	{
		led_on();
		delay_ms(1000);		
		led_flag = 1;
	}
	else
	{
		led_off();
		delay_ms(1000);
		led_flag = 0;
	}
	
}

void delay_ms(int len)
{
	 volatile unsigned int i = 6*1000*len;
	 while(i--);
}
 
