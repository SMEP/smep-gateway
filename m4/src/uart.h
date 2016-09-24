/*
 * uart.h
 *
 *  Created on: Sep 22, 2016
 *      Author: Matheus
 */

#ifndef UART_H_
#define UART_H_

#define LPC_UART LPC_USART0

#include "chip.h"


void UART_Init( const uint32_t baud );
void UART_Send(const void * data, int numBytes );
bool UART_Available();
uint8_t UART_Read();

#endif /* UART_H_ */
