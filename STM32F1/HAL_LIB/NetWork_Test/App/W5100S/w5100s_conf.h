/**
******************************************************************************
* @file         w5100s_conf.h                                                                                              
* @version      V1.0                          
* @date         2018-06-18                      
* @brief        w5100s_conf.c的头文件      
*        
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100s官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com  
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/
#ifndef _W5100S_CONF_H_
#define _W5100S_CONF_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include "stdio.h"
#include "Type.h"
#include "tim.h"
#define __GNUC__

typedef  void (*pFunction)(void);

extern uint16 rxlen;
extern uint8  rxbuf[1024];

extern uint8  local_ip[4];                             // 定义W5100s默认IP地址
extern uint8  subnet[4];                               // 定义W5100s默认子网掩码
extern uint8  gateway[4];                              // 定义W5100s默认网关

extern uint8  remote_ip[4];                            // 远端IP地址
extern uint16 remote_port;                             // 远端端口号
extern uint16 local_port;                              // 定义本地端口

extern uint32 dhcp_time;                               // DHCP运行计数
extern __IO uint8_t    ntptimer;                                // NTP运行计数


#define TX_RX_MAX_BUF_SIZE      2048

#define IP_FROM_DEFINE          0                      // 使用初始定义的IP信息
#define IP_FROM_DHCP            1                      // 使用DHCP获取IP信息
#define IP_FROM_FLASH           2                      // 从FLASH中读取IP信息
    
#define FW_VER_HIGH             1
#define FW_VER_LOW              0

extern uint8 ip_from;                                  // 选择IP信息配置源


#define W5100S_RESET_GPIO		GPIOC
#define W5100S_RESET_PIN		GPIO_PIN_6


#pragma pack(1)
/*此结构体定义了W5100S可供配置的主要参数*/
typedef struct _CONFIG_MSG                      
{
  uint8 mac[6];            // MAC地址
  uint8 lip[4];            // local IP本地IP地址
  uint8 sub[4];            // 子网掩码
  uint8 gw[4];             // 网关  
  uint8 dns[4];            // DNS服务器地址
  uint8 rip[4];            // remote IP远程IP地址
  uint8 sw_ver[2];         // 软件版本号
}CONFIG_MSG;

#pragma pack()

extern CONFIG_MSG ConfigMsg;

/*MCU配置相关函数*/
void reboot(void);           

/*W5100S基本配置相关函数*/
void reset_break_gpio_init(void);
void reset_w5100s(void);           
void set_w5100s_netinfo(void);                 
void set_w5100s_mac(void);
void dhcp_timer_init(void);
void ntp_timer_init(void);
void timer2_init(void);
void timer2_isr(void);
uint8 getPHYStatus( void );
void PHY_check(void);
void sysinit(uint8 tx_size,uint8 rx_size);
#endif //_W5100S_CONF_H_
