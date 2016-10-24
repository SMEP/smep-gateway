#include "board.h"

int _write(int iFileHandle, char *pcBuffer, int iLength) {
	unsigned int i;

	for( i = 0; i < iLength; i++) {
		ITM_SendChar(  pcBuffer[i]  );
	}


	return iLength;
}
