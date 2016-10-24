#ifndef UART_H_
#define UART_H_

#define LPC_UART LPC_USART0
#define UARTx_IRQHandler UART0_IRQHandler

#include "chip.h"
#include "WString.h"


void UART_Init( const uint32_t baud );
void UART_Send(const void * data, int numBytes );
void UART_Send( String cmd );
bool UART_Available();
uint8_t UART_Read();
void UART_IRQ_Init();
void UART_IntEnable();
void UART_IntDisable();

#ifdef __cplusplus
extern "C" {
#endif

void UARTx_IRQHandler(void);
#ifdef __cplusplus
}
#endif



#endif /* UART_H_ */
