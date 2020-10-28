#ifndef	__MY_GPIO_H__
#define __MY_GPIO_H__


#include "stm32f4xx.h"
#include "Bit_Band_Con.h"

#define ON 0
#define OFF ~ON

#define LED_CON		PCout(0)

#define KEY_UP		PCin(13)

#define KEY_DOWN	PEin(3)

#define KEY_Return	PEin(2)

#define KEY_Config	PEin(4)

#define KEY_Left	PEin(6)

#define KEY_Right	PEin(5)

void LED_GPIO_Init(void);


#endif















