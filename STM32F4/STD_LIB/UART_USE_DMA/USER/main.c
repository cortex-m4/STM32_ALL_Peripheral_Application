/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


extern uint8_t read_point;

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
//修改DMA UART 传送的数据
void Modify_UART_DATA(uint8_t *data){
	uint8_t i;
	memset(aDST_Buffer,0,sizeof aDST_Buffer);	//清空这个数组的数据
	for(i=0;i<strlen(data);i++){
		aDST_Buffer[i]=*data++;
	}
}





/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	
	Systick_Init();
	
	LED_GPIO_Init();
	
	UART_ALL_Init();		//串口初始化
	
	Delay_ms(100);
	printf("\n\rDMA UART Test\r\n");
	DMA_Config();
	
	Delay_ms(100);
    //填充要发送的数据
//	for(i=0;i<BUFFER_SIZE;i++){
//		aDST_Buffer[i]='a';
//	}
	//串口向DMA发出请求
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
	/* Infinite loop */
	while (1)
	{
		
		USART2_DMA_SendByte("\r\nhello,world\r\n",15);
		
		Delay_ms(1000);
		
		USART2_DMA_SendByte("\r\nni,hao\r\n",10);
		
		Delay_ms(1000);
		USART2_DMA_SendByte(Uart2_RxBuff,strlen(Uart2_RxBuff));

		Delay_ms(1000);
	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
