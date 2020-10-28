#include "MY_GPIO.h"
#include "main.h"

void LED_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		// 使能GPIOC端口时钟
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		// 使能GPIOC端口时钟
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;					// IO管脚8
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;			// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);						// 根据设定参数初始化GPIO	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);						// 根据设定参数初始化GPIO	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// 根据设定参数初始化GPIO

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// 根据设定参数初始化GPIO		
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// 根据设定参数初始化GPIO		
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// 根据设定参数初始化GPIO		

}













