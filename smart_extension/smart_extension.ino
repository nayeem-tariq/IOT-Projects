void setup() {
  // put your setup code here, to run 
  Serial.begin(9600);
  Serial1.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial1.available()>0){
char data = Serial1.read();
Serial.println(data);
}}
