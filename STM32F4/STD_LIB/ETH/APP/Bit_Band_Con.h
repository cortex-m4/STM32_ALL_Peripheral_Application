#ifndef		_BIT_BAND_CON_H__
#define 	_BIT_BAND_CON_H__

#include "stm32f4xx.h"
/*
		λ������,ʵ��51���Ƶ�GPIO���ƹ���
		����ʵ��˼��,�ο�<<CM4Ȩ��ָ��>>
		IO�ڲ����궨��
		λ������,ʵ��51���Ƶ�GPIO���ƹ���
		����ʵ��˼��,�ο�<<CM4Ȩ��ָ��>>
		IO�ڲ����궨��
		bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number �� 4)
		���У�
		�� bit_word_addr ������������н�ӳ�䵽Ŀ��λ���ֵĵ�ַ
		�� bit_band_base ��������������ʼ��ַ
		�� byte_offset ����Ŀ��λ����λ�������е��ֽڱ��
		�� bit_number ����Ŀ��λ��λλ�� (0-7)
		ʾ��
		����˵����ν� SRAM ��ַ 0x20000300 ���ֽڵ�λ 2 ӳ�䵽��������
		0x22006008 = 0x22000000 + (0x300*32) + (2*4)
		�Ե�ַ 0x22006008 ִ��д�����൱���� SRAM ��ַ 0x20000300 ���ֽڵ�λ 2 ִ�ж�-��
		��-д������
		�Ե�ַ 0x22006008 ִ�ж����������� SRAM ��ַ 0x20000300 ���ֽڵ�λ 2 ��ֵ�� 0x01
		��ʾλ��λ�� 0x00 ��ʾλ��λ����
		
		
*/
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814 AHB1   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014 

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020008  
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020008  
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020008  
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020008  
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40020008  
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40020008  
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40020008 AHB1 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����



#endif


