#include "board.h"
#include "adc.h"
#include "definitions.h"

static ADC_CLOCK_SETUP_T ADCSetup;
static ADC_CLOCK_SETUP_T ADC1Setup;



void ADC_Init() {
	Board_ADC_Init();
	Chip_ADC_Init( LPC_ADC_CURRENT, &ADCSetup);
	Chip_ADC_Init( LPC_ADC_VOLTAGE, &ADC1Setup );

	Chip_ADC_EnableChannel( LPC_ADC_CURRENT, ADC_CH_CURRENT, ENABLE);
	Chip_ADC_EnableChannel( LPC_ADC_VOLTAGE, ADC_CH_VOLTAGE, ENABLE);
}


ADC_RESULT ADC_Read() {
	ADC_RESULT result;

	Chip_ADC_SetStartMode(LPC_ADC_CURRENT, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	Chip_ADC_SetStartMode(LPC_ADC_VOLTAGE, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

	while(Chip_ADC_ReadStatus( LPC_ADC_CURRENT, ADC_CH_CURRENT, ADC_DR_DONE_STAT) != SET &&
			Chip_ADC_ReadStatus( LPC_ADC_VOLTAGE, ADC_CH_VOLTAGE, ADC_TRIGGERMODE_RISING) != SET) {}

	Chip_ADC_ReadValue( LPC_ADC_CURRENT, ADC_CH_CURRENT, &result.current );

	Chip_ADC_ReadValue( LPC_ADC_VOLTAGE, ADC_CH_VOLTAGE, &result.voltage );


	return result;
}
