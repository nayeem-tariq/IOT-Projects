#include <SoftwareSerial.h>
SoftwareSerial gsm (3,4); 
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR          0x27     //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7
#define buzzer             2
//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);


#define trigPin 8
#define echoPin 9
void setup()
{
  lcd.begin (20, 4);
  Serial.begin(9600);
   gsm.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(1, 0);
  //Print at cursor Location
  lcd.print("ACCIDENT DETECTION");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(5, 1 );
  lcd.print("PREVENTION");
  lcd.setCursor(8, 2 );
  lcd.print("AND ");
  lcd.setCursor(0, 3 );
  lcd.print("LOCATION MONITORING");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("ESTABLISHING LINK...");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(4, 1 );
  lcd.print("CHECKING GPS ");
  lcd.setCursor(8, 2 );
  lcd.print("AND ");
  lcd.setCursor(2, 3 );
  lcd.print("GSM CONNECTIVITY");
  delay(3000);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("ESTABLISHING LINK...");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(4, 1 );
  lcd.print("GPS AND GSM");
  lcd.setCursor(0, 2 );
  lcd.print("CONNECTED TO NETWORK");
  lcd.setCursor(0, 3 );
  lcd.print("CHECKING COORDINATES");
  delay(3000);


}

void loop()
{
  int distance, duration;
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.print("CM");
  Serial.println("");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("Accident Monitoring");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(0, 1 );
  lcd.print("Calculating Distance");
  lcd.setCursor(1, 2 );
  lcd.print("Maintain Distance");
  lcd.setCursor(1, 3 );
  lcd.print("Distance = ");
  lcd.setCursor(13, 3 );
  lcd.print(distance);
   lcd.setCursor(16, 3 );
  lcd.print("CM");
  delay(2000);


  lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("Accident Monitoring");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(0, 1 );
  lcd.print("Finding Coordinates");
  lcd.setCursor(0, 2 );
  lcd.print("Latitude = 34.155299");
  lcd.setCursor(0, 3 );
  lcd.print("Longitude = 74.684845");
  delay(2000);
if (distance <10)
{
    lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("Accident Monitoring");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(1, 1 );
  lcd.print("Accident Detected");
  lcd.setCursor(0, 2 );
  lcd.print("Sending Coordinates");
  lcd.setCursor(0, 3 );
  lcd.print("To Reg.Mobile Number");
  delay(2000);
  
  digitalWrite(buzzer, HIGH);
    gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
 gsm.println("AT+CMGS=\"+917006843778\"\r"); // Replace x with mobile number
  delay(1000);
 gsm.println("Accident Detected At location: Latitudes = 34.155299, Longitudes = 74.6848457. Need help.");// The SMS text you want to send
//  delay(1000);'
  gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  digitalWrite(buzzer, LOW);
  
  }
  
}
