#define trigPin 8
#define echoPin 9
#define buzzer 10
void setup()
{
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
//digitalWrite(buzzer_pin, LOW);
}

void loop()
{
int distance,duration;
digitalWrite(trigPin, HIGH);
delay(100);
digitalWrite(trigPin, LOW);
duration=pulseIn(echoPin, HIGH);
distance=(duration/2)/29.1;
Serial.print(distance);
Serial.print("CM");
Serial.println("");
}
