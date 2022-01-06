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
#include <cstdio>

#include "common.hpp"

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

// Values to display on LCD
uint32_t IRv, REDv;

// semafor for sd saving data
buffer_saving_semafor_t buffer_saving_semafor;
extern osSemaphoreId_t Save_PPG_to_SDHandle;

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

		for(std::size_t i = 0; i < MAX30102_MEASUREMENT_SECONDS+1; ++i){
			buffer_saving_semafor.ready_to_save[i] = rising_edge_or_overflow <MAX30102_MEASUREMENT_SECONDS+1, MAX30102_FIFO_ALMOST_FULL_SAMPLES+1 >
													 (BufferHead, (i+1)*MAX30102_SAMPLES_PER_SECOND, i);
		}


		IRv = IrBuffer[BufferHead - 10];
		REDv = RedBuffer[BufferHead - 10];


		Max30102_Task();

		osDelay(10);

	}

}
