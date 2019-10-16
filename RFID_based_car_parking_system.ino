#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
int servoPin = 8;
int servooPin = 7;
const int analogInPin1 = A0;
const int analogInPin2 = A1;
const int analogInPin3 = A2;
const int analogInPin4 = A3;
const int analogInPin5 = A4;
const int analogInPin6 = A5;
int sensorValue = 0;
int sensorrValue = 0;
int i = 0;
int j = 0;
int entval=0;  // for opened check value at enterance
int occval=0;  // for occupency check value
int extval=0;  // for opened check value at exit
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 Servo servo;
Servo servoo;
void setup() 
{servo.attach(servoPin = 8);
servoo.attach(servooPin = 7);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void gate_opening() // code to open the gate at enterance
 {

    sensorValue = analogRead(analogInPin1);
    if (sensorValue <600) // entrance Gate
      {

         for ( i=0;i<=90;i++)
          {
               servo.write(i);
               delay(30);
          }

         Serial.println(" ENTERANCE GATE IS OPENED");
         entval=1;// indicating that gate is opened
         delay(3000);
     }

 }

void exit_gate()
 {
    sensorrValue = analogRead(analogInPin6);
    if (sensorrValue <600) // exit Gate
      {
        for ( j=0;j<=90;j++)
          {
            servoo.write(j);
            delay(30);
          }
        extval=1;
      }
     if(entval==1) // condition to close the gate
         {
           for ( i=90;i>0;i--)
           servo.write(i);
           delay(30);
         }
 }


void occupency(){
  if (analogRead(A1)<500)       
       {
        Serial.println("a1 is occupied");
        occval++;
       }
     else
        {
         Serial.println("a1 is unoccupied");
        }
          
   if (analogRead(A2)<500)       
       {
        Serial.println("a2 is occupied");
        occval++;
       }
     else
        {
         Serial.println("a2 is unoccupied");
        }
          
    if (analogRead(A3)<500)       
       {
       Serial.println("a3 is occupied");
       occval++;
       }
     else
       { 
       Serial.println("a3 is unoccupied");
       }
          
    if (analogRead(A4)<500)       
       {
       Serial.println("a4 is occupied");
       occval++;
       }
     else
       {
         Serial.println("a4 is unoccupied");
       }
}


void loop() 
{
  occval=0;
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
  }
    return;
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
   {
      Serial.println("Authorized access");
      Serial.println();
      delay(1000);
      if(occval<5)
         {
          gate_opening();     
        }
      else
      {
        Serial.println("PLACE IS FULLY OCCUPIED");
      }
      
       if(entval==1) // condition to close the gate
         {
           for ( i=90;i>0;i--)
           servo.write(i);
           delay(30);
         }
  
  
       occupency();// check for the occupency of car slots
       
  
  
  
  
  
  
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 
