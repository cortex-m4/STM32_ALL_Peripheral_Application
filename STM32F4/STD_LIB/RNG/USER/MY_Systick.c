
#include "MY_Systick.h"
#include "main.h"

static uint16_t fac_us=0;	//us��ʱ������
static uint32_t	fac_ms=0;	//ms��ʱ������

void Systick_Init(){

	/*
		SysTick_CLKSource_HCLK_Div8
		SysTick_CLKSource_HCLK
	*/
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	fac_us=SystemCoreClock/1000000;		//ϵͳʱ�ӵ�1/10	100
	fac_ms=fac_us*1000;
}
void Delay_us(uint32_t nus){
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	/*
	����ѭ��������	1.�ر�systickʹ��
					2.16λ��һ
	λ16 COUNTFLAG R/W 0 �����꣬��λ��1��������ϴζ�ȡ���Ĵ�����SysTick �Ѿ��Ƶ���0�����λΪ 1��
	λ2 CLKSOURCE  R/W 0 ʱ��Դѡ��λ�� 0=AHB/8�� 1=������ʱ�� AHB
	λ1 TICKINT    R/W 0 1=SysTick ���������� 0 ʱ���� SysTick �쳣���� 0=���� 0 ʱ�޶�����
					Ҳ����ͨ����ȡCOUNTFLAG ��־λ��ȷ���������Ƿ�ݼ���0
	λ0 ENABLE     R/W 0 SysTick ��ʱ����ʹ��λ
	*/
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	

}


void Delay_ms(uint32_t nms){
	/*
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����
	*/
	while(nms--){
		Delay_us(1000);
	}
}



