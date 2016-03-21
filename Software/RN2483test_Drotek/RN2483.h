#include "arduino.h"

void RN2483_sendCmd( char *cmd);
void RN2483_waitForResponse ();
char RN2483_getHexHi( char ch );
char RN2483_getHexLo( char ch );
void RN2483_sendData( byte data);
void RN2483_receiveData();
void RN2483_init();
