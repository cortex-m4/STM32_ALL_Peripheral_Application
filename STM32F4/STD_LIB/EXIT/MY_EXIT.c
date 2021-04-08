
/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_EXIT.c
  * @author  Fourth Team -yanzong
  * @version	V0.0.1 ������ʼ��
  * @date    2020-10-20
  * @brief   EXIT 
  ******************************************************************************
  * @attention
  * Ӳ��ƽ̨:stm32f407zgt6
	* �����ⲿ�жϣ����þ���
  ******************************************************************************
  */


#include "MY_EXIT.h"

EXIT_Callback	GPIOE_Lin3_Callback;
EXIT_Callback	GPIOE_Lin5_Callback;


static void EXIT_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(Front_Limt_Switch_GPIO_Clk, ENABLE);//ʹ��GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = Front_Limt_Switch_Pin|Back_Limt_Switch_Pin; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Front_Limt_Switch_GPIO, &GPIO_InitStructure);//��ʼ��GPIOE3,5
 
} 

void EXIT_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXIT_GPIO_Init(); //��Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);//PE5 ���ӵ��ж���5
	
	
	/* ����EXTI_Line3,5 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3 | EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;						//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;				//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//�ⲿ�ж�5
  NVIC_Init(&NVIC_InitStructure);//����
	   
}
__weak void EXIT_LineCallback(void){
									//ʲô������
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
		
		GPIOE_Lin3_Callback=EXIT_LineCallback;
		GPIOE_Lin3_Callback();
		EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�5�������
void EXTI9_5_IRQHandler(void)
{
		
		GPIOE_Lin5_Callback=EXIT_LineCallback;
		GPIOE_Lin5_Callback();
		EXTI_ClearITPendingBit(EXTI_Line5);
		//���LINE5~9�ϵ��жϱ�־λ  
	
}


