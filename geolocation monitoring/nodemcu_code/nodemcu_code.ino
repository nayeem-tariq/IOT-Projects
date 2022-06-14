/* The Code is developed by Alok Shaw (alokom78@gmaail.com) and is free to use and modify. Watch the full explanation for the same on
    Youtube : www.youtube.com/roboshala
*/
//
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int buzzer = D7;
int flag = 1;
static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget
//WidgetLCD lcd(V6);
SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device

BlynkTimer timer;

float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS

char auth[] = "tq9USfDRFwB9h2TOulZfit8p575TIKNc";              //Your Project authentication key
char ssid[] = "bhatsaleem";                                       // Name of your network (HotSpot or Router name)
char pass[] = "psycho123";                                      // Corresponding Password




//unsigned int move_index;         // moving index, to be used later
unsigned int move_index = 1;       // fixed location for now


void setup()
{
  lcd.setBacklight(HIGH);
  //Use predefined PINS consts
  Wire.begin(D4, D3);
  lcd.begin(16, 2);
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Geolocation and");
  lcd.setCursor(0, 1);
  lcd.print("Route monitoring");
  delay(2000);
  lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("Saleem Yousuf");
  lcd.setCursor(4,1);
  lcd.print("CSE DBIT");
  delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print("Connecting to...");
  lcd.setCursor(2,1);
  lcd.print("Blynk Server");
  delay(2000);
  Serial.begin(9600);
  // Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  //timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
  pinMode(buzzer,OUTPUT);
}

void checkGPS() {
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    //Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
    //lcd.print(0,0, "connecting....");
    //Blynk.virtualWrite(V6, LOW);
    flag =1;
  }
}

void loop()
{

  while (ss.available() > 0)
  {

    flag = flag+1;
    if (flag ==2)
    {
      digitalWrite(buzzer,HIGH);
      delay(2000);
      digitalWrite(buzzer,LOW);
      delay(500);
      
    lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("GPS connected");
  lcd.setCursor(1,1);
  lcd.print("Data Received");
  delay(2000);      
      
      }
    // sketch displays information every time a new sentence is correctly encoded.
    if (gps.encode(ss.read()))
      displayInfo();
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{

  if (gps.location.isValid() )
  {
    //Blynk.virtualWrite(V6, HIGH);
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon.
    float longitude = (gps.location.lng());

    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lat = ");
    lcd.setCursor(6, 0);
    lcd.print(latitude);
    lcd.setCursor(0, 1);
    lcd.print("Lon = ");
    lcd.setCursor(6, 1);
    lcd.print(longitude);
    Blynk.virtualWrite(V1, String(latitude, 6));
    Blynk.virtualWrite(V2, String(longitude, 6));
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph();               //get speed
    Blynk.virtualWrite(V3, spd);

    sats = gps.satellites.value();    //get number of satellites
    Blynk.virtualWrite(V4, sats);

    bearing = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
    Blynk.virtualWrite(V5, bearing);


  }


  Serial.println();
}
