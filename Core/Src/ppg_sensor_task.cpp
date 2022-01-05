/*
 * sensor_task.cpp
 *
 *  Created on: Dec 20, 2021
 *      Author: jan
 */

#include <main.h>
#include <cmsis_os.h>
#include "ppg_sensor_task.hpp"
#include "helper_func.hpp"

// MAX3010
extern I2C_HandleTypeDef hi2c1;

extern "C"{
// https://github.com/lamik/MAX30102_STM32_HAL
#include "MAX30102.h"
extern volatile uint32_t IrBuffer[MAX30102_BUFFER_LENGTH]; //IR LED sensor data
extern volatile uint32_t RedBuffer[MAX30102_BUFFER_LENGTH];    //Red LED sensor data
extern volatile uint32_t BufferHead;
extern volatile uint32_t BufferTail;
}


uint32_t IRv, REDv;



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(PPG_INT_Pin == GPIO_Pin){
		Max30102_InterruptCallback();
	}
}


void start_sensor_task([[maybe_unused]] void *argument){


	// Turn on Sensor power supply rail
	HAL_GPIO_WritePin(EN_SENSOR_GPIO_Port, EN_SENSOR_Pin, GPIO_PIN_RESET);

	// Power section start up
	osDelay(500);

	auto max30102_init_status = Max30102_Init(&hi2c1);
	assert_param(MAX30102_OK == max30102_init_status);



	for(;;){



		IRv = IrBuffer[BufferHead - 10];
		REDv = RedBuffer[BufferHead - 10];

		// save first 100 if buf
		// Buffer head += 18
		// if na początku
		// semafor do datasaver task

		Max30102_Task();

		osDelay(10);

	}

}
