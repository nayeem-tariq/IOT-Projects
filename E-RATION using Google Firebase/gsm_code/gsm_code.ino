#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"
SoftwareSerial gsm (13,15,false,256); // for node mcu the software serial is D2,D1.
void setup()
{
  //gsm.begin(9600);   // Setting the baud rate of GSM Module  
 gsm.begin(9600);
}

void loop()

{
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
 gsm.println("AT+CMGS=\"+917006207921\"\r"); // Replace x with mobile number
  delay(1000);
 gsm.println("hello this is a nmessage from gsm");// The SMS text you want to send
//  delay(1000);'
  gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000000);
}
