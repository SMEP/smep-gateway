/*
 * millis.c
 *
 *  Created on: Sep 22, 2016
 *      Author: Matheus
 */
#include "board.h"
#include "millis.h"


volatile unsigned long _millis;


void Millis_Start(void) {
	SysTick_Config( SystemCoreClock / 1000);
}


void SysTick_Handler(void) {
	_millis++;
}

unsigned long Millis(void) {
	return _millis;
}
