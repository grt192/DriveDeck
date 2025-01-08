#include "Arduino.h"
#include "SigmaServos.h"
#include "RotaryEncoder.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Gui.h>
#include "RP2040_PWM.h"
int PWM_Pins[] = {0, 1, 2, 3};
void init_pwm(uint gpio_pin) {
    // Set the GPIO function to PWM
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM);

    // Get the PWM slice for the GPIO pin
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

    // Calculate 'top' value for a 20 ms period (50 Hz frequency)
    uint32_t clock_freq = clock_get_hz(clk_sys); // System clock frequency
    uint32_t clock_div = 64;                    // Clock divider
    uint32_t top = (clock_freq / clock_div / 50) - 1; // 'top' value for 50 Hz

    // Set the PWM configuration
    pwm_set_clkdiv(slice_num, clock_div); // Set the clock divider
    pwm_set_wrap(slice_num, top);        // Set the PWM top value

    // Enable the PWM output
    pwm_set_enabled(slice_num, true);
}
// Function to set the pulse width based on input from -100 to 100
void set_pwm_duty_cycle(uint gpio_pin, int input) {
    // Clamp input to range [-100, 100]
    if (input < -100) input = -100;
    if (input > 100) input = 100;

    // Map input to pulse width in milliseconds (1 ms to 2 ms)
    float pulse_width_ms = 1.5f + (input / 200.0f); // Centered at 1.5 ms, ±0.5 ms

    // Get the PWM slice and channel for the GPIO pin
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);
    uint channel = pwm_gpio_to_channel(gpio_pin);

    // Get the current 'top' value
    uint32_t top = pwm_hw->slice[slice_num].top + 1;

    // Convert pulse width in ms to the corresponding level
    uint32_t level = (uint32_t)((pulse_width_ms / 20.0f) * top); // Scale by 20 ms period

    // Set the channel level
    pwm_set_chan_level(slice_num, channel, level);
}


RotaryEncoder encoderA;  // create rotaryencoder object to read a rotary encoder
RotaryEncoder encoderB; 
RotaryEncoder encoderC; 
RotaryEncoder encoderD;

Gui guiA('A',0,0);
Gui guiB('B',9,0);
Gui guiC('C',0,1);
Gui guiD('D',9,1);

void mainLogic(Gui& gui, RotaryEncoder& encoder){
  if (false){//(gui1.ifStopped()){
      encoder.resetCounter();

    }
    else{
      
    }
}

volatile bool startLoop1 = false;
volatile bool startLoop = false;

//flag to start the second loop when the setup finishes
void setup() {
  Serial.begin(112500);


 

  encoderA.attach(6,7,8);
  encoderB.attach(9,10,11);
  encoderC.attach(12,13,14);
  encoderD.attach(15,16,17);

  LCDsetup();

  guiA.guiSetup();
  guiB.guiSetup();
  guiC.guiSetup();
  guiD.guiSetup();
  startLoop1 = true;
  while (startLoop == false){
    delay(1);
  }
}
void setup1(){
  //aval pmw pins: GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15, GPIO16, GPIO17, GPIO18, GPIO19, GPIO20, GPIO21, GPIO22, GPIO26, GPIO27, GPIO28, GPIO29.
  init_pwm(0);//A

  init_pwm(2);//B
  init_pwm(3);//C
  init_pwm(28);//D

  //pmwSt  setPWM(1, 50, 10);
  //PWM_Instances[1] = new RP2040_PWM(1, 50, 10);

  // if (PWM_Instances[1])
  // {
  //   PWM_Instances[1] ->setPWM();
  // }
  startLoop = true;
  while (startLoop1 == false){
    delay(1);
  }
}
void loop() {
  guiA.LCDloop(encoderA.getButton(), encoderA.getCounter());
  guiB.LCDloop(encoderB.getButton(), encoderB.getCounter());
  guiC.LCDloop(encoderC.getButton(), encoderC.getCounter());
  guiD.LCDloop(encoderD.getButton(), encoderD.getCounter());
  /*
  mainLogic(guiA,encoderA,servoA);
  mainLogic(guiB,encoderB,servoB);
  mainLogic(guiC,encoderC,servoC);
  mainLogic(guiD,encoderD,servoD);
  */
  
  
}
void loop1(){
  guiA.displayStuff();
  guiB.displayStuff();
  guiC.displayStuff();
  guiD.displayStuff();
  set_pwm_duty_cycle(0,encoderA.getCounter());
  set_pwm_duty_cycle(2,encoderB.getCounter());
  set_pwm_duty_cycle(3,encoderC.getCounter());
  set_pwm_duty_cycle(28,encoderD.getCounter());

  //PWM_Instances[1]->
}