/*
 * ipc.cpp
 *
 *      Author: Matheus
 */

#include "board.h"
#include "definitions.h"
#include "ipc_cfg.h"
#include <string.h>


bool M0Ready = false;

inline void ipc_send_signal(void)
{
	M0Ready = false;
	__DSB();
	__SEV();
}

bool WriteLCD(const char * msg) {
	if( !M0Ready ) {
		printf("M0 Busy! Rejecting: %s", msg);
		return false;
	}
	strcpy((char *)IPC, msg);
	ipc_send_signal();

	return true;
}

extern "C" void M0APP_IRQHandler(void) {
	 Chip_CREG_ClearM0AppEvent();
	 M0Ready = true;
}



