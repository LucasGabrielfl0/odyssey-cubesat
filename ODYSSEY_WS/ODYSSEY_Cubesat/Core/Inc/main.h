/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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
#define LED_Status_Pin GPIO_PIN_14
#define LED_Status_GPIO_Port GPIOC
#define LED_Fault_Pin GPIO_PIN_15
#define LED_Fault_GPIO_Port GPIOC
#define LORA_AUX_Pin GPIO_PIN_1
#define LORA_AUX_GPIO_Port GPIOA
#define LORA_TX_Pin GPIO_PIN_2
#define LORA_TX_GPIO_Port GPIOA
#define LORA_RX_Pin GPIO_PIN_3
#define LORA_RX_GPIO_Port GPIOA
#define LORA_M1_Pin GPIO_PIN_5
#define LORA_M1_GPIO_Port GPIOA
#define LORA_M0_Pin GPIO_PIN_6
#define LORA_M0_GPIO_Port GPIOA
#define ADC_Temp_Pin GPIO_PIN_0
#define ADC_Temp_GPIO_Port GPIOB
#define ADC_Vbat_Pin GPIO_PIN_1
#define ADC_Vbat_GPIO_Port GPIOB
#define MOTOR1_PWM1_Pin GPIO_PIN_13
#define MOTOR1_PWM1_GPIO_Port GPIOB
#define MOTOR1_PWM2_Pin GPIO_PIN_14
#define MOTOR1_PWM2_GPIO_Port GPIOB
#define MOTOR2_PWM1_Pin GPIO_PIN_10
#define MOTOR2_PWM1_GPIO_Port GPIOA
#define MOTOR2_PWM2_Pin GPIO_PIN_11
#define MOTOR2_PWM2_GPIO_Port GPIOA
#define BNO_SCL_Pin GPIO_PIN_8
#define BNO_SCL_GPIO_Port GPIOB
#define BNO_SDA_Pin GPIO_PIN_9
#define BNO_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
