/*
 * led_processing.c
 *
 *  Created on: Nov 19, 2021
 *      Author: ADMIN
 */
#include "main.h"
#include "timer.h"
#include "led_display.h"
#include "button_reading.h"
#define MAX_LED 4
int green_time = 4;
int yellow_time = 2;
int red_time = 6;
int done_check_1 = 0;
int done_check_2 = 0;
enum LedState {
	NORMAL, RED_CUSTOM, YELLOW_CUSTOM, GREEN_CUSTOM
};
enum LedState ledState = NORMAL;
static int time_1 = 6;
static int time_1_buffer = 0;
static int time_2 = 4;
static int time_2_buffer = 0;
void led_processing() {
	init_timer_setting();

	switch (ledState) {
	case NORMAL: {
		updateBuffer(led_buffer, 1, time_1 - 1);
		updateBuffer(led_buffer, 2, time_2 - 1);
		//running the first led (1) (starting from red)
		if (!done_check_1) {
			done_check_1 = 1;
			if (time_1 == red_time) {
				HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
				HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, 1);
				time_1_buffer = green_time;
			}
			if (time_1 == green_time) {
				HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
				HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, 0);
				time_1_buffer = yellow_time;
			}
			if (time_1 == yellow_time) {
				HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, 0);
				HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, 1);
				time_1_buffer = red_time;
			}
		}
		if (!done_check_2) {
			done_check_2 = 1;
			if (time_2 == red_time) {
				HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
				HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, 1);
				time_2_buffer = green_time;
			}
			if (time_2 == green_time) {
				HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
				HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, 0);
				time_2_buffer = yellow_time;
			}
			if (time_2 == yellow_time) {
				HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, 0);
				HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, 1);
				time_2_buffer = red_time;
			}
		}
		if (time_1 == 0) {
			done_check_1 = 0;
			time_1 = time_1_buffer;
		}
		if (time_2 == 0) {
			done_check_2 = 0;
			time_2 = time_2_buffer;
		}
		//
		//running---------------------------------
		if (get_timer0_flag() == 1) {
			time_1--;
			time_2--;
		}
		if (get_timer1_flag() == 1) {
			update7SEG(get_index_led());
			int index_led = get_index_led();
			index_led++;
			set_index_led(index_led);
			if (get_index_led() == MAX_LED)
				set_index_led(0);
		}

		if (is_button_pressed(0) && get_timer3_flag() == 1) {
			setTimer3(200);
			ledState = RED_CUSTOM;
			reset7LED();
		}
		break;
	}

	case RED_CUSTOM: {
		static int red_time_modify = 6;
		updateBuffer(led_buffer, 1, 2);
		updateBuffer(led_buffer, 2, red_time_modify);
		if (get_timer2_flag() == 1) {
			HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
			HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
		}
		if (is_button_pressed(1) && get_timer3_flag() == 1) {
			setTimer3(200);
			red_time_modify++;
		}

		if (is_button_pressed(2) && get_timer3_flag() == 1) {
			red_time = red_time_modify;
			setTimer3(200);
		}

		if (is_button_pressed(0) && (get_timer3_flag() == 1)) {
			ledState = YELLOW_CUSTOM;
			reset7LED();
			setTimer3(200);
		}

		if (get_timer1_flag() == 1) {
			update7SEG(get_index_led());
			int index_led = get_index_led();
			index_led++;
			set_index_led(index_led);
			if (get_index_led() == MAX_LED)
				set_index_led(0);
		}
		break;
	}
	case YELLOW_CUSTOM: {
		static int yellow_time_modify = 2;
		updateBuffer(led_buffer, 1, 3);
		updateBuffer(led_buffer, 2, yellow_time_modify);
		if (get_timer2_flag() == 1) {
			HAL_GPIO_TogglePin(YEL2_GPIO_Port, YEL2_Pin);
			HAL_GPIO_TogglePin(YEL1_GPIO_Port, YEL1_Pin);
		}
		if (is_button_pressed(1) && get_timer3_flag() == 1) {
			setTimer3(200);
			yellow_time_modify++;
		}

		if (is_button_pressed(2) && get_timer3_flag() == 1) {
			yellow_time = yellow_time_modify;
			setTimer3(200);
		}

		if (is_button_pressed(0) && get_timer3_flag() == 1) {
			ledState = GREEN_CUSTOM;
			reset7LED();
			setTimer3(200);
		}

		if (get_timer1_flag() == 1) {
			update7SEG(get_index_led());
			int index_led = get_index_led();
			index_led++;
			set_index_led(index_led);
			if (get_index_led() == MAX_LED)
				set_index_led(0);
		}

		break;
	}
	case GREEN_CUSTOM: {
		static int green_time_modify = 4;
		updateBuffer(led_buffer, 1, 4);
		updateBuffer(led_buffer, 2, green_time_modify);
		if (get_timer2_flag() == 1) {
			HAL_GPIO_TogglePin(GRN2_GPIO_Port, GRN2_Pin);
			HAL_GPIO_TogglePin(GRN1_GPIO_Port, GRN1_Pin);
		}
		if (is_button_pressed(1) && get_timer3_flag() == 1) {
			setTimer3(200);
			green_time_modify++;
		}

		if (is_button_pressed(2) && get_timer3_flag() == 1) {
			green_time = green_time_modify;
			setTimer3(200);
		}

		if (is_button_pressed(0) && get_timer3_flag() == 1) {
			ledState = NORMAL;
			reset7LED();
			setTimer3(200);
		}

		if (get_timer1_flag() == 1) {
			update7SEG(get_index_led());
			int index_led = get_index_led();
			index_led++;
			set_index_led(index_led);
			if (get_index_led() == MAX_LED)
				set_index_led(0);
		}
		time_1=red_time;
		tỉme_2=green_time;
		break;
	}
	default: {
		break;
	}
	}
}

