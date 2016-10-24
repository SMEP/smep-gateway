/*
 * ipc_cfg.h
 *
 *      Author: Matheus
 */

#ifndef IPC_CFG_H_
#define IPC_CFG_H_

#define SHARED_MEM_IPC      0x10088000	/* Shared memory used by IPC */

inline void ipc_send_signal(void);
void WriteLCD(const char * msg);


#endif /* IPC_CFG_H_ */
