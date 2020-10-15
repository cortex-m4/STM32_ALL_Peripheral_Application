#ifndef		__ADC_DMA_H__
#define 	__ADC_DMA_H__
#include "stm32f10x.h"

#define ADC1_DMA_Data_Size		128

#define ADC1_DR_Addr					((u32)0x40012400+0x4c)


void ADC1_DMA_Init(void);

#endif
