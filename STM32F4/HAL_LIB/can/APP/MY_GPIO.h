#ifndef	__MY_GPIO_H__
#define __MY_GPIO_H__


#include "stm32f4xx_hal.h"
#include "main.h"

#define LED_ON					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)
#define LED_OFF					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)
#define LED_TOGGLE				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5)
#define GPIO_CLK_ON				__HAL_RCC_GPIOA_CLK_ENABLE()
void Init_LED(void);
#endif



