#ifndef	__MY_F4_FLASH_H__
#define __MY_F4_FLASH_H__

#include "main.h"
#include "string.h"

#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_5   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_5   /* End @ of user Flash area : sector start address + sector size -1 */


#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes Total 16kb*/
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes Total 32kb*/
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes Total 48kb*/
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes Total 64kb*/
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes Total 128kb*/
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes Total 256kb*/


#define ADDR_FLASH_SECTOR_6			((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes Total 384kb*/
#define ADDR_FLASH_SECTOR_7			((uint32_t)0x08060000) /* Base @ of Sector 6, 128 Kbytes Total 512kb*/
#define ADDR_FLASH_SECTOR_8			((uint32_t)0x08080000) /* Base @ of Sector 6, 128 Kbytes Total 640kb*/
#define ADDR_FLASH_SECTOR_9			((uint32_t)0x080A0000) /* Base @ of Sector 6, 128 Kbytes Total 768kb*/
#define ADDR_FLASH_SECTOR_10		((uint32_t)0x080C0000) /* Base @ of Sector 6, 128 Kbytes Total 896kb*/
#define ADDR_FLASH_SECTOR_11		((uint32_t)0x080E0000) /* Base @ of Sector 6, 128 Kbytes *Total 1024kb*/



#define GROUP_SIZE			15		//组的大小	

#define SAVE_DATA_SIZE	8			//名称和数据的最大长度为8		一组数据是16个  总共可以存1K组




void Flash_Test(void);
uint32_t GetSectorSize(uint32_t Sector);
uint32_t GetSector(uint32_t Address);
void Flash_WriteByte_Test(uint32_t addr,uint8_t dat);
uint8_t Flash_ReadByte(uint32_t addr);

uint8_t Flash_Write(uint32_t addr,uint32_t * buff,int word_size);
void Flash_Read(uint32_t addr, uint32_t * buff, uint16_t word_size);
uint8_t FLASH_EraseSector(uint32_t addr,uint32_t size);


void Flash_Save_Data(uint8_t *key_name,uint8_t *val,uint8_t size);
uint8_t Flash_Get_Data(uint8_t *key,uint8_t *val,uint8_t size);

#endif

