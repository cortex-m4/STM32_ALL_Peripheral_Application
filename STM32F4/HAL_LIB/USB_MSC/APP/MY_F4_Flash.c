#include "MY_F4_Flash.h"
#define DATA_32                 ((uint32_t)0x12345678)



static FLASH_EraseInitTypeDef EraseInitStruct;

uint8_t address_log;											//存储扇区的偏移地址

uint8_t save_name_buf[SAVE_DATA_SIZE];		//名称暂存

uint8_t save_data_buf[SAVE_DATA_SIZE];		//数据暂存

uint32_t sector_size=0;

uint8_t log_buf[4]={0};

/**
  * @brief  Gets sector Size
  * @param  None
  * @retval The size of a given sector
  */
uint32_t GetSectorSize(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;

  if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) || (Sector == FLASH_SECTOR_3))
  {
    sectorsize = 16 * 1024;
  }
  else if(Sector == FLASH_SECTOR_4)
  {
    sectorsize = 64 * 1024;
  }
  else
  {
    sectorsize = 128 * 1024;
  }  
  return sectorsize;
}
/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
//   else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_5))*/
//  {
//    sector = FLASH_SECTOR_5;
//  }

  return sector;
}
void Flash_Test(void){
	
	uint32_t FirstSector = 0, NbOfSectors = 0, Address = 0;
	uint32_t SectorError = 0;
	__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;
	HAL_FLASH_Unlock();
	/* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
	/* Get the 1st sector to erase */
	FirstSector = GetSector(FLASH_USER_START_ADDR);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = GetSector(FLASH_USER_END_ADDR) - FirstSector + 1;
	/* Fill EraseInit structure*/
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector = FirstSector;
  EraseInitStruct.NbSectors = NbOfSectors;
  if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
  {
    /* 
      Error occurred while sector erase. 
      User can add here some code to deal with this error. 
      SectorError will contain the faulty sector and then to know the code error on this sector,
      user can call function 'HAL_FLASH_GetError()'
    */
    /*
      FLASH_ErrorTypeDef errorcode = HAL_FLASH_GetError();
    */
    Error_Handler();
  }
	/* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
	__HAL_FLASH_DATA_CACHE_DISABLE();
  __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

  __HAL_FLASH_DATA_CACHE_RESET();
  __HAL_FLASH_INSTRUCTION_CACHE_RESET();

  __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
  __HAL_FLASH_DATA_CACHE_ENABLE();
	/* Program the user Flash area word by word
	(area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  Address = FLASH_USER_START_ADDR;
	while (Address < FLASH_USER_END_ADDR)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, DATA_32) == HAL_OK)
    {
      Address = Address + 4;
    }
    else
    { 
      /* Error occurred while writing data in Flash memory. 
         User can add here some code to deal with this error */
      /*
        FLASH_ErrorTypeDef errorcode = HAL_FLASH_GetError();
      */
      Error_Handler();
    }
  }
	/* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock(); 
	/* Check if the programmed data is OK 
      MemoryProgramStatus = 0: data programmed correctly
      MemoryProgramStatus != 0: number of words not programmed correctly ******/
  Address = FLASH_USER_START_ADDR;
  MemoryProgramStatus = 0x0;
  
  while (Address < FLASH_USER_END_ADDR)
  {
    data32 = *(__IO uint32_t*)Address;

    if (data32 != DATA_32)
    {
      MemoryProgramStatus++;  
    }

    Address = Address + 4;
  }  

  /*Check if there is an issue to program data*/
  if (MemoryProgramStatus == 0)
  {
    /* No error detected. Switch on LED4*/
    printf("write and read data ok!\r\n");
  }
  else
  {
    /* Error detected. Switch on LED5*/
    Error_Handler();
  }
}
//==========================PORT==================================
#define FLASH_Lock()			HAL_FLASH_Lock()
#define FLASH_Unlock()			HAL_FLASH_Unlock()
#define FLASH_ClearFlag(n)		__HAL_FLASH_CLEAR_FLAG(n)
/*
	读出一个字
*/
uint32_t Flash_ReadWord(uint32_t addr){
	return *(uint32_t*)addr;
}
/*
	flash 写 word
*/
uint8_t Flash_Write(uint32_t addr,uint32_t * buff,int word_size){

	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	
	
	for(int i = 0; i < word_size; i++)	
	{
		
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + 4 * i, buff[i])==HAL_OK){
//			if((*(uint32_t*)addr)!=buff[i]){
//				return 0;
//			}
		}
	}
	HAL_FLASH_Lock();
	return 1;

	
}

/*
	flash 读 word
*/
void Flash_Read(uint32_t addr, uint32_t * buff, uint16_t word_size)
{
	for(int i =0; i < word_size; i++)
	{
		buff[i] = *(__IO uint32_t*)(addr + 4 * i);
	}
	return;
}
/*
	flash擦
	addr:地址
	size:大小 单位：byte
	return:0 失败 1成功
*/
uint8_t FLASH_EraseSector(uint32_t addr,uint32_t size){
	uint8_t result=0;
	uint32_t first_sector=GetSector(addr);
	uint32_t SectorError = 0;
	static uint32_t NbofSector;
	NbofSector=GetSector(addr+size-1)-first_sector+1;
	static FLASH_EraseInitTypeDef EraseInitStruct;
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	EraseInitStruct.TypeErase=FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.Sector=first_sector;
	EraseInitStruct.NbSectors=NbofSector;
	EraseInitStruct.VoltageRange=FLASH_VOLTAGE_RANGE_3;
	if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError)!=HAL_OK){
		result=0;
		goto __exit;
	}else{
		result=1;
	}
	__exit:
	HAL_FLASH_Lock();
	return result;

}
uint8_t Flash_ReadByte(uint32_t addr){
	uint32_t dat_buf;
	dat_buf=*(uint32_t*)addr;
	return (uint8_t)(dat_buf&0xff);
}

void FLASH_Program_Byte(uint32_t Address, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));
  
  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_BYTE;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint8_t*)Address = Data;
}
/*
	写数据测试，具有写一个word大小数据的能力
*/
void Flash_WriteByte_Test(uint32_t addr,uint8_t dat){
	
	
	uint8_t i=0;
	uint8_t now_data_len=0;
	
	now_data_len=((addr-FLASH_USER_START_ADDR)&0xff);
	
	for(i=0;i<4;i++){
		log_buf[i]=Flash_ReadByte(FLASH_USER_START_ADDR+i);
	}
	log_buf[now_data_len]=dat;

	uint16_t sector_buf;
	sector_buf=GetSector(addr);
	FLASH_Unlock();
	FLASH_EraseSector(sector_buf,1);
	
//	__HAL_FLASH_DATA_CACHE_DISABLE();
//  __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

//  __HAL_FLASH_DATA_CACHE_RESET();
//  __HAL_FLASH_INSTRUCTION_CACHE_RESET();

//  __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
//  __HAL_FLASH_DATA_CACHE_ENABLE();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);


	for(i=0;i<4;i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, FLASH_USER_START_ADDR+i, log_buf[i]);
	}
	FLASH_Lock();
}

//=========================USE=====================================
/*
		装入并且补齐8个  补齐的数据为0
*/
void my_strreset(uint8_t *str1,uint8_t *str2){
		uint8_t str2_len=0;
		uint8_t i=0;
		str2_len=strlen(str2);
		if(str2_len<SAVE_DATA_SIZE){
			for(i=0;i<SAVE_DATA_SIZE;i++){
				if(i<str2_len){
					str1[i]=str2[i];
				}else{
					str1[i]=0;
				}
			}
		}else{
			memcpy(str1,str2,SAVE_DATA_SIZE);
		}
}

void Flash_Save_Data(uint8_t *key_name,uint8_t *val,uint8_t size){

		uint8_t  data_buf[SAVE_DATA_SIZE*2*GROUP_SIZE]={0};				//最大可存16组数据
		uint8_t  i=0;
		uint8_t  j=0;
		uint8_t  k=0;
		uint8_t  same_flag=0;				//名字相同标志位   0 不同  1 相同
		uint8_t check_counter=0;		//验证相等计数		7
		uint16_t sector_num=0;
		sector_size=GetSectorSize(GetSector(FLASH_USER_START_ADDR));
		address_log=Flash_ReadWord(FLASH_USER_START_ADDR+sector_size);
		if(address_log==0xff)address_log=0;
		//将之前的数据读出到暂存器里
		for(i=0;i<address_log;i++){
				data_buf[i]=Flash_ReadWord(FLASH_USER_START_ADDR+i);
		}
		FLASH_Unlock();
		//清空所有标志
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		/**********写入名称以及数据************/
		//再把新的数据存入 并且补齐8个
		my_strreset(save_name_buf,key_name);
		my_strreset(save_data_buf,val);
		//*********检查是否重名***********
		for(i=0;i<size;i++){
			//发现一个一样的
			if(data_buf[i*16]==save_name_buf[0]){
					check_counter=0;
					for(j=0;j<SAVE_DATA_SIZE;j++){
							if(save_name_buf[j]==data_buf[i*16+j]){
									check_counter++;
							}
					}
					if(check_counter==SAVE_DATA_SIZE){		//说明一样	替换数据
							for(k=0;k<SAVE_DATA_SIZE;k++){
									data_buf[i*16+SAVE_DATA_SIZE+k]=save_data_buf[k];
							}
							same_flag=1;
					}else{
							same_flag=0;
					}
			}else{
					continue;
			}
		}
		sector_num=GetSector(FLASH_USER_START_ADDR);
		FLASH_EraseSector(sector_num,1);	//擦除扇区
		//将之前的数据存入到flash里
		for(i=0;i<address_log;i++){
				FLASH_Program_Byte(FLASH_USER_START_ADDR+i,data_buf[i]);
		}
		if(same_flag==0){
			for(i=0;i<SAVE_DATA_SIZE;i++){		//存下了名字
					FLASH_Program_Byte(FLASH_USER_START_ADDR+address_log,save_name_buf[i]);
					address_log += 1;
			}
			for(i=0;i<SAVE_DATA_SIZE;i++){		//存下了数据
					FLASH_Program_Byte(FLASH_USER_START_ADDR+address_log,save_data_buf[i]);
					address_log += 1;
			}
		}
		//已经存入了10组数据,就从头开始存
		if(address_log==16*size){					
				address_log=0;
		}
		/**********向下一个扇区存入该扇区的地址**********/
		FLASH_EraseSector(sector_num+1,1);				//擦除扇区4
		FLASH_Program_Byte(sector_num+1,address_log);
		FLASH_Lock();
}
/*
		函数功能：往flash内读出数据
		key_name:	名称
		val:			值
		size:			大小
		返回0 表示找不到

*/
uint8_t Flash_Get_Data(uint8_t *key,uint8_t *val,uint8_t size){
		
		uint8_t i=0;
		uint8_t j=0;
		uint8_t k=0;
		uint8_t check_counter=0;		//验证相等计数		7
		uint8_t  data_read_buf[SAVE_DATA_SIZE*2*GROUP_SIZE]={0};				//规定仅仅可存10组数据

		
		
		//将之前的数据读出到暂存器里以便处理
		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
				data_read_buf[i]=Flash_ReadWord(FLASH_USER_START_ADDR);
		}
		//将key里的val里的值先放入名称暂存和数据暂存 
		memcpy(save_name_buf,key,SAVE_DATA_SIZE);
		
		//搜索一下
		for(i=0;i<size;i++){
				//发现一个一样的
				if(data_read_buf[i*16]==save_name_buf[0]){
						check_counter=0;
						for(j=0;j<SAVE_DATA_SIZE;j++){
								if(save_name_buf[j]==data_read_buf[i*16+j]){
										check_counter++;
								}
						}
						if(check_counter==8){		//说明一样	读出数据
								for(k=0;k<SAVE_DATA_SIZE;k++){
										//这里的i表示第几组
										save_data_buf[k]=Flash_ReadWord(FLASH_USER_START_ADDR+i*16+8+k);
								}
								memcpy(val,save_data_buf,SAVE_DATA_SIZE);	//把数据给val
								break;											//退出循环
						}else{									//说明不一样
								if(i==size)return 0;
						}
				}
				if(i==size)return 0;
		}
		return 0;
}


