/*Design by Stoica Tudor, Iul 2020. Rew Aug 2020.
The program allows the control of a digital potentiometer type M62429 
and the estimated display of the sound level on an LED ring.*/

int cNt=-1;//counter
byte n; //n=0...23 there are 24 states of the system, for 24 attenuation 
        //levels and 24 states of the LED display
        //8 states for Blue, 8 states for Green, 8 states for Red
byte mn;// modulo 
#define dTa 7 // connect to DATA M62429
#define cLk 8 // connect to CLOCK M62429
#define rEnb 5 //Rot enc "B" to ground
#define rEna 3 //Rot enc "A" to ground
#include <FastLED.h>
#define NUM_LEDS 8//the number of LEDs in the ring, here 8
#define DATA_PIN 6//Arduino pin 6 that connects to the data input of the LED ring
CRGB leds[NUM_LEDS];

void setup() {
 pinMode(dTa, OUTPUT);
 pinMode(cLk, OUTPUT);
 pinMode(rEnb, INPUT_PULLUP);
 pinMode(rEna, INPUT_PULLUP);
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
leds[0] = CRGB::Blue;//at start-up there is only one blue LED on, the others off,
                      //corresponding to the maximum attenuation
for(int i=1;i<NUM_LEDS;i++){
leds[i] = CRGB::Black;
FastLED.show(); 
}
}

void loop() {
 n=roTen();//is assigned to the variable "n" one of the 24 values 
           //​​that are associated with the Rotary Encoder position.
  
  mn=n%NUM_LEDS;

switch (n){//depending on the value of the variable n, 
           //choose one of the cases 0 ... 23, 
           //and the LED ring will light up accordingly.

  case 0://lights the first LED blue, the others off
  leds[0] = CRGB::Blue;
  for(int i=mn+1 ;i<NUM_LEDS ;i++){
  leds[i] = CRGB::Black;
  }
  break;
  
  case 1:
   fBlue(mn);
  break;
  

  
 case 2:
  fBlue(mn);
  break;
  

  case 3:
  fBlue(mn);
  break;
  

  
case 4:
  fBlue(mn);
  break;
  
  
  case 5:
   fBlue(mn);
  break;
 

 case 6:
   fBlue(mn);
  break;
  

   case 7://lights all  LEDs blue
  for(int i=0 ;i<mn+1 ;i++){
  leds[i] = CRGB::Blue;
  }
  break;

case 8://lights the first LED green, the others blue
  leds[0] = CRGB::Green;
  for(int i=mn+1 ;i<NUM_LEDS ;i++){
  leds[i] = CRGB::Blue;
   }
  break;
  
  
  case 9:
   fGreen(mn);
   break;
  

  
 case 10:
  fGreen(mn);
  break;
 

  case 11:
 fGreen(mn);
  break;
  

  
case 12:
  fGreen(mn);
  break;
  

  
  case 13:
  fGreen(mn);
  break;
  

  case 14:
  fGreen(mn);
  break;
  

   case 15://lights all  LEDs green
  for(int i=0 ;i<mn+1 ;i++){
  leds[i] = CRGB::Green;
  }
  break;
  

 
case 16://lights the first LED red,the others green
  leds[0] = CRGB::Red;
  for(int i=mn+1 ;i<NUM_LEDS ;i++){
  leds[i] = CRGB::Green;
   }
  break;
  
  
  case 17:
  fRed(mn);
  break;
  

  
 case 18:
  fRed(mn);
  break;
  

  case 19:
  fRed(mn);
  break;
  

  
  case 20:
  fRed(mn);
  break;

  
  case 21:
  fRed(mn);
  break;
  

  case 22:
  fRed(mn);
  break;
  

  case 23://lights all  LEDs red
  for(int i=0 ;i<mn+1 ;i++){
  leds[i] = CRGB::Red;
  }
  break;
  
  }
  
   FastLED.show();//lights the LEDs as appropriate case
   
   vOl(n);//call routine for drive M62429
   
  }


//routine for blue lights LED1 up to LEDi(i<7),the others off
void fBlue(byte x)
{
  for( byte i=0 ;i<mn+1 ;i++){
  leds[i] = CRGB::Blue;
  }
  for( byte i=mn+1 ;i<NUM_LEDS ;i++){
  leds[i] = CRGB::Black;
}
}

//routine for green lights LED1 up to LEDi(i<7),the others blue
void fGreen(byte x)
 {
  for( byte i=0 ;i<mn+1 ;i++){
  leds[i] = CRGB::Green;
  }
  for( byte i=mn+1 ;i<NUM_LEDS ;i++){
  leds[i] = CRGB::Blue;
}
}

//routine for red lights LED1 up to LEDi(i<7),the others green
void fRed(byte x)
{
  for( byte i=0 ;i<mn+1 ;i++){
  leds[i] = CRGB::Red;
  }
  for( byte i=mn+1 ;i<NUM_LEDS ;i++){
  leds[i] = CRGB::Green;
}
}

   // Rotary Encoder routine
   int roTen(){  
   
   while(digitalRead(rEnb) & digitalRead(rEna)==1);
 
 
   switch(digitalRead(rEnb)) {
    
    case HIGH:
    while(digitalRead(rEna)==0);
    while(digitalRead(rEnb)==0);
    cNt ++;
    cNt=constrain(cNt,0,23);
    break;
   
   case LOW:
   while(digitalRead(rEnb)==0);
   while(digitalRead(rEna)==0);
   cNt --;
   cNt=constrain(cNt,0,23);
   break;
  
   }
   return cNt;
   }   
          
   //Drive M62429 routine
   void vOl (uint8_t aTTn){
   uint16_t maTn []={//matrix with 24 elements, containing the binary words that 
                     //will program the attenuation level of M62429
    0x0604, 0x0784, 0x0788, 0x078C, 0x0790, 0x0794, 0x0798, 0x079C, 
    0x07A0, 0x07A4, 0x07A8, 0x07AC, 0x07B0, 0x07B4, 0x07B8, 0x07BC, 
    0x07C0, 0x07C4, 0x07C8, 0x07CC, 0x07D0, 0x0654, 0x06D4, 0x0754
    };
    
    // send out 11 control bits
    for (byte i = 0; i < 11; i++) { 
    delayMicroseconds (2); // M62429P datasheet
    digitalWrite (dTa, 0);
    delayMicroseconds (2);// M62429P datasheet
    digitalWrite (cLk, 0);
    delayMicroseconds (2);// M62429P datasheet
    digitalWrite (dTa, (maTn[aTTn] >> i) & 0x01);
    delayMicroseconds (2);// M62429P datasheet
    digitalWrite(cLk, 1);
  }
  delayMicroseconds (2);// M62429P datasheet
  digitalWrite (dTa, 1); 
  delayMicroseconds (2);// M62429P datasheet
  digitalWrite (cLk, 0);
}
