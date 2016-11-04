/*
 * adc.h
 *
 *      Author: Matheus
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef struct {
	uint16_t current;
	uint16_t voltage;
} ADC_RESULT;

void ADC_Init();
ADC_RESULT ADC_Read();




#endif /* ADC_H_ */
