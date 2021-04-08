#ifndef	__MY_EXIT_H__
#define __MY_EXIT_H__

#include "main.h"
#include "Task_Handler.h"

#define Front_Limt_Switch_GPIO_Clk	RCC_AHB1Periph_GPIOE
#define Back_Limt_Switch_GPIO_Clk		RCC_AHB1Periph_GPIOE

#define Front_Limt_Switch_GPIO			GPIOE
#define Back_Limt_Switch_GPIO				GPIOE

#define Front_Limt_Switch_Pin				GPIO_Pin_5
#define Back_Limt_Switch_Pin				GPIO_Pin_3

#define Front_Limt_Switch_ITLine		
#define Back_Limt_Switch_ITLine		


typedef void(* EXIT_Callback)(void);
//串口回调函数

void EXIT_Init(void);

void EXIT_LineCallback(void);
#endif


