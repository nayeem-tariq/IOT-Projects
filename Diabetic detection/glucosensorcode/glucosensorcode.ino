#define button_pin 2

void setup() {
  // put your setup code here, to run once:
pinMode(button_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int button_status = digitalRead(button_pin);

}
