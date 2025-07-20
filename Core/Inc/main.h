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
#include "stm32wlxx_hal.h"

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
void MX_DMA_Init(void);
void MX_RTC_Init(void);
void MX_SUBGHZ_Init(void);
void MX_USART2_UART_Init(void);
void MX_ADC_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)
#define RTC_N_PREDIV_S 10
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define LED3_Pin GPIO_PIN_10
#define LED3_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_4
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOA
#define SR04_TRIGGER_Pin GPIO_PIN_9
#define SR04_TRIGGER_GPIO_Port GPIOA
#define SR04_ECHO_Pin GPIO_PIN_12
#define SR04_ECHO_GPIO_Port GPIOB
#define SW_I2C_SCL_Pin GPIO_PIN_1
#define SW_I2C_SCL_GPIO_Port GPIOB
#define BAT_DRIVE_Pin GPIO_PIN_10
#define BAT_DRIVE_GPIO_Port GPIOA
#define REED_SWITCH_Pin GPIO_PIN_12
#define REED_SWITCH_GPIO_Port GPIOA
#define REED_SWITCH_EXTI_IRQn EXTI15_10_IRQn
#define SW_I2C_SDA_Pin GPIO_PIN_7
#define SW_I2C_SDA_GPIO_Port GPIOB
#define INT1_Pin GPIO_PIN_4
#define INT1_GPIO_Port GPIOB
#define INT1_EXTI_IRQn EXTI4_IRQn
#define INT2_Pin GPIO_PIN_5
#define INT2_GPIO_Port GPIOB
#define INT2_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
