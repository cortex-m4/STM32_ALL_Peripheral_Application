/**
  ******************************************************************************
  * @file    MY_IWDG.c 
  * @author  yanzong
  * @version V1.0.1
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
		用户需要用的函数：MY_IWDG_Feed_Dog();
  ******************************************************************************
  */
#include "MY_IWDG.h"


/*
param:

看门狗主频：32khz

pres:分频
	IWDG_Prescaler_4			最高512ms
	IWDG_Prescaler_8			最高1024ms
	IWDG_Prescaler_16			最高2048ms
	IWDG_Prescaler_32			最高4096ms
	IWDG_Prescaler_64			最高8192ms
	IWDG_Prescaler_128		最高16384ms
	IWDG_Prescaler_256		最高32768ms
ms:计数

*/
void MY_IWDG_Init(uint8_t pres,uint16_t  ms)
{
	IWDG_WriteAccessCmd (IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler (pres);
	IWDG_SetReload(ms);
	IWDG_ReloadCounter();
	IWDG_Enable();
	
}
 void MY_IWDG_Feed_Dog(void)
{
	IWDG_ReloadCounter();
}



