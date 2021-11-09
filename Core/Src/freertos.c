/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "drv_uart.h"
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

/* USER CODE END Variables */
osThreadId InitTaskHandle;
osThreadId CommunicateTaskHandle;
osThreadId LensTaskHandle;
osThreadId CmdTaskHandle;
osTimerId once_timerHandle;
osMutexId uploadMutexHandle;
osMutexId packMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void init_task(void const * argument);
extern void communicate_task(void const * argument);
extern void lens_task(void const * argument);
extern void system_cmd_task(void const * argument);
extern void stop_protect_motor(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of uploadMutex */
  osMutexDef(uploadMutex);
  uploadMutexHandle = osMutexCreate(osMutex(uploadMutex));

  /* definition and creation of packMutex */
  osMutexDef(packMutex);
  packMutexHandle = osMutexCreate(osMutex(packMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of once_timer */
  osTimerDef(once_timer, stop_protect_motor);
  once_timerHandle = osTimerCreate(osTimer(once_timer), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of InitTask */
  osThreadDef(InitTask, init_task, osPriorityNormal, 0, 128);
  InitTaskHandle = osThreadCreate(osThread(InitTask), NULL);

  /* definition and creation of CommunicateTask */
  osThreadDef(CommunicateTask, communicate_task, osPriorityRealtime, 0, 256);
  CommunicateTaskHandle = osThreadCreate(osThread(CommunicateTask), NULL);

  /* definition and creation of LensTask */
  osThreadDef(LensTask, lens_task, osPriorityRealtime, 0, 512);
  LensTaskHandle = osThreadCreate(osThread(LensTask), NULL);

  /* definition and creation of CmdTask */
  osThreadDef(CmdTask, system_cmd_task, osPriorityRealtime, 0, 512);
  CmdTaskHandle = osThreadCreate(osThread(CmdTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osThreadSuspend(LensTaskHandle);

  taskEXIT_CRITICAL();
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_init_task */
/**
  * @brief  Function implementing the InitTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_init_task */
__weak void init_task(void const * argument)
{
    
    
    
    
    

  /* USER CODE BEGIN init_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END init_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
