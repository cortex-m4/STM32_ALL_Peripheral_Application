#include "my_stm32f4xx_flash.h"
#include "stm32f4xx_gpio.h"
#include "string.h"
#include "my_uart.h"
#include "stdio.h"
//0x31 0xcf 0x5a 0x74 0x0a 0x11 0x31 0xcf 0x5a 0x74
#define LED_GPIO_PORT    	GPIOA		              /* GPIO端口 */
#define LED_GPIO_CLK 	    RCC_AHB1Periph_GPIOA		/* GPIO端口时钟 */
#define LED_GPIO_PIN			GPIO_Pin_5		

#define SAVE_DATA_SIZE		8
static uint8_t test_buf[10]={0x31,0xcf,0x5a,0x74,0x0a,0x11,0x31,0xcf,0x5a,0x74};

uint8_t write_buf[SAVE_DATA_SIZE]={1,2,3,4,5,6,7,8};		//名称暂存

uint8_t data_buf[SAVE_DATA_SIZE];		//数据暂存

void delay_ms(uint16_t n){
		uint16_t i,j;
		for(i=n;i>0;i--){
				for(j=10000;j>0;j--);
		}
}
void LED_GPIO_Config(void)
{		

		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd(LED_GPIO_CLK , ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
		
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	
		GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}
int main(void){
		uint8_t i;
		USART2_Config();
		LED_GPIO_Config();
		Init_Flash(1);		
		flash_save_data("hello123",write_buf,10);
		delay_ms(100);
		flash_get_data("hello123",data_buf,10);
		delay_ms(100);
	
//--------------------------------------------------------------
//		FLASH_Unlock();
//		delay_ms(10);
//		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
//		delay_ms(10);
//		FLASH_EraseSector(FLASH_Sector_4,VoltageRange_3);				//擦除扇区3
//		delay_ms(10);
//		FLASH_ProgramByte(WRITE_START_ADDR4,0xcc);	//写入扇区4一个东西
//------------------------------测试字符串读写--------------------------------
//		USART_SendData(USART2,'c');
//		flash_write_str(WRITE_START_ADDR2,"hello123",8);
//		flash_write_str(WRITE_START_ADDR2+8,write_buf,8);
//		delay_ms(100);
//		flash_read_str(WRITE_START_ADDR4,data_buf,8);
//		delay_ms(100);
		while(1){
//					if(0xcc==(*(__IO uint8_t*)WRITE_START_ADDR4)){
//							GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
//					}
				
//				if(strcmp(data_buf,write_buf)==0){
//						GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
//				}
				for(i=0;i<8;i++){
						printf("%d,",data_buf[i]);
				}
				printf("\n");
				delay_ms(200);
				//GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		}


}


