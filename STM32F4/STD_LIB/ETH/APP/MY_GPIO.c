#include "MY_GPIO.h"
#include "main.h"

void LED_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// ʹ��GPIOC�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;					// IO�ܽ�8
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;			// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// �����趨������ʼ��GPIO	

}













