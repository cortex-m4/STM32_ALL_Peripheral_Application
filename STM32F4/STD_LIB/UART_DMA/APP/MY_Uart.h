#ifndef	__MY_UART_H__
#define __MY_UART_H__

#include "stm32f4xx.h"
#include "main.h"
#include "stdio.h"

#define  USE_UART2			USART2					//FOR USE witch uart
#define  UART_GPIO_CLOCK	RCC_AHB1Periph_GPIOA	//uart rcc port clock
#define  UART_CLOCK			RCC_APB1Periph_USART2	//uart rcc clock
#define  USART_GPIO_PORT	GPIOA   				//uart pin port
#define  UART_TX_PIN		GPIO_Pin_2				//uart pin
#define  UART_RX_PIN		GPIO_Pin_3
#define  UART_TX_AF_PIN		GPIO_PinSource2			//uart pin AF
#define  UART_RX_AF_PIN 	GPIO_PinSource3

#define  UART_IT_SOURCE		USART2_IRQn				//UART IT SOURCE

#define  UART_Print			USART2					//choice a uart to printf


static void UART_NVIC_Config(void);
void USART_Config(void);
void Uart_Send_Data_Nowait( USART_TypeDef * pUSARTx, uint8_t ch);
void Uart_Send_Data(USART_TypeDef *pUSARTx,uint8_t ch);
void Uart_Send_String(USART_TypeDef * pUSARTx, char *str);
void Uart_Send_Halfworld(USART_TypeDef * pUSARTx, uint16_t ch);

#endif


