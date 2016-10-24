/*
===============================================================================
 Name        : m0app.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


#include "board.h"


#include <cr_section_macros.h>

#include "string.h"


#include "ipc_cfg.h"
#include "lcd_st7565s.h"
#include "lpc_rom8x8.h"

static char *IPC = (char *) SHARED_MEM_IPC;

#if defined (M0_SLAVE_PAUSE_AT_MAIN)
volatile unsigned int pause_at_main;
#endif

#define NEW_LINE_H 10


void PrintLine(const char * str) {
	LCD_PutStrXY(1, NEW_LINE_H, str );
}

void M4_IRQHandler(void) {
	Chip_CREG_ClearM4Event();

	PrintLine( IPC );

}

int main(void) {

#if defined (M0_SLAVE_PAUSE_AT_MAIN)
    // Pause execution until debugger attaches and modifies variable
    while (pause_at_main == 0) {}
#endif

    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    NVIC_EnableIRQ(M4_IRQn);

    Board_LED_Set(0, true);


    Board_LCD_Init();
    LCD_Init();
    LCD_SetFontColor(1);
    LCD_SetFontBgColor(0);
    LCD_SetFont(&font_rom8x8);


    char str[] = "SMEP v0.1";
    int x_center = (LCD_X_RES - strlen(str)*8) / 2;

    LCD_PutStrXY(x_center, 1, str );

    PrintLine("Iniciando..");

    while(1) {
        __WFI(); // Wait for interrupts
    }
    return 0 ;
}
