
#include "MY_Systick.h"
#include "main.h"

static uint16_t fac_us=0;	//us延时倍乘数
static uint32_t	fac_ms=0;	//ms延时倍乘数

void Systick_Init(){

	/*
		SysTick_CLKSource_HCLK_Div8
		SysTick_CLKSource_HCLK
	*/
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	fac_us=SystemCoreClock/1000000;		//系统时钟的1/10	100
	fac_ms=fac_us*1000;
}
void Delay_us(uint32_t nus){
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	/*
	跳出循环条件：	1.关闭systick使能
					2.16位置一
	位16 COUNTFLAG R/W 0 计数完，该位置1，如果在上次读取本寄存器后，SysTick 已经计到了0，则该位为 1。
	位2 CLKSOURCE  R/W 0 时钟源选择位， 0=AHB/8， 1=处理器时钟 AHB
	位1 TICKINT    R/W 0 1=SysTick 倒数计数到 0 时产生 SysTick 异常请求， 0=数到 0 时无动作。
					也可以通过读取COUNTFLAG 标志位来确定计数器是否递减到0
	位0 ENABLE     R/W 0 SysTick 定时器的使能位
	*/
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	

}


void Delay_ms(uint32_t nms){
	/*
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器
	*/
	while(nms--){
		Delay_us(1000);
	}
}



