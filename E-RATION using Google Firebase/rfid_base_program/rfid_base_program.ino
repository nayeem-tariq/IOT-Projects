#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include "SoftwareSerial.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial rfid (4, 5, false, 256); // for node mcu the software serial is D2,D1.
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define FIREBASE_HOST "e-ration-distribution-system.firebaseio.com"
#define FIREBASE_AUTH "fgfXxcTwSOYkwEou4K6HVYUySwx0XC9fi6Q8aYAI"
//Change line with your WiFi router name and password
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "1234554321"
int data1 = 0;
int ok = -1;
// use Listing 16-1 to find your tag numbers
int tag1[14] = {2, 53, 70, 48, 48, 66, 48, 65, 52, 69, 52, 65, 70, 3};
int tag2[14] = {2, 53, 70, 48, 48, 57, 67, 69, 69, 50, 52, 48, 57, 3};
int tag3[14] = {2, 53, 70, 48, 48, 57, 66, 57, 70, 68, 70, 56, 52, 3};
int tag4[14] = {2, 54, 49, 48, 48, 49, 56, 56, 49, 48, 50, 70, 65, 3};
int newtag[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // used for read comparisons
void setup()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lcd.setBacklight(HIGH); Wire.begin(D4, D3); lcd.begin(20, 4);
  rfid.flush();  Serial.begin(9600); rfid.begin(9600);
  lcd.clear(); lcd.setCursor(1, 0); lcd.print("E-RATION CONSUMER"); lcd.setCursor(1, 1); lcd.print("IDENTIFICATION AND"); lcd.setCursor(0, 2); lcd.print("DISTRIBUTION THROUGH"); lcd.setCursor(2, 3); lcd.print("GOOGLE DATABASE");
  delay(4000);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("connecting to......."); lcd.setCursor(2, 1); lcd.print("google firebase"); lcd.setCursor(0, 2); lcd.print("Establishing link...");
  delay(1000);
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void firebasereconnect()
{
  lcd.setCursor(0, 3);
  lcd.print("Trying to reconnect ");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
boolean comparetag(int aa[14], int bb[14])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 14 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 14)
  {
    ff = true;
  }
  return ff;
}
void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (comparetag(newtag, tag1) == true)
  {
    ok++;
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print("Fetching Details...."); lcd.setCursor(8, 1);  lcd.print("From"); lcd.setCursor(2, 2);  lcd.print("Google Firebase"); lcd.setCursor(3, 3); lcd.print(WiFi.localIP()); delay(2000);
    String Name1 = Firebase.getString("Name1"); String Count1 = Firebase.getString("Count1"); String Rice1 = Firebase.getString("Rice1"); String Flour1 = Firebase.getString("Flour1");
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print(Name1); lcd.setCursor(0, 1);  lcd.print(Count1); lcd.setCursor(0, 2);  lcd.print(Rice1); lcd.setCursor(0, 3);  lcd.print(Flour1); delay(4000);

  }
  if (comparetag(newtag, tag2) == true)
  {
    ok++;
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print("Fetching Details...."); lcd.setCursor(8, 1);  lcd.print("From"); lcd.setCursor(2, 2);  lcd.print("Google Firebase"); lcd.setCursor(3, 3); lcd.print(WiFi.localIP()); delay(2000);
    String Name2 = Firebase.getString("Name2"); String Count2 = Firebase.getString("Count2"); String Rice2 = Firebase.getString("Rice2"); String Flour2 = Firebase.getString("Flour2");
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print(Name2); lcd.setCursor(0, 1);  lcd.print(Count2); lcd.setCursor(0, 2);  lcd.print(Rice2); lcd.setCursor(0, 3);  lcd.print(Flour2); delay(4000);
  }
  if (comparetag(newtag, tag3) == true)
  {
    ok++;
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print("Fetching Details...."); lcd.setCursor(8, 1);  lcd.print("From"); lcd.setCursor(2, 2);  lcd.print("Google Firebase"); lcd.setCursor(3, 3); lcd.print(WiFi.localIP()); delay(2000);
    String Name3 = Firebase.getString("Name3"); String Count3 = Firebase.getString("Count3"); String Rice3 = Firebase.getString("Rice3"); String Flour3 = Firebase.getString("Flour3");
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print(Name3); lcd.setCursor(0, 1);  lcd.print(Count3); lcd.setCursor(0, 2);  lcd.print(Rice3); lcd.setCursor(0, 3);  lcd.print(Flour3); delay(4000);

  }
  if (comparetag(newtag, tag4) == true)
  {
    ok++;
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print("Fetching Details...."); lcd.setCursor(8, 1);  lcd.print("From"); lcd.setCursor(2, 2);  lcd.print("Google Firebase"); lcd.setCursor(3, 3); lcd.print(WiFi.localIP()); delay(2000);
    String Name4 = Firebase.getString("Name4"); String Count4 = Firebase.getString("Count4"); String Rice4 = Firebase.getString("Rice4"); String Flour4 = Firebase.getString("Flour4");
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print(Name4); lcd.setCursor(0, 1);  lcd.print(Count4); lcd.setCursor(0, 2);  lcd.print(Rice4); lcd.setCursor(0, 3);  lcd.print(Flour4); delay(4000);

  }

}
void loop()
{
  if (Firebase.failed())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Firebase Connection");
    lcd.setCursor(7, 1);
    lcd.print("Failed");
    lcd.setCursor(1, 2);
    lcd.print("Data Fetch Failed");
    delay(2000);
    firebasereconnect();
    return;
  }

  lcd.clear(); lcd.setCursor(2, 0);  lcd.print("SHOW YOUR UNIQUE"); lcd.setCursor(2, 1);  lcd.print("RATION CARD AND"); lcd.setCursor(2, 2);  lcd.print("VERIFY PERSONAL"); lcd.setCursor(2, 3); lcd.print("ACCOUNT DETAILS"); delay(500);
  ok = -1;
  if (rfid.available() > 0) // if a read has been attempted
  {
    // read the incoming number on serial RX
    delay(50); // needed to allow time for the data
    // to come in from the serial buffer.
    for (int z = 0 ; z < 14 ; z++) // read the rest of the tag
    {
      data1 = rfid.read();
      newtag[z] = data1;
    }
    rfid.flush(); // stops multiple reads
    // now to match tags up
    checkmytags();
  }
  //now do something based on tag type
  if (ok > 0) // if we had a match
  {

    ok = -1;
  }
  else if (ok == 0) // if we didn't have a match
  {
    ok = -1;
    lcd.clear(); lcd.setCursor(0, 0);  lcd.print("USER NOT REGISTERED"); lcd.setCursor(3, 1);  lcd.print("CONTACT OFFICE"); lcd.setCursor(8, 2);  lcd.print("FOR"); lcd.setCursor(4, 3); lcd.print("REGISTRATION"); delay(500);delay(2000);

    
  }
  rfid.flush();
}
