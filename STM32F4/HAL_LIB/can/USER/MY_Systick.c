#include "MY_Systick.h"

void Delay_ms(uint16_t nms) 
{
		uint32_t i;
		SysTick_Config(100000);
		for(i=0; i<nms; i++)
		{
			while( !((SysTick->CTRL) & (1<<16)) );
		}
		/* Ê§ÄÜsystick */
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Delay_us(uint32_t us)
{
    uint32_t J;
		SysTick_Config(100);						//·ÖÆµ16
		for(J=0; J<us; J++)
		{
			while( !((SysTick->CTRL) & (1<<16)) );
		}
		/* Ê§ÄÜsystick */
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}









