/*
 * button_reading.c
 *
 *  Created on: Nov 19, 2021
 *      Author: ADMIN
 */
#include "main.h"
// we aim to work with more than one buttons
#define N0_OF_BUTTONS 3
// timer interrupt duration is 10ms , so to pass 1 second ,
// we need to jump to the interrupt service routine 100 time
#define BUTTON_IS_PRESSED  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET
// the buffer that the final result is stored after
// debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS] = { 1, 1, 1 };
// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];
// we define a flag for a button pressed more than 1 second .
// we define counter for automatically increasing the value
// after the button is pressed more than 1 second .
void button_reading(void) {
	for (uint8_t i = 0; i < N0_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		switch (i) {
		case 0:{
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUT1_GPIO_Port,
			BUT1_Pin);
			break;
		}
		case 1:{
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUT2_GPIO_Port,
			BUT2_Pin);
			break;
		}
		case 2:{
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUT3_GPIO_Port,
			BUT3_Pin);
			break;
		}
		}
		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];

	}
}

unsigned char is_button_pressed(uint8_t index) {
	if (index >= N0_OF_BUTTONS)
		return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}
