/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_Uart.h
  * @author  Fourth Team - yanzong
  * @version V2.1.2
  * @date    2020-10-12
  * @brief   Header for MY_Uart.h module
  ******************************************************************************
  * @attention
  * 硬件平台:stm32f407zgt6
  ******************************************************************************
  */
#ifndef	__MY_UART_H__
#define __MY_UART_H__

#include "stm32f4xx.h"
#include "main.h"
#include "stdio.h"






#define SUPER_UART_USE  1

#define  USE_UART1					USART1					//FOR USE witch uart
#define  UART1_GPIO_CLOCK		RCC_AHB1Periph_GPIOA	//uart rcc port clock
#define  UART1_CLOCK				RCC_APB2Periph_USART1	//uart rcc clock
#define  USART1_GPIO_PORT		GPIOA   				//uart pin port
#define  UART1_TX_PIN				GPIO_Pin_9				//uart pin
#define  UART1_RX_PIN				GPIO_Pin_10
#define  UART1_TX_AF_PIN		GPIO_PinSource9			//uart pin AF
#define  UART1_RX_AF_PIN 		GPIO_PinSource10
#define  UART1_IT_SOURCE		USART1_IRQn				//UART IT SOURCE

#define  USE_UART2					USART2					//FOR USE witch uart
#define  UART2_GPIO_CLOCK		RCC_AHB1Periph_GPIOA	//uart rcc port clock
#define  UART2_CLOCK				RCC_APB1Periph_USART2	//uart rcc clock
#define  USART2_GPIO_PORT		GPIOA   				//uart pin port
#define  UART2_TX_PIN				GPIO_Pin_2				//uart pin
#define  UART2_RX_PIN				GPIO_Pin_3
#define  UART2_TX_AF_PIN		GPIO_PinSource2			//uart pin AF
#define  UART2_RX_AF_PIN 		GPIO_PinSource3
#define  UART2_IT_SOURCE		USART2_IRQn				//UART IT SOURCE

#if defined(STM32F40_41xxx)
#define  USE_UART3					USART3					//FOR USE witch uart
#define  UART3_GPIO_CLOCK		RCC_AHB1Periph_GPIOD	//uart rcc port clock
#define  UART3_CLOCK				RCC_APB1Periph_USART3	//uart rcc clock
#define  USART3_GPIO_PORT		GPIOD   				//uart pin port
#define  UART3_TX_PIN				GPIO_Pin_8				//uart pin
#define  UART3_RX_PIN				GPIO_Pin_9
#define  UART3_TX_AF_PIN		GPIO_PinSource8			//uart pin AF
#define  UART3_RX_AF_PIN 		GPIO_PinSource9
#define  UART3_IT_SOURCE		USART3_IRQn				//UART IT SOURCE
#endif

#define  UART_Print					USART2					//choice a uart to printf

/*
USART_ConfigTypeDef:串口号 PIN GPIO_PORT 串口时钟 GPIO时钟 波特率
		IT_ConfigTypeDef:
				IT_Channel:	USART1_IRQn
							USART2_IRQn
							USART3_IRQn
						...
				Pre_Priority:1-15
				Sub_Priority:0
		USART_IT_MODE:
			@arg USART_IT_CTS:  CTS change interrupt
  *     	@arg USART_IT_LBD:  LIN Break detection interrupt
  *         @arg USART_IT_TXE:  Transmit Data Register empty interrupt
  *     	@arg USART_IT_TC:   Transmission complete interrupt
  *     	@arg USART_IT_RXNE: Receive Data register not empty interrupt
  *    		@arg USART_IT_IDLE: Idle line detection interrupt
  *     	@arg USART_IT_PE:   Parity Error interrupt
  *     	@arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
*/

//串口配置
typedef struct{
	USART_TypeDef* USARTn;		//串口号
	uint32_t USARTn_BaudRate;	//波特率
	GPIO_TypeDef* GPIOn;		//GPIO端口
	uint32_t GPIO_Pin;			//GPIO pin
	uint32_t UART_GPIO_CLK;		//串口GPIO时钟
	uint32_t UART_CLK;			//串口时钟
	
}Uart_Config_TypeDef;

//串口中断配置
typedef struct{
	IRQn_Type IT_Channel;		//中断选择
	uint8_t Pre_Priority;		//抢占优先级
	uint8_t Sub_Priority;		//子优先级
	uint16_t UART_IT_MODE;		//中断模式
	
}Uart_NVIC_TypeDef;




#if SUPER_UART_USE
typedef void(* UART_Recevie_Callback)(Uart_Config_TypeDef *uart);
//串口回调函数

void USART_Config(Uart_Config_TypeDef Uartx_Config,Uart_NVIC_TypeDef Uartx_NVIC_Config);
void UART_ALL_Init(void);
#else
void USART_Config(uint16_t USART_IT_MODE);
#endif
void Uart_Send_Data_Nowait( USART_TypeDef * pUSARTx, uint8_t ch);
void Uart_Send_Data(USART_TypeDef *pUSARTx,uint8_t ch);
void Uart_Send_String(USART_TypeDef * pUSARTx, char *str);
void Uart_Send_String_Nowait(USART_TypeDef * pUSARTx, char *str);
void Uart_Send_Halfworld(USART_TypeDef * pUSARTx, uint16_t ch);

void USART_DMA_SendStart(DMA_Stream_TypeDef *DMA_Streamx, u16 m_u16SendCnt) ;


void UART_ALL_Init(void);

void UART_RxCallback(Uart_Config_TypeDef *uart);
#endif


