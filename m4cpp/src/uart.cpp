#include "uart.h"

#include "board.h"

#include "WString.h"

#define UARTx_IRQn  USART0_IRQn

void UART_Init( const uint32_t baud ) {
	Board_UART_Init( LPC_UART );
	Chip_UART_Init( LPC_UART );

	Chip_UART_SetBaud( LPC_UART, baud );
	Chip_UART_TXEnable( LPC_UART );
}

void UART_IRQ_Init() {
	UART_IntEnable();
    Chip_UART_SetupFIFOS( LPC_UART, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2 | UART_FCR_RX_RS );

	NVIC_SetPriority(UARTx_IRQn, 1);

	NVIC_EnableIRQ(UARTx_IRQn);
}

void UART_IntEnable() {
	Chip_UART_IntEnable( LPC_UART, (UART_IER_RBRINT | UART_IER_RLSINT) );
}

void UART_IntDisable() {
	Chip_UART_IntDisable( LPC_UART, (UART_IER_RBRINT | UART_IER_RLSINT) );
}

void UART_Send(const void * data, int numBytes ) {
	Chip_UART_SendBlocking( LPC_UART, data, numBytes );
}

void UART_Send( String cmd ) {
	UART_Send( cmd.c_str(), cmd.length() );
}

uint8_t UART_Read() {
	return Chip_UART_ReadByte( LPC_UART );
}

bool UART_Available() {
	return Chip_UART_ReadLineStatus( LPC_UART ) & UART_LSR_RDR;
}


#define MAX_BUFFER_SIZE 1500
String receiveBuffer;
void UARTx_IRQHandler(void)
{
	String out;
	uint32_t IIR = LPC_UART->IIR & UART_IIR_BITMASK;
	uint32_t INTID = IIR & UART_IIR_INTID_MASK;
	uint32_t LSR = 0;

	bool recv = false;

	switch(INTID) {
		case UART_IIR_INTID_CTI:
		case UART_IIR_INTID_RDA:
			recv = true;

			if( receiveBuffer.length() > MAX_BUFFER_SIZE )
				receiveBuffer = receiveBuffer.substring( MAX_BUFFER_SIZE / 2); // Discard half of the contents

			while( UART_Available() ) {
				receiveBuffer += (char) UART_Read();
			}

			break;
		case UART_IIR_INTID_RLS:
			LSR = Chip_UART_ReadLineStatus(LPC_UART) & UART_LSR_BITMASK; // Clear RLS interrupt
			printf("RLS %d", LSR);
			break;

		default:
			printf("Unkown %d", INTID);
	}

	/*if( recv ) {
		printf("UART_IRQ:");
		printf( receiveBuffer );
		receiveBuffer = "";
	}*/

}
