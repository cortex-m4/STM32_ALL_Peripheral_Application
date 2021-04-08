#ifndef	__MY_GPIO_H__
#define __MY_GPIO_H__


#include "stm32f4xx.h"
#include "Bit_Band_Con.h"

#define ON 0
#define OFF ~ON

#define LED_CON		PAout(5)

void LED_GPIO_Init(void);


#endif















