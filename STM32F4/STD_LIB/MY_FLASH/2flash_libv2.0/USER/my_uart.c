#include "my_uart.h"
#include "stdio.h"

void USART2_Config(void){
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef	UART_GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART1
	UART_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9��GPIOA10
	UART_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	UART_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	UART_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	UART_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&UART_GPIO_InitStructure); 				//��ʼ��PA2��PA3
	
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2,&USART_InitStructure);
	
//#if EN_USART1_RX	
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
// 
//	//Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//#endif
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	USART_ClearFlag(USART2, USART_FLAG_TC);
	
}


int fputc(int ch,FILE *f)
{
  USART_SendData(USART2,ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
  return ch;
}









