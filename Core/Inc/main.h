/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define UART_radio huart2
#define I2C_sensors hi2c1
#define TRACE_MESSAGE_STRUCT TraceMessage_t
#define SPI_sensors hspi2
#define UART_trace huart1
#define RADIO_MESSAGE_STRUCT RadioMessage_t
#define BOARD_LED0_Pin GPIO_PIN_13
#define BOARD_LED0_GPIO_Port GPIOC
#define Exti_d0_BOARD_KEY0_Pin GPIO_PIN_0
#define Exti_d0_BOARD_KEY0_GPIO_Port GPIOA
#define Exti_d0_BOARD_KEY0_EXTI_IRQn EXTI0_IRQn
#define Exti_d1_Pin GPIO_PIN_1
#define Exti_d1_GPIO_Port GPIOA
#define Exti_d1_EXTI_IRQn EXTI1_IRQn
#define KBD_o0_Pin GPIO_PIN_2
#define KBD_o0_GPIO_Port GPIOB
#define KBD_i2_Pin GPIO_PIN_12
#define KBD_i2_GPIO_Port GPIOB
#define KBD_i3_Pin GPIO_PIN_13
#define KBD_i3_GPIO_Port GPIOB
#define Exti_d2_Pin GPIO_PIN_8
#define Exti_d2_GPIO_Port GPIOA
#define Exti_d2_EXTI_IRQn EXTI9_5_IRQn
#define KBD_i0_Pin GPIO_PIN_4
#define KBD_i0_GPIO_Port GPIOB
#define KBD_i1_Pin GPIO_PIN_5
#define KBD_i1_GPIO_Port GPIOB
#define KBD_o1_Pin GPIO_PIN_7
#define KBD_o1_GPIO_Port GPIOB
#define KBD_o2_Pin GPIO_PIN_8
#define KBD_o2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
