#include "my_stm32f4xx_flash.h"
#include "stm32f4xx_flash.h"
#include "string.h"

#define SAVE_DATA_SIZE		8			//名称和数据的最大长度为8		一组数据是16个  总共可以存1K组




uint32_t address_log;					//当前的地址

uint8_t save_name_buf[SAVE_DATA_SIZE];		//名称暂存

uint8_t save_data_buf[SAVE_DATA_SIZE];		//数据暂存

/*
		字符串长度
*/
uint8_t  my_strlen(uint8_t *str1){
		uint8_t i=0;
		while(1){
				if((str1[i])=='\0')break;
				i++;
		}
		return i;
}
/*
		装入并且补齐8个  补齐的数据为0
*/
void my_strreset(uint8_t *str1,uint8_t *str2){
		uint8_t str2_len=0;
		uint8_t i=0;
		str2_len=my_strlen(str2);
		if(str2_len<8){
				for(i;i<SAVE_DATA_SIZE;i++){
						if(i<str2_len)str1[i]=str2[i];
						else		str1[i]=0;
				}
		}else{
				my_strcpy(str1,str2);
		}
}
/*
		字符串拷贝
*/
void my_strcpy(uint8_t *str1,uint8_t *str2){
		uint8_t i;
		for(i=0;i<SAVE_DATA_SIZE;i++){
				str1[i]=str2[i];
		}
}
/*
		读出一个字
*/
uint32_t Flash_ReadWord(uint32_t addr){

		return *(uint32_t*)addr;
}
/*
		将地址转换成Sector
*/
uint32_t GetSector(uint32_t Address){
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }

  return sector;
}

/*
		函数功能：初始化flash  开时钟
		void

*/
void Init_Flash(uint8_t run_once){
		//解锁flash
		FLASH_Unlock();
		//锁定flash
		//FLASH_Lock();
		//清空所有标志
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
		//按页擦除	
		if(run_once){
				
				FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3);				//擦除扇区3
				FLASH_ProgramWord(WRITE_START_ADDR3,0);	//写入扇区2的初始地址
		}
		address_log=(*(__IO uint8_t*)WRITE_START_ADDR3);						//读出上一次的地址
}


/*
		函数功能：往flash内写入数据
		key_name:	名称
		val:			值
		size:			组的个数 不超过50
		other:		扇区0 基地址0x0800 0000-0x0800 3FFF 		16KB
	
*/
void flash_save_data(uint8_t *key_name,uint8_t *val,uint8_t size){

		uint8_t  data_buf[SAVE_DATA_SIZE*2*10]={0};				//规定仅仅可存10组数据
		uint8_t  i=0;
		FLASH_Unlock();
		//清空所有标志
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		/**********写入名称以及数据************/
		//再把新的数据存入 并且补齐8个
		my_strreset(save_name_buf,key_name);
		my_strreset(save_data_buf,val);
		//将之前的数据读出到暂存器里
//		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
//				data_buf[i]=Flash_ReadWord(WRITE_START_ADDR2+i);
//		}
		FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);	//擦除扇区2
		//将之前的数据存入到flash里
//		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
//				FLASH_ProgramByte(WRITE_START_ADDR2+i,data_buf[i]);
//		}
		for(i=0;i<SAVE_DATA_SIZE;i++){		//存下了名字
				FLASH_ProgramByte(WRITE_START_ADDR2+address_log,save_name_buf[i]);
				address_log += 1;
		}
		for(i=0;i<SAVE_DATA_SIZE;i++){		//存下了数据
				FLASH_ProgramByte(WRITE_START_ADDR2+address_log,save_data_buf[i]);
				address_log += 1;
		}
		/**********向扇区3存入扇区2新的地址**********/
		FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3);				//擦除扇区3
		FLASH_ProgramByte(WRITE_START_ADDR3,address_log);
		FLASH_Lock();
}

/*
		函数功能：往flash内读出数据
		key_name:	名称
		val:			值
		size:			大小
		返回0 表示找不到

*/
uint8_t flash_get_data(uint8_t *key,uint8_t *val,uint8_t size){
		
		uint8_t i=0;
		uint8_t j=0;
		uint8_t k=0;
		uint8_t check_counter=0;		//验证相等计数		7
		uint8_t  data_read_buf[SAVE_DATA_SIZE*2*10]={0};				//规定仅仅可存10组数据
		//将之前的数据读出到暂存器里以便处理
		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
				data_read_buf[i]=Flash_ReadWord(WRITE_START_ADDR2+i);
		}
		//将key里的val里的值先放入名称暂存和数据暂存 
		my_strcpy(save_name_buf,key);
		
		//搜索一下
		for(i=0;i<size;i++){
				//发现一个一样的
				if(data_read_buf[i*16]==save_name_buf[0]){		
						for(j=0;j<SAVE_DATA_SIZE;j++){
								if(save_name_buf[j]==data_read_buf[i*16+j]){
										check_counter++;
								}
						}
						if(check_counter==8){		//说明一样	读出数据
								for(k=0;k<SAVE_DATA_SIZE;k++){
										//这里的i表示第几组
										save_data_buf[k]=Flash_ReadWord(WRITE_START_ADDR2+i*16+8+k);
								}
								my_strcpy(val,save_data_buf);	//把数据给val
								break;											//退出循环
						}else{									//说明不一样
								if(i==9)return 0;
						}
				}
				if(i==9)return 0;
		}
		
}
/*
		test_fun
*/
void flash_write_str(uint32_t addr,uint8_t *strw,uint8_t size){
		uint8_t i;
		uint8_t j;
		uint32_t add;
		add=addr;
		j=0;
		FLASH_Unlock();
		//清空所有标志
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		//擦除数据
		if(FLASH_EraseSector(GetSector(addr),VoltageRange_3)!=FLASH_COMPLETE){	//擦除扇区2
				while(1);
		}
		for(i=0;i<size*1;i+=1){
				FLASH_ProgramByte(add,strw[j]);
				j++;
				add=add+1;
		}
		FLASH_Lock();
}
/*
		test_fun
*/
void flash_read_str(uint32_t addr,uint8_t *strr,uint8_t size){
		uint8_t i,j;
		uint32_t add;
		add=addr;
		j=0;
		for(i=0;i<size*1;i+=1){
				strr[j++]=Flash_ReadWord(add);
				add+=1;
		}
}

