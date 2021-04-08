#include "MY_GPIO.h"
#include "main.h"

void LED_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// 使能GPIOC端口时钟
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;					// IO管脚8
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;			// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// 根据设定参数初始化GPIO	

}













