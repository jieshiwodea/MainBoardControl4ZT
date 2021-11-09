/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SAMPLE_CHANNEL_NUM 3
#define SAMPLE_PER_CHANNEL 50
#define Laser_Fiber_En_Pin GPIO_PIN_2
#define Laser_Fiber_En_GPIO_Port GPIOE
#define AOM1_En_Pin GPIO_PIN_3
#define AOM1_En_GPIO_Port GPIOE
#define AOM2_En_Pin GPIO_PIN_4
#define AOM2_En_GPIO_Port GPIOE
#define Charge_Test_Pin GPIO_PIN_5
#define Charge_Test_GPIO_Port GPIOE
#define Battery_Voltage_ADC1_CH10_Pin GPIO_PIN_0
#define Battery_Voltage_ADC1_CH10_GPIO_Port GPIOC
#define RSSI1_ADC1_CH12_Pin GPIO_PIN_2
#define RSSI1_ADC1_CH12_GPIO_Port GPIOC
#define M1_RS422_A_Pin GPIO_PIN_0
#define M1_RS422_A_GPIO_Port GPIOA
#define M1_RS422_B_Pin GPIO_PIN_1
#define M1_RS422_B_GPIO_Port GPIOA
#define M2_ADC3_CH3_AWD_Pin GPIO_PIN_3
#define M2_ADC3_CH3_AWD_GPIO_Port GPIOA
#define NTC_ADC1_CH4_Pin GPIO_PIN_4
#define NTC_ADC1_CH4_GPIO_Port GPIOA
#define Stepper_LR_Sleep_Pin GPIO_PIN_7
#define Stepper_LR_Sleep_GPIO_Port GPIOA
#define Sleep2_Pin GPIO_PIN_4
#define Sleep2_GPIO_Port GPIOC
#define M1_ADC2_CH8_AWD_Pin GPIO_PIN_0
#define M1_ADC2_CH8_AWD_GPIO_Port GPIOB
#define Sleep1_Pin GPIO_PIN_7
#define Sleep1_GPIO_Port GPIOE
#define M1_PWM_OUT__Pin GPIO_PIN_8
#define M1_PWM_OUT__GPIO_Port GPIOE
#define M1_PWM_OUT_E9_Pin GPIO_PIN_9
#define M1_PWM_OUT_E9_GPIO_Port GPIOE
#define M2_PWM_OUT__Pin GPIO_PIN_10
#define M2_PWM_OUT__GPIO_Port GPIOE
#define M2_PWM_OUT_E11_Pin GPIO_PIN_11
#define M2_PWM_OUT_E11_GPIO_Port GPIOE
#define M_Protect_OUT__Pin GPIO_PIN_12
#define M_Protect_OUT__GPIO_Port GPIOE
#define M_Protect_OUT_E13_Pin GPIO_PIN_13
#define M_Protect_OUT_E13_GPIO_Port GPIOE
#define LR_Limit_Switch_Pin GPIO_PIN_12
#define LR_Limit_Switch_GPIO_Port GPIOB
#define LR_Limit_Switch_EXTI_IRQn EXTI15_10_IRQn
#define UD_Limit_Switch_Pin GPIO_PIN_13
#define UD_Limit_Switch_GPIO_Port GPIOB
#define UD_Limit_Switch_EXTI_IRQn EXTI15_10_IRQn
#define Ceju_UART3_TX_Pin GPIO_PIN_8
#define Ceju_UART3_TX_GPIO_Port GPIOD
#define Ceju_UART3_RX_Pin GPIO_PIN_9
#define Ceju_UART3_RX_GPIO_Port GPIOD
#define Stepper_LR_Dir_Pin GPIO_PIN_11
#define Stepper_LR_Dir_GPIO_Port GPIOD
#define Stepper_Protect_Sleep_Pin GPIO_PIN_12
#define Stepper_Protect_Sleep_GPIO_Port GPIOD
#define Stepper_UD_Sleep_Pin GPIO_PIN_13
#define Stepper_UD_Sleep_GPIO_Port GPIOD
#define Stepper_Up_Dir_Pin GPIO_PIN_14
#define Stepper_Up_Dir_GPIO_Port GPIOD
#define Stepper_Protect_Dir_Pin GPIO_PIN_15
#define Stepper_Protect_Dir_GPIO_Port GPIOD
#define Stepper_UD_Step_Pin GPIO_PIN_7
#define Stepper_UD_Step_GPIO_Port GPIOC
#define Jetson_UART1_TX_Pin GPIO_PIN_9
#define Jetson_UART1_TX_GPIO_Port GPIOA
#define Jetson_UART1_RX_Pin GPIO_PIN_10
#define Jetson_UART1_RX_GPIO_Port GPIOA
#define Stepper_LR_Step_Pin GPIO_PIN_15
#define Stepper_LR_Step_GPIO_Port GPIOA
#define Fiber_UART4_TX_Pin GPIO_PIN_10
#define Fiber_UART4_TX_GPIO_Port GPIOC
#define Fiber_UART4_RX_Pin GPIO_PIN_11
#define Fiber_UART4_RX_GPIO_Port GPIOC
#define TestPin_Pin GPIO_PIN_5
#define TestPin_GPIO_Port GPIOD
#define M62429_D_Pin GPIO_PIN_6
#define M62429_D_GPIO_Port GPIOD
#define M62429_CLK_Pin GPIO_PIN_7
#define M62429_CLK_GPIO_Port GPIOD
#define M2_RS422_B_Pin GPIO_PIN_4
#define M2_RS422_B_GPIO_Port GPIOB
#define M2_RS422_A_Pin GPIO_PIN_5
#define M2_RS422_A_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
