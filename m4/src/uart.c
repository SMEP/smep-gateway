#include "uart.h"
#include "board.h"

void UART_Init( const uint32_t baud ) {
	Board_UART_Init( LPC_UART );
	Chip_UART_Init( LPC_UART );

	Chip_UART_SetBaud( LPC_UART, baud );
	Chip_UART_TXEnable( LPC_UART );
}

void UART_Send(const void * data, int numBytes ) {
	Chip_UART_SendBlocking( LPC_UART, data, numBytes );
}

uint8_t UART_Read() {
	return Chip_UART_ReadByte( LPC_UART );
}

bool UART_Available() {
	return Chip_UART_ReadLineStatus( LPC_UART ) & UART_LSR_RDR;
}
