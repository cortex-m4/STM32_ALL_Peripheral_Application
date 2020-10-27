/**
  ******************************************************************************
  * @file    MY_IWDG.h 
  * @author  yanzong
  * @version V1.0.1
  * @date    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
#ifndef		__MY_IWDG_H__
#define 	__MY_IWDG_H__

#include "main.h"

void MY_IWDG_Init(uint8_t pres,uint16_t  ms);

void MY_IWDG_Feed_Dog(void);
#endif


