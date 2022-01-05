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



extern "C" {
#include <../st7735/st7735.h>
#include "../st7735/fonts.h"
#include "../st7735/testimg.h"
}

extern uint32_t IRv, REDv;



void start_display_task([[maybe_unused]]void *argument){

	ST7735_Init();
	ST7735_FillScreen(ST7735_BLACK);


	ST7735_WriteString(0, 0, "Thermal Comfort", Font_11x18, ST7735_RED, ST7735_BLACK);
	ST7735_WriteString(0, 3*12, "Recognition", Font_7x10, ST7735_RED, ST7735_BLACK);
	ST7735_WriteString(0, 4*12, "System", Font_11x18, ST7735_RED, ST7735_BLACK);

	const std::size_t buff_size = 13;
	char  temp_buff[buff_size];

	for(;;){

		snprintf(temp_buff, buff_size,"r: %-9lu", REDv);
		ST7735_WriteString(0, 6*12, temp_buff, Font_7x10, ST7735_RED, ST7735_BLACK);

		snprintf(temp_buff, buff_size,"i: %-9lu", IRv);
		ST7735_WriteString(0, 7*12, temp_buff, Font_7x10, ST7735_RED, ST7735_BLACK);

		osDelay(50);
	}

}
