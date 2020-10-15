#ifndef		__UART_H__
#define 	__UART_H__
#include "stm32f10x.h"

#define  USART1_GPIO_PORT    GPIOA   
#define  UART1_TX_PIN        GPIO_Pin_10
#define  UART1_RX_PIN        GPIO_Pin_9

#define  USART2_GPIO_PORT     GPIOA   
#define  UART2_TX_PIN        GPIO_Pin_2
#define  UART2_RX_PIN        GPIO_Pin_3

static void UART_NVIC_Config(void);
void USART_Config(void);
void uart_send_data_nowait( USART_TypeDef * pUSARTx, uint8_t ch);
void uart_send_data(USART_TypeDef *pUSARTx,uint8_t ch);
void uart_send_string(USART_TypeDef * pUSARTx, char *str);
void uart_send_halfworld(USART_TypeDef * pUSARTx, uint16_t ch);


#endif




