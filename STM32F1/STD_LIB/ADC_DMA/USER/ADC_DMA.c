#include "ADC_DMA.h"

uint16_t __IO ADC1_DMA_Data_Buf[ADC1_DMA_Data_Size];
//ADC1 DMA的初始化
void ADC1_DMA_Init(void){
	
		DMA_InitTypeDef DMA_InitStructure;
	
		DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Addr;
		//外设基地址
		DMA_InitStructure.DMA_BufferSize =ADC1_DMA_Data_Size;
		//传输数组的大小
		DMA_InitStructure.DMA_DIR =DMA_DIR_PeripheralSRC;
		//DMA传送方向
		DMA_InitStructure.DMA_M2M =DISABLE ;
		//内存到内存方向
		DMA_InitStructure.DMA_MemoryBaseAddr =(u32)ADC1_DMA_Data_Buf;
		//数组地址
		DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord;
		//内存数据单位
		DMA_InitStructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
		//内存自增
		DMA_InitStructure.DMA_Mode =DMA_Mode_Circular;
		//DMAmode
		DMA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_HalfWord;
		//传输数据单位
		DMA_InitStructure.DMA_PeripheralInc  =DMA_PeripheralInc_Disable;
		//外设地址不自增
		DMA_InitStructure.DMA_Priority =DMA_Priority_High;
		//传输优先级
		DMA_Init(DMA1_Channel1 ,&DMA_InitStructure);
		
		DMA_Cmd (DMA1_Channel1,ENABLE );
		ADC_DMACmd (ADC1,ENABLE );
	
}



