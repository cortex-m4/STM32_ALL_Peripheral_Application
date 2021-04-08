#ifndef		__MY_STM32F4XX_FLASH_H__
#define		__MY_STM32F4XX_FLASH_H__
#include "stm32f4xx.h"

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define WRITE_START_ADDR2 ((uint32_t)0x08008000)			//扇区2	开始地址		存储所有 共16KB
#define WRITE_END_ADDR2 	((uint32_t)0x0800BFFF)			//扇区2	结束地址

#define WRITE_START_ADDR3 ((uint32_t)0x0800C000)			//扇区3	开始地址		存储上次的地址
#define WRITE_END_ADDR3 	((uint32_t)0x0800FFFF)			//扇区3	结束地址

#define WRITE_START_ADDR4 ((uint32_t)0x08010000)			//扇区4	开始地址		存储
#define WRITE_END_ADDR4 	((uint32_t)0x0800FFFF)			//扇区4	结束地址

#define WRITE_START_ADDR5 ((uint32_t)0x08020000)			//扇区5	开始地址		存储
#define WRITE_END_ADDR5 	((uint32_t)0x0803FFFF)			//扇区5	结束地址
typedef enum 
{
	FAILED = 0, 
  PASSED = !FAILED
} TestStatus;


//typedef enum 
//{
//		SMALL = 0xff;				//8-bit				256个
//		MEDIUM =0xffff;			//16-bits			65536个
//		MEDIUM =0xffffffff;	//32-bit			
//}SAVE_DATA_SIZE;			//允许储存空间的大小

void my_strcpy(uint8_t *str1,uint8_t *str2);
uint8_t  my_strlen(uint8_t *str1);
void my_strreset(uint8_t *str1,uint8_t *str2);
uint32_t Flash_ReadWord(uint32_t addr);
uint32_t GetSector(uint32_t Address);


void Init_Flash(uint8_t run_once);
void flash_save_data(uint8_t *key_name,uint8_t *val,uint8_t size);
uint8_t flash_get_data(uint8_t *key,uint8_t *val,uint8_t size);

void flash_write_str(uint32_t addr,uint8_t *strw,uint8_t size);
void flash_read_str(uint32_t addr,uint8_t *strr,uint8_t size);

#endif


