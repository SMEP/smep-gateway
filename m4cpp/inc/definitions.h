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

#define SERVER_IP 	String("192.168.1.225")
#define SERVER_PORT 8080
#define SERVER_PATH	"/sample"

#include "wifi_credentials.h"
/*#define AP_SSID "your ssid"
#define AP_PW	"your pwd"*/

#define NTP_SERVER 	String("pool.ntp.org")
#define NTP_PORT 	123


// Sampling

#define ADC_CH_CURRENT	ADC_CH3
#define LPC_ADC_CURRENT LPC_ADC0

#define ADC_CH_VOLTAGE	ADC_CH2
#define LPC_ADC_VOLTAGE LPC_ADC1


#define NUM_AVG_PEAKS 3
#define VOLT_REF 212
#define INPUT_GAIN 1.63


#define FREQ_SAMPLE 1000
#define DELAY_MS_SAMPLES 1


#define MEAN_PW_INTERVAL_S 3

#define SEND_THRESHOLD (FREQ_SAMPLE * MEAN_PW_INTERVAL_S)


// Global Variables
extern char* const IPC;
class ESP8266; // Forward implementation
extern ESP8266 esp;

#endif /* DEFINITIONS_H_ */
