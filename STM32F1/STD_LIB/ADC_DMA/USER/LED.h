#ifndef		__LED_H__
#define 	__LED_H__
#include "stm32f10x.h"

#define 	Color_LED_CLK		RCC_APB2Periph_GPIOB
#define 	LED_CLK					RCC_APB2Periph_GPIOF

#define 	Color_LED_PORT	GPIOB
#define 	LED_PORT	GPIOF

#define 	GREEN_LED_PIN		GPIO_Pin_0
#define 	RED_LED_PIN			GPIO_Pin_5
#define 	BLUE_LED_PIN		GPIO_Pin_1

#define 	LED1_PIN				GPIO_Pin_7
#define 	LED2_PIN				GPIO_Pin_8


#define 	GREEN_LED_ON		GPIO_ResetBits(Color_LED_PORT,GREEN_LED_PIN)
#define 	GREEN_LED_OFF		GPIO_SetBits(Color_LED_PORT,GREEN_LED_PIN)

#define 	RED_LED_ON			GPIO_ResetBits(Color_LED_PORT,RED_LED_PIN)
#define 	RED_LED_OFF			GPIO_SetBits(Color_LED_PORT,RED_LED_PIN)

#define 	BLUE_LED_ON			GPIO_ResetBits(Color_LED_PORT,BLUE_LED_PIN)
#define 	BLUE_LED_OFF		GPIO_SetBits(Color_LED_PORT,BLUE_LED_PIN)

void LED_Init(void);
#endif



