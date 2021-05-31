/*
	*Author: //作者
	*Version: v1.0
	*Date: 2021/5/31
	*Description://按键驱动
	*History: 	2021/5/31 创建完成文件
*/
#include "lib_key.h"


#define WAIT_TIME		10

static uint8_t key_on_flag=0;		//按键按下标志位 0：没有按下  
static uint8_t key_on_counter=0;	//长按按键


uint8_t KeysCan(void){
	if((KEY1_IN==0)||(KEY2_IN==0)||(KEY3_IN==0)||(KEY4_IN==0)){
//		key_up_flag=0;
		key_on_flag=1;
		if(KEY1_IN==0){
			if(key_on_counter<0xff)key_on_counter++;
			key_on_flag=1;

		}else if(KEY2_IN==0){
			if(key_on_counter<0xff)key_on_counter++;
			key_on_flag=2;

		}else if(KEY3_IN==0){
			if(key_on_counter<0xff)key_on_counter++;
			key_on_flag=3;

		}else if(KEY4_IN==0){
			if(key_on_counter<0xff)key_on_counter++;
			key_on_flag=4;

		}
	}
	switch(key_on_flag){
		case 1:
			if(KEY1_IN){
				key_on_counter=0;
				key_on_flag=0;
				return KEY1_ON;
			}
			if(key_on_counter>WAIT_TIME){
				return KEY1_ON;
			}
			break;
		case 2:
			if(KEY2_IN){
				key_on_counter=0;
				key_on_flag=0;
				return KEY2_ON;
			}
			if(key_on_counter>WAIT_TIME){
				return KEY2_ON;
			}
			
		break;
		case 3:
			if(KEY3_IN){
				key_on_counter=0;
				key_on_flag=0;
				return KEY3_ON;
			}
			if(key_on_counter>WAIT_TIME){
				return KEY3_ON;
			}
			
		break;
		case 4:
			if(KEY4_IN){
				key_on_counter=0;
				key_on_flag=0;
				return KEY4_ON;
			}
			if(key_on_counter>WAIT_TIME){
				return KEY4_ON;
			}
		break;
		default:

			break;
	}
	return 0;
}



