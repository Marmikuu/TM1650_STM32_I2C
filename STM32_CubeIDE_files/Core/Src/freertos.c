/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


//// Peripherals
#include "gpio.h"
#include "adc.h"
#include "i2c.h"
#include "usart.h"

#include <stdio.h>


//////  TM1650 library
#include "TM1650.h"

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
/* USER CODE BEGIN Variables */
	TM1650_HandleTypeDef htm1;



/* USER CODE END Variables */
/* Definitions for LED_task */
osThreadId_t LED_taskHandle;
const osThreadAttr_t LED_task_attributes = {
  .name = "LED_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TM1650_task */
osThreadId_t TM1650_taskHandle;
const osThreadAttr_t TM1650_task_attributes = {
  .name = "TM1650_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

int __io_putchar(int ch); /// printf


/* USER CODE END FunctionPrototypes */

void LED_task_init(void *argument);
void TM1650_task_init(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LED_task */
  LED_taskHandle = osThreadNew(LED_task_init, NULL, &LED_task_attributes);

  /* creation of TM1650_task */
  TM1650_taskHandle = osThreadNew(TM1650_task_init, NULL, &TM1650_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_LED_task_init */
/**
  * @brief  Function implementing the LED_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LED_task_init */
void LED_task_init(void *argument)
{
  /* USER CODE BEGIN LED_task_init */
  /* Infinite loop */
  for(;;)
  {


	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	osDelay(500);

  }
  /* USER CODE END LED_task_init */
}

/* USER CODE BEGIN Header_TM1650_task_init */
/**
* @brief Function implementing the TM1650_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TM1650_task_init */
void TM1650_task_init(void *argument)
{
  /* USER CODE BEGIN TM1650_task_init */

	//////////////// ADC //////////
	uint32_t ADC_value=0;

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start(&hadc1);


	////////////// Initialize TM1650 ///////////////




	////// DEMO - INIT
	//range values :  0 , 1 ,2 , 3 , 4
	/// RANGE_0, - positive integers in the range(0 , 9999)
	/// RANGE_1 - integers in the range(-999 , 999)
	/// RANGE_2, - positive and negative float numbers  (-99.9 , 99.9)
	/// RANGE_3, - positive and negative float numbers  (-9.99 , 9.99)
	// 	RANGE_4, - positive float numbers (0.0 , 999.9)


	TM1650_Init(&htm1, &hi2c1, 4, RANGE_0, ZEROS); /// RAW 12 bit ADC values are
												//// between 0 and 4095, so the RANGE0 is suitable

  /* Infinite loop */
  for(;;)
  {

	ADC_value = HAL_ADC_GetValue(&hadc1);
	float ADC_value_float = ((float)ADC_value);

	TM1650_show(&htm1, ADC_value_float);

	printf("Number: %.2f\r\n", ADC_value_float);
	osDelay(200);



  }
  /* USER CODE END TM1650_task_init */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
int __io_putchar(int ch)
{
  if (ch == '\n') {
    __io_putchar('\r');
  }
  HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
  return 1;
}
/* USER CODE END Application */

