Describe:	
use save all stm32 peripheral application
include hal lib,std lib

All project structure(For std lib):
APP:	user's function feature code
Doc:	detail and describe
Pro:	keil generate some files
STM32Lib:hal lib or std lib
USER:	main.c and some basic C files

Hareware platform:
Cortex-m3:STM32F103ZETx
Cortex-m4:STM32F410RBTx
	 STM32F427ZI

=================================
Task:	Progress		Detail
ADC	O		ADC_DMA for STM32F1
CAN	X
DAC	X
EXTI	X
FLASH	X
GPIO	O
I2C	X
I2S	X
IWDG	X
RNG	X
RTC	X
SDIO	X
SPI	X
SysTick	O		no IT
TIM	O
	TIM_PWM_OUT	O
	TIM_PWM_IN	X	
	TIM_BASE_IT	X
	TIM_Encoder	X
USART	0		add DMA FOR STD LIB	
WWDG	X
=================================
O:complete
X:no edit
-:doing
