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
#define RX_RN2483


const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;          // ledState used to set the LED

/***************************************
*                setup                 *
***************************************/
void setup() 
{
  Serial.begin(9600);
  Serial.println("RN2483 Test");
  
   // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  
  RN2483_init();

}

/***************************************
*                loop                  *
***************************************/
void loop() {

#ifdef TX_RN2483
 
  /*byte val = B01011010;
  Serial.print("Valeur lue dans serialEvent: ");
  Serial.println(val,HEX);
  RN2483_sendData(val);*/
#endif


#ifdef RX_RN2483
  RN2483_receiveData(); 
  
  // if the LED is off turn it on and vice-versa:
  if (ledState == LOW)  ledState = HIGH;
  else                  ledState = LOW;
      
   // set the LED with the ledState of the variable:
   digitalWrite(ledPin, ledState);
#endif

}


/***************************************
*            serialEvent               *
***************************************/
void serialEvent() 
{
  char inChar; //[45];
  byte val;
  
  while (Serial.available()) 
  { 
    val = Serial.read();
     
    Serial.print("Valeur lue dans serialEvent: ");
    Serial.print("   DEC: ");
    Serial.print(val,DEC);
    Serial.print("   HEX: 0X");
    Serial.print(val,HEX);
    Serial.print("   BIN: ");
    Serial.println(val,BIN);
    RN2483_sendData(val);
    
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)  ledState = HIGH;
    else                  ledState = LOW;
      
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
   
  }
}


