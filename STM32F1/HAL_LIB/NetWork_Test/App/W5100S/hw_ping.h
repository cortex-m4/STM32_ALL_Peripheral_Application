/**
******************************************************************************
* @file         hw_ping.h                                         
* @version      V1.0                          
* @date         2018-06-18                 
* @brief        hw_ping.c的头文件        
*
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100S官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/
#ifndef _HW_PING_H_
#define _HW_PING_H_

#include "main.h"
#include "w5100s.h"
#include "usart.h"
#include "Type.h"

extern uint8 hw_ping_ip[4];
extern uint8 exti_flag;

void hw_ping_init(void);                   // 硬件PING初始化参数
void hw_ping(void);                        // 发送PING请求

void EXTI_GPIO_Init(void);                 // PING中断触发 外部中断配置

#endif
