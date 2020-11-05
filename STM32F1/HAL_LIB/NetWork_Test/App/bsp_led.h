#ifndef	__LED_H__
#define __LED_H__

#include "gpio.h"

#define LED_RUN_TOGGLE	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8)
#define LED_WAR_TOGGLE	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9)
#define LED_ERR_TOGGLE	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8)

#endif
