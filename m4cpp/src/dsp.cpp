/*
 * dsp.cpp
 *
 *      Author: Matheus
 */
#include "board.h"
#include "dsp.h"
#include "adc.h"
#include "millis.h"
#include "esp.h"



float sample_to_v(uint16_t sample ) {
	return (float) (3.3 / (float) 1023) * sample;
}


void StartAquisition() {
	bool state = 0;

	uint16_t read = 0;
	float volt = 0;
	float amp = 0;
	float pot = 0;

	uint64_t peaksSum = 0;
	uint64_t offsetSum = 0;


	uint32_t sum = 0;
	uint16_t maxes[NUM_AVG_PEAKS] = { 0 };

	uint32_t i = 0;
	uint32_t cnt = 0;
	while(1) {
		read = ADC_Read();
		sum += read;

		for( uint16_t i = 0; i < NUM_AVG_PEAKS; i++) {
			if( read > maxes[i] ) {
				for( uint16_t n = i; n < NUM_AVG_PEAKS-1; n++ ) {//do swaps
					maxes[n + 1] = maxes[n];
				}
				maxes[ i ] = read;
				break;
			}
		}

		volt = sample_to_v( read );
		amp = AMP( volt );
		pot = WATT ( amp );

		//printf("Lido %d %.6f V   AMP:  %.3f WATT: %.3f \n", read, volt, amp, pot);

		if( i == 100) { // Each 6 complete cycles of the sine 60Hz
			float mean = sum / 100;

			uint16_t sumMax = 0;

			for( uint16_t i = 0; i < NUM_AVG_PEAKS; i++) {
				sumMax += maxes[i];
			}

			float meanMax = sumMax / 3;

			float offset = sample_to_v(mean);
			float peak = sample_to_v( meanMax );
			float pp = peak - offset;
			float power = WATT( AMP( pp ) );

			peaksSum += meanMax;
			offsetSum += mean;

			printf("Mean: %.2f %.4f V  %.2f MeanMax: %.4f PP: %.4f Power: %.3f\n", mean, offset, meanMax, peak, peak - offset, power );

			sprintf(IPC, "POT: %.2f W", power );
			ipc_send_signal(); // Send to M0 write to LCD

			// Reset variables
			sum = 0;
			i = 0;

			// invalidate peak max
			for( uint16_t n = 2; n > 0; n-- ) {
				maxes[n - 1] = maxes[n];
			}
			maxes[2] = 0;


			cnt++;
		}


		if( cnt == SEND_THRESHOLD / 100 ) {
			float mPks = peaksSum / cnt;

			float meanPeak = sample_to_v( mPks );
			float meanOffset = sample_to_v( offsetSum / cnt );

			float pp = meanPeak - meanOffset;
			float meanPower = WATT( AMP( pp ));


			PostParameters params;
			params["power"] = String( meanPower );
			params["interval"] = MEAN_PW_INTERVAL_S;
			params["offset"] = meanOffset;
			params["voltage"] = VOLT_REF;
			params["sample"] = mPks;


			Chip_GPIO_SetPinState( LPC_GPIO_PORT, 1, 12, state);
			state = !state;




			printf("Sending HTTP post... MeanPower: %.4f", meanPower);

			esp.SendHTTPPost( SERVER_IP, SERVER_PORT, SERVER_PATH, params );

			peaksSum = offsetSum = 0;
			cnt = 0;
		}


		i++;


		Delay_ms( DELAY_MS_SAMPLES );
	}
}





