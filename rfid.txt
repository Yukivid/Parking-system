RFID Read Code:

#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9); // RX, TX

int count = 0;

void setup()
{
  Serial.begin(9600);
 
  mySerial.begin(9600);
 
  Serial.println("EM18 RFID Read Code");
}
void loop()
{
  if(mySerial.available())
  {
    count = 0; // Reset count to zero// Keep reading Byte by Byte from the Buffer till the Buffer is empty
    {
      char input = mySerial.read();
      Serial.print(input);
      count++; //
      delay(5); //
    }
  }
}