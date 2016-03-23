#include <SoftwareSerial.h>
#include "arduino.h"
#include "RN2483.h"

byte mask = 0xFF;
byte b;
SoftwareSerial lora(3, 4);   // RX, TX
String str, str2;
int ledState2 = LOW;         // ledState used to set the LED


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
  while (lora.available())
    Serial.write(lora.read());
}


/***************************************
*               sendData               *
***************************************/
void RN2483_sendData( byte data[]) 
{ 
   //Serial.write( "radio tx " );
   lora.write( "radio tx " );

   for (int k=0; k<MAX_SIZE_TRAME ;k++)
   {
     lora.print( data[k] );
     Serial.write( data[k]);
     
   }
   lora.print("\r\n");

   // to check the feedback of the RN2483
   /*while (lora.available())
     Serial.write(lora.read());*/
}

/***************************************
*             receiveData              *
***************************************/
void RN2483_receiveData() 
{  
   
  // switch recieve mode
  lora.println("radio rx 0");
  str = lora.readStringUntil('\n');
  
  
  if ( str.indexOf("ok") == 0 ) 
  {
       // if the LED is off turn it on and vice-versa:
       if (ledState2 == LOW)  ledState2 = HIGH;
       else                   ledState2 = LOW;
      
       // set the LED with the ledState of the variable:
       digitalWrite(LEDPIN, ledState2);
       
   
       str = lora.readStringUntil('\n');
       //Serial.println(str );
       
       if ( str.length() > 1 ) 
       {
          //Serial.println(str.length() );
          
          if ( str.indexOf("radio_rx") >= 0 ) 
          {   
              // keep just the hexa data        
              str = str.substring(10);
              
              //Serial.println(str.length() );
              
              for (int l=0; l<(str.length()-2); l=l+2)
              {
                str2 = str.substring(l,l+2);
              
                int val;
                val = str2.toInt();
                b = val & mask;
                Serial.write(b);
              }
                          
         }
      }   
  }
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
  RN2483_sendCmd("radio set sf sf7");
  RN2483_sendCmd("radio set crc on");
  RN2483_sendCmd("radio set cr 4/5");
  RN2483_sendCmd("radio set wdt 0");
  RN2483_sendCmd("radio set sync 12");
  RN2483_sendCmd("radio set bw 500");
  RN2483_sendCmd("mac pause");
}
