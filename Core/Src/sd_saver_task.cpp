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

	const unsigned int sd_string_to_save_len = 64;
	char sd_string_to_save[sd_string_to_save_len] = {0};
	unsigned int sd_byteswritten = 0;

	unsigned int counter = 0;

	auto init = init_file_system();

	auto status_lseek = f_lseek(&SDFile, 0);

	char buffer_fom_sd[64] = {0};
	auto status = f_gets(buffer_fom_sd, 30, &SDFile);

	f_lseek(&SDFile, SDFile.fptr);


	for(;;){

		osDelay(100);

		auto size = snprintf(sd_string_to_save, sd_string_to_save_len, "nowe dane zapisae na zajeciach %d, \n", counter++);

		auto write_status = f_write(&SDFile, sd_string_to_save, size, &sd_byteswritten);

		auto sync_status = f_sync(&SDFile);


		if( FRESULT::FR_OK == write_status && FRESULT::FR_OK == sync_status ){
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		}
		else {
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		}
		counter %= 1000;
	}
}



FRESULT init_file_system(){

	FRESULT res =  f_mount(&SDFatFS, SDPath, 0);
	if(FRESULT::FR_OK != res){
		return res;
	}

	res =  f_open(&SDFile, "d.txt", FA_OPEN_APPEND | FA_WRITE | FA_READ);
	if(FRESULT::FR_OK != res){
		return res;
	}

	res = f_lseek(&SDFile, f_size(&SDFile));
	return res;
}
