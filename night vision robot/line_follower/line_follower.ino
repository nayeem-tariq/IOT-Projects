const int ir_left = 8; const int ir_right = 9 ;
const int in1 = 2; const int in2 = 3; const int in3 = 4; const int in4 = 5;
void setup() {
  // put your setup code here, to run once:
pinMode(ir_left,INPUT); pinMode(ir_right,INPUT);
pinMode(in1,OUTPUT); pinMode(in2,OUTPUT); pinMode(in3,OUTPUT); pinMode(in4,OUTPUT);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int ir_left_status = digitalRead(ir_left); int ir_right_status = digitalRead(ir_right);
Serial.print(ir_left_status);  Serial.print("\t\t\t");  Serial.print(ir_right_status);  Serial.println("\t\t\t"); 

if(ir_left_status == HIGH && ir_right_status == HIGH)
{
  digitalWrite(in1,LOW);digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);digitalWrite(in4,HIGH);
 // digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
//digitalWrite(in3,LOW);digitalWrite(in4,HIGH);  
  }
if(ir_left_status == HIGH && ir_right_status == LOW)
{
    digitalWrite(in1,HIGH);digitalWrite(in2,LOW);
digitalWrite(in3,LOW);digitalWrite(in4,HIGH); 
  }
  if(ir_left_status == LOW && ir_right_status == HIGH)
{
    digitalWrite(in1,LOW);digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);digitalWrite(in4,LOW); 
  }
}
