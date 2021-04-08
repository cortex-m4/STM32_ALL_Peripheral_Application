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

////�жϽṹ��
//struct   
//{
//	 uint8_t   usart_channel;                /*�����ж�ͨ��*/
//	 uint8_t   usart_Preemption;             /*��ռ���ȼ�*/
//	 uint8_t   usart_Sub;                    /*�����ȼ�*/
//			
//	 uint8_t   dma_txchannel;               /*dma�ж�ͨ��*/
//	 uint8_t   dma_txPreemption;            /*��ռ���ȼ�*/			
//     uint8_t   dma_txSub;	                /*�����ȼ�*/
//}nvic_cfg;

//  
////dma �ṹ��
//struct   
//{
//	uint32_t                 rxCHANNEL;                        /*����ͨ��*/
//	uint32_t                 txCHANNEL;                        /*����ͨ��*/
//	uint32_t                 txFLAG;                           /*������ɱ�־*/
//    DMA_Stream_TypeDef*      rxSTREAM ;                        /*����dma������*/
//	DMA_Stream_TypeDef*      txSTREAM ;                        /*����dma������*/
//    USART_TypeDef*           USARTx;                           /*���ں�*/
//	uint8_t                  rxbuff[FIFO_SIZE];                /*���ջ���*/
//	uint8_t                  txbuff[FIFO_SIZE];                /*���ͻ���*/
//	uint8_t                  fifo_record[FRAME_SIZE];          /*����֡���Ȼ���*/
//	uint16_t                 record_point;                     /*֡���Ȼ���ָ��*/
//	uint16_t                 length;                           /*���泤��*/
//	uint16_t                 tail;                             /*����βָ��*/
//	uint16_t                 head;			                   /*����ͷָ��*/
// 
//}dma_cfg;
////���ڽṹ��
//struct   
//{
//	 uint32_t           baud;                 /*������*/
//	 USART_TypeDef*     USARTx;               /*���ں�*/
//	 GPIO_TypeDef*      rxPORT;               /*���ڽ������Ŷ˿ں�*/
//	 GPIO_TypeDef*      txPORT;               /*���ڷ������Ŷ˿ں�*/
//	 uint16_t           rxPIN;                /*���ڽ����������ź�*/
//	 uint16_t           txPIN;                /*���ڷ����������ź�*/
//	 uint8_t            rxAF;	              /*�������Ÿ���*/
//	 uint8_t            txAF;                 /*�������Ÿ���*/
//	 uint8_t            rxSOURCE;             /*����Դ*/
//	 uint8_t            txSOURCE;             /*����Դ*/	
//}port_cfg;

////ʱ�ӽṹ��
//struct   /*rcc */
//{
//	uint32_t rxPORT;  /*Port_RCC*/                   
//	uint32_t txPORT;
//	uint32_t USART;   /*USART_RCC*/ 
//	uint32_t rxDMA;   /*DMA_RCC*/
//	uint32_t txDMA;	
//}rcc_cfg;

////SERIAL_INIT_TYPE�ṹ��
//typedef struct 
//{
//	    struct   
//		{
//			/*�й�ʱ�ӵ�������*/
//		}rcc_cfg;
//		struct  
//		{
//			/*�йش��ڵ�������*/
//		}port_cfg;
//		struct  
//		{
//		    /*�й�DMA������*/				
//		}dma_cfg;
//		struct  
//		{
//			/*�й��жϵ�����*/	
//		}nvic_cfg;

//}SERIAL_INIT_TYPE;




void uart1_init();
void init_uart1_gpio();








#endif

