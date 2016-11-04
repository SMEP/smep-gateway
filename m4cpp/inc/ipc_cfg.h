/*
 * ipc_cfg.h
 *
 *      Author: Matheus
 */

#ifndef IPC_CFG_H_
#define IPC_CFG_H_

#define SHARED_MEM_IPC      0x10088000	/* Shared memory used by IPC */

inline void ipc_send_signal(void);
bool WriteLCD(const char * msg);

extern bool M0Ready;


#endif /* IPC_CFG_H_ */
