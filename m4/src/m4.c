/*
===============================================================================
 Name        : m4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


#include "board.h"


#include <cr_section_macros.h>
#include "cr_start_m0.h"


#include "uart.h"
#include "millis.h"

#include <string.h>
// TODO: insert other definitions and declarations here


void SendData( const char * cmd, char * resp, const int timeout, bool debug) {
	UART_Send(cmd, strlen(cmd));

	long int time = Millis();

	while( 1 ) {
		if( (time + timeout) < Millis() ) {
			printf("\nTimed out\n");
			break;
		}

		while( UART_Available()  ) {
			char c = UART_Read();
			*resp = c;
			resp++;
		}

		if( strstr( resp, "OK") != NULL || strstr( resp, "FAIL") != NULL ) {
			//*resp = '\0';
			break;
		}
	}



	//*resp = '\0';


	if( debug )
		printf("%s", resp);
}

int main(void) {


    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();

    // Set the LED to the state of "On"
    Board_LED_Set(0, true);


    // Start M0APP slave processor
    cr_start_m0(SLAVE_M0APP,&__core_m0app_START__);


    static uint8_t teste[] = "Hello World!";


    // TODO: insert code here

    UART_Init( 9600 );

    Millis_Start();




    bool s = false;
    //char * resp = (char*) calloc(sizeof(char), 500);
    char resp[1000];


    while(1) {

        printf("Mandando CWLAP");
        SendData( "AT+CWLAP\r\n", (char *) &resp[0], 15000, false );
        printf("Recebido: \n");
        printf("%s", resp);



    	//UART_Send( resp, strlen(resp) );


//    	UART_Send( teste, sizeof(teste));

    	for( int i = 0; i < 9999999; i ++) {

    	}
    	s = !s;
		Board_LED_Set(0, s);
    }

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
