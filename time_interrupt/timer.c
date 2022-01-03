/*
 * timer.c
 *
 *  Created on: Nov 19, 2021
 *      Author: ADMIN
 */
#include "main.h"
#include "button_reading.h"
#define TIMER_CYCLE 10;

int timer0_counter = 0;
int timer0_flag = 0; //for 1s
int timer1_counter = 0;
int timer1_flag = 0; // displaying the led
int timer2_counter = 0;
int timer2_flag = 0; // 2hz = 0.5s led blinking.
int timer3_counter = 0;
int timer3_flag = 0; // 50ms for debouncing.
void setTimer0(int duration){
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}
void setTimer1(int duration){
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}
void setTimer2(int duration){
	timer2_counter = duration / TIMER_CYCLE;
	timer2_flag = 0;
}
void setTimer3(int duration){
	timer3_counter = duration / TIMER_CYCLE;
	timer3_flag = 0;
}
void timer_run() {
	if (timer0_counter > 0) {
		timer0_counter--;
		if (timer0_counter == 0)
			timer0_flag = 1;
	}
	if (timer1_counter > 0) {
		timer1_counter--;
		if (timer1_counter == 0)
			timer1_flag = 1;
	}
	if (timer2_counter > 0) {
		timer2_counter--;
		if (timer2_counter == 0)
			timer2_flag = 1;
	}
	if (timer3_counter > 0) {
		timer3_counter--;
		if (timer3_counter == 0)
			timer3_flag = 1;
	}
}
int get_timer0_flag(){
	return timer0_flag;
}
int get_timer1_flag(){
	return timer1_flag;
}
int get_timer2_flag(){
	return timer2_flag;
}
int get_timer3_flag(){
	return timer3_flag;
}
void set_timer0_flag(){
	timer0_flag = 0;
}
void init_timer_setting(){
	if(timer0_counter==0)
		setTimer0(1000);
	if(timer1_counter==0)
		setTimer1(250);
	if(timer2_counter==0)
		setTimer2(500);
}
int counter=50;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	timer_run();
	button_reading();
	if(counter==0)
	{
		HAL_GPIO_TogglePin(TIMER_LED_GPIO_Port, TIMER_LED_Pin);
		counter=50;
	}
	counter--;
}
