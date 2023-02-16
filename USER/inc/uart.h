#ifndef __UART_H
#define __UART_H
#include <stm32f10x_usart.h>
extern void printText(char* buf);
extern void pputc(char ch);
extern void printText(char* buf);
extern void uart_init(void);
extern void USART1_IRQHandler(void);
#endif
