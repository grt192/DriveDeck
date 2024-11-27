#include "Arduino.h"
#include "SigmaServos.h"
#include "RotaryEncoder.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Gui.h>

SigmaServos servoA;  // create Servo object to control a servo
SigmaServos servoB;  
SigmaServos servoC;  
SigmaServos servoD;  

RotaryEncoder encoderA;  // create rotaryencoder object to read a rotary encoder
RotaryEncoder encoderB; 
RotaryEncoder encoderC; 
RotaryEncoder encoderD;

Gui guiA('A',0,0);
Gui guiB('B',9,0);
Gui guiC('C',0,1);
Gui guiD('D',9,1);

void mainLogic(Gui& gui1, RotaryEncoder& encoder1, SigmaServos& servo1){
  if (gui1.ifStopped()){
      encoder1.resetCounter();
      servo1.write(100);
    }
    else{
      servo1.write(encoder1.getCounter()+100);
    }
}

void setup() {
  Serial.begin(112500);

  servoA.attach(0);  // attaches the servo on pin 9 to the Servo object
  servoB.attach(1);  // attaches the servo on pin 9 to the Servo object
  servoC.attach(2);  // attaches the servo on pin 9 to the Servo object
  servoD.attach(3);  // attaches the servo on pin 9 to the Servo object

  encoderA.attach(6,7,8);
  encoderB.attach(9,10,11);
  encoderC.attach(12,13,14);
  encoderD.attach(15,16,17);

  LCDsetup();

  guiA.guiSetup();
  guiB.guiSetup();
  guiC.guiSetup();
  guiD.guiSetup();

}

void loop() {
  guiA.LCDloop(encoderA.getButton(), encoderA.getCounter());
  guiB.LCDloop(encoderB.getButton(), encoderB.getCounter());
  guiC.LCDloop(encoderC.getButton(), encoderC.getCounter());
  guiD.LCDloop(encoderD.getButton(), encoderD.getCounter());
  mainLogic(guiA,encoderA,servoA);
  mainLogic(guiB,encoderB,servoB);
  mainLogic(guiC,encoderC,servoC);
  mainLogic(guiD,encoderD,servoD);
  

  
  
}
void loop1(){
  
}