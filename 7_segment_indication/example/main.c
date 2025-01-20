/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "dinamic_led.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//создаём структуру в которой указываем к каким портам и пинам подключены сегменты индикатора
segments_t segments = {
  .port_seg_A = seg_A_GPIO_Port,
  .pin_seg_A = seg_A_Pin,
  .port_seg_B = seg_B_GPIO_Port,
  .pin_seg_B = seg_B_Pin,
  .port_seg_C = seg_C_GPIO_Port,
  .pin_seg_C = seg_C_Pin,
  .port_seg_D = seg_D_GPIO_Port,
  .pin_seg_D = seg_D_Pin,
  .port_seg_E = seg_E_GPIO_Port,
  .pin_seg_E = seg_E_Pin,
  .port_seg_F = seg_F_GPIO_Port,
  .pin_seg_F = seg_F_Pin,
  .port_seg_G = seg_G_GPIO_Port,
  .pin_seg_G = seg_G_Pin,
  .port_seg_Point = seg_DP_GPIO_Port,
  .pin_seg_Point = seg_DP_Pin,
};

indicator_t ind_H = { .port = ind_Hundred_GPIO_Port, .pin = ind_Hundred_Pin };
indicator_t ind_D = { .port = ind_Tens_GPIO_Port, .pin = ind_Tens_Pin };
indicator_t ind_E = { .port = ind_Edin_GPIO_Port, .pin = ind_Edin_Pin};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim11;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint16_t switch_seg = 0; //для переключения сегментов

uint16_t hundred = 'A'; //сотни
uint16_t tens = 'L'; //десятки
uint16_t edin = 'P'; //единицы



void HAL_TIM_PeriodElapsedCallback(const TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM11) {
    //этого можно не делать
    disable_indicator(&ind_H, 0); //гасим индикатор 1
    disable_indicator(&ind_D, 0); //гасим индикатор 2
    disable_indicator(&ind_E, 0); //гасим индикатор 3

    switch (switch_seg) { //перебираем индикаторы
      case 0:               //если очередь индикатора 1
        enable_indicator(&ind_H, 0);  //включаем индикатор 1
      disable_indicator(&ind_D, 0); //выключаем индикатор 2
      disable_indicator(&ind_E, 0); //выключаем индикатор 3
      write_code(hundred, &segments, POINT_OFF, OK); //выводим на сегменты число val1, точка выключена, тип индикатора общий катод
      break;
      case 1: //если очередь индикатора 2
        disable_indicator(&ind_H, 0); //выключаем индикатор 1
      enable_indicator(&ind_D, 0);  //включаем индикатор 2
      disable_indicator(&ind_E, 0); //выключаем индикатор 3
      write_code(tens, &segments, POINT_OFF, OK); //выводим на сегменты число val2, точка выключена, тип индикатора общий катод
      break;
      case 2: //если очередь индикатора 3
        disable_indicator(&ind_H, 0); //выключаем индикатор 1
      disable_indicator(&ind_D, 0); //выключаем индикатор 2
      enable_indicator(&ind_E, 0); //включаем индикатор 3
      write_code(edin, &segments, POINT_OFF, OK); //выводим на сегменты число val3, точка включена, тип индикатора общий катод
      break;
    }

    switch_seg++;
    if (switch_seg > 2) { //если дошли до 3 индикатора, то обнуляемся и снова
      switch_seg = 0;
    }
  }
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
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
  __HAL_TIM_CLEAR_FLAG(&htim11, TIM_SR_UIF);
  HAL_TIM_Base_Start_IT(&htim11); //запускаем таймер в режиме прерываний (в настройках не забываем включить прерывания)
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 15;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 10000;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, seg_A_Pin|seg_B_Pin|seg_C_Pin|seg_D_Pin
                          |seg_E_Pin|seg_F_Pin|seg_G_Pin|seg_DP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ind_Hundred_Pin|ind_Tens_Pin|ind_Edin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : seg_A_Pin seg_B_Pin seg_C_Pin seg_D_Pin
                           seg_E_Pin seg_F_Pin seg_G_Pin seg_DP_Pin */
  GPIO_InitStruct.Pin = seg_A_Pin|seg_B_Pin|seg_C_Pin|seg_D_Pin
                          |seg_E_Pin|seg_F_Pin|seg_G_Pin|seg_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ind_Hundred_Pin ind_Tens_Pin ind_Edin_Pin */
  GPIO_InitStruct.Pin = ind_Hundred_Pin|ind_Tens_Pin|ind_Edin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
