#ifndef	__MY_GPIO_H__
#define __MY_GPIO_H__


#include "stm32f4xx.h"
#include "Bit_Band_Con.h"

#define ON 0
#define OFF ~ON

#define LED_CON		PAout(5)
#define LED_TOGGLE	GPIO_ToggleBits(GPIOA,GPIO_Pin_5)

void LED_GPIO_Init(void);


#endif















