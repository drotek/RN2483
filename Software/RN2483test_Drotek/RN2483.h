#include "arduino.h"

#define MAX_SIZE_TRAME 50
#define LEDPIN 13


void RN2483_sendCmd( char *cmd);
void RN2483_waitForResponse ();
void RN2483_sendData( byte data[]);
void RN2483_receiveData();
void RN2483_init();
