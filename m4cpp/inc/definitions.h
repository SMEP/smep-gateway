/*
 * const.h
 *
 *      Author: Matheus
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include "ipc_cfg.h"


// WIFI

#define UNIT_ID 1

#define SERVER_IP 	String("10.0.0.9")
#define SERVER_PORT 8080
#define SERVER_PATH	"/sample"

#define AP_SSID "Raul"
#define AP_PW	"raul10mb"

#define NTP_SERVER String("br.pool.ntp.org")


// Sampling

#define ADC_CH ADC_CH3
#define LPC_ADC LPC_ADC0

#define NUM_AVG_PEAKS 3
#define VOLT_REF 212
#define INPUT_GAIN 1.63


#define FREQ_SAMPLE 1000
#define DELAY_MS_SAMPLES 1


#define MEAN_PW_INTERVAL_S 3

#define SEND_THRESHOLD (FREQ_SAMPLE * MEAN_PW_INTERVAL_S)


// Global Variables
extern char *IPC;
class ESP8266; // Forward implementation
extern ESP8266 esp;

#endif /* DEFINITIONS_H_ */
