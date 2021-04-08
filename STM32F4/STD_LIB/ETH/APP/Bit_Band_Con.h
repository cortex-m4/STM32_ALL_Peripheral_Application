#ifndef		_BIT_BAND_CON_H__
#define 	_BIT_BAND_CON_H__

#include "stm32f4xx.h"
/*
		位带操作,实现51类似的GPIO控制功能
		具体实现思想,参考<<CM4权威指南>>
		IO口操作宏定义
		位带操作,实现51类似的GPIO控制功能
		具体实现思想,参考<<CM4权威指南>>
		IO口操作宏定义
		bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number × 4)
		其中：
		— bit_word_addr 代表别名区域中将映射到目标位的字的地址
		— bit_band_base 代表别名区域的起始地址
		— byte_offset 代表目标位所在位段区域中的字节编号
		— bit_number 代表目标位的位位置 (0-7)
		示例
		下例说明如何将 SRAM 地址 0x20000300 处字节的位 2 映射到别名区域：
		0x22006008 = 0x22000000 + (0x300*32) + (2*4)
		对地址 0x22006008 执行写操作相当于在 SRAM 地址 0x20000300 处字节的位 2 执行读-修
		改-写操作。
		对地址 0x22006008 执行读操作将返回 SRAM 地址 0x20000300 处字节的位 2 的值（ 0x01
		表示位置位， 0x00 表示位复位）。
		
		
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
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入



#endif


