#ifndef		__SYSTICK_H__
#define 	__SYSTICK_H__
#include "stm32f10x.h"

void SysTick_Init(void);
void delay_us( __IO uint32_t us);
void delay_ms( __IO uint32_t ms);




#endif
