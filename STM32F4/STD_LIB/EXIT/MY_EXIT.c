
/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_EXIT.c
  * @author  Fourth Team -yanzong
  * @version	V0.0.1 基本初始化
  * @date    2020-10-20
  * @brief   EXIT 
  ******************************************************************************
  * @attention
  * 硬件平台:stm32f407zgt6
	* 基本外部中断，能用就行
  ******************************************************************************
  */


#include "MY_EXIT.h"

EXIT_Callback	GPIOE_Lin3_Callback;
EXIT_Callback	GPIOE_Lin5_Callback;


static void EXIT_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(Front_Limt_Switch_GPIO_Clk, ENABLE);//使能GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = Front_Limt_Switch_Pin|Back_Limt_Switch_Pin; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(Front_Limt_Switch_GPIO, &GPIO_InitStructure);//初始化GPIOE3,5
 
} 

void EXIT_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXIT_GPIO_Init(); //对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);//PE5 连接到中断线5
	
	
	/* 配置EXTI_Line3,5 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3 | EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;						//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;				//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//外部中断5
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}
__weak void EXIT_LineCallback(void){
									//什么都不做
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
		
		GPIOE_Lin3_Callback=EXIT_LineCallback;
		GPIOE_Lin3_Callback();
		EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}
//外部中断5服务程序
void EXTI9_5_IRQHandler(void)
{
		
		GPIOE_Lin5_Callback=EXIT_LineCallback;
		GPIOE_Lin5_Callback();
		EXTI_ClearITPendingBit(EXTI_Line5);
		//清除LINE5~9上的中断标志位  
	
}


