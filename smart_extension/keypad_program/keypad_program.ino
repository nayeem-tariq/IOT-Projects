/* @file CustomKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates changing the keypad size and key values.
  || #
*/
#include <Keypad.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR          0x27       //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7
//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
char hour1[2] = "";
int ind1 = 0;
char min1[2] = "";
int ind2 = 0;
char sec1[2] = "";
int ind3 = 0;
int flag1 = 0;


char hour2[2] = "";
int ind4 = 0;
char min2[2] = "";
int ind5 = 0;
char sec2[2] = "";
int ind6 = 0;
int flag2 = 0;



char hour3[2] = "";
int ind7 = 0;
char min3[2] = "";
int ind8 = 0;
char sec3[2] = "";
int ind9 = 0;
int flag3 = 0;



char hour4[2] = "";
int ind10 = 0;
char min4[2] = "";
int ind11 = 0;
char sec4[2] = "";
int ind12 = 0;
int flag4 = 0;




void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(11, OUTPUT);
  analogWrite(A0,255);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  lcd.begin (20, 4);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);

  //goto first column (column 0) and first line (Line 0)
  lcd.setCursor(3, 0);

  //Print at cursor Location
  lcd.print("LOAD SHEDDING");

  //goto first column (column 0) and second line (line 1)
  lcd.setCursor(2, 1 );
  lcd.print("TIME MANAGEMENT");
  lcd.setCursor(8, 2 );
  lcd.print("WITH");
  lcd.setCursor(2, 3 );
  lcd.print("PROG. INTERFACE");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press A; D1 On Time");
  lcd.setCursor(0, 1);
  lcd.print("Press B; D1 Off Time");
  lcd.setCursor(0, 2);
  lcd.print("Press C; D2 On Time");
  lcd.setCursor(0, 3);
  lcd.print("Press D; D2 Off Time");
}

void loop() {

  char customKey = customKeypad.getKey();
  if (customKey) {



    if (customKey == 'A')
    {

      flag1 = flag1 + 1;
      customKey = 0;
    }





    switch (flag1)
    {
      case 1:
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Enter Hour:");
        if (customKey) {
          hour1[ind1] = customKey;
          ind1++;

          if (ind1 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Hour =");
            lcd.setCursor(10, 1);
            lcd.print(hour1);


            ind1 = 0;
          }

        }
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Enter Minutes:");
        if (customKey) {
          min1[ind2] = customKey;
          ind2++;

          if (ind2 == 2)
          {
            lcd.setCursor(3, 1);
            lcd.print("Minutes =");
            lcd.setCursor(12, 1);
            lcd.print(min1);
            ind2 = 0;
          }
        }
        break;


      case 3:

        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Enter Seconds:");


        if (customKey) {
          sec1[ind3] = customKey;
          ind3++;

          if (ind3 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Seconds =");
            lcd.setCursor(12, 1);
            lcd.print(sec1);
            ind3 = 0;
          }
        }

        break;

      case 4:
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Device 1 ON Time");
        lcd.setCursor(6, 1);
        lcd.print(hour1);
        lcd.setCursor(8, 1);
        lcd.print(":");

        lcd.setCursor(9, 1);
        lcd.print(min1);
        lcd.setCursor(11, 1);
        lcd.print(":");
        lcd.setCursor(12, 1);
        lcd.print(sec1);


    }
  }

  if (customKey) {

    if (customKey == 'B')
    {
      flag1 = 0;
      flag2 = flag2 + 1;
      customKey = 0;
    }


    switch (flag2)
    {
      case 1:

        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Enter Hour:");


        if (customKey) {
          hour2[ind4] = customKey;
          ind4++;

          if (ind4 == 2)
          {
            lcd.setCursor(3, 1);
            lcd.print("Hour =");
            lcd.setCursor(10, 1);
            lcd.print(hour2);
            ind4 = 0;
          }
        }
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Enter Minutes:");
        if (customKey) {
          min2[ind5] = customKey;
          ind5++;

          if (ind5 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Minutes =");
            lcd.setCursor(12, 1);
            lcd.print(min2);
            ind5 = 0;
          }
        }
        break;


      case 3:

        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Enter Seconds:");
        if (customKey) {
          sec2[ind6] = customKey;
          ind6++;

          if (ind6 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Seconds =");
            lcd.setCursor(12, 1);
            lcd.print(sec2);
            ind6 = 0;
          }
        }
        break;
      case 4:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Device 1 OFF Time");
        lcd.setCursor(6, 1);
        lcd.print(hour2);
        lcd.setCursor(8, 1);
        lcd.print(":");

        lcd.setCursor(9, 1);
        lcd.print(min2);
        lcd.setCursor(11, 1);
        lcd.print(":");
        lcd.setCursor(12, 1);
        lcd.print(sec2);




    }

  }


  if (customKey) {

    if (customKey == 'C')
    {
      flag3 = flag3 + 1;
      customKey = 0;
    }


    switch (flag3)
    {
      case 1:
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Enter Hour:");
        if (customKey) {
          hour3[ind7] = customKey;
          ind7++;

          if (ind7 == 2)
          {lcd.setCursor(3, 1);
            lcd.print("Hour =");
            lcd.setCursor(10, 1);
            lcd.print(hour3);
            ind7 = 0;
          }
        }
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Enter Minutes:");
        if (customKey) {
          min3[ind8] = customKey;
          ind8++;

          if (ind8 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Minutes =");
            lcd.setCursor(12, 1);
            lcd.print(min3);
            ind8 = 0;
          }
        }
        break;


      case 3:
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Enter Seconds:");
        if (customKey) {
          sec3[ind9] = customKey;
          ind9++;

          if (ind9 == 2)
          {


            lcd.setCursor(3, 1);
            lcd.print("Seconds =");
            lcd.setCursor(12, 1);
            lcd.print(sec3);
            ind9 = 0;
          }
        }
        break;

      case 4:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Device 2 ON Time");
        lcd.setCursor(6, 1);
        lcd.print(hour3);
        lcd.setCursor(8, 1);
        lcd.print(":");

        lcd.setCursor(9, 1);
        lcd.print(min3);
        lcd.setCursor(11, 1);
        lcd.print(":");
        lcd.setCursor(12, 1);
        lcd.print(sec3);




    }

  }






  if (customKey) {

    if (customKey == 'D')
    {
      flag4 = flag4 + 1;
      customKey = 0;
    }


    switch (flag4)
    {
      case 1:
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Enter Hour:");
        if (customKey) {
          hour4[ind10] = customKey;
          ind10++;

          if (ind10 == 2)
          {lcd.setCursor(3, 1);
            lcd.print("Hour =");
            lcd.setCursor(10, 1);
            lcd.print(hour4);
            ind10 = 0;
          }
        }
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Enter Minutes:");
        if (customKey) {
          min4[ind11] = customKey;
          ind11++;

          if (ind11 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Minutes =");
            lcd.setCursor(12, 1);
            lcd.print(min4);
            ind11 = 0;
          }
        }
        break;


      case 3:
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Enter Seconds:");
        if (customKey) {
          sec4[ind12] = customKey;
          ind12++;

          if (ind12 == 2)
          {

            lcd.setCursor(3, 1);
            lcd.print("Seconds =");
            lcd.setCursor(12, 1);
            lcd.print(sec4);
            ind12 = 0;
          }
        }
        break;
          case 4:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Device 2 OFF Time");
        lcd.setCursor(6, 1);
        lcd.print(hour4);
        lcd.setCursor(8, 1);
        lcd.print(":");

        lcd.setCursor(9, 1);
        lcd.print(min4);
        lcd.setCursor(11, 1);
        lcd.print(":");
        lcd.setCursor(12, 1);
        lcd.print(sec4);

    }

  }




  if (customKey) {

    if (customKey == '*')
    {
      while (1)
      {
        tmElements_t tm;

        if (RTC.read(tm)) {
          /*Serial.print("Ok, Time = ");
          print2digits(tm.Hour);
          Serial.write(':');
          print2digits(tm.Minute);
          Serial.write(':');
          print2digits(tm.Second);
          /*  Serial.print(", Date (D/M/Y) = ");
            Serial.print(tm.Day);
            Serial.write('/');
            Serial.print(tm.Month);
            Serial.write('/');
            Serial.print(tmYearToCalendar(tm.Year));
          Serial.println();*/
   if (tm.Hour == atoi(hour1) && tm.Minute == atoi(min1))
          {
            digitalWrite(10, HIGH);
           
          }

   if (tm.Hour == atoi(hour2) && tm.Minute == atoi(min2))
          {
            digitalWrite(10, LOW);
           
          }


    if (tm.Hour == atoi(hour3) && tm.Minute == atoi(min3))
          {
            digitalWrite(11, HIGH);
           
          }

   if (tm.Hour == atoi(hour4) && tm.Minute == atoi(min4))
          {
            digitalWrite(11, LOW);
           
          }
lcd.clear();
lcd.setCursor(3, 0);
lcd.print("CURRENT TIME");
lcd.setCursor(6, 1);
    lcd.print(tm.Hour);
          lcd.print(':');
//          lcd.setCursor(9, 1);
         lcd.print(tm.Minute);
         lcd.print(':');
  //         lcd.setCursor(12, 1);
          lcd.print(tm.Second);

        lcd.setCursor(0, 2);
        lcd.print("D1 ON TIME:");
    //    lcd.setCursor(12, 2);
        lcd.print(hour1);
      //  lcd.setCursor(13, 2);
        lcd.print(":");

      //  lcd.setCursor(15, 2);
        lcd.print(min1);
        //lcd.setCursor(16, 2);
        lcd.print(":");
        //lcd.setCursor(18, 2);
        lcd.print(sec1);



      lcd.setCursor(0, 3);
        lcd.print("D1 OFF TIME:");
        //lcd.setCursor(12, 3);
        lcd.print(hour2);
        //lcd.setCursor(14, 2);
        lcd.print(":");

        //lcd.setCursor(15, 3);
        lcd.print(min2);
        //lcd.setCursor(17, 2);
        lcd.print(":");
        //lcd.setCursor(18, 3);
        lcd.print(sec2);


        delay(2000);

        lcd.clear();
lcd.setCursor(3, 0);
lcd.print("CURRENT TIME");
lcd.setCursor(6, 1);
    lcd.print(tm.Hour);
          lcd.print(':');
          //lcd.setCursor(9, 1);
         lcd.print(tm.Minute);
         lcd.print(':');
           //lcd.setCursor(12, 1);
          lcd.print(tm.Second);

        lcd.setCursor(0, 2);
        lcd.print("D2 ON TIME:");
        //lcd.setCursor(12, 2);
        lcd.print(hour3);
      //  lcd.setCursor(13, 2);
        lcd.print(":");

        //lcd.setCursor(15, 2);
        lcd.print(min3);
        //lcd.setCursor(16, 2);
        lcd.print(":");
        //lcd.setCursor(18, 2);
        lcd.print(sec3);


lcd.setCursor(0, 3);
        lcd.print("D2 OFF TIME:");
      
       // lcd.setCursor(12, 3);
        lcd.print(hour4);
        //lcd.setCursor(14, 2);
        lcd.print(":");

       // lcd.setCursor(15, 3);
        lcd.print(min4);
        //lcd.setCursor(17, 2);
        lcd.print(":");
        //lcd.setCursor(18, 3);
        lcd.print(sec4);
delay(2000);
          
        } else {
          /*
            if (RTC.chipPresent()) {
              Serial.println("The DS1307 is stopped.  Please run the SetTime");
              Serial.println("example to initialize the time and begin running.");
              Serial.println();
            } else {
              Serial.println("DS1307 read error!  Please check the circuitry.");
              Serial.println();
            }
            delay(9000);*/
        }
        delay(1000);

      }

    }






  }


}




void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
