#include "led.h"
#include "pwm.h"
#include "key_exti.h"
#include "uart.h"
#include "dma.h"
#include "uart_dma.h"

int main()
{
	led_init();
	//pwm();
	EXTI_KEY();
	dma_mtom();
	//uart_init();
	uart_dma();
	//printText("test...\n");
	while(1)
	{
		delay_ms(1000);
		DMA_Cmd(DMA1_Channel4, DISABLE);
		uart_dma_send();
	}
}

