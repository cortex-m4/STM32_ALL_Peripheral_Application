/**
******************************************************************************
* @file         w5100s_conf.h                                                                                              
* @version      V1.0                          
* @date         2018-06-18                      
* @brief        w5100s_conf.c��ͷ�ļ�      
*        
* @company      ��������Ƽ����޹�˾
* @information  WIZnet W5100s�ٷ������̣�ȫ�̼���֧�֣��۸����ƴ�
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

extern uint8  local_ip[4];                             // ����W5100sĬ��IP��ַ
extern uint8  subnet[4];                               // ����W5100sĬ����������
extern uint8  gateway[4];                              // ����W5100sĬ������

extern uint8  remote_ip[4];                            // Զ��IP��ַ
extern uint16 remote_port;                             // Զ�˶˿ں�
extern uint16 local_port;                              // ���屾�ض˿�

extern uint32 dhcp_time;                               // DHCP���м���
extern __IO uint8_t    ntptimer;                                // NTP���м���


#define TX_RX_MAX_BUF_SIZE      2048

#define IP_FROM_DEFINE          0                      // ʹ�ó�ʼ�����IP��Ϣ
#define IP_FROM_DHCP            1                      // ʹ��DHCP��ȡIP��Ϣ
#define IP_FROM_FLASH           2                      // ��FLASH�ж�ȡIP��Ϣ
    
#define FW_VER_HIGH             1
#define FW_VER_LOW              0

extern uint8 ip_from;                                  // ѡ��IP��Ϣ����Դ


#define W5100S_RESET_GPIO		GPIOC
#define W5100S_RESET_PIN		GPIO_PIN_6


#pragma pack(1)
/*�˽ṹ�嶨����W5100S�ɹ����õ���Ҫ����*/
typedef struct _CONFIG_MSG                      
{
  uint8 mac[6];            // MAC��ַ
  uint8 lip[4];            // local IP����IP��ַ
  uint8 sub[4];            // ��������
  uint8 gw[4];             // ����  
  uint8 dns[4];            // DNS��������ַ
  uint8 rip[4];            // remote IPԶ��IP��ַ
  uint8 sw_ver[2];         // �����汾��
}CONFIG_MSG;

#pragma pack()

extern CONFIG_MSG ConfigMsg;

/*MCU������غ���*/
void reboot(void);           

/*W5100S����������غ���*/
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