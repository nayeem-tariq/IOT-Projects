#include<SoftwareSerial.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
const int motor1 = 3;
const int motor2 = 4;
#define I2C_ADDR          0x27     //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void setup() {
  lcd.begin (20, 4);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
      lcd.setCursor(5,0);
    //Print at cursor Location
    lcd.print("Riz-Confit");
    //goto first column (column 0) and second line (line 1)
    lcd.setCursor(2,1 );
    lcd.print("A Modified Rice");
     lcd.setCursor(5,2 );
    lcd.print("Cooker For");
    lcd.setCursor(1,3 );
    lcd.print("Starch Extraction");
    delay(5000);
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  lcd.clear();
        lcd.setCursor(1,0);
    //Print at cursor Location
    lcd.print("Initializing......");
    //goto first column (column 0) and second line (line 1)
    lcd.setCursor(2,1 );
    lcd.print("Real Time Clock");
     lcd.setCursor(5,2 );
    lcd.print("Servo Motor");
    lcd.setCursor(3,3 );
    lcd.print("Motor Circuit");
    delay(5000);
    pinMode(motor1, OUTPUT); pinMode(motor2, OUTPUT);
    digitalWrite(motor1,HIGH); delay(3000); digitalWrite(motor1,LOW);delay(3000);
     digitalWrite(motor2,HIGH); delay(3000); digitalWrite(motor2,LOW);delay(3000);
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {

        lcd.clear();
lcd.setCursor(3, 0);
lcd.print("CURRENT TIME");
lcd.setCursor(6, 1);
    lcd.print(tm.Hour);
          lcd.print(':');
          //lcd.setCursor(9, 1);
         lcd.print(tm.Minute);
         lcd.print(':');
           //lcd.setCursor(12, 1);
          lcd.print(tm.Second); 

    
  /*  Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();*/
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
