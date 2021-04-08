#ifndef	__MY_SYSTICK_H__
#define __MY_SYSTICK_H__

#include "stm32f4xx.h"


void Systick_Init(void);
void Delay_us(uint32_t nus);
void Delay_ms(uint32_t nms);


#endif
