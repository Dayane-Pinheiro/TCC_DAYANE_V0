/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    platform.h
  * @author  MCD Application Team
  * @brief   Header for General HW instances configuration
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
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Exported constants --------------------------------------------------------*/

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32wlxx.h"
#include "main.h"
#include "stm32wlxx_ll_gpio.h"
#if defined(USE_BSP_DRIVER)
/* code generated by STM32CubeMX does not support BSP.  */
/* In order to use BSP, users can add the BSP files in the IDE project space */
/* and define USE_BSP_DRIVER in the preprocessor definitions  */
/* #include "b_wl5m_subg_radio.h" */
/* #include "b_wl5m_subg.h" */    /* not used by this project*/
#endif /* defined(USE_BSP_DRIVER) */

/* USER CODE BEGIN include */

/* USER CODE END include */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H__ */
