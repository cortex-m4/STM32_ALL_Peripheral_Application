#ifndef	__TIM_INPUTCAPTURE_H__
#define __TIM_INPUTCAPTURE_H__

#include "main.h"

#define 	USE_TIM_IN		TIM1

#define 	TIM1_GPIO_CLK						RCC_AHB1Periph_GPIOE
#define 	TIM1_InputCapture_GPIO	GPIOA
#define 	TIM1_Input1Capture_Pin	GPIO_Pin_8

#define 	TIM1_CLK										RCC_APB2Periph_TIM1
#define 	TIM1_IT_Source							TIM1_CC_IRQn
#define 	TIM1_InputCapture_Channel		TIM_Channel_1




void TIM_IC_Config(void);
#endif
