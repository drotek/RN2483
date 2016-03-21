#include <SoftwareSerial.h>
#include "arduino.h"


SoftwareSerial lora(3, 4); // RX, TX
String str;

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
  /*while (!lora.available() ) 
    delay(100);*/
  
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
void RN2483_sendData( byte data) 
{ 
   Serial.write( "radio tx " );
   lora.write( "radio tx " );

   lora.print( data );
   lora.print("\r\n");
    
   Serial.println(data,HEX);
   Serial.write("\n");

   // to check the feedback of the RN2483
   /*while (lora.available())
     Serial.write(lora.read());*/
    
    delay(100);
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
       str = lora.readStringUntil('\n');
       
       if ( str.length() > 1 ) 
       {
          //Serial.println(str.length() - 11);
          
          if ( str.indexOf("radio_rx") >= 0 ) 
          {           
              str = str.substring(10);
              
              //Serial.print("str: ");
              //Serial.println(str);
              
              int val;
              val = str.toInt();
             
              Serial.print("Received data by RN2483: ");
              Serial.print("   DEC: ");
              Serial.print(val,DEC);
              Serial.print("   HEX: 0X");
              Serial.print(val,HEX);
              Serial.print("   BIN: ");
              Serial.println(val,BIN);             
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
