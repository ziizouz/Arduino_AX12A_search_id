#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin (2u)
#define LED_P (13u)
#define BD_VALUES 9

// Possible values
long BaudRates[BD_VALUES] = {1000000ul, 500000ul, 400000ul, 250000ul, 200000ul, 115200ul, 57600ul, 19200ul, 9600ul};
unsigned char id;
bool done = false;

void setup() {
  // put your setup code here, to run once:
  id = 0u;
  pinMode(LED_P, OUTPUT);
  digitalWrite(LED_P, LOW);
}

void loop() {
  
  for (int j=0; j<BD_VALUES; j++)
  {
    ax12a.begin(BaudRates[j], DirectionPin, &Serial);
    ax12a.setEndless(id, ON);
    ax12a.turn(id, RIGHT, 100);
    delay(1000);
    ax12a.end(); // end communication
    delay(100);

    if (!done){
      for(int k =0; k<=j; k++){
        digitalWrite(LED_P, HIGH);
        delay(50);
        digitalWrite(LED_P, LOW);
        delay(50);
        }
        delay(50);  
      }
      
    if (id == 0xfd){
      digitalWrite(LED_P, HIGH);
      done = true;
      }
      
  }
  // update id
  id+=0x01;
  delay(100);
   
}
