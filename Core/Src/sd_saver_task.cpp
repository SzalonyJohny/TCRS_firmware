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



void start_sd_saver_task([[maybe_unused]]void *argument){


	char sd_string_to_save[64] = {0};
	unsigned int sd_byteswritten = 0;

	unsigned int counter = 0;

	init_file_system();


	for(;;){

		auto size = snprintf(sd_string_to_save, 64, "jakies dlugie dane dane dane halo halo %d, \n", counter++);

		auto write_status = f_write(&SDFile, sd_string_to_save, size, &sd_byteswritten);
		auto sync_status = f_sync(&SDFile);

		osDelay(100);

		if( FRESULT::FR_OK == write_status && FRESULT::FR_OK == sync_status ){
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		}
		else {
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		}
	}
}


FRESULT init_file_system() {

	FRESULT res = FRESULT::FR_OK;

	res = f_mount(&SDFatFS, SDPath, 0);
	if(FRESULT::FR_OK != res){
		return res;
	}

	res =  f_open(&SDFile, "t.txt", FA_OPEN_APPEND | FA_WRITE);
	if(FRESULT::FR_OK != res){
		return res;
	}

	res = f_lseek(&SDFile, f_size(&SDFile));


	return res;
}
