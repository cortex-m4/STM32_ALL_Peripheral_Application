#ifndef		__LED_H__
#define 	__LED_H__

#include "main.h"

#define LED_GPIO_Port		GPIOF
#define LED_GPIO_CLK		RCC_AHB1Periph_GPIOF

#define LED1_GPIO_PIN		GPIO_Pin_11
#define LED2_GPIO_PIN		GPIO_Pin_12
#define LED3_GPIO_PIN		GPIO_Pin_13
#define LED4_GPIO_PIN		GPIO_Pin_14

#define LED1(n)		if(n)	GPIO_SetBits(LED_GPIO_Port, LED1_GPIO_PIN);	\
									else GPIO_ResetBits(LED_GPIO_Port, LED1_GPIO_PIN);
#define LED2(n)		if(n)	GPIO_SetBits(LED_GPIO_Port, LED2_GPIO_PIN);	\
									else GPIO_ResetBits(LED_GPIO_Port, LED2_GPIO_PIN);
#define LED3(n)		if(n)	GPIO_SetBits(LED_GPIO_Port, LED3_GPIO_PIN);	\
									else GPIO_ResetBits(LED_GPIO_Port, LED3_GPIO_PIN);
#define LED4(n)		if(n)	GPIO_SetBits(LED_GPIO_Port, LED4_GPIO_PIN);	\
									else GPIO_ResetBits(LED_GPIO_Port, LED4_GPIO_PIN);


void LED_GPIO_Init(void);

#endif



