#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

Serial.begin(115200);
lcd.setBacklight(HIGH);

//Use predefined PINS consts

Wire.begin(D4, D3);

lcd.begin(16,2);

lcd.home();

lcd.print("Hello, NodeMCU");

}

void loop() 
{ // do nothing here }
  
}

