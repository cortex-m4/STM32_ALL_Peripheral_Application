#ifndef	__BSP_SPI_H__
#define __BSP_SPI_H__
#include "stm32f1xx_hal.h"
#include "spi.h"
#include "gpio.h"


#define SPI_CS_GPIO		GPIOB
#define SPI_CS_PIN		GPIO_PIN_12

void cs_high(void);
void cs_low(void);
void spi_send_byte(uint8_t byte);
uint8_t spi_read_byte(void);

#endif
