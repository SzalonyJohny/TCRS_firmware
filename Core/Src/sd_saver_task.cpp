/*
 * sd_saver_task.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: jan
 */



#include "fatfs.h"

extern "C"{
	#include "main.h"
	#include "cmsis_os.h"
	#include "cmsis_os2.h"
	#include <string.h>

	#include "MAX30102.h"
	extern volatile uint32_t IrBuffer[MAX30102_BUFFER_LENGTH]; //IR LED sensor data
	extern volatile uint32_t RedBuffer[MAX30102_BUFFER_LENGTH];    //Red LED sensor data
}

#include "sd_saver_task.hpp"
#include "common.hpp"
#include <cstdio>



extern osSemaphoreId_t Save_PPG_to_SDHandle;
extern buffer_saving_semafor_t buffer_saving_semafor;

void start_sd_saver_task( [[maybe_unused]] void *argument){


	const uint32_t sd_string_to_save_len = 2048;
	char sd_string_to_save[sd_string_to_save_len] = {0};
	unsigned int sd_byteswritten = 0;

	auto init = init_file_system();
	assert_param(FRESULT::FR_OK == init);


	auto status_lseek = f_lseek(&SDFile, 0);
	assert_param(FRESULT::FR_OK == status_lseek);

	const unsigned int str_form_sd_len = 64;
	char buffer_fom_sd[str_form_sd_len] = {0};
	f_gets(buffer_fom_sd, str_form_sd_len, &SDFile);
	f_lseek(&SDFile, f_size(&SDFile));

	uint32_t counter = 0;


	for(;;){

		auto semaphore_status = osSemaphoreAcquire(Save_PPG_to_SDHandle, osWaitForever);
		assert_param(osOK == semaphore_status);


		std::size_t start_saving = 0;
		std::size_t end_saving = 0;

		{
		unsigned int iterator = 0;

		for(auto flag : buffer_saving_semafor.ready_to_save){
			if(flag){
				start_saving = (iterator)*MAX30102_SAMPLES_PER_SECOND;
				end_saving = (iterator+1)*MAX30102_SAMPLES_PER_SECOND - 1;
			}
			iterator++;
		}
		}

		std::size_t snprintf_iter = 0;

		auto res_header = snprintf(sd_string_to_save, sd_string_to_save_len, "Timestamp = %lu \n", counter++);
		assert_param(-1 != res_header);
		snprintf_iter += res_header;


		for(std::size_t buff_iter = start_saving; buff_iter <= end_saving; buff_iter++){
			auto res = snprintf( &sd_string_to_save[snprintf_iter], sd_string_to_save_len - snprintf_iter,"%lu, %lu;", IrBuffer[buff_iter], RedBuffer[buff_iter]);
			assert_param(sd_string_to_save_len - snprintf_iter >= 0);
			snprintf_iter += res;
		}


		auto write_status = f_write(&SDFile, sd_string_to_save, snprintf_iter, &sd_byteswritten);
		assert_param(FRESULT::FR_OK == write_status);

		auto sync_status = f_sync(&SDFile);
		assert_param(FRESULT::FR_OK == sync_status);

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
