#include <SoftwareSerial.h>
#include "arduino.h"


SoftwareSerial lora(3, 4); // RX, TX

/***************************************
*                sendCmd               *
***************************************/
void RN2483_sendCmd( char *cmd) 
{
  Serial.write( cmd );
  Serial.write("\n");
  lora.write(cmd);
  lora.write("\r\n");
  while (!lora.available() ) 
    delay(100);
  
  while (lora.available())
    Serial.write(lora.read());
}

/***************************************
*           waitForResponse            *
***************************************/
void RN2483_waitForResponse() 
{
  while (!lora.available() ) 
    delay(100);
  
  while (lora.available())
    Serial.write(lora.read());
}

/***************************************
*               getHexHi               *
***************************************/
char RN2483_getHexHi( char ch ) 
{  
  char nibble = ch >> 4;
  return (nibble > 9) ? nibble + 'A' - 10 : nibble + '0';
}

/***************************************
*               getHexLo               *
***************************************/
char RN2483_getHexLo( char ch ) 
{
  char nibble = ch & 0x0f;
  return (nibble > 9) ? nibble + 'A' - 10 : nibble + '0';
}

/***************************************
*               sendData               *
***************************************/
void RN2483_sendData( char *data) 
{
  Serial.write( "mac tx uncnf 1 " );
  lora.write( "mac tx uncnf 1 " );
  // Write data as hex characters
  char *ptr = data;
  int idiotCount = 50;
  while (*ptr && idiotCount ) {
    lora.write( RN2483_getHexHi( *ptr ) );
    lora.write( RN2483_getHexLo( *ptr ) );

    Serial.write( RN2483_getHexHi( *ptr ) );
    Serial.write( RN2483_getHexLo( *ptr ) );

    ptr++;
    idiotCount--;
  }
  lora.write("\r\n");
  Serial.write("\n");
  delay(5000);

  while (lora.available())
    Serial.write(lora.read());
}

/***************************************
*              initRN2483              *
***************************************/
void RN2483_init()
{
  lora.begin(57600); 
  
  RN2483_waitForResponse();

  RN2483_sendCmd("sys factoryRESET");
  RN2483_sendCmd("sys reset");
  RN2483_sendCmd("radio set mod lora");
  RN2483_sendCmd("radio set freq 868100000");
  RN2483_sendCmd("radio set pwr 14");
  RN2483_sendCmd("radio set sf sf12");
  RN2483_sendCmd("radio set afcbw 125");
  RN2483_sendCmd("radio set rxbw 250");
  RN2483_sendCmd("radio set fdev 5000");
  RN2483_sendCmd("radio set prlen 8");
  RN2483_sendCmd("radio set crc on");
  RN2483_sendCmd("radio set cr 4/8");
  RN2483_sendCmd("radio set wdt 0");
  RN2483_sendCmd("radio set sync 12");
  RN2483_sendCmd("radio set bw 250");
  RN2483_sendCmd("mac pause");
}
