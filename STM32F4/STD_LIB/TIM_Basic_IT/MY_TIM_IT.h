#ifndef		__MY_TIM_IT_H__
#define 	__MY_TIM_IT_H__

#include "Task_Handler.h"
#include "main.h"

#define USE_Basic_TIM				TIM2
#define USE_Basic_TIM_IRQn	TIM2_IRQn
#define USE_Basic_TIM_CLK		RCC_APB1Periph_TIM2

#define TIM2_Counter_Stop			TIM_Cmd(USE_Basic_TIM,DISABLE);
#define TIM2_Counter_Start		TIM_Cmd(USE_Basic_TIM,ENABLE);
#define TIM2_Counter_Set(n)			TIM_SetCounter(USE_Basic_TIM,n);

void Basic_TIM_Init(uint16_t psc,uint32_t arr);


#endif


