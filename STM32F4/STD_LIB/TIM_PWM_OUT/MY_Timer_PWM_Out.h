/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_Timer_PWM_Out.h
  * @author  Fourth Team - yanzong
  * @version V1.0.2
  * @date    2020-10-13
  * @brief   Header for MY_Timer.h module
  ******************************************************************************
  * @attention
  * Ó²¼þÆ½Ì¨:stm32f407zgt6
  ******************************************************************************
  */

#ifndef __MY_TIMER_PWM_OUT_H__
#define __MY_TIMER_PWM_OUT_H__

#include "main.h"

#define USE_TIM4			TIM4
#define TIM4_GPIO_AF		GPIO_AF_TIM4
#define TIM4_OUT_GPIO_Port	GPIOD

#define TIM4_PWM_OUT1_GPIO	GPIO_Pin_12
#define TIM4_PWM_OUT2_GPIO	GPIO_Pin_13
#define TIM4_PWM_OUT3_GPIO	GPIO_Pin_14
#define TIM4_PWM_OUT4_GPIO	GPIO_Pin_15

#define TIM4_GPIO_Source1  GPIO_PinSource12	
#define TIM4_GPIO_Source2  GPIO_PinSource13	
#define TIM4_GPIO_Source3  GPIO_PinSource14	
#define TIM4_GPIO_Source4  GPIO_PinSource15	

#define TIM4_GPIO_CLK	RCC_AHB1Periph_GPIOD
#define TIM4_CLK		RCC_APB1Periph_TIM4


void Timer_Init(uint32_t arr,uint32_t psc,uint32_t date);

void Set_Pwm1_Duty(uint16_t duty);
void Set_Pwm2_Duty(uint16_t duty);
void Set_Pwm3_Duty(uint16_t duty);
void Set_Pwm4_Duty(uint16_t duty);

#endif




