/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_DMA.h
  * @author  Fourth Team - yanzong
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Header for MY_DMA.h module
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#ifndef		__MY_DMA_H__
#define 	__MY_DMA_H__
#include "stm32f4xx.h"
#include "MY_GPIO.h"
#include "main.h"

//================UART DATE REG BASE ADDR==================
#define USART1_DR_BASE			0X40011004
#define USART2_DR_BASE			0X40004404
#define USART3_DR_BASE			0X40004804
#define UART4_DR_BASE			0X40004C04
#define UART5_DR_BASE			0X40005004
#define USART6_DR_BASE			0X40011404
#define UART7_DR_BASE			0X40007804
#define UART8_DR_BASE			0X40007C04

//USART 2  TX ������6 ͨ��4
//USART 2  RX ������5 ͨ��4
#define DMA_STREAM_TX            DMA1_Stream6
#define DMA_STREAM_RX            DMA1_Stream5

#define DMA_TX_CHANNEL              DMA_Channel_4
#define DMA_RX_CHANNEL							DMA_Channel_4
#define DMA_STREAM_CLOCK        	 RCC_AHB1Periph_DMA1 

#define DMA_STREAM_IRQ           DMA1_Stream6_IRQn
#define DMA_IT_TCIF_TX              DMA_IT_TCIF6				//�������������
#define DMA_STREAM_TX_IRQHANDLER    DMA1_Stream6_IRQHandler	
#define DMA_STREAM_RX_IRQHANDLER    DMA1_Stream5_IRQHandler	

#define BUFFER_SIZE              1024
#define TIMEOUT_MAX              10000 /* Maximum timeout value */


extern uint8_t aDST_Buffer[BUFFER_SIZE];


extern uint8_t DMA_READ_UART[BUFFER_SIZE];

void DMA_NVIC_Config(void);
void DMA_NVIC_DeInit(void);
void DMA_Config(void);

#endif






