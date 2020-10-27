/*
	版本号：v1.0
	描述	：基于导航控制板的LED
*/
#include "LED.h"

void LED_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(LED_GPIO_CLK, ENABLE);		// 使能LED端口时钟
	GPIO_InitStructure.GPIO_Pin   = LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN;// IO管脚
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;					// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// IO口速度为50MHz
	GPIO_Init(LED_GPIO_Port, &GPIO_InitStructure);									// 根据设定参数初始化GPIO	
		
	LED1(1);LED2(1);LED3(1);LED4(1);
	
}



