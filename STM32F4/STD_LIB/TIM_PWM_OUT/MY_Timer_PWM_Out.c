/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_Timer_PWM_Out.c
  * @author  Fourth Team - yanzong
  * @version V1.0.2
  * @date    2020-10-13
  * @brief   TIMER pwm out program body
  ******************************************************************************
  * @attention
  * 硬件平台:stm32f407zgt6
  ******************************************************************************
  */
#include "MY_Timer_PWM_Out.h"

/*
	arr:自动重载值
	psc:分频
	data:脉宽

*/
void Timer_Init(uint32_t arr,uint32_t psc,uint32_t date){
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(TIM4_CLK, ENABLE);

	/* GPIOD clock enable */
	RCC_AHB1PeriphClockCmd(TIM4_GPIO_CLK, ENABLE);
  
	
	/* Connect TIM4 pins to AF */  
	GPIO_PinAFConfig(TIM4_OUT_GPIO_Port, TIM4_GPIO_Source1, TIM4_GPIO_AF);
	GPIO_PinAFConfig(TIM4_OUT_GPIO_Port, TIM4_GPIO_Source2, TIM4_GPIO_AF); 
	GPIO_PinAFConfig(TIM4_OUT_GPIO_Port, TIM4_GPIO_Source3, TIM4_GPIO_AF);
	GPIO_PinAFConfig(TIM4_OUT_GPIO_Port, TIM4_GPIO_Source4, TIM4_GPIO_AF); 
	
	/* GPIOD Configuration: TIM4 CH1 (PD12), TIM4 CH2 (PC13), TIM4 CH3 (PC14) and TIM4 CH4 (PC15) */
	GPIO_InitStructure.GPIO_Pin = TIM4_PWM_OUT1_GPIO|TIM4_PWM_OUT2_GPIO|TIM4_PWM_OUT3_GPIO|TIM4_PWM_OUT4_GPIO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(TIM4_OUT_GPIO_Port, &GPIO_InitStructure); 

	
	
	/* Compute the prescaler value */

	/* Time base configuration */	
	TIM_TimeBaseStructure.TIM_Period = arr;			//计数
	TIM_TimeBaseStructure.TIM_Prescaler = psc;		//分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//分频因子
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(USE_TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = date;					//脉宽值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(USE_TIM4, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(USE_TIM4, TIM_OCPreload_Enable);
	
	//PWM1 Mode configuration: Channel2 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = date;

	TIM_OC2Init(USE_TIM4, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(USE_TIM4, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel3 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = date;

	TIM_OC3Init(USE_TIM4, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(USE_TIM4, TIM_OCPreload_Enable);

	//PWM1 Mode configuration: Channel4 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = date;

	TIM_OC4Init(USE_TIM4, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(USE_TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(USE_TIM4, ENABLE);
	//TIM4 enable counter 
	TIM_Cmd(USE_TIM4, ENABLE);
}

//设置占空比
void Set_Pwm1_Duty(uint16_t duty){
	
	TIM_SetCompare1(USE_TIM4,duty);
	
	
}
void Set_Pwm2_Duty(uint16_t duty){
	
	TIM_SetCompare2(USE_TIM4,duty);
}
void Set_Pwm3_Duty(uint16_t duty){
	
	TIM_SetCompare3(USE_TIM4,duty);
}
void Set_Pwm4_Duty(uint16_t duty){
	
	TIM_SetCompare4(USE_TIM4,duty);
}



