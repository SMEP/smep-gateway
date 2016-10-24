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



char *IPC = (char *) SHARED_MEM_IPC;
ESP8266 esp;



void InitESP() {
	 esp.SetMux( true );

	 //WriteLCD("Conectando AP");

	// esp.ConnectAP( AP_SSID, AP_PW);
}


void Init() {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();

    UART_Init(9600);
    UART_IRQ_Init();
    ADC_Init();
    Millis_Start();

    std::setbuf(stdout, NULL);

    memset(IPC, 0, 256);

}

int main(void) {
	Init();

    // Start M0APP slave processor
    cr_start_m0(SLAVE_M0APP,&__core_m0app_START__);


	InitESP();

    Chip_GPIO_SetPinDIROutput( LPC_GPIO_PORT, 1, 12); // GPIO1[12] = P2_12


    StartAquisition();


    while(1) {} // Ooops should not be here

    return 0 ;
}
