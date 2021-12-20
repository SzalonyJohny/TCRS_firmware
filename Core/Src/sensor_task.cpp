/*
 * sensor_task.cpp
 *
 *  Created on: Dec 20, 2021
 *      Author: jan
 */




#include "main.h"
#include "cmsis_os.h"
#include "sensor_task.hpp"


void start_sensor_task([[maybe_unused]] void *argument){



	for(;;){
		HAL_GPIO_TogglePin(EN_SENSOR_GPIO_Port, EN_SENSOR_Pin);
		HAL_Delay(3000);
	}

}
