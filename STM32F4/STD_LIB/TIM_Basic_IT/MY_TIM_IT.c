/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_TIM_IT.c
  * @author  Fourth Team - yanzong
  * @version V1.0.0
  * @date    2020-10-21
  * @brief   basic TIMER interrupt
  ******************************************************************************
  * @attention
  * 硬件平台:stm32f407zgt6
	* 基本定时器中断
  ******************************************************************************
  */
#include "MY_TIM_IT.h"


/*
	param:
	*psc:分频
	*arr:计数

*/

void Basic_TIM_Init(uint16_t psc,uint32_t arr){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_APB1PeriphClockCmd(USE_Basic_TIM_CLK,ENABLE);  ///使能USE_Basic_TIM时钟
	
	NVIC_InitStructure.NVIC_IRQChannel=USE_Basic_TIM_IRQn; 							//定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; 	//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 				//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 			//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  		//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(USE_Basic_TIM,&TIM_TimeBaseInitStructure);//初始化USE_Basic_TIM
	TIM_ClearFlag(USE_Basic_TIM, TIM_FLAG_Update);
	TIM_ITConfig(USE_Basic_TIM,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(USE_Basic_TIM,ENABLE); 										//使能定时器3
	
	
	
}


__weak void Basic_IT_Callback(void){
									
}

//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(USE_Basic_TIM,TIM_IT_Update)!= RESET) //溢出中断
	{
		Basic_IT_Callback();
		TIM_ClearITPendingBit(USE_Basic_TIM,TIM_IT_Update);  //清除中断标志位
	}
	
}





