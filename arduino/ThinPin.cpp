/* Simple Arduino Library for sending strings to RPI single GPIO pin 

Usage:

#include <ThinPin.h>

int tx_pin=1; 

void setup() {

  pinMode(tx_pin, OUTPUT);

}

void loop() {

  TPsendString("Hello From ThinPin\n",tx_pin);
}

*/
#include <Arduino.h> include "ThinPin.h"

void TPsendString(char *string,int pin) {
  int i;
  for(i=0;i!=strlen(string);i++)
 {
   TPsendByte(string[i],pin);
   TPstartstop(pin);
 } 
}

void TPsendByte(char byte, int pin) {
  char bit;
  int i=0;
  for(i = 0; i < 8; i++) {
     bit = ((byte >> i) & 0x01);
     if(bit)
     {
        TPsendOne(pin);
     } else
     {
        TPsendZero(pin);
     }
  }
}

void TPstartstop(int pin) {
  digitalWrite(pin,1);
  delay(15);
  digitalWrite(pin,0);
  delay(2);
}

void TPsendZero(int pin) {
  digitalWrite(pin,1);
  delay(5);
  digitalWrite(pin,0);
  delay(2);
}

void TPsendOne(int pin) {
  digitalWrite(pin,1);
  delay(10);
  digitalWrite(pin,0);
  delay(2);
}
