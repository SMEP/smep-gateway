#include "board.h"
#include "adc.h"

static ADC_CLOCK_SETUP_T ADCSetup;



void ADC_Init() {
	Board_ADC_Init();
	Chip_ADC_Init( LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel( LPC_ADC, ADC_CH, ENABLE);
}


uint16_t ADC_Read() {
	uint16_t dataADC;

	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

	while(Chip_ADC_ReadStatus( LPC_ADC, ADC_CH, ADC_DR_DONE_STAT) != SET) {}

	Chip_ADC_ReadValue( LPC_ADC, ADC_CH, &dataADC );

	return dataADC;
}
