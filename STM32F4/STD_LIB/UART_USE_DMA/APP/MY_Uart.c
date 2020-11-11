
/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_Uart.c
  * @author  Fourth Team - yanzong
  * @version V1.0.0
	* @version V1.1.0	2020-11-11 增加了DMA的接收 将接收的数据放入了Uart2_RxBuff
  * @date    2020-10-12
  * @brief   UART program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */



#include "stdio.h"
#include "MY_Uart.h"
#include "MY_DMA.h"


             
uint8_t read_point=0;
uint16_t Uart2_RxCounter=0;
char Uart2_RxBuff[UART2_RXBUFF_SIZE]; 

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void UART_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* 嵌套向量中断控制器组选择 */
  NVIC_InitStructure.NVIC_IRQChannel = UART_IT_SOURCE;
 /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 使能中断 */
  NVIC_Init(&NVIC_InitStructure);
	/* 初始化配置NVIC */
}

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  USART_IT_MODE
			   @arg USART_IT_CTS:  CTS change interrupt
  *            @arg USART_IT_LBD:  LIN Break detection interrupt
  *            @arg USART_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg USART_IT_TC:   Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_PE:   Parity Error interrupt
  *            @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval 无
  */
void USART_Config(uint16_t USART_IT_MODE)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(UART_GPIO_CLOCK, ENABLE);
	// 打开串口GPIO的时钟
	
	RCC_APB1PeriphClockCmd(UART_CLOCK, ENABLE);
	// 打开串口外设的时钟
	GPIO_PinAFConfig(USART_GPIO_PORT,UART_TX_AF_PIN,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(USART_GPIO_PORT,UART_RX_AF_PIN,GPIO_AF_USART2); //GPIOA3复用为USART2
	GPIO_InitStructure.GPIO_Pin = UART_TX_PIN|UART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//GPIO_Mode_AF v1.8 GPIO_Mode_AF_PP v3.5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;			//复用推挽
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;				//上拉
	GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);
	
	//配置串口的工作参数
	USART_InitStructure.USART_BaudRate = 115200;
	// 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置 针数据字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 配置工作模式，收发一起
	USART_Init(USE_UART2, &USART_InitStructure);
	// 完成串口的初始化配置
	
	UART_NVIC_Config();
	// 串口中断优先级配置
	
	USART_ITConfig(USE_UART2, USART_IT_MODE, ENABLE);	
	USART_ITConfig(USE_UART2, USART_IT_IDLE, ENABLE);	
	// 使能串口接收中断
	
	USART_Cmd(USE_UART2, ENABLE);		
	// 使能串口
	USART_ClearFlag(USE_UART2, USART_FLAG_TC); 
	// 清除发送完成标志	
}

//========无阻塞发送一个字符===================
void Uart_Send_Data_Nowait( USART_TypeDef * pUSARTx, uint8_t ch){
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
}

//========有阻塞发送字符=======================
void Uart_Send_Data(USART_TypeDef *pUSARTx,uint8_t ch){
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	

}

//============阻塞发送字符串========================
void Uart_Send_String(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do{
		USART_SendData( pUSARTx, *(str + k) );
		k++;
  }while(*(str + k)!='\0');
	
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//=============阻塞发送一个16位数=====================
void Uart_Send_Halfworld(USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


void USART_DMA_SendStart(DMA_Stream_TypeDef *DMA_Streamx, u16 m_u16SendCnt)  
{    
	u16 l_u16RetryCnt = 0;
	
    DMA_Cmd(DMA_Streamx, DISABLE);                      //关闭DMA传输           
    while ((DMA_GetCmdStatus(DMA_Streamx) != DISABLE) && (l_u16RetryCnt++ < 500));	//等待DMA可配置	
    DMA_SetCurrDataCounter(DMA_Streamx, m_u16SendCnt);  //数据传输量 	   
    DMA_Cmd(DMA_Streamx, ENABLE);                      	//开启DMA传输   
} 



//重定向printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(UART_Print, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(UART_Print, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

//重定向scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(UART_Print, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(UART_Print);
}

void USART2_IRQHandler(void){
	
//	if((USART_GetITStatus(UART_Print, USART_IT_RXNE) != RESET)){
//		Uart2_RxBuff[Uart2_RxCounter]=UART_Print->DR;
//		Uart2_RxCounter++;
//		USART_ClearITPendingBit(UART_Print,USART_IT_RXNE); // 清除标志位
//	}	
		
	
	if(USART_GetITStatus(UART_Print,USART_IT_IDLE)!=RESET)
	{	
		//read_point=0;
		//Uart_Send_String(UART_Print,Uart2_RxBuff);
		Uart2_RxCounter=UART_Print->SR;			//清除USART_IT_IDLE标志  步骤1 
		Uart2_RxCounter=UART_Print->DR;			//清除USART_IT_IDLE标志  步骤2
		Uart2_RxCounter=UART2_RXBUFF_SIZE-DMA_GetCurrDataCounter(DMA_STREAM_RX);
		memcpy(Uart2_RxBuff, DMA_READ_UART, 1024);	 
		memset(DMA_READ_UART,0,1024);
		DMA_Cmd(DMA_STREAM_RX,DISABLE);
		
		
		DMA_ClearFlag(DMA_STREAM_RX,DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);
    DMA_SetCurrDataCounter(DMA_STREAM_RX, BUFFER_SIZE);  
    DMA_Cmd(DMA_STREAM_RX, ENABLE); //  这两行是重新设置DMA  让这个搬运工准备下一次的工作
		USART_ClearITPendingBit(UART_Print,USART_IT_IDLE); // 清除标志位
	}	
	
}



