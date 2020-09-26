/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define len(string) strlen(string)
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxbuffer[1];
uint8_t rxbuffer_index_uart1=0;
uint8_t rxbuffer_uart1[128];

uint8_t rxbuffer_espressif[1];
uint8_t rxbuffer_espressif_index=0;
uint8_t rxbuffer_espressif_uart3[128];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void exec(uint8_t *message){
	HAL_UART_Transmit(&huart1, "LED ON/OFF\n", 11, 128);
	
	uint8_t len = strlen(message);
	//LED 0 on
	if(message[4] == '0'){
		if(strstr(message+6, "on") != NULL){
			HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_RESET);
		}else{
			HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_SET);
		}
		
	}else{
		if(strstr(message+6, "on") != NULL){
			HAL_GPIO_WritePin(GPIOG, LED3_Pin, GPIO_PIN_RESET);
		}else{
			HAL_GPIO_WritePin(GPIOG, LED3_Pin, GPIO_PIN_SET);
		}
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t cmd[128] = {"AT\r\n"};
	HAL_UART_Transmit(&huart3, cmd, strlen(cmd),128);
	
  if(huart->Instance == USART1){
    rxbuffer_uart1[rxbuffer_index_uart1++] = *rxbuffer;
	
    if(*rxbuffer == '\n'){
			HAL_UART_Transmit(&huart1, "uart1:", 6, 128);
			
      rxbuffer_uart1[rxbuffer_index_uart1] = '\0';
      rxbuffer_index_uart1 = 0;
      HAL_UART_Transmit(&huart1, rxbuffer_uart1, len(rxbuffer_uart1), 128);
			if(strstr(rxbuffer_uart1, "led") != NULL){
				exec(rxbuffer_uart1);
			}
			
    }
		
		HAL_UART_Receive_IT(&huart1, (uint8_t *)rxbuffer, 1);
  }else if(huart->Instance == USART3){
		HAL_UART_Transmit(&huart1, "\nesp:", 6, 128);
		HAL_UART_Receive_IT(&huart3, (uint8_t *)rxbuffer, 1);
	}
	else{
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOF, LED1_Pin);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOF, LED0_Pin | LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, LED2_Pin | LED3_Pin, GPIO_PIN_SET);
	
	HAL_TIM_Base_Start_IT(&htim2);

  HAL_UART_Receive_IT(&huart1, (uint8_t *)rxbuffer, 1);
	HAL_UART_Receive_IT(&huart3, (uint8_t *)rxbuffer_espressif, 1);
	
	uint8_t message[128] = {"This is for every one!\r\n"};
	HAL_UART_Transmit(&huart1, message, strlen(message),128);
	
	uint8_t cmd[128] = {"AT\r\n"};
	HAL_UART_Transmit(&huart3, cmd, strlen(cmd),128);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_GPIO_TogglePin(GPIOF, LED0_Pin);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOF, LED0_Pin);
		HAL_Delay(800);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
