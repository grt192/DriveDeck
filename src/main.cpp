#include "Arduino.h"
#include "SigmaServos.h"
#include "RotaryEncoder.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Gui.h>


SigmaServos myservo;  // create Servo object to control a servo
RotaryEncoder encoder1; 
RotaryEncoder encoder2; 

RotaryEncoder* instance = nullptr;
RotaryEncoder* instance2 = nullptr;

Gui guiA('A',0,0);
Gui guiB('B',7,0);
Gui guiC('C',0,1);
Gui guiD('D',7,1);
const uint SERVO_PIN = 15;
const int SW_PIN = 2;
// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(112500);
  myservo.attach(15);  // attaches the servo on pin 9 to the Servo object
  encoder1.attach(1,0,SW_PIN);
  encoder2.attach(6,7,SW_PIN);
  pinMode(SW_PIN, INPUT);
  LCDsetup();
}
bool stopped = false;

void loop() {
  guiA.LCDloop(stopped, encoder1.counter);
  guiB.LCDloop(stopped, encoder2.counter);
  guiC.LCDloop(stopped, encoder1.counter);
  guiD.LCDloop(stopped, encoder1.counter);
  /*
  if (digitalRead(SW_PIN) && buttonFlag == true){//pressed
    buttonFlag = false;
    stopped = !stopped;
  }
  else if (!digitalRead(SW_PIN)){
    buttonFlag = true;
  }*/
  //Serial.println(digitalRead(SW_PIN));
  //Serial.print(",");
  //Serial.print(stopped);
  //Serial.print(",");
  //Serial.println(encoder1.counter);
  //0 -200, 100
  if (stopped){
    myservo.write(100);                  // sets the servo position according to the scaled value
  }
  else{
    myservo.write(encoder1.counter+100);                  // sets the servo position according to the scaled value
  }
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}