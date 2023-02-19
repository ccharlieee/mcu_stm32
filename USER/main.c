#include "led.h"
#include "pwm.h"
#include "key_exti.h"
#include "uart.h"
#include "dma.h"
#include "uart_dma.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "delay.h"
char time_buf[128] ;
void time_ing()
{
	
	delay_ms(1000);
	second ++;
	if(second == 60)
	{
		min ++;
		second = 0;
	}
	else if(min==60)
	{
		hour ++;
		min = 0;
	}
	sprintf(time_buf,"%02d:%02d:%02d",hour,min,second);
}


int main()
{
	
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
		OLED_Init();			//初始化OLED  
	OLED_Clear()  	; 
	led_init();
	//pwm();
	EXTI_KEY();
	dma_mtom();
	uart_init();
	//uart_dma();
	//printText("test...\n");
	hour = 0;
	min = 0;
	second =0;
	while(1)
	{
//OLED_Clear();
	/*	LED_ON;
		OLED_ShowCHinese(0,0,0);//中
		OLED_ShowCHinese(18,0,1);//景
		OLED_ShowCHinese(36,0,2);//园
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
		OLED_ShowString(0,3,"1.3' OLED TEST");
		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		OLED_ShowChar(48,6,t);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			
	
		delay_ms(8000);
		OLED_Clear();

		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP2);
		delay_ms(8000);
		OLED_Clear();*/
		
		time_ing();
		OLED_ShowString(8,1,(u8*)time_buf);
		//OLED_ShowString(0,3,);
		
	}
}

