/*
 * start_display_task.cpp
 *
 *  Created on: Aug 26, 2021
 *      Author: jan
 */




#include <display_task.hpp>
#include "main.h"
#include "cmsis_os.h"

#include <string.h>
#include <cstdio>
#include <stdio.h>



extern "C" {
#include <../st7735/st7735.h>
#include "../st7735/fonts.h"
#include "../st7735/testimg.h"
}

// raw value to display
extern uint32_t IRv, REDv;


void start_display_task([[maybe_unused]]void *argument){

	ST7735_Init();
	ST7735_FillScreen(ST7735_BLACK);


	ST7735_WriteString(0, 0, "Thermal Comfort", Font_11x18, ST7735_RED, ST7735_BLACK);
	ST7735_WriteString(0, 3*12, "Recognition", Font_7x10, ST7735_RED, ST7735_BLACK);
	ST7735_WriteString(0, 4*12, "System", Font_11x18, ST7735_RED, ST7735_BLACK);

	const std::size_t buff_size = 20;
	char  temp_buff[buff_size];


	const uint32_t display_refresh_rate = 10; // in Hz
	const uint32_t display_delay = 1000 / display_refresh_rate;

	const auto line_len = 11; // using font Font_7x10


	for(;;){

		auto line_len_1 = snprintf(temp_buff, buff_size,"r: %-6lu", REDv);
		if(line_len_1 <= line_len){
			ST7735_WriteString(0, 6*12, temp_buff, Font_7x10, ST7735_RED, ST7735_BLACK);
		}

		auto line_len_2 = snprintf(temp_buff, buff_size,"i: %-6lu", IRv);
		if(line_len_2 <= line_len){
			ST7735_WriteString(0, 7*12, temp_buff, Font_7x10, ST7735_RED, ST7735_BLACK);
		}

		osDelay(display_delay);

		printf("%lu \n", REDv);

	}




}
