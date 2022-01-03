/*
 * led_display.c
 *
 *  Created on: Nov 19, 2021
 *      Author: ADMIN
 */
#include "timer.h"
#include "main.h"
#include "led_display.h"
#include "led_processing.h"

int index_led=0;
int led_buffer[4]={0,0,0,0};
#define MAX_LED 4
void display7SEG(int count) {
	if (count == 0) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
	} else if (count == 1) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
	} else if (count == 2) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 1);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	} else if (count == 3) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	} else if (count == 4) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 1);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	} else if (count == 5) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	} else if (count == 6) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 1);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	} else if (count == 7) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 1);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 1);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 1);
	} else if (count == 8) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	} else if (count == 9) {
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	}
}
void update7SEG(int index_led){
	switch(index_led){
	case 0:{
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, 1);
		display7SEG(led_buffer[0]);
		break;
	}
	case 1:{
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, 1);
		display7SEG(led_buffer[1]);
		break;

	}
	case 2:{
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, 1);
		display7SEG(led_buffer[2]);
		break;
	}
	case 3:{
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, 0);
		display7SEG(led_buffer[3]);
		break;
	}
	}
}
void updateBuffer(int led_buffer[], int led_number, int count){
	switch(led_number){
		case 1:{
			if(count<10){
				led_buffer[0]=0;
				led_buffer[1]=count;
			}
			else{
				led_buffer[0]=count/10;
				led_buffer[1]=count%10;
			}
			}
		case 2:{
			if(count<10){
				led_buffer[2]=0;
				led_buffer[3]=count;
			}
			else{
				led_buffer[2]=count/10;
				led_buffer[3]=count%10;
			}
	}
}
}
void set_index_led(int index){
	index_led = index;
}
int get_index_led(){
	return index_led;
}
void reset7LED() {
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
	HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, 1);
	HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, 1);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
	HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, 1);
	HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, 1);
}
void turnon7LED() {
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
	HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, 0);
	HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, 0);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
	HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, 0);
	HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, 0);
}
