/******************************************************************************
*
* @file       RN2483.ino
* @author     J.Perin, http://www.drotek.com Copyright (C) 2016.
* @brief      Software to test RN2483 breakout board
* @license    The GNU Public License (GPL) Version 3
* @Changelog  xx-xx-2015 - ...
*
*****************************************************************************/

#include <SoftwareSerial.h>
#include "RN2483.h"

String str;

/***************************************
*                setup                 *
***************************************/
void setup() 
{
  Serial.begin(9600);
  Serial.println("RN2483 Test");
  
  RN2483_init();

  /*pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  delay(50);
  digitalWrite(5, LOW);
  delay(50);
  digitalWrite(5, HIGH);
  delay(50);*/
}

/***************************************
*                loop                  *
***************************************/
void loop() {

#ifdef TX
  char msgBuf[40] = "helloworld";
  //sprintf(msgBuf, "{\"temp\":%d.%01d}", (int)temperature, (int)(temperature * 10) % 10);
  Serial.println(msgBuf);
  RN2483_sendData(msgBuf);

  delay(60000);
#endif


#ifdef RX

#endif
}





#ifdef toto

  // switch recieve mode
  Serial.println("radio rx 0");
  str = Serial.readStringUntil('\n');
  
  if ( str.indexOf("ok") == 0 ) {
    int ok=0;
    while ( ok == 0 ) {
       str = Serial.readStringUntil('\n');
       if ( str.length() > 1 ) {
          if ( str.indexOf("radio_rx") >= 0 ) {
            if ( str.indexOf("0123456789AB") >= 0 ) {
              int j;
              for ( j = 0 ; j < 10 ; j++) {
                 digitalWrite(3,HIGH);
                 delay(100);
                 digitalWrite(3,LOW);
                 delay(100);
              }
            }
            ok = 1;
         }
      }
  } 
}
#endif
