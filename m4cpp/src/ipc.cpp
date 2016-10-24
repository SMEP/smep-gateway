/*
 * ipc.cpp
 *
 *      Author: Matheus
 */

#include "board.h"
#include "definitions.h"
#include "ipc_cfg.h"
#include <string.h>


inline void ipc_send_signal(void)
{
	__DSB();
	__SEV();
}

void WriteLCD(const char * msg) {
	strcpy(IPC, msg);
	ipc_send_signal();
}



