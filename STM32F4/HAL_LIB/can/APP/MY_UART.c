/**
  ******************************************************************************
  * @file    CAN/APP/MY_UART.c 
  * @author  Fourth Team -yanzong
  * @brief   uart program body
  ******************************************************************************
  * @version V1.1
  * @attention
  * FOR STM32F407ZGT6
  * USE HAL LIB
  * USE sturct to init uart
  
  ******************************************************************************
  */
#include "MY_UART.h"



////初始化串口1
//SERIAL_INIT_TYPE usart1=
//{        .rcc_cfg.USART     			 = RCC_APB2Periph_USART1, /*时钟*/
//		 .rcc_cfg.rxPORT    			 = RCC_AHB1Periph_GPIOA,
//		 .rcc_cfg.txPORT     			 = RCC_AHB1Periph_GPIOA,
//		 .rcc_cfg.rxDMA      			 = RCC_AHB1Periph_DMA2,
//		 .rcc_cfg.txDMA      			 = RCC_AHB1Periph_DMA2, 
//		 .port_cfg.USARTx    			 = USART1,               /*串口*/
//		 .port_cfg.baud	     		     = 115200,
//		 .port_cfg.rxPORT    			 = GPIOA,
//		 .port_cfg.txPORT     		     = GPIOA,
//		 .port_cfg.rxPIN     			 = GPIO_Pin_10,
//		 .port_cfg.txPIN    			 = GPIO_Pin_9,
//		 .port_cfg.rxAF     			 = GPIO_AF_USART1,
//		 .port_cfg.txAF      			 = GPIO_AF_USART1,
//		 .port_cfg.rxSOURCE  			 = GPIO_PinSource10,
//		 .port_cfg.txSOURCE  			 = GPIO_PinSource9,
//		 .dma_cfg.USARTx     		     = USART1,               /*dma*/
//		 .dma_cfg.rxCHANNEL  		     = DMA_Channel_4,
//		 .dma_cfg.txCHANNEL  		     = DMA_Channel_4,
//		 .dma_cfg.txSTREAM   		     = DMA2_Stream7,
//		 .dma_cfg.rxSTREAM			     = DMA2_Stream5,
//		 .dma_cfg.txFLAG     		     = DMA_FLAG_TCIF4,
//		 .dma_cfg.head      			 = 0,
//		 .dma_cfg.tail      			 = 0,
//		 .dma_cfg.length    			 = FIFO_SIZE,
//		 .nvic_cfg.usart_channel    	 = USART1_IRQn,         /*中断*/
//		 .nvic_cfg.usart_Preemption      = 0,
//		 .nvic_cfg.usart_Sub       	     = 1, 
//		 .nvic_cfg.dma_txchannel   	     = DMA2_Stream7_IRQn,
//		 .nvic_cfg.dma_txPreemption	     = 0,
//		 .nvic_cfg.dma_txSub       	     = 2   
//};


//void USART_RCC_Config(){

//}
//void USART_NVIC_Config(){

//}

//void USART_DMA_Config(){



//}
//void USART_Port_Config(){

//}

//void USART_Config(SERIAL_INIT_TYPE* USART)
//{
//	 USART_RCC_Config(USART); 
//	 USART_NVIC_Config(USART);	 
//	 USART_DMA_Config(USART);
//     USART_Port_Config(USART);	
//}




UART_HandleTypeDef uart1_init;

void uart1_init(){
	__HAL_RCC_USART2_CLK_ENABLE();						//使能USART1时钟
	uart1_init.Instance=USART1;
	uart1_init.Init.BaudRate=115200;					//波特率
	uart1_init.Init.WordLength=UART_WORDLENGTH_8B;		//字长为8位数据格式
	uart1_init.Init.StopBits=UART_STOPBITS_1;   		//一个停止位
	uart1_init.Init.Parity=UART_PARITY_NONE;   			//无奇偶校验位
	uart1_init.Init.HwFlowCtl=UART_HWCONTROL_NONE;  	//无硬件流控
	uart1_init.Init.Mode=UART_MODE_TX_RX;   			//收发模式
	HAL_UART_Init(&uart1_init);
}
void init_uart1_gpio(){
		GPIO_InitTypeDef led_gpio_init;
		__HAL_RCC_GPIOA_CLK_ENABLE();												
		led_gpio_init.Alternate=GPIO_AF7_USART2;
		led_gpio_init.Mode=GPIO_MODE_AF_PP;
		led_gpio_init.Pin=GPIO_PIN_9;
		led_gpio_init.Pull=GPIO_PULLUP;
		led_gpio_init.Speed=GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA,&led_gpio_init);			//初始化PA9  TX
		led_gpio_init.Pin=GPIO_PIN_10;
		led_gpio_init.Mode=GPIO_MODE_INPUT;
		HAL_GPIO_Init(GPIOA,&led_gpio_init);			//初始化PA10  RX
}
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&uart1_init, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}














