#ifndef __DMA_H
#define __DMA_H

#include <stm32f10x_dma.h>

extern void dma_mtom(void);
extern int bufcmp(const uint32_t* pbuf,uint32_t* pbuf1,uint16_t buflen);
extern void DMA1_Channel3_IRQHandler(void);
#endif
