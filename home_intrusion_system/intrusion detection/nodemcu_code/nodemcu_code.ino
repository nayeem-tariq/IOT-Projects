#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
Servo myservo;
#define buzzer_pin D5
#define pir_pin D1
#define ldr_pin D6
#define led_pin D8
#define lock_pin D2
LiquidCrystal_I2C lcd(0x27, 20, 4);
const char* ssid = "Redmi"; //Your Network SSID
const char* password = "1234554321"; //Your Network Password
WiFiClient client;
unsigned long myChannelNumber = 764776; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "J8WOLG5744A4XJQO"; //Your Write API Key
boolean pir_value = 0;
boolean ldr_value = 0;
boolean lock_value = 0;
int pos = 0; 
void setup() {
  lcd.setBacklight(HIGH); Wire.begin(D4, D3); lcd.begin(20, 4);
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(0, 1); lcd.print("DETECTION WITH VIDEO"); lcd.setCursor(1, 2); lcd.print("SURVELLIANCE,TWEET "); lcd.setCursor(1, 3); lcd.print("REMOTE LOCK/UNLOCK");
    WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  myservo.attach(D7);
  myservo.write(0);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connecting to.......");
  lcd.setCursor(1, 1);
  lcd.print("Matlab Thingspeak");
  lcd.setCursor(0, 2);
  lcd.print("Establishing link...");
  delay(4000);
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(4, 3);
    lcd.print("Waiting.....");
    delay(2000);
  }
  lcd.setCursor(0, 3);
  lcd.print("     connected      ");
  delay(3000);
  lcd.setCursor(3, 3);
  lcd.print(WiFi.localIP());
  delay(3000);
 Serial.begin(9600);
pinMode(buzzer_pin, OUTPUT); pinMode(ldr_pin, INPUT); pinMode(led_pin, OUTPUT); pinMode(pir_pin, INPUT); pinMode(lock_pin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
lock_value = digitalRead(lock_pin);
pir_value = digitalRead(pir_pin);
ldr_value = digitalRead(ldr_pin);
Serial.print(pir_value);
Serial.print("\t\t\t\t");
Serial.println(ldr_value);
delay(500);

if(ldr_value == HIGH)

{
  digitalWrite(led_pin,HIGH);
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(2, 1); lcd.print("DETECTION SYSTEM"); lcd.setCursor(1, 2); lcd.print("NIGHT VISION MODE"); lcd.setCursor(6, 3); lcd.print("ENABLED");
  delay(2000);
  }
if(pir_value == HIGH)

{
   digitalWrite(buzzer_pin, HIGH);
  delay(500);
  digitalWrite(buzzer_pin, LOW);
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(2, 1); lcd.print("DETECTION SYSTEM"); lcd.setCursor(1, 2); lcd.print("INTRUSION DETECTION"); lcd.setCursor(6, 3); lcd.print("ENABLED");
 delay(2000);
  }
  if(pir_value == LOW)

{
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(2, 1); lcd.print("DETECTION SYSTEM"); lcd.setCursor(4, 2); lcd.print("NO INTRUSION"); lcd.setCursor(6, 3); lcd.print("DETECTED");
  digitalWrite(buzzer_pin, LOW);
 delay(1000);
  }

  if(ldr_value == LOW)

{
  digitalWrite(buzzer_pin, LOW);
  digitalWrite(led_pin,LOW);
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(2, 1); lcd.print("DETECTION SYSTEM"); lcd.setCursor(1, 2); lcd.print("NIGHT VISION MODE"); lcd.setCursor(5, 3); lcd.print("DISABLED");
  delay(2000);
  }
if(lock_value == HIGH)

{
  
  
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(2, 1); lcd.print("DETECTION SYSTEM"); lcd.setCursor(5, 2); lcd.print("DOOR ACCESS"); lcd.setCursor(6, 3); lcd.print("GRANTED");
  delay(2000);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
   digitalWrite(buzzer_pin, LOW);

    for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  delay(2000);
  for (pos = 150; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

   
  }
if(lock_value == LOW)

{
  
  digitalWrite(buzzer_pin, LOW);
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("HOME INTRUSION"); lcd.setCursor(2, 1); lcd.print("DETECTION SYSTEM"); lcd.setCursor(5, 2); lcd.print("DOOR ACCESS"); lcd.setCursor(6, 3); lcd.print("DISABLED");
  delay(2000);

  }


 //ThingSpeak.setField(1, pir_value);
 // ThingSpeak.setField(2, ldr_value);
//ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
}
