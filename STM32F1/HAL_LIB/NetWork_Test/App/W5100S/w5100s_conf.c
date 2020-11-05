/**
******************************************************************************
* @file         w5100s_conf.c                                                                                              
* @version      V1.0                          
* @date         2018-06-18             
* @brief        配置MCU，移植w5100s程序需要修改的文件，配置w5100s的MAC和IP地址   
*        
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100s官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com   
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/

#include "stdio.h" 
#include "string.h"
#include "w5100s_conf.h"
#include "utility.h"
#include "w5100s.h"
#include "socket.h"
//#include "bsp_TiMbase.h"
//#include "bsp_flash.h"

extern TIM_HandleTypeDef htim2;

#include "DHCP.h"

CONFIG_MSG  ConfigMsg, RecvMsg;                             // 配置结构体

uint16 rxlen=0;
uint8 rxbuf[1024];

/*MAC地址首字节必须为偶数
  如果多块W5100s网络适配板在同一现场工作，请使用不同的MAC地址
*/
uint8 mac[6]={0x00,0x08,0xdc,0x22,0x33,0x33};

/*定义默认IP信息*/
uint8 local_ip[4] = {192,168,1,233};                        // 定义W5100s默认IP地址
uint8 subnet[4] = {255,255,255,0};                          // 定义W5100s默认子网掩码
uint8 gateway[4] = {192,168,1,1};                           // 定义W5100s默认网关
uint8 dns_server[4] = {114,114,114,114};                    // 定义W5100s默认DNS

uint16 local_port = 8080;                                   // 定义本地端口

/*定义远端IP信息*/
uint8  remote_ip[4] = {192,168,1,100};                      // 远端IP地址
uint16 remote_port = 8080;                                  // 远端端口号

/*IP配置方法选择，请自行选择*/
uint8  ip_from=IP_FROM_DEFINE;      

uint32 ms=0;                                                // 毫秒计数
__IO uint8_t    ntptimer = 0;                                        // NPT秒计数



/**
*@brief  配置W5100s的IP地址
*@param  无
*@return 无
*/
void set_w5100s_netinfo(void)
{
  volatile uint8 temp;
  // 复制定义的配置信息到配置结构体
  memcpy(ConfigMsg.mac, mac, 6);
  memcpy(ConfigMsg.lip,local_ip,4);
  memcpy(ConfigMsg.sub,subnet,4);
  memcpy(ConfigMsg.gw,gateway,4);
  memcpy(ConfigMsg.dns,dns_server,4);
#ifdef DEBUG_HTTP
/*仅在使用HTTP Server例程时生效，使用请检查"http_server.h"头文件的引用*/
  ReadFlashNBtye(0,&temp,1);
  if(temp != 255)
    ip_from = IP_FROM_FLASH;
  else
    ip_from = IP_FROM_DEFINE;
#endif
  switch(ip_from)
  {
    case IP_FROM_DEFINE:
      printf(" 使用定义的IP信息配置W5100S：\r\n");
      break;
      
    case IP_FROM_FLASH:
      printf(" 使用Flash内IP信息配置W5100S：\r\n");
//      ReadFlashNBtye(0,ConfigMsg.lip,12);
      break;
  }
  setSUBR(ConfigMsg.sub);
  setGAR(ConfigMsg.gw);
  setSIPR(ConfigMsg.lip);

  getSIPR (local_ip);      
  printf(" W5100S IP地址   : %d.%d.%d.%d\r\n", local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
  getSUBR(subnet);
  printf(" W5100S 子网掩码 : %d.%d.%d.%d\r\n", subnet[0],subnet[1],subnet[2],subnet[3]);
  getGAR(gateway);
  printf(" W5100S 网关     : %d.%d.%d.%d\r\n", gateway[0],gateway[1],gateway[2],gateway[3]);
}

/**
*@brief  配置W5100S的MAC地址
*@param  无
*@return 无
*/
void set_w5100s_mac(void)
{
  // 以下配置信息，根据需要选用  
  ConfigMsg.sw_ver[0]=FW_VER_HIGH;
  ConfigMsg.sw_ver[1]=FW_VER_LOW;  
  
  memcpy(ConfigMsg.mac, mac, 6);
  setSHAR(ConfigMsg.mac);
  getSHAR(mac);
  printf(" W5100S MAC地址  : %02x.%02x.%02x.%02x.%02x.%02x\r\n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}
  

/**
*@brief  W5100s复位设置函数
*@param  无
*@return 无
*/
void reset_w5100s(void)
{
  HAL_GPIO_WritePin(W5100S_RESET_GPIO,W5100S_RESET_PIN,GPIO_PIN_RESET);
  HAL_Delay(500);  
  HAL_GPIO_WritePin(W5100S_RESET_GPIO,W5100S_RESET_PIN,GPIO_PIN_SET);
  HAL_Delay(1500);  

}

/**
*@brief  STM32系统软复位函数
*@param  无
*@return 无
*/
void reboot(void)
{
  pFunction Jump_To_Application;
  uint32 JumpAddress;
  printf(" 系统重启中……\r\n");
  JumpAddress = *(__IO uint32_t*) (0x00000004);
  Jump_To_Application = (pFunction) JumpAddress;
  Jump_To_Application();
}

/**
*@brief  dhcp用到的定时器初始化
*@param  无
*@return 无
*/
void dhcp_timer_init(void)
{
  MX_TIM2_Init();                                 
}

/**
*@brief  ntp用到的定时器初始化
*@param  无
*@return 无
*/
void ntp_timer_init(void)
{
  MX_TIM2_Init();                                 
}

/**
*@brief  STM32定时器2初始化
*@param  无
*@return 无
*/
void timer2_init(void)
{
    HAL_TIM_Base_MspInit(&htim2);     //  TIM2 重新开时钟，开始计时
		HAL_TIM_Base_Start(&htim2);
}

/**
*@brief  定时器2中断函数
*@param  无
*@return 无
*/
void timer2_isr(void)
{
  ms++;  
  if(ms>=1000)
  {  
    ms=0;
    dhcp_time++;             // DHCP定时加1S
#ifndef __NTP_H__
    ntptimer++;              // NTP重试时间加1S
#endif
  }
}

/**
*@brief  检测物理层连接
*@param  无
*@return 无
*/
void PHY_check(void)
{
  uint8 PHY_connect=0;
  PHY_connect=0x01&getPHYStatus();
  if(PHY_connect==0)
  {
    printf(" \r\n 请检查网线是否连接?\r\n");
    PHY_connect = 0;
    do
    {
      close(PHY_connect++);
    }while(PHY_connect < 4);
    PHY_connect = 0;
    while(PHY_connect == 0) { 
      PHY_connect=0x01&getPHYStatus();  
      printf(" .");
      HAL_Delay(500);
    }
    printf(" \r\n");  
  }
}
/**
*@brief  读取PHY寄存器数据
*@param  无
*@return PHYSR寄存器数值
*/
uint8 getPHYStatus( void )
{
  return IINCHIP_READ(PHYSR);
}

/**
*@brief  设置4个socket收发缓存大小
*@param  tx_size:发送缓存；rx_size:接收缓存
*@return 无
//RX memory size register, R/W, default=0x55
//--------------------------------------------------------    S1      S0      Memory size
//  Socket3    |  Socket2    |  Socket1    |  Socket0    |    0       0           1KB
//-------------|-------------|-------------|-------------|    0       1           2KB
//S1       S0  |S1       S0  |S1       S0  |S1       S0  |    1       0           4KB
//--------------------------------------------------------    1       1           8KB
*/
void sysinit(uint8 tx_size,uint8 rx_size)
{
	IINCHIP_WRITE(RMSR,tx_size);
	IINCHIP_WRITE(TMSR,rx_size);
}
