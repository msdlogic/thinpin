/*

Simple single pin serial reciever for RPI
Requires WiringPI

To Use:

Connect Arduino/AVR pin to RPI GPIO pin
Connect Arduino/AVR Ground pin to RPI Ground pin 

In Arduino IDE, include ThinPin.h library and use TPsendString("Hello From ThinPin\n",avrdigitalpin);

To Compile on RPI

Set RXPIN below to your RPIO GPIO pin
Compile with  gcc thinpin.c -lwiringPi -lrt -o thinpin

Must Run as Root:

% sudo thinpin
Hello From ThinPin


*/
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>

#define RXPIN 22 // GPIO PIN FOR RECEIVE

unsigned char reverse(unsigned char b);
char inrange(long x,long y,long r);

main()
{

unsigned int t_; // Timer Start
unsigned int T1;  // Timer Stop

wiringPiSetupGpio();  // Setup WiringPI in GPIO mode
pinMode(RXPIN,INPUT); // Setup GPIO Receive PIN
piHiPri (1);  // Set priority high

  while(1)
  {
    char byte;
  
    while(!digitalRead(22)) delayMicroseconds(500); // Wait for high input
    
    t_=millis(); // Start Timer
 
    while(digitalRead(22)) delayMicroseconds (500); // Wait for low input
    
    T1=millis()-t_; // Stop Timer

    if(inrange(T1,15,2))
    { 
      byte=reverse(byte);
      printf("%c",byte);
    }
  
    if(inrange(T1,10,2)) byte=(byte << 1)+1; // if we receive a 10ms one signal, add to byte
    if(inrange(T1,5,2))  byte=(byte << 1);  // if we receive a 5ms zero signal, add to byte

  
  }

}

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

char inrange(long x,long y,long r)
{
  if( x > (y-r) & x < (y+r) ) return 1; 
  return 0;
}
