#ifndef __UART_DMA_H
#define __UART_DMA_H

#include "uart.h"

#define BUFSIZE 128
#define USART1_DR_ADDR (USART1_BASE+4)
extern void uart_dma(void);
extern void uart_dma_send(void);
#endif
