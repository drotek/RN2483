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
#define TX


const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;          // ledState used to set the LED

/***************************************
*                setup                 *
***************************************/
void setup() 
{
  Serial.begin(57600);
  Serial.println("RN2483 Test");
  
   // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  
  RN2483_init();

}

/***************************************
*                loop                  *
***************************************/
void loop() {

#ifdef TX
  
  char msgBuf[45];// = "01234567890123456789012345678901234567890123";
  
  for (int i=0; i<10; i++)
  {
    sprintf(msgBuf, "0123456789012345678901234567890123456789%d", (int)i);
    RN2483_sendData(msgBuf);
    
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
      
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    
    if (i==9) i=0;
  }
#endif


#ifdef RX
  RN2483_receiveData(); 
  
  // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
      
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
#endif

}


