#ifndef __MY_UART_H__
#define __MY_UART_H__
/**
  ******************************************************************************
  * @file    CAN/APP/MY_UART.h 
  * @author  Fourth Team -yanzong
  * @brief   Header for main.c module
  ******************************************************************************
  * @version V1.1
  * @attention
  * FOR STM32F407ZGT6
  * USE HAL LIB
  * USE sturct to init uart
  
  ******************************************************************************
*/

////中断结构体
//struct   
//{
//	 uint8_t   usart_channel;                /*串口中断通道*/
//	 uint8_t   usart_Preemption;             /*抢占优先级*/
//	 uint8_t   usart_Sub;                    /*从优先级*/
//			
//	 uint8_t   dma_txchannel;               /*dma中断通道*/
//	 uint8_t   dma_txPreemption;            /*抢占优先级*/			
//     uint8_t   dma_txSub;	                /*从优先级*/
//}nvic_cfg;

//  
////dma 结构体
//struct   
//{
//	uint32_t                 rxCHANNEL;                        /*接收通道*/
//	uint32_t                 txCHANNEL;                        /*发送通道*/
//	uint32_t                 txFLAG;                           /*发送完成标志*/
//    DMA_Stream_TypeDef*      rxSTREAM ;                        /*接收dma数据流*/
//	DMA_Stream_TypeDef*      txSTREAM ;                        /*发送dma数据流*/
//    USART_TypeDef*           USARTx;                           /*串口号*/
//	uint8_t                  rxbuff[FIFO_SIZE];                /*接收缓存*/
//	uint8_t                  txbuff[FIFO_SIZE];                /*发送缓存*/
//	uint8_t                  fifo_record[FRAME_SIZE];          /*接收帧长度缓存*/
//	uint16_t                 record_point;                     /*帧长度缓存指针*/
//	uint16_t                 length;                           /*缓存长度*/
//	uint16_t                 tail;                             /*缓存尾指针*/
//	uint16_t                 head;			                   /*缓存头指针*/
// 
//}dma_cfg;
////串口结构体
//struct   
//{
//	 uint32_t           baud;                 /*波特率*/
//	 USART_TypeDef*     USARTx;               /*串口号*/
//	 GPIO_TypeDef*      rxPORT;               /*串口接收引脚端口号*/
//	 GPIO_TypeDef*      txPORT;               /*串口发送引脚端口号*/
//	 uint16_t           rxPIN;                /*串口接收引脚引脚号*/
//	 uint16_t           txPIN;                /*串口发送引脚引脚号*/
//	 uint8_t            rxAF;	              /*接收引脚复用*/
//	 uint8_t            txAF;                 /*发送引脚复用*/
//	 uint8_t            rxSOURCE;             /*接收源*/
//	 uint8_t            txSOURCE;             /*发送源*/	
//}port_cfg;

////时钟结构体
//struct   /*rcc */
//{
//	uint32_t rxPORT;  /*Port_RCC*/                   
//	uint32_t txPORT;
//	uint32_t USART;   /*USART_RCC*/ 
//	uint32_t rxDMA;   /*DMA_RCC*/
//	uint32_t txDMA;	
//}rcc_cfg;

////SERIAL_INIT_TYPE结构体
//typedef struct 
//{
//	    struct   
//		{
//			/*有关时钟的配置项*/
//		}rcc_cfg;
//		struct  
//		{
//			/*有关串口的配置项*/
//		}port_cfg;
//		struct  
//		{
//		    /*有关DMA的配置*/				
//		}dma_cfg;
//		struct  
//		{
//			/*有关中断的配置*/	
//		}nvic_cfg;

//}SERIAL_INIT_TYPE;




void uart1_init();
void init_uart1_gpio();








#endif

