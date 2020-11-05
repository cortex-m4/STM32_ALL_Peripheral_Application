#include "bsp_spi.h"

extern SPI_HandleTypeDef hspi2;



void cs_high(void)
{
  HAL_GPIO_WritePin(SPI_CS_GPIO,SPI_CS_PIN,GPIO_PIN_SET);
}

void cs_low(void)
{
  HAL_GPIO_WritePin(SPI_CS_GPIO,SPI_CS_PIN,GPIO_PIN_RESET);
}

void spi_send_byte(uint8_t byte){
	uint8_t test;
	uint8_t *send_point=&byte;
	uint8_t *read_point=&test;
	HAL_SPI_TransmitReceive(&hspi2,send_point,read_point,1,0xffff);
}


uint8_t spi_read_byte(void){
	uint8_t test;
	uint8_t *send_point=&test;
	uint8_t *read_point;
	HAL_SPI_TransmitReceive(&hspi2,send_point,read_point,1,0xffff);
	return *read_point;
}
