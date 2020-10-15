#include "MY_ADC.h"


//ADC1 GPIO的初始化
static void ADC1_GPIO_Config(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1 ,ENABLE );
		//开启DMA1时钟
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC ,ENABLE );
		//开启GPIOC和ADC1的时钟
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
		//模拟输入模式
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}
//ADC1 的初始化
void ADC1_Config(void){
		
		ADC_InitTypeDef ADC_InitStructure;
		
		ADC1_GPIO_Config();		//ADC1 GPIO 初始化
	
		ADC_InitStructure.ADC_ContinuousConvMode =ENABLE ;
		//连续转换模式，不停的进行ADC转换
		ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right ;
		//通道数据右对齐
		ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None ;
		//不使用外部触发
		ADC_InitStructure.ADC_Mode=ADC_Mode_Independent ;
		//独立ADC模式
		ADC_InitStructure.ADC_NbrOfChannel=1;
		//要转换的通道数目1
		ADC_InitStructure.ADC_ScanConvMode =DISABLE ;
		//不使用扫描模式,扫描模式是多通道ADC使用的
		ADC_Init(ADC1,&ADC_InitStructure);
		
		RCC_ADCCLKConfig (RCC_PCLK2_Div8 );
		//配置ADC时钟，为8分频   9MHZ
		ADC_RegularChannelConfig (ADC1,ADC_Channel_11 ,1,ADC_SampleTime_55Cycles5 );
		//配置ADC1的通道为11为55.5个采样周期
		ADC_Cmd (ADC1,ENABLE );
		ADC_ResetCalibration (ADC1);
		//复位校准寄存器
		while(ADC_GetResetCalibrationStatus (ADC1));
		//等待校准寄存器复位完成
		ADC_SoftwareStartConvCmd (ADC1,ENABLE);

}







