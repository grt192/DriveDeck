#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include <Gui.h>
LiquidCrystal_I2C lcd(0x27,8,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
byte disableChar[] = {
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0x00
};
byte stoppedChar[] = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0x00
};
byte clockwiseChar1[] = {
  0b00000,
  0b00000,
  0b01110,
  0b00000,
  0b10001,
  0b10001,
  0b01010,
  0x00
};
byte clockwiseChar2[] = {
  0b00000,
  0b00000,
  0b01100,
  0b10001,
  0b00001,
  0b10001,
  0b01100,
  0x00
};
byte clockwiseChar3[] = {
  0b00000,
  0b00000,
  0b01010,
  0b10001,
  0b10001,
  0b00000,
  0b01110,
  0x00
};
byte clockwiseChar4[] = {
  0b00000,
  0b00000,
  0b00110,
  0b10001,
  0b10000,
  0b10001,
  0b00110,
  0x00
};
void LCDsetup(){
  lcd.init();                      // initialize the lcd
  lcd.begin(16,2);
  lcd.backlight();
  lcd.createChar(0, clockwiseChar1);
  lcd.createChar(1, clockwiseChar2);
  lcd.createChar(2, clockwiseChar3);
  lcd.createChar(3, clockwiseChar4);
  lcd.createChar(4, disableChar);
  lcd.createChar(5, stoppedChar);

}



Gui::Gui(char ID, int newX, int newY){
        letter = ID;
        dir = 0;
        maxdir = 19;
        symbol = 0;
        stopped = false;
        x = newX;
        y = newY;
        
    };
void Gui::guiSetup(){
    lcd.setCursor(x+0,y);
    lcd.print(letter);
  }
void Gui::displayStuff(){
  if (stopped){
  symbol = 4;
  
  }
  else{
  if (count < 0){
    dir ++;
    dir %= maxdir;
    symbol = dir / 5;
  }
  else if (count > 0){
    dir --;
    if (dir < 0){
      dir = maxdir;
    }
    symbol = dir / 5 ;
  }
  else {//stopped moving
    symbol = 5;
  }
  }
    lcd.setCursor(x+2,y);
    lcd.write(symbol);
    lcd.setCursor(x+4,y);
    lcd.print((String)abs(count) + "  ");
  }
void Gui::LCDloop(bool button, int counter){
    count = counter;
    if (button){//pressed
    if (buttonFlag == true){
      stopped = !stopped;
      Serial.println(stopped);
      buttonFlag = false;
    } 
  }
  else{
    buttonFlag = true;
  }
  
  
};
bool Gui::ifStopped(){
  return stopped;
}