#include "MY_GPIO.h"

void Init_LED(){
		GPIO_InitTypeDef led_gpio_init;
		GPIO_CLK_ON;												
		led_gpio_init.Alternate=0;
		led_gpio_init.Mode=GPIO_MODE_OUTPUT_PP;
		led_gpio_init.Pin=GPIO_PIN_5;
		led_gpio_init.Pull=GPIO_PULLUP;
		led_gpio_init.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOA,&led_gpio_init);
}



