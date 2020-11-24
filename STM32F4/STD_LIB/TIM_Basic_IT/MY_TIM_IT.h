#ifndef		__MY_TIM_IT_H__
#define 	__MY_TIM_IT_H__


#include "main.h"

extern uint16_t tim2_counter;
extern uint16_t tim3_counter;
extern uint16_t tim4_counter;

#define USE_Basic_TIM			TIM2
#define USE_Basic_TIM_IRQn	    TIM2_IRQn

#define TIM2_CLK						RCC_APB1Periph_TIM2
#define TIM3_CLK						RCC_APB1Periph_TIM3
#define TIM4_CLK						RCC_APB1Periph_TIM4

#define TIM_Counter_Stop(timn)		TIM_Cmd(timn,DISABLE);
#define TIM_Counter_Start(timn)		TIM_Cmd(timn,ENABLE);
#define TIM_Counter_Set(timn,n)		TIM_SetCounter(timn,n);

void Basic_TIM_Init(uint8_t timx,uint16_t psc,uint32_t arr);


#endif


