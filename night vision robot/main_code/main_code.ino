// sound sensor D0 = 10;
// pir sensor D0 = 11
// in 1= 2; in2 = 3; in3 = 4; in4 = 5;
//servo motor signal = 6;
// ir left = 8; if right = 9;
// buzzer = 12;
#include <Servo.h>
Servo myservo; 
const int sound_sensor = 10; const int pir_sensor = 11;
const int buzzer = 12;
const int ir_left = 8; const int ir_right = 9 ;
const int in1 = 2; const int in2 = 3; const int in3 = 4; const int in4 = 5;
int var = 1;int pos = 0; 
void setup() {
  myservo.attach(6);
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sound_sensor,INPUT); pinMode(pir_sensor,INPUT); pinMode(ir_left,INPUT); pinMode(ir_right,INPUT);
pinMode(in1,OUTPUT); pinMode(in2,OUTPUT); pinMode(in3,OUTPUT); pinMode(in4,OUTPUT); pinMode(buzzer,OUTPUT);

}

void loop() {
int sound_sensor_status = digitalRead(sound_sensor); int pir_sensor_status = digitalRead(pir_sensor);
int ir_left_Status = digitalRead(ir_left); int ir_right_Status = digitalRead(ir_right);
Serial.print(sound_sensor_status);  Serial.print("\t\t\t");  Serial.print(pir_sensor_status);  Serial.println("\t\t\t"); 
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
if(sound_sensor_status == HIGH)
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  
  }
if(pir_sensor_status == HIGH)
{
   var = var +1;
   if(var == 2)
   { 
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
   }
  //var =1;
  }
  
  // put your main code here, to run repeatedly:
digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);digitalWrite(in4,LOW);
delay(4000);
digitalWrite(in1,LOW);digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);digitalWrite(in4,HIGH);
delay(4000);
}
