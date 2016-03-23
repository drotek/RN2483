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

int ledState = LOW;          // ledState used to set the LED
byte val[MAX_SIZE_TRAME];
int i =0;

/***************************************
*                setup                 *
***************************************/
void setup() 
{
  Serial.begin(9600);
  
  // set the digital pin as output:
  pinMode(LEDPIN, OUTPUT);
  
  // initialisation of RN2483
  RN2483_init();
}

/***************************************
*                loop                  *
***************************************/
void loop() 
{

#ifdef RX_RN2483
  RN2483_receiveData(); 
#endif

}


/***************************************
*            serialEvent               *
***************************************/
void serialEvent() 
{ 
  while (Serial.available()) 
  { 
    val[i] = Serial.read(); 
    i++;
    
    if (i==MAX_SIZE_TRAME)
    {   
         RN2483_sendData(val); 
    
         // if the LED is off turn it on and vice-versa:
        if (ledState == LOW)  ledState = HIGH;
        else                  ledState = LOW;
      
        // set the LED with the ledState of the variable:
        digitalWrite(LEDPIN, ledState);     
       i=0;
    }
   
  }
}


