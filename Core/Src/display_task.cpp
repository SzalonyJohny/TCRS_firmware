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
#include <../st7735/st7735.h>
#include "../st7735/fonts.h"
#include "../st7735/testimg.h"


void start_display_task([[maybe_unused]]void *argument){


	for(;;){

		ST7735_FillScreen(ST7735_BLACK);

		osDelay(300);

		// Check fonts
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
		ST7735_WriteString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
		ST7735_WriteString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
		osDelay(100);

		// Check colors
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
		osDelay(200);

		ST7735_FillScreen(ST7735_BLUE);
		ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
		osDelay(200);

		ST7735_FillScreen(ST7735_RED);
		ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
		osDelay(200);

		ST7735_FillScreen(ST7735_GREEN);
		ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
		osDelay(200);

		ST7735_FillScreen(ST7735_CYAN);
		ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
		osDelay(200);

		ST7735_FillScreen(ST7735_MAGENTA);
		ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
		osDelay(200);

		ST7735_FillScreen(ST7735_YELLOW);
		ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
		osDelay(200);

		ST7735_FillScreen(ST7735_WHITE);
		ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
		osDelay(200);

	}
}
