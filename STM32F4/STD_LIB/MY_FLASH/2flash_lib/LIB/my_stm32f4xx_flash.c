#include "my_stm32f4xx_flash.h"
#include "stm32f4xx_flash.h"
#include "string.h"

#define SAVE_DATA_SIZE		8			//���ƺ����ݵ���󳤶�Ϊ8		һ��������16��  �ܹ����Դ�1K��




uint32_t address_log;					//��ǰ�ĵ�ַ

uint8_t save_name_buf[SAVE_DATA_SIZE];		//�����ݴ�

uint8_t save_data_buf[SAVE_DATA_SIZE];		//�����ݴ�

/*
		�ַ�������
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
		װ�벢�Ҳ���8��  ���������Ϊ0
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
		�ַ�������
*/
void my_strcpy(uint8_t *str1,uint8_t *str2){
		uint8_t i;
		for(i=0;i<SAVE_DATA_SIZE;i++){
				str1[i]=str2[i];
		}
}
/*
		����һ����
*/
uint32_t Flash_ReadWord(uint32_t addr){

		return *(uint32_t*)addr;
}
/*
		����ַת����Sector
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
		�������ܣ���ʼ��flash  ��ʱ��
		void

*/
void Init_Flash(uint8_t run_once){
		//����flash
		FLASH_Unlock();
		//����flash
		//FLASH_Lock();
		//������б�־
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
		//��ҳ����	
		if(run_once){
				
				FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3);				//��������3
				FLASH_ProgramWord(WRITE_START_ADDR3,0);	//д������2�ĳ�ʼ��ַ
		}
		address_log=(*(__IO uint8_t*)WRITE_START_ADDR3);						//������һ�εĵ�ַ
}


/*
		�������ܣ���flash��д������
		key_name:	����
		val:			ֵ
		size:			��ĸ��� ������50
		other:		����0 ����ַ0x0800 0000-0x0800 3FFF 		16KB
	
*/
void flash_save_data(uint8_t *key_name,uint8_t *val,uint8_t size){

		uint8_t  data_buf[SAVE_DATA_SIZE*2*10]={0};				//�涨�����ɴ�10������
		uint8_t  i=0;
		FLASH_Unlock();
		//������б�־
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		/**********д�������Լ�����************/
		//�ٰ��µ����ݴ��� ���Ҳ���8��
		my_strreset(save_name_buf,key_name);
		my_strreset(save_data_buf,val);
		//��֮ǰ�����ݶ������ݴ�����
//		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
//				data_buf[i]=Flash_ReadWord(WRITE_START_ADDR2+i);
//		}
		FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);	//��������2
		//��֮ǰ�����ݴ��뵽flash��
//		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
//				FLASH_ProgramByte(WRITE_START_ADDR2+i,data_buf[i]);
//		}
		for(i=0;i<SAVE_DATA_SIZE;i++){		//����������
				FLASH_ProgramByte(WRITE_START_ADDR2+address_log,save_name_buf[i]);
				address_log += 1;
		}
		for(i=0;i<SAVE_DATA_SIZE;i++){		//����������
				FLASH_ProgramByte(WRITE_START_ADDR2+address_log,save_data_buf[i]);
				address_log += 1;
		}
		/**********������3��������2�µĵ�ַ**********/
		FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3);				//��������3
		FLASH_ProgramByte(WRITE_START_ADDR3,address_log);
		FLASH_Lock();
}

/*
		�������ܣ���flash�ڶ�������
		key_name:	����
		val:			ֵ
		size:			��С
		����0 ��ʾ�Ҳ���

*/
uint8_t flash_get_data(uint8_t *key,uint8_t *val,uint8_t size){
		
		uint8_t i=0;
		uint8_t j=0;
		uint8_t k=0;
		uint8_t check_counter=0;		//��֤��ȼ���		7
		uint8_t  data_read_buf[SAVE_DATA_SIZE*2*10]={0};				//�涨�����ɴ�10������
		//��֮ǰ�����ݶ������ݴ������Ա㴦��
		for(i=0;i<SAVE_DATA_SIZE*2*size;i++){
				data_read_buf[i]=Flash_ReadWord(WRITE_START_ADDR2+i);
		}
		//��key���val���ֵ�ȷ��������ݴ�������ݴ� 
		my_strcpy(save_name_buf,key);
		
		//����һ��
		for(i=0;i<size;i++){
				//����һ��һ����
				if(data_read_buf[i*16]==save_name_buf[0]){		
						for(j=0;j<SAVE_DATA_SIZE;j++){
								if(save_name_buf[j]==data_read_buf[i*16+j]){
										check_counter++;
								}
						}
						if(check_counter==8){		//˵��һ��	��������
								for(k=0;k<SAVE_DATA_SIZE;k++){
										//�����i��ʾ�ڼ���
										save_data_buf[k]=Flash_ReadWord(WRITE_START_ADDR2+i*16+8+k);
								}
								my_strcpy(val,save_data_buf);	//�����ݸ�val
								break;											//�˳�ѭ��
						}else{									//˵����һ��
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
		//������б�־
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		//��������
		if(FLASH_EraseSector(GetSector(addr),VoltageRange_3)!=FLASH_COMPLETE){	//��������2
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

