/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/



#include "board.h"
#include <cr_section_macros.h>
#include <functional>

#include <cstdio>
#include "cr_start_m0.h"

#include "definitions.h"
#include "esp.h"
#include "adc.h"
#include "millis.h"
#include "uart.h"
#include "WString.h"
#include "dsp.h"
#include "ipc_cfg.h"



char* const IPC = (char *) SHARED_MEM_IPC;
ESP8266 esp;



static void InitESP() {
	 esp.SetMux( true );

	 WriteLCD("Conectando AP");

	 //esp.ConnectAP( AP_SSID, AP_PW);
	 WriteLCD("AP Conectado");
}


void Init() {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();

    UART_Init( 115200 );
    UART_IRQ_Init();
    ADC_Init();
    Millis_Start();

    std::setbuf(stdout, NULL);

    memset(IPC, 0, 256);

    NVIC_EnableIRQ( M0APP_IRQn );
}




int main(void) {
	Init();

	uint64_t start = Millis();

    // Start M0APP slave processor
    cr_start_m0(SLAVE_M0APP,&__core_m0app_START__);

    while( !M0Ready ) {} // wait for M0 StartUp
    uint64_t end = Millis();



	InitESP();

    Chip_GPIO_SetPinDIROutput( LPC_GPIO_PORT, 1, 12); // GPIO1[12] = P2_12

    uint32_t uid[5];
    Chip_IAP_ReadUID( &uid[0] );


    char * uidStr = (char*) &uid;
    uidStr[17] = '\0';

    printf("UID: %X %X %X %X %s", uid[0], uid[1], uid[2], uid[3], uidStr);

   // esp.NTPRequest( NTP_SERVER, NTP_PORT );


    StartAquisition();


    while(1) {} // Ooops should not be here

    return 0 ;
}
