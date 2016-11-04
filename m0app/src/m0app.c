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

#define N_LINES LCD_Y_RES / NEW_LINE_H


static char localBuffer[500] = { 0 };
static uint16_t nChars[ N_LINES ] = { 0 };


void FillLine( uint16_t lineIndex, uint16_t currentChars, uint32_t xp, uint32_t yp ) {
	if( currentChars < nChars[lineIndex] ) {
		uint16_t diff = nChars[lineIndex] - currentChars;
		for( uint16_t i = 0; i < diff; i++) {
			xp = LCD_PutCharXY( xp & 0xFFF, yp, ' ' );
		}
	}
}

void PutStrXY(int xPos, int lineN, const char *str) {
	uint32_t xp = xPos;
	uint32_t lineIndex = lineN - 1;
	uint32_t yp = (lineN == 1) ? 1 : ((lineIndex) * NEW_LINE_H);
	uint16_t count = 0;

	while (str && *str) {
		if( *str == '\n') {
			*str++;

			FillLine(lineIndex, count, xp, yp);

			nChars[ lineIndex ] = count;
			count = 0;

			lineIndex++;
			yp = lineIndex * NEW_LINE_H;
			xp = 1;

		} else {
			xp = LCD_PutCharXY(xp & 0xFFFF, yp, *str++);
			count++;
		}
	}

	FillLine( lineIndex, count, xp, yp );
	nChars[ lineIndex ] = count; // update last line
}


void PrintLine(const char * str) {

	PutStrXY(1, 2, str );

    // Send signal to M4
	__DSB();
	__SEV();
}

void M4_IRQHandler(void) {
	Chip_CREG_ClearM4Event();

	strcpy(localBuffer, IPC );

	PrintLine( localBuffer );

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


    char str[] = "SMEP v0.1 ";
    int x_center = (LCD_X_RES - strlen(str)*8) / 2;

    LCD_PutStrXY(x_center, 1, str );

    PrintLine("Iniciando..");


    // Send signal to M4
	__DSB();
	__SEV();

    while(1) {
        __WFI(); // Wait for interrupts
    }
    return 0 ;
}
