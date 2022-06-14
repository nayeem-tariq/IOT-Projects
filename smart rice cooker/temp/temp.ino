#include <Servo.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
const int menu1 = 5; const int menu2 = 6; const int menu3 = 7;
const int temp = A0; const int motor = 3; const int valve = 4;
int tempval = 0; int var = 1; int var1 = 1; int time_elapsed1 = 0; int mm1=0; int ss1 = 0;
Servo myservo; int pos = 0;
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
  // put your setup code here, to run once:
  Serial.begin(9600);  myservo.attach(2);
  lcd.begin (20, 4);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(5, 0);
  //Print at cursor Location
  lcd.print("Riz-Confit");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(2, 1 );
  lcd.print("A Modified Rice");
  lcd.setCursor(5, 2 );
  lcd.print("Cooker For");
  lcd.setCursor(1, 3 );
  lcd.print("Starch Extraction");
  delay(5000);
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  lcd.clear();
  lcd.setCursor(1, 0);
  //Print at cursor Location
  lcd.print("Initializing......");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(2, 1 );
  lcd.print("Real Time Clock");
  lcd.setCursor(5, 2 );
  lcd.print("Servo Motor");
  lcd.setCursor(3, 3 );
  lcd.print("Motor Circuit");
  delay(5000);
    lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("Make Your Selection");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(1, 1 );
  lcd.print("Menu 1: 2 Persons");
  lcd.setCursor(1, 2 );
  lcd.print("Menu 2: 3 Persons");
  lcd.setCursor(1, 3 );
  lcd.print("Menu 3: 5 Persons");
  pinMode(menu1, INPUT); pinMode(menu2, INPUT); pinMode(menu3, INPUT); pinMode(motor, OUTPUT);pinMode(valve,OUTPUT);
}

void loop() {
  boolean menu1_status = digitalRead(menu1); boolean menu2_status = digitalRead(menu2); boolean menu3_status = digitalRead(menu3);
  // Serial.print(menu1_status); Serial.print("\t\t\t\t");   Serial.print(menu2_status); Serial.print("\t\t\t\t");  Serial.println(menu3_status);
  // put your main code here, to run repeatedly:

  //Serial.println(tempval);
  if (menu1_status == HIGH)
  { delay(100);
var1 = var1+1;
while(var1==2)
{//int inst = millis();
    tempval = analogRead(temp);
  tempval = tempval * 0.48828125;
    lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("Cooking Starch free");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(0, 1 );
  lcd.print("Rice for Two Persons");
  lcd.setCursor(1, 2 );
  lcd.print("Current temp: ");
  lcd.setCursor(15, 2 );
   lcd.print(tempval);
  lcd.setCursor(1, 3 );
  lcd.print("Time Elapsed: ");
   lcd.setCursor(15, 3 );
   lcd.print(mm1);
   lcd.setCursor(17, 3 );
   lcd.print(":");
     lcd.setCursor(18, 3 );
   lcd.print(time_elapsed1);
  delay(1000);
   var = var+1;
   if(var == 2)
    {

      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }



    }
   


   Serial.println(tempval);
     time_elapsed1 = time_elapsed1+1;
if (time_elapsed1 >60)
{mm1 = mm1+1;
time_elapsed1 = 0;
}    
   }
 
  }





}
