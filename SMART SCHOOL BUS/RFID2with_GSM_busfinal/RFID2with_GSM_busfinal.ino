#include <RFID.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
/*
* MOSI: Pin 11
* MISO: Pin 12
* SCK: Pin 13
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);


int led = 7;
int power = 8; 
int serNum[5];
int cards[][5] = {
  {16,156,119,163,88}
};
int cards2[][5] = {
  {230,149,117,99,101}
};

bool access = false;
bool access2 = false;
void setup(){

    mySerial.begin(9600);
 Serial.begin(9600); 
  delay(100);
    SPI.begin();
    rfid.init();

    pinMode(led, OUTPUT);

    digitalWrite(led, LOW);
   
}

void loop(){
    if (Serial.available()>0)
  switch(Serial.read())
  {
    case 's':
      {SendMessage();
      Serial.print(mySerial.println("AT+CSQ"));
      break;}
    case 'r':
     SendM();
     Call();
      break;
  }
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }


              for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards2[x][i]) {
                      access2 = false;
                      break;
                  } else {
                      access2 = true;
                  }
              }
              if(access2) break;
            }
           
        }
        
       if(access){
          Serial.println("Welcome!");
          SendMessage();
  Serial.print(mySerial.println("AT+CSQ"));
           digitalWrite(led, HIGH); 
           delay(1500);
           digitalWrite(led, LOW);
           digitalWrite(power, HIGH);
           delay(1500);
           digitalWrite(power, LOW);
           
      }
     else if(access2){
          Serial.println("Welcome! tag");
          SendM();
  Serial.print(mySerial.println("AT+CSQ"));
          delay(3000);
          delay(2);
      Call();
  Serial.print(mySerial.println("AT+CSQ"));
           digitalWrite(led, HIGH); 
           delay(1000);
           digitalWrite(led, LOW);
           digitalWrite(power, HIGH);
           delay(1000);
           digitalWrite(power, LOW);
           delay(5000);
      } 
      else {
           Serial.println("Not allowed!"); 
           digitalWrite(led, HIGH);
           delay(500);
           digitalWrite(led, LOW); 
           delay(500);
           digitalWrite(led, HIGH);
           delay(500);
           digitalWrite(led, LOW);         
       }        
    }
    
    
    
    rfid.halt();

}


void SendMessage()
{
  Serial.print("hfhjfj");
  mySerial.println("AT+CMGF=1"); 
  delay(1000);
  mySerial.println("AT+CMGS=\"+918109157256\"\r");
  delay(1000);
  mySerial.println("Child is ON bus");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}

void SendM()
{
  Serial.print("asdffg");
  mySerial.println("AT+CMGF=1"); 
  delay(1000);
  mySerial.println("AT+CMGS=\"+918109157256\"\r");
  delay(1000);
  mySerial.println("Child Reached");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
void Call()
{
  mySerial.println("ATE0\r\n");  
  delay(1000);
  ShowSerialData();
  mySerial.println("AT\r\n");
  delay(1000);
  ShowSerialData();
  mySerial.println("ATD+918109157256;\r\n");
  delay(1000);
  ShowSerialData();
 }

void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}
