/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_DMA.c
  * @author  Fourth Team - yanzong
  * @version V1.0.1
  * @date    2020-10-12
  * @brief   DMA program body
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#include "MY_DMA.h"
#define TIMEOUT_MAX              10000 /* Maximum timeout value */

uint8_t aDST_Buffer[BUFFER_SIZE];
uint8_t DMA_READ_UART[BUFFER_SIZE];

void DMA_NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the DMA Stream IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA_STREAM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	/* Enable DMA Stream Transfer Complete interrupt */
  
	DMA_ITConfig(DMA_STREAM_TX, DMA_IT_TC, ENABLE);

}
void DMA_NVIC_DeInit(void){
	DMA_ITConfig(DMA_STREAM_TX, DMA_IT_TC, DISABLE);
}
void DMA_Config(void)
{
  
  DMA_InitTypeDef  DMA_InitStructure_TX;
  DMA_InitTypeDef  DMA_InitStructure_RX;
  __IO uint32_t    Timeout = TIMEOUT_MAX;
    
  /*开DMA时钟 */
  RCC_AHB1PeriphClockCmd(DMA_STREAM_CLOCK, ENABLE);
  
  /* Reset DMA Stream registers (for debug purpose) */
  DMA_DeInit(DMA_STREAM_TX);
  DMA_DeInit(DMA_STREAM_RX);
  
  /* Check if the DMA Stream is disabled before enabling it.
     Note that this step is useful when the same Stream is used multiple times:
     enabled, then disabled then re-enabled... In this case, the DMA Stream disable
     will be effective only at the end of the ongoing data transfer and it will 
     not be possible to re-configure it before making sure that the Enable bit 
     has been cleared by hardware. If the Stream is used only once, this step might 
     be bypassed. */
  while (DMA_GetCmdStatus(DMA_STREAM_TX) != DISABLE)
  {
  }
  
  /* Configure DMA Stream for TX */
  DMA_InitStructure_TX.DMA_Channel = DMA_CHANNEL;  					//选择通道
  DMA_InitStructure_TX.DMA_PeripheralBaseAddr =USART2_DR_BASE;			//外设基地址
  DMA_InitStructure_TX.DMA_Memory0BaseAddr =(uint32_t) aDST_Buffer;	//外部memory地址
  DMA_InitStructure_TX.DMA_DIR = DMA_DIR_MemoryToPeripheral;			//传送方向
  DMA_InitStructure_TX.DMA_BufferSize = (uint8_t)BUFFER_SIZE;			//大小
  DMA_InitStructure_TX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址自增？ 失能
  DMA_InitStructure_TX.DMA_MemoryInc = DMA_MemoryInc_Enable;			//memory地址自增 使能
  DMA_InitStructure_TX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure_TX.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure_TX.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure_TX.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure_TX.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure_TX.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure_TX.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure_TX.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA_STREAM_TX, &DMA_InitStructure_TX);
  /* Configure DMA Stream for RX */
  DMA_InitStructure_RX.DMA_Channel = DMA_CHANNEL;  						//选择通道
  DMA_InitStructure_RX.DMA_PeripheralBaseAddr =USART2_DR_BASE;			//外设基地址
  DMA_InitStructure_RX.DMA_Memory0BaseAddr =(uint32_t) DMA_READ_UART;	//memory地址
  DMA_InitStructure_RX.DMA_DIR = DMA_DIR_PeripheralToMemory;			//传送方向
  DMA_InitStructure_RX.DMA_BufferSize = (uint8_t)BUFFER_SIZE;			//大小
  DMA_InitStructure_RX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址自增？ 失能
  DMA_InitStructure_RX.DMA_MemoryInc = DMA_MemoryInc_Enable;			//memory地址自增 使能
  DMA_InitStructure_RX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure_RX.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure_RX.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure_RX.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure_RX.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure_RX.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure_RX.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure_RX.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA_STREAM_RX, &DMA_InitStructure_RX);
    

  /* DMA Stream enable */
  DMA_Cmd(DMA_STREAM_TX, ENABLE);
  DMA_Cmd(DMA_STREAM_RX, ENABLE);

  /* Check if the DMA Stream has been effectively enabled.
     The DMA Stream Enable bit is cleared immediately by hardware if there is an 
     error in the configuration parameters and the transfer is no started (ie. when
     wrong FIFO threshold is configured ...) */
  Timeout = TIMEOUT_MAX;
  while ((DMA_GetCmdStatus(DMA_STREAM_TX) != ENABLE) && (Timeout-- > 0))
  {
  }
   
  /* Check if a timeout condition occurred */
  if (Timeout == 0)
  {
    /* Manage the error: to simplify the code enter an infinite loop */
    while (1)
    {
    }
  }
	//enable DMA NVIC
	DMA_NVIC_Config();
      
}


/**
 
*/
void DMA_STREAM_TX_IRQHANDLER(void)
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if(DMA_GetITStatus(DMA_STREAM_TX, DMA_IT_TCIF_TX)==SET)
  {
    /* Clear DMA Stream Transfer Complete interrupt pending bit */
	DMA_ClearFlag(DMA_STREAM_TX, DMA_FLAG_TCIF6 | DMA_FLAG_FEIF6 | 
					  DMA_FLAG_DMEIF6 | DMA_FLAG_TEIF6 | DMA_FLAG_HTIF6); 	//清除标志位			
		
	//while(!USART_GetFlagStatus(USART2, USART_FLAG_TC));	//等待USART2发送完成标志TC置1
	USART_ClearFlag(USART2, USART_FLAG_TC); 			//清除发送完成标志
	  
	USART_DMACmd(USART2, USART_DMAReq_Tx, DISABLE);		/* 失能串口发送请求 */
	DMA_Cmd(DMA_STREAM_TX, DISABLE);		/* 失能 DMA_STREAM */
	DMA_ClearITPendingBit(DMA_STREAM_TX, DMA_IT_TCIF_TX);	/* 清除 DMA_STREAM 传输完成中断标志位，否则程序会无限陷入中断 */
	DMA_Cmd(DMA_STREAM_TX, ENABLE);	/* 重新使能 DMA_STREAM */
	
  }
}

