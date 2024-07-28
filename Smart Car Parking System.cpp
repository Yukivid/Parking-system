Smart Car Parking System with Billing using EM18 RFID, DS1307 RTC, LCD Display and Servo Motor:

#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9); // RX, TX

/*
 * 520035F565F7
 * 520013BECF30
 * 52001501E7A1
 * 52001593D80C
 * 52001370FBCA
 */

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int pos = 0;

char input[12];
int count = 0;

int z = 0;

int a = 0, b = 0, c = 0, d = 0, e = 0;

int i = 0;

#define servo 12

void setup()
{
  Serial.begin(9600);

  mySerial.begin(9600);
 
  myservo.attach(servo);
  myservo.write(0);
 
  lcd.begin(16, 2);
 
  lcd.setCursor(0, 0);
  lcd.print("RFID Parking Sys");
}

void loop()
{
  if(i > 0)
  {
    lcd.setCursor(0, 1);
    lcd.print(" Free Slots = ");
    lcd.print(5-i);
    lcd.print(" ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print(" Free Slots = ");
    lcd.print(5-i);
    lcd.print(" ");
  }
 
  tmElements_t tm;
 
  RTC.read(tm);
  int hr = tm.Hour;
  int mint = tm.Minute;
  Serial.println(hr);
  Serial.println(mint);
 
  if (mySerial.available())
  {
    z = 0;
   
    count = 0;
   
    while (mySerial.available() && count < 12)
    {
      input[count] = mySerial.read();
      count++;
      delay(5);
    }
   
    if (count == 12)
    {
      if ((strncmp(input, "520035F565F7", 12) == 0) && (z == 0))
      {
        a++;

        if(a == 1)
        {
          i++;
        }
       
        if((a >= 2) && (hr <= 10))
        {
          a = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.50 ");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((a >= 2) && (hr <= 16))
        {
          a = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.100");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((a >= 2) && (hr > 16))
        {
          a = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.150");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        lcd.setCursor(0, 1);
        lcd.print(" Access Granted ");

        myservo.write(90);              // tell servo to go to position in variable 'pos'
         
        delay(5000);

        myservo.write(0);              // tell servo to go to position in variable 'pos'

        lcd.setCursor(0, 1);
        lcd.print("                ");
       
        z = 1;
      }
     
      else if ((strncmp(input, "520013BECF30", 12) == 0) && (z == 0))//0B0028715705
      {
        b++;

        if(b == 1)
        {
          i++;
        }
       
        if((b >= 2) && (hr <= 10))
        {
          b = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.50 ");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((b >= 2) && (hr <= 16))
        {
          b = 0;
          i = i-1;

          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.100");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((b >= 2) && (hr > 16))
        {
          b = 0;
          i = i-1;

          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.150");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
                         
        lcd.setCursor(0, 1);
        lcd.print(" Access Granted ");
       
        myservo.write(90);              // tell servo to go to position in variable 'pos'
         
        delay(5000);

        myservo.write(0);              // tell servo to go to position in variable 'pos'

        lcd.setCursor(0, 1);
        lcd.print("                ");
       
        z = 1;
      }

      else if ((strncmp(input, "52001501E7A1", 12) == 0) && (z == 0))
      {  
        c++;

        if(c == 1)
        {
          i++;
        }
       
        if((c >= 2) && (hr <= 10))
        {
          c = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.50 ");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
             
        else if((c >= 2) && (hr <= 16))
        {
          c = 0;
          i = i-1;

          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.100");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((c >= 2) && (hr > 16))
        {
          c = 0;
          i = i-1;

          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.150");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        lcd.setCursor(0, 1);
        lcd.print(" Access Granted ");

        myservo.write(90);              // tell servo to go to position in variable 'pos'
         
        delay(5000);

        myservo.write(0);              // tell servo to go to position in variable 'pos'

        lcd.setCursor(0, 1);
        lcd.print("                ");
       
        z = 1;
      }
     
      else if ((strncmp(input, "52001593D80C", 12) == 0) && (z == 0))//0B0028715705
      {        
        d++;

        if(d == 1)
        {
          i++;
        }
       
        if((d >= 2) && (hr <= 10))
        {
          d = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.50 ");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((d >= 2) && (hr <= 16))
        {
          d = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.100");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((d >= 2) && (hr > 16))
        {
          d = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.150");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        lcd.setCursor(0, 1);
        lcd.print(" Access Granted ");
       
        myservo.write(90);              // tell servo to go to position in variable 'pos'
         
        delay(5000);

        myservo.write(0);              // tell servo to go to position in variable 'pos'
       
        lcd.setCursor(0, 1);
        lcd.print("                ");
       
        z = 1;
      }

      else if ((strncmp(input, "52001370FBCA", 12) == 0) && (z == 0))//0B0028715705
      {        
        e++;

        if(e == 1)
        {
          i++;
        }
       
        if((e >= 2) && (hr <= 10))
        {
          e = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.50 ");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((e >= 2) && (hr <= 16))
        {
          e = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.100");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
       
        else if((e >= 2) && (hr > 16))
        {
          e = 0;
          i = i-1;
         
          lcd.setCursor(0, 1);
          lcd.print("Payment = Rs.150");

          delay(1500);
         
          lcd.setCursor(0, 1);
          lcd.print("                ");  
          delay(100);
        }
               
        lcd.setCursor(0, 1);
        lcd.print(" Access Granted ");
       
        myservo.write(90);              // tell servo to go to position in variable 'pos'
         
        delay(5000);

        myservo.write(0);              // tell servo to go to position in variable 'pos'

        lcd.setCursor(0, 1);
        lcd.print("                ");
       
        z = 1;
      }
           
      else
      {
        if (z != 1)
        {          
          lcd.setCursor(0, 1);
          lcd.print("  Access Denied ");
         
          delay(3000);

          lcd.setCursor(0, 1);
          lcd.print("                ");
       
          z = 0;
        }
      }
    }
  }
}