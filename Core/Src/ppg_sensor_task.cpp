/*
 * sensor_task.cpp
 *
 *  Created on: Dec 20, 2021
 *      Author: jan
 */





#include <main.h>
#include <cmsis_os.h>

#include "ppg_sensor_task.hpp"


extern "C"{
// https://github.com/lamik/MAX30102_STM32_HAL
#include "MAX30102.h"

}

int32_t HR, SPO2;
extern I2C_HandleTypeDef hi2c1;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == PPG_INT_Pin){
		Max30102_InterruptCallback();
	}
}


void start_sensor_task([[maybe_unused]] void *argument){


	// Turn on Sensor power supply rail
	HAL_GPIO_WritePin(EN_SENSOR_GPIO_Port, EN_SENSOR_Pin, GPIO_PIN_RESET);

	// Power secition start up
	osDelay(200);

	auto s = Max30102_Init(&hi2c1);




	for(;;){



		Max30102_Task();

		HR = Max30102_GetHeartRate();
		SPO2 = Max30102_GetSpO2Value();

		osDelay(10);

	}

}
