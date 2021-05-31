#ifndef	__LIB_KEY_H__
#define __LIB_KEY_H__
#include "main.h"

#define KEY1_ON		0x44
#define KEY2_ON		0x4d
#define KEY3_ON		0x56
#define KEY4_ON		0x5f


#define KEY1_IN		HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2_IN		HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3_IN		HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY4_IN		HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)


uint8_t KeysCan(void);



#endif


