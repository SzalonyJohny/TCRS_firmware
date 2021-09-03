/*
 * sd_saver_task.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: jan
 */

#include "main.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>
#include "fatfs.h"

#include "sd_saver_task.hpp"


unsigned int byteswritten = 0;



void start_sd_saver_task(void *argument){


	char string_to_save[64];

	unsigned int counter = 0;

	//FATFS_LinkDriver(&SD_Driver, SDPath);

	initFileSystem();

	for(;;){

		auto size = snprintf(string_to_save, 64, "zapisuje dane %d, \n\r", counter++);
		f_write(&SDFile, string_to_save, size, &byteswritten);

		f_sync(&SDFile);

		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		osDelay(500);
	}

}


FRESULT initFileSystem() {

	FRESULT res = FRESULT::FR_OK;

	res = f_mount(&SDFatFS, SDPath, 0);

    uint8_t val = BSP_SD_IsDetected();
	GPIO_PinState val2 = HAL_GPIO_ReadPin(EN_1V8_GPIO_Port, EN_1V8_Pin);

	res =  f_open(&SDFile, "t.txt", FA_OPEN_APPEND | FA_WRITE);


	res = f_lseek(&SDFile, f_size(&SDFile));

	return res;
}
