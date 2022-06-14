#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"
SoftwareSerial rfid (4,5,false,256); // for node mcu the software serial is D2,D1.
int data = 0;
void setup() {
  Serial.begin(9600);// put your setup code here, to run once:
rfid.begin(9600); // initialize rfid module
}

void loop()
{
if (rfid.available() > 0) {
  delay(100);
data = rfid.read();
// display incoming number
Serial.print(" ");
Serial.print(data, DEC);
}
}
