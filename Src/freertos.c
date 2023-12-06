/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stdio.h"
#include "mpu6050.h"
#include "car_task.h"
#include "inv_mpu.h"
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
int task_flag = 0;
float Encoder = 0;
float Encoder_Integral = 0;
/* USER CODE END Variables */
osThreadId Task_200HZHandle;
osThreadId Task_100HZHandle;
osThreadId Task_5HZHandle;
osThreadId Task_InteractioHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask_200HZ(void const * argument);
void StartTask_100HZ(void const * argument);
void StartTask_5HZ(void const * argument);
void StartTask_Interaction(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* definition and creation of Task_200HZ */
  osThreadDef(Task_200HZ, StartTask_200HZ, osPriorityNormal, 0, 128);
  Task_200HZHandle = osThreadCreate(osThread(Task_200HZ), NULL);

  /* definition and creation of Task_100HZ */
  osThreadDef(Task_100HZ, StartTask_100HZ, osPriorityIdle, 0, 128);
  Task_100HZHandle = osThreadCreate(osThread(Task_100HZ), NULL);

  /* definition and creation of Task_5HZ */
  osThreadDef(Task_5HZ, StartTask_5HZ, osPriorityIdle, 0, 128);
  Task_5HZHandle = osThreadCreate(osThread(Task_5HZ), NULL);

  /* definition and creation of Task_Interactio */
  osThreadDef(Task_Interactio, StartTask_Interaction, osPriorityIdle, 0, 128);
  Task_InteractioHandle = osThreadCreate(osThread(Task_Interactio), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTask_200HZ */
/**
  * @brief  Function implementing the Task_200HZ thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask_200HZ */
void StartTask_200HZ(void const * argument)
{
  /* USER CODE BEGIN StartTask_200HZ */
  vTaskSuspendAll() ;
//	printf("Environment Task Running\n");
	

	while(mpu_dmp_init()){}; // waiting for environment task finish
//	printf("MPU Initialization\n");
	task_flag = 1;

	
  /* Infinite loop */
//	printf("200HZ Task Running\n");
	xTaskResumeAll() ;

  for(;;)
  {

		Car_Task_200HZ();
    osDelay(5);
  }
  /* USER CODE END StartTask_200HZ */
}

/* USER CODE BEGIN Header_StartTask_100HZ */
/**
* @brief Function implementing the Task_100HZ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_100HZ */
void StartTask_100HZ(void const * argument)
{
  /* USER CODE BEGIN StartTask_100HZ */
  /* Infinite loop */
//	printf("100HZ task running\n");
  for(;;)
  {	
    // 将 Encoder，Encoder_Least的指针传入下面的函数
 		Car_Task_100HZ();
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osDelay(10);
  }
  /* USER CODE END StartTask_100HZ */
}

/* USER CODE BEGIN Header_StartTask_5HZ */
/**
* @brief Function implementing the Task_5HZ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_5HZ */
void StartTask_5HZ(void const * argument)
{
  /* USER CODE BEGIN StartTask_5HZ */

  /* Infinite loop */
  for(;;)
  {
//		Car_Task_5HZ();
//    osDelay(100);
  }
  /* USER CODE END StartTask_5HZ */
}

/* USER CODE BEGIN Header_StartTask_Interaction */
/**
* @brief Function implementing the Task_Interactio thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Interaction */
void StartTask_Interaction(void const * argument)
{
  /* USER CODE BEGIN StartTask_Interaction */
  /* Infinite loop */
  for(;;)
  {
		Car_Task_Interaction();
    osDelay(200);
  }
  /* USER CODE END StartTask_Interaction */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

