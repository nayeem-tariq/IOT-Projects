int x=A0;

int y=A1;

int headlight=2;

int dimmer=3;

void setup() {
 Serial.begin(9600);

pinMode(x,INPUT);

pinMode(y,INPUT);

pinMode(headlight,OUTPUT);

pinMode(dimmer,OUTPUT);
}

void loop() {
  int ldr1=analogRead(x);

Serial.print("ldr1=");

Serial.print(ldr1);

Serial.print("\t\t\t\t");
int ldr2=analogRead(y);

Serial.print("ldr2=");


Serial.println(ldr2);
delay(500);
 if (ldr1 < 50 && ldr2 < 50)
 {
  digitalWrite(headlight,LOW);
  digitalWrite(dimmer,LOW);
  }
   else if(ldr1 > 150 && ldr2 > 150)
   {
  digitalWrite(dimmer,HIGH);
   digitalWrite(headlight,HIGH);
  }

   else if(ldr1 < 100 && ldr2 > 200)
   {
  analogWrite(dimmer,100);
   analogWrite(headlight,150);
  }
 
 }
