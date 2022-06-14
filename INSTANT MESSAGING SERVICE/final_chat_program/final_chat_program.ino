#include<SoftwareSerial.h>
SoftwareSerial bluetooth (3,4);
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include<SPI.h>
#include"nRF24L01.h"
#include"RF24.h"
#include"printf.h"
#define I2C_ADDR          0x27     //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7
const int buzzer = 8;
//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
bool go_to_tx_mode = false;
char input[32] = "";
void setup() {
  lcd.begin (20,4);
  bluetooth.begin(9600);
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
  radio.printDetails();
     lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("WELCOME TO INSTANT");
    lcd.setCursor(1,1);
    lcd.print("MESSAGING SERVICE");
    lcd.setCursor(2,2);
    lcd.print("WAITING FOR THE");
  lcd.setCursor(1,3);
    lcd.print("SENDER MESSAGES...");
  pinMode(buzzer, OUTPUT);
  // put your setup code here, to run once:
}
void loop() {
  if (go_to_tx_mode)
  {
    radio.stopListening();
    bool ok = radio.write(input, 32);
    if (ok)
    {
      printf("ME : %s\n", input);
      go_to_tx_mode = false;
      radio.startListening();
    }
    else
      printf("could not write....\n");
  }
  if (radio.available())
  {
    char payload[32] = "";
    bool done = false;
    while (!done)
    {
     
      done = radio.read( payload , 32 );
      delay(100);
      printf("HIM : %s\n", payload);
       lcd.clear();
       lcd.setCursor(0,0);
     lcd.print(payload);
     Serial.print(payload);
     digitalWrite(buzzer,HIGH);
     delay(1000);
     digitalWrite(buzzer,LOW);
     // bluetooth.write(payload);
     //delay(2000);
    }

  }
  if (bluetooth.available())
  { 
    int len = bluetooth.readBytesUntil('\n', input, 31);
    input[len] = '\0';
    Serial.print(len);
    go_to_tx_mode = true;
  }


  if (Serial.available())
  { 
    int len = Serial.readBytesUntil('\n', input, 31);
    input[len] = '\0';
    Serial.print(len);
    go_to_tx_mode = true;
  }


 
}
//  if (Serial.available())
//  { 
//  	char txmsg[32];
//  	char buf[100]= Serial.read();
//    int len= sizeof(buf);
//    end=0;
//    for(int i=0;end!=1;i=i+31)
//    {
//    	if(i<len)&&(len<i+31)
//    	for(j=1;buf[i+j]!='\0';j++)
//    	{
//    		txm[j]=buf[i+j];
//    	}
//    	else
//    	for(j=1;j<31;j++)
//    	{
//    		txm[j]=buf[i+j];
//    	}
//    	if(j==30)
//    	{
//    		txm[31]='\0';
//    	}
//    	else
//    	end=1;
//    	go_to_tx(txm);
    	


  //  }

  //}
