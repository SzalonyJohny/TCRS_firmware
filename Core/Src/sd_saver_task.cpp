/*
 * sd_saver_task.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: jan
 */

#include "main.h"
#include "cmsis_os.h"

#include <string.h>
#include <../st7735/st7735.h>
#include "../st7735/fonts.h"
#include "../st7735/testimg.h"


#include "sd_saver_task.hpp"


void start_sd_saver_task(void *argument){


	for(;;){

		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		osDelay(500);
	}

}
