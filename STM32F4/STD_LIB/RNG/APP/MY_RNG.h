#ifndef	__MY_RNG_H__
#define __MY_RNG_H__

#include "stm32f4xx.h"
#include "string.h"



void RNG_Config(void);

void Get_Random_Num(uint8_t size,uint32_t *RNG_Data);



#endif

