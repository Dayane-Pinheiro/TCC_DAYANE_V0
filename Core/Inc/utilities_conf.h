/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    utilities_conf.h
  * @author  MCD Application Team
  * @brief   Header for configuration file to utilities
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
#ifndef __UTILITIES_CONF_H__
#define __UTILITIES_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_compiler.h"

/* definitions to be provided to "sequencer" utility */
#include "stm32_mem.h"
/* definition and callback for tiny_vsnprintf */
#include "stm32_tiny_vsnprintf.h"

/* enum number of task and priority*/
#include "utilities_def.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
#define VLEVEL_OFF    0  /*!< used to set UTIL_ADV_TRACE_SetVerboseLevel() (not as message param) */
#define VLEVEL_ALWAYS 0  /*!< used as message params, if this level is given
                              trace will be printed even when UTIL_ADV_TRACE_SetVerboseLevel(OFF) */
#define VLEVEL_L 1       /*!< just essential traces */
#define VLEVEL_M 2       /*!< functional traces */
#define VLEVEL_H 3       /*!< all traces */

#define TS_OFF 0         /*!< Log without TimeStamp */
#define TS_ON 1          /*!< Log with TimeStamp */

#define T_REG_OFF  0     /*!< Log without bitmask */

/* USER CODE BEGIN EC */

/* USER CODE END EC */
/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/******************************************************************************
  * common
  ******************************************************************************/
/**
  * @brief Memory placement macro
  */
#if defined(__CC_ARM)
#define UTIL_PLACE_IN_SECTION( __x__ )  __attribute__((section (__x__), zero_init))
#elif defined(__ICCARM__)
#define UTIL_PLACE_IN_SECTION( __x__ )  __attribute__((section (__x__)))
#else  /* __GNUC__ */
#define UTIL_PLACE_IN_SECTION( __x__ )  __attribute__((section (__x__)))
#endif /* __CC_ARM | __ICCARM__ | __GNUC__ */

/**
  * @brief Memory alignment macro
  */
#undef ALIGN
#ifdef WIN32
#define ALIGN(n)
#else
#define ALIGN(n)             __attribute__((aligned(n)))
#endif /* WIN32 */

/**
  * @brief macro used to initialize the critical section
  */
#define UTILS_INIT_CRITICAL_SECTION()

/**
  * @brief macro used to enter the critical section
  */
#define UTILS_ENTER_CRITICAL_SECTION() uint32_t primask_bit= __get_PRIMASK();\
  __disable_irq()

/**
  * @brief macro used to exit the critical section
  */
#define UTILS_EXIT_CRITICAL_SECTION()  __set_PRIMASK(primask_bit)
/******************************************************************************
  * sequencer
  ******************************************************************************/

/**
  * @brief default number of tasks configured in sequencer
  */
#define UTIL_SEQ_CONF_TASK_NBR    CFG_SEQ_Task_NBR

/**
  * @brief default value of priority task
  */

#define UTIL_SEQ_CONF_PRIO_NBR    CFG_SEQ_Prio_NBR

/**
  * @brief macro used to initialize the critical section
  */
#define UTIL_SEQ_INIT_CRITICAL_SECTION( )    UTILS_INIT_CRITICAL_SECTION()

/**
  * @brief macro used to enter the critical section
  */
#define UTIL_SEQ_ENTER_CRITICAL_SECTION( )   UTILS_ENTER_CRITICAL_SECTION()

/**
  * @brief macro used to exit the critical section
  */
#define UTIL_SEQ_EXIT_CRITICAL_SECTION( )    UTILS_EXIT_CRITICAL_SECTION()

/**
  * @brief Memset utilities interface to application
  */
#define UTIL_SEQ_MEMSET8( dest, value, size )   UTIL_MEM_set_8( dest, value, size )

/******************************************************************************
  * trace\advanced
  * the define option
  *    UTIL_ADV_TRACE_CONDITIONNAL shall be defined if you want use conditional function
  *    UTIL_ADV_TRACE_UNCHUNK_MODE shall be defined if you want use the unchunk mode
  *
  ******************************************************************************/

#define UTIL_ADV_TRACE_CONDITIONNAL                                                      /*!< not used */
#define UTIL_ADV_TRACE_UNCHUNK_MODE                                                      /*!< not used */
#define UTIL_ADV_TRACE_DEBUG(...)                                                        /*!< not used */
#define UTIL_ADV_TRACE_INIT_CRITICAL_SECTION( )    UTILS_INIT_CRITICAL_SECTION()         /*!< init the critical section in trace feature */
#define UTIL_ADV_TRACE_ENTER_CRITICAL_SECTION( )   UTILS_ENTER_CRITICAL_SECTION()        /*!< enter the critical section in trace feature */
#define UTIL_ADV_TRACE_EXIT_CRITICAL_SECTION( )    UTILS_EXIT_CRITICAL_SECTION()         /*!< exit the critical section in trace feature */
#define UTIL_ADV_TRACE_TMP_BUF_SIZE                (512U)                                /*!< default trace buffer size */
#define UTIL_ADV_TRACE_TMP_MAX_TIMESTMAP_SIZE      (15U)                                 /*!< default trace timestamp size */
#define UTIL_ADV_TRACE_FIFO_SIZE                   (1024U)                               /*!< default trace fifo size */
#define UTIL_ADV_TRACE_MEMSET8( dest, value, size) UTIL_MEM_set_8((dest),(value),(size)) /*!< memset utilities interface to trace feature */
#define UTIL_ADV_TRACE_VSNPRINTF(...)              tiny_vsnprintf_like(__VA_ARGS__)      /*!< vsnprintf utilities interface to trace feature */

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*__UTILITIES_CONF_H__ */
