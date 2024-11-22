
#pragma once

#include <Arduino.h>
#include <hardware/pio.h>

#define DEFAULT_MIN_COUNTER -100;
#define DEFAULT_MAX_COUNTER 100;

class RotaryEncoder {
public:
    RotaryEncoder();//constructor
    ~RotaryEncoder();//destructor
    // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure.
    // returns channel number or 0 if failure.
    void attach(pin_size_t DT_PIN, pin_size_t CLK_PIN, pin_size_t SW_PIN);
    // attach the given pin to the next free channel, sets pinMode, min, and max values for write().
    // returns channel number or 0 if failure.
    //int attach(pin_size_t DT_PIN, pin_size_t CLK_PIN);
    // attach the given pin to the next free channel, sets pinMode, min, and max values for write(),
    // and sets the initial value, the same as write().
    // returns channel number or 0 if failure.
    void detach();
    void DTInterrupt();             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
    void CLKinterrupt(); // Write pulse width in microseconds
    int counter;
    bool lastDT;
    bool lastCLK;
    bool currDT;
    bool currCLK;
    pin_size_t  _DT_PIN;
    pin_size_t _CLK_PIN;
    pin_size_t _SW_PIN;
    int minCounter;
    int maxCounter;
private:


    bool lastDTorCLK;//flag
    bool Button;
    static void InterruptHandler(uint gpio, uint32_t events);
    void InterruptHandler1(uint gpio, uint32_t events);

    void DTInterruptFunc(uint gpio, uint32_t events);
    void CLKInterruptFunc(uint gpio, uint32_t events);
    static RotaryEncoder* instance;
    static RotaryEncoder* instance2;
    static RotaryEncoder* instance3;
    static RotaryEncoder* instance4;

};
