#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
const int A = A2; const int B = A0; const int C = A3;  const int D = A1;
const int in1 = 7; const int in2 = 6; const int in3 = 5; const int in4 = 4;
int A_value = 0; int B_value = 0; int C_value = 0; int D_value = 0;
Servo myservo1; Servo myservo2;
int pos = 0;
#define trigPin 8
#define echoPin 9
#define buzzer 10
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
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT); pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  Serial.begin(9600);
  lcd.begin (16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("AUTONOMOUS CAR");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(0, 1 );
  lcd.print("ADAPTIVE LIGHTS");
  myservo1.attach(2);myservo2.attach(3);
  myservo1.write(90);myservo2.write(90);
}
void loop() {
  int distance, duration;
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
//  Serial.print(distance);
  //Serial.print("CM");
  //Serial.println("");
  A_value = analogRead(A);
  B_value = analogRead(B);
  C_value = analogRead(C);
  D_value = analogRead(D);
  /*Serial.print(A_value); Serial.print("\t\t\t"); Serial.print(B_value); Serial.print("\t\t\t");
    Serial.print(C_value); Serial.print("\t\t\t"); Serial.println(D_value);
  */
  delay(10);
  if (A_value > 1000)
  {
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    digitalWrite(in4, HIGH); digitalWrite(in3, LOW);
  }
  else if (B_value > 1000)
  {
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
    digitalWrite(in4, LOW); digitalWrite(in3, HIGH);
  }
  else if (C_value > 1000)
  {
      for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos); myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
    
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH); digitalWrite(in3, LOW);// waits 15ms for the servo to reach the position
  
  }
  }
  else if (D_value > 1000)
  {
  
 for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos); myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);  
    
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    digitalWrite(in4, LOW); digitalWrite(in3, HIGH);
  }}
  else if (distance < 10)

  {
    lcd.clear();
    lcd.setCursor(0, 0);

    //Print at cursor Location
    lcd.print("FINDING DISTANCE");
    //goto first column (column 0) and second line (line 1)
    lcd.setCursor(0, 1 );
    lcd.print("OBJECT DETECTED");

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
digitalWrite(in1, LOW); digitalWrite(in2, LOW);
    digitalWrite(in4, LOW); digitalWrite(in3, LOW);// waits 15ms for the servo to reach the position
  
    

  }
  else{
    lcd.clear();
  lcd.setCursor(0, 0);
  //Print at cursor Location
  lcd.print("AUTONOMOUS CAR");
  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(0, 1 );
  lcd.print("ADAPTIVE LIGHTS");
   
    
    }



}
