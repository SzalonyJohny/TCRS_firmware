/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOA
#define DISPLAY_CS_Pin GPIO_PIN_4
#define DISPLAY_CS_GPIO_Port GPIOA
#define SD_CARD_CMD_Pin GPIO_PIN_6
#define SD_CARD_CMD_GPIO_Port GPIOA
#define DISPLAY_COMAND_Pin GPIO_PIN_0
#define DISPLAY_COMAND_GPIO_Port GPIOB
#define DISPLAY_RESET_Pin GPIO_PIN_1
#define DISPLAY_RESET_GPIO_Port GPIOB
#define DISPLAY_BACKLIGHT_Pin GPIO_PIN_2
#define DISPLAY_BACKLIGHT_GPIO_Port GPIOB
#define EN_1V8_Pin GPIO_PIN_12
#define EN_1V8_GPIO_Port GPIOB
#define SD_CARD_CK_Pin GPIO_PIN_15
#define SD_CARD_CK_GPIO_Port GPIOB
#define SD_CARD_D1_Pin GPIO_PIN_8
#define SD_CARD_D1_GPIO_Port GPIOA
#define SD_CARD_D2_Pin GPIO_PIN_9
#define SD_CARD_D2_GPIO_Port GPIOA
#define SD_CARD_D0_Pin GPIO_PIN_4
#define SD_CARD_D0_GPIO_Port GPIOB
#define SD_CARD_D3_Pin GPIO_PIN_5
#define SD_CARD_D3_GPIO_Port GPIOB
#define EN_SENSOR_Pin GPIO_PIN_6
#define EN_SENSOR_GPIO_Port GPIOB
#define PPG_INT_Pin GPIO_PIN_7
#define PPG_INT_GPIO_Port GPIOB
#define PPG_INT_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
