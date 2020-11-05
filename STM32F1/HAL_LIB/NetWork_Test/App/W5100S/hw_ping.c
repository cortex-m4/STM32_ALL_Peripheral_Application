/**
******************************************************************************
* @file         hw_ping.c                                         
* @version      V1.0                          
* @date         2018-06-18                 
* @brief        W5100S硬件主动PING功能           
*
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100S官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/

#include "hw_ping.h"
#include "w5100s.h"
#include "usart.h"
#include "Type.h"

uint8 hw_ping_ip[4] = {192,168,1,100};     // PING的IP
uint8 exti_flag = 0;                       // 中断发生标志
void hw_ping_init(void)
{
	setSLRTR(0x03E8);       // 重传超时时间设置：1000 * 100us
	setSLRCR(3);            // 重传次数设置：3次
  /* 使用中断时可开启该配置 */	
	setSLIMR(0x05);         // 中断开启 PING & TIMEOUT
	
	setPINGSEQR(0x03E8);    // 请求数据包序列号设置：1000
	setPINGIDR(0x0100);     // 请求数据包ID：100
}

void hw_ping(void)
{
	setSLPIPR(hw_ping_ip);  // 目标IP设置：PING对象IP
  setSLCR(0x01);				  // 发送PING请求
}



