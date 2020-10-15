#include "stdio.h"
#include "UART.h"
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
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 打开串口GPIO的时钟
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	// 打开串口外设的时钟

	GPIO_InitStructure.GPIO_Pin = UART2_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);
	// 将USART Tx的GPIO配置为推挽复用模式

	GPIO_InitStructure.GPIO_Pin = UART2_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);
	// 将USART Rx的GPIO配置为浮空输入模式
	
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
	USART_Init(USART2, &USART_InitStructure);
	// 完成串口的初始化配置
	
	UART_NVIC_Config();
	// 串口中断优先级配置
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
	// 使能串口接收中断
	
	USART_Cmd(USART2, ENABLE);		
	// 使能串口
	//USART_ClearFlag(USART1, USART_FLAG_TC); 
	// 清除发送完成标志	
}

//========无阻塞发送一个字符===================
void uart_send_data_nowait( USART_TypeDef * pUSARTx, uint8_t ch){
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
}

//========有阻塞发送字符=======================
void uart_send_data(USART_TypeDef *pUSARTx,uint8_t ch){
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	

}

//============发送字符串========================
void uart_send_string(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do{
		USART_SendData( pUSARTx, *(str + k) );
		k++;
  }while(*(str + k)!='\0');
	
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//=============发送一个16位数=====================
void uart_send_halfworld(USART_TypeDef * pUSARTx, uint16_t ch)
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


//重定向printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART2, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

//重定向scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART2);
}

void USART2_IRQHandler(void){
	uint8_t read_point;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{		
		read_point = USART_ReceiveData(USART2);
    uart_send_data(USART2,read_point);   		//将接受到的数据发送 
	}	
}



