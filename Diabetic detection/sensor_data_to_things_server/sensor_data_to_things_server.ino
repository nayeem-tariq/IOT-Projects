#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include<dht.h>
#include <Adafruit_BMP085.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
dht DHT;
#define DHT11_PIN 14
Adafruit_BMP085 bmp;
float dst, bt, bp, ba;
char dstmp[20], btmp[20], bprs[20], balt[20];
bool bmp085_present = true;
const char* ssid = "Bazil"; //Your Network SSID
const char* password = "password"; //Your Network Password
int pulse_rate = 0;
int pulsepin = A0; //LDR Pin Connected at A0 Pin
WiFiClient client;
unsigned long myChannelNumber = 754073; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "RUAJNECL956CG0TT"; //Your Write API Key
void setup()
{
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  delay(100);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  Wire.begin(D4, D3);
  lcd.begin(20, 4); lcd.clear(); lcd.setCursor(2, 0); lcd.print("PATIENT'S HEALTH"); lcd.setCursor(1, 1); lcd.print("MONITORING SYSTEM"); lcd.setCursor(1, 2); lcd.print("USING THINGS SPEAK"); lcd.setCursor(2, 3); lcd.print("VISUAL ANALYTICS");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connecting to.......");
  lcd.setCursor(1, 1);
  lcd.print("Matlab Thingspeak");
  lcd.setCursor(0, 2);
  lcd.print("Establishing link...");
  delay(2000);
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(4, 3);
    lcd.print("Waiting.....");
    delay(1000);
  }
  lcd.setCursor(0, 3);
  lcd.print("     connected      ");
  delay(2000);
  lcd.setCursor(3, 3);
  lcd.print(WiFi.localIP());
  delay(2000);
}
void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  pulse_rate = analogRead(pulsepin); //Read Analog values and Store in val variable
  //Serial.print(pulse_rate); //Print on Serial Monitor
  int temp = DHT.temperature;
  int humidity = DHT.humidity;
  if (!bmp.begin())
  {
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("Could not find a"); lcd.setCursor(0, 1); lcd.print("valid BMP085 sensor"); lcd.setCursor(3, 2); lcd.print("check wiring!");
    while (1) {}
  }
  int bp =  bmp.readPressure() / 1000;
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Body Temp: "); lcd.setCursor(12, 0); lcd.print(temp); lcd.setCursor(0, 1); lcd.print("Body Hum.: "); lcd.setCursor(12, 1); lcd.print(humidity); lcd.setCursor(0, 2); lcd.print("Pulse Rate: "); lcd.setCursor(13, 2); lcd.print(pulse_rate / 10); lcd.setCursor(0, 3); lcd.print("Blood Pressure: "); lcd.setCursor(17, 3); lcd.print(bp);
  delay(2000);
  ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey); delay(1000);
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey); delay(1000);
  ThingSpeak.writeField(myChannelNumber, 4, (pulse_rate / 10), myWriteAPIKey); delay(1000); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 3, bp, myWriteAPIKey); delay(1000);
  lcd.begin(20, 4); lcd.clear(); lcd.setCursor(4, 0); lcd.print("Sending Data"); lcd.setCursor(9, 1); lcd.print("To"); lcd.setCursor(1, 2); lcd.print("Thingspeak Server"); lcd.setCursor(2, 3); lcd.print(WiFi.localIP());
  delay(3000);

}
