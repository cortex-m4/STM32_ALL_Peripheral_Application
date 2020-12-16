
/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_Uart.c
  * @author  Fourth Team - yanzong
  * @version V1.0.0
	* @version V1.1.0	2020-11-11 增加了DMA的接收 将接收的数据放入了Uart2_RxBuff
						V2.1.2 ：完善了高级通用操作
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

Uart_Config_TypeDef uart1_init;
Uart_Config_TypeDef uart2_init;
Uart_Config_TypeDef uart3_init;

UART_Recevie_Callback uart1_callback;
UART_Recevie_Callback uart2_callback;
UART_Recevie_Callback uart3_callback;
             
uint8_t read_point=0;
uint16_t Uart2_RxCounter=0;
char Uart2_RxBuff[UART2_RXBUFF_SIZE]; 

/**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  IT_Channel:	USART1_IRQn
						USART2_IRQn
						USART3_IRQn
						...
			Pre_Priority:1-15
			Sub_Priority:0
			sta:DISABLE or ENABLE
  * @retval 无
  */
static void UART_NVIC_Config(IRQn_Type IT_Channel,uint8_t Pre_Priority,uint8_t Sub_Priority)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* 嵌套向量中断控制器组选择 */
  NVIC_InitStructure.NVIC_IRQChannel = IT_Channel;
 /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_Priority;
   /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = Sub_Priority;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 使能中断 */
  NVIC_Init(&NVIC_InitStructure);
	/* 初始化配置NVIC */
}


 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  Uartx_Config
			Uartx_NVIC_Config
		
  * @retval 无
  */
void USART_Config(Uart_Config_TypeDef Uartx_Config,Uart_NVIC_TypeDef Uartx_NVIC_Config)
{
	uint8_t i_source;
								//引脚暂存
	uint16_t pin_list_buf=Uartx_Config.GPIO_Pin;		
	
	uint8_t gpio_af_buf;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(Uartx_Config.UART_GPIO_CLK, ENABLE);
	if(Uartx_Config.USARTn==USART1){
		RCC_APB2PeriphClockCmd(Uartx_Config.UART_CLK, ENABLE);
	}else if(Uartx_Config.USARTn==USART2||Uartx_Config.USARTn==USART3){
		RCC_APB1PeriphClockCmd(Uartx_Config.UART_CLK, ENABLE);
	}
	// 打开串口GPIO的时钟
	
	
	// 打开串口外设的时钟
	if((Uartx_Config.USARTn==USART1)||(Uartx_Config.USARTn==USART2)||(Uartx_Config.USARTn==USART3)){
		gpio_af_buf=GPIO_AF_USART2;
	}
	
	//复用为USART
	for(i_source=0;i_source<16;i_source++){
		if((pin_list_buf>>i_source)&0x0001){
			GPIO_PinAFConfig(Uartx_Config.GPIOn,i_source,gpio_af_buf); 				
		}
		if((pin_list_buf>>(i_source+1))==0)break;
	}
	GPIO_InitStructure.GPIO_Pin = pin_list_buf;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//GPIO_Mode_AF v1.8 GPIO_Mode_AF_PP v3.5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;			//复用推挽
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;				//上拉
	GPIO_Init(Uartx_Config.GPIOn, &GPIO_InitStructure);
	
	//配置串口的工作参数
	USART_InitStructure.USART_BaudRate = Uartx_Config.USARTn_BaudRate;
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
	USART_Init(Uartx_Config.USARTn, &USART_InitStructure);
	// 完成串口的初始化配置
	
	UART_NVIC_Config(Uartx_NVIC_Config.IT_Channel,Uartx_NVIC_Config.Pre_Priority,Uartx_NVIC_Config.Sub_Priority);
	// 串口中断优先级配置
	
	USART_ITConfig(Uartx_Config.USARTn, Uartx_NVIC_Config.UART_IT_MODE, ENABLE);	
	// 使能串口接收中断
	
	USART_Cmd(Uartx_Config.USARTn, ENABLE);		
	// 使能串口
	USART_ClearFlag(Uartx_Config.USARTn, USART_FLAG_TC); 
	// 清除发送完成标志	
}
void UART_ALL_Init(void){
	//=======================uart1==========================
	
	uart1_init.USARTn=USE_UART1;
	uart1_init.USARTn_BaudRate=115200;
	uart1_init.GPIOn=USART1_GPIO_PORT;
	uart1_init.GPIO_Pin=UART1_TX_PIN|UART1_RX_PIN;
	uart1_init.UART_GPIO_CLK=UART1_GPIO_CLOCK;
	uart1_init.UART_CLK=UART1_CLOCK;

	Uart_NVIC_TypeDef uart1_nvic_init;
	uart1_nvic_init.IT_Channel=UART1_IT_SOURCE;
	uart1_nvic_init.Pre_Priority=2;
	uart1_nvic_init.Sub_Priority=1;
	uart1_nvic_init.UART_IT_MODE=USART_IT_RXNE;
	//========================uart2=========================
	
	
	uart2_init.USARTn=USE_UART2;
	uart2_init.USARTn_BaudRate=9600;
	uart2_init.GPIOn=USART2_GPIO_PORT;
	uart2_init.GPIO_Pin=UART2_TX_PIN|UART2_RX_PIN;
	uart2_init.UART_GPIO_CLK=UART2_GPIO_CLOCK;
	uart2_init.UART_CLK=UART2_CLOCK;

	Uart_NVIC_TypeDef uart2_nvic_init;
	uart2_nvic_init.IT_Channel=USART2_IRQn;
	uart2_nvic_init.Pre_Priority=1;
	uart2_nvic_init.Sub_Priority=1;
	uart2_nvic_init.UART_IT_MODE=USART_IT_RXNE;
	//========================uart3=========================
	
	uart3_init.USARTn=USE_UART3;
	uart3_init.USARTn_BaudRate=115200;
	uart3_init.GPIOn=USART3_GPIO_PORT;
	uart3_init.GPIO_Pin=UART3_TX_PIN|UART3_RX_PIN;
	uart3_init.UART_GPIO_CLK=UART3_GPIO_CLOCK;
	uart3_init.UART_CLK=UART3_CLOCK;

#ifndef	STM32F410xx
	Uart_NVIC_TypeDef uart3_nvic_init;
	uart3_nvic_init.IT_Channel=USART3_IRQn;
	uart3_nvic_init.Pre_Priority=3;
	uart3_nvic_init.Sub_Priority=1;
	uart3_nvic_init.UART_IT_MODE=USART_IT_RXNE;
	USART_Config(uart3_init,uart3_nvic_init);
#endif
	USART_Config(uart2_init,uart2_nvic_init);
	
	
	USART_Config(uart1_init,uart1_nvic_init);
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

void USART2_DMA_SendByte(u8 *m_pSendBuf, u16 m_u16SendCnt)  
{    
	memset(aDST_Buffer,0,sizeof aDST_Buffer);	//清空这个数组的数据
	memcpy(aDST_Buffer, m_pSendBuf, m_u16SendCnt);	  
  USART_DMA_SendStart(DMA_STREAM_TX, m_u16SendCnt); //启动一次DMA传输  
	USART_DMACmd (USART2,USART_DMAReq_Tx ,ENABLE);	
}

#if USE_UART_DMA
void USART2_IRQHandler(void){
	uint8_t read_point;
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)
	{	
		DMA_Cmd(DMA_STREAM_RX,DISABLE);
		read_point=USART1->SR;
		read_point = USART_ReceiveData(USART2);
		DMA_ClearFlag(DMA_STREAM_RX,DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);
        DMA_SetCurrDataCounter(DMA_STREAM_RX, BUFFER_SIZE);  
        DMA_Cmd(DMA_STREAM_RX, ENABLE); //  这两行是重新设置DMA  让这个搬运工准备下一次的工作
		USART_ClearITPendingBit(USART2,USART_IT_IDLE); // 清除标志位
	}	
}

#else

void USART1_IRQHandler(void){
	//uint8_t read_point;
	if(USART_GetITStatus(USE_UART1,USART_IT_RXNE)!=RESET)
	{		
		uart1_callback=UART_RxCallback;
		uart1_callback(&uart1_init);
		/*
		read_point = USART_ReceiveData(USE_UART1);
		rt_kprintf("%c",read_point);   		//将接受到的数据发送 
		USART_ClearITPendingBit(USE_UART1,USART_IT_RXNE); // 清除标志位
		*/
	}	
}

void USART2_IRQHandler(void){
	//uint8_t read_point;
	if(USART_GetITStatus(USE_UART2,USART_IT_RXNE)!=RESET)
	{	
		uart2_callback=UART_RxCallback;
		uart2_callback(&uart2_init);
		/*
		read_point = USART_ReceiveData(USE_UART2);
		rt_kprintf("%c",read_point);   		//将接受到的数据发送 
		USART_ClearITPendingBit(USE_UART2,USART_IT_RXNE); // 清除标志位
		*/
	}	
}
void USART3_IRQHandler(void){
	//uint8_t read_point;
	if(USART_GetITStatus(USE_UART3,USART_IT_RXNE)!=RESET)
	{	
		uart3_callback=UART_RxCallback;
		uart3_callback(&uart3_init);
		/*
		read_point = USART_ReceiveData(USE_UART3);
		rt_kprintf("%c",read_point);   		//将接受到的数据发送 
		USART_ClearITPendingBit(USE_UART3,USART_IT_RXNE); // 清除标志位
		*/
	}	
}



#endif

__weak void UART_RxCallback(Uart_Config_TypeDef *uart){
									//什么都不做
}






