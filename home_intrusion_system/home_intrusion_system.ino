#define buzzer_pin D5
#define pir_pin D1
#define ldr_pin D6
#define led_pin D8
boolean pir_value = 0;
boolean ldr_value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(buzzer_pin, OUTPUT); pinMode(ldr_pin, INPUT); pinMode(led_pin, OUTPUT); pinMode(pir_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
pir_value = digitalRead(pir_pin);
ldr_value = digitalRead(ldr_pin);
Serial.print(pir_value);
Serial.print("\t\t\t\t");
Serial.println(ldr_value);
delay(500);
}
