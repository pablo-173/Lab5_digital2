/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile uint8_t dato;
int IniciarCarrera=0;
int J1=0;
int J2=0;
int ContadorJugador1=0;
int ContadorJugador2=0;
uint8_t dec[5][4]={
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,1,0,0},
  {1,0,0,0}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void J_1(int valor);
void J_2(int valor);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, (uint8_t*)&dato,1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (IniciarCarrera==1){
		  HAL_GPIO_WritePin(D3_ledV_GPIO_Port, D3_ledV_Pin, 1);
		  HAL_GPIO_WritePin(D4_ledA_GPIO_Port, D4_ledA_Pin, 0);
		  HAL_GPIO_WritePin(D5_ledR_GPIO_Port, D5_ledR_Pin, 0);
		  HAL_Delay(1000);
		  HAL_GPIO_WritePin(D3_ledV_GPIO_Port, D3_ledV_Pin, 0);
		  HAL_GPIO_WritePin(D4_ledA_GPIO_Port, D4_ledA_Pin, 1);
		  HAL_GPIO_WritePin(D5_ledR_GPIO_Port, D5_ledR_Pin, 0);
		  HAL_Delay(1000);
		  HAL_GPIO_WritePin(D3_ledV_GPIO_Port, D3_ledV_Pin, 0);
		  HAL_GPIO_WritePin(D4_ledA_GPIO_Port, D4_ledA_Pin, 0);
		  HAL_GPIO_WritePin(D5_ledR_GPIO_Port, D5_ledR_Pin, 1);
		  HAL_Delay(1000);
		  HAL_GPIO_WritePin(D5_ledR_GPIO_Port, D5_ledR_Pin, 0);
		  J1=1;
		  J2=1;
		  IniciarCarrera=2;
	  }
	  J_1(ContadorJugador1);
	  J_2(ContadorJugador2);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D11_led2_2_Pin|D7_led2_1_Pin|D8_led3_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D6_led1_1_Pin|D3_ledV_Pin|D5_ledR_Pin|D4_ledA_Pin
                          |D10_led1_2_Pin|D15_led4_2_Pin|D14_led3_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D9_led4_1_GPIO_Port, D9_led4_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BT2_Pin BT1_Pin */
  GPIO_InitStruct.Pin = BT2_Pin|BT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D11_led2_2_Pin D7_led2_1_Pin D8_led3_1_Pin */
  GPIO_InitStruct.Pin = D11_led2_2_Pin|D7_led2_1_Pin|D8_led3_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D6_led1_1_Pin D3_ledV_Pin D5_ledR_Pin D4_ledA_Pin
                           D10_led1_2_Pin D15_led4_2_Pin D14_led3_2_Pin */
  GPIO_InitStruct.Pin = D6_led1_1_Pin|D3_ledV_Pin|D5_ledR_Pin|D4_ledA_Pin
                          |D10_led1_2_Pin|D15_led4_2_Pin|D14_led3_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : D9_led4_1_Pin */
  GPIO_InitStruct.Pin = D9_led4_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D9_led4_1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance==USART2 && IniciarCarrera==0){
		if (dato=='s' || dato=='S'){
			IniciarCarrera=1;


		}
		HAL_UART_Receive_IT(&huart2, (uint8_t*)&dato,1);
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t  GPIO_Pin){
	if (GPIO_Pin==BT1_Pin && J1==1){
			ContadorJugador1++;
			if (ContadorJugador1==5){
				ContadorJugador1=0;
				ContadorJugador2=0;
				IniciarCarrera=0;
				J1=0;
				J2=0;
				uint8_t TEST[]="\n\ Ganador jugador 1\r\n";
				HAL_UART_Transmit(&huart2,TEST, sizeof(TEST),1000);
		}

	}
	if(GPIO_Pin==BT2_Pin && J2==1){
		ContadorJugador2++;
		if (ContadorJugador2==5){
			ContadorJugador1=0;
			ContadorJugador2=0;
			IniciarCarrera=0;
			J1=0;
			J2=0;
			uint8_t TEST[]="\n\Ganador jugador 2\r\n";
			HAL_UART_Transmit(&huart2,TEST, sizeof(TEST),1000);
		}

			}
	}

void J_1(int valor){
		HAL_GPIO_WritePin(D6_led1_1_GPIO_Port, D6_led1_1_Pin, dec[valor][0]);
		HAL_GPIO_WritePin(D7_led2_1_GPIO_Port, D7_led2_1_Pin, dec[valor][1]);
		HAL_GPIO_WritePin(D8_led3_1_GPIO_Port, D8_led3_1_Pin, dec[valor][2]);
		HAL_GPIO_WritePin(D9_led4_1_GPIO_Port, D9_led4_1_Pin, dec[valor][3]);
}
void J_2(int valor){
	HAL_GPIO_WritePin(D10_led1_2_GPIO_Port, D10_led1_2_Pin, dec[valor][0]);
	HAL_GPIO_WritePin(D11_led2_2_GPIO_Port, D11_led2_2_Pin, dec[valor][1]);
	HAL_GPIO_WritePin(D14_led3_2_GPIO_Port, D14_led3_2_Pin, dec[valor][2]);
	HAL_GPIO_WritePin(D15_led4_2_GPIO_Port, D15_led4_2_Pin, dec[valor][3]);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
