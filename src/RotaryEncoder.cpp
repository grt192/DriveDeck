#include <Arduino.h>
#include <RotaryEncoder.h>
#include <hardware/pio.h>
#include <array>

std::array<int, RotaryEncoder::maxEncoders> RotaryEncoder::DTpins = { -1 }; // Initialize all pins to -1 (unused)
std::array<int, RotaryEncoder::maxEncoders> RotaryEncoder::CLKpins = { -1 }; // Initialize all pins to -1 (unused)
std::array<RotaryEncoder*, RotaryEncoder::maxEncoders> RotaryEncoder::instances = { nullptr }; // Initialize all pointers to nullptr

size_t RotaryEncoder::encoderCount = 0;

int counterWrap(int counter,int mini,int maxi){
    if (counter < mini){
        return mini;
    }
    else if (counter > maxi){
        return maxi;
    }
    else{
        return counter;
    }
}

void RotaryEncoder::InterruptHandler(uint gpio, uint32_t events){
    for (int i = 0; i < encoderCount; i++){
        if (gpio == CLKpins[i]){
            instances[i]->CLKInterruptFunc();
            return;
        }
        else if (gpio == DTpins[i]){
            instances[i]->DTInterruptFunc();
            return;
        }
    }
};
void interruptSetup(uint gpio){
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);

    gpio_set_irq_enabled_with_callback(
        gpio,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        &RotaryEncoder::InterruptHandler
    );
}


void RotaryEncoder::DTInterruptFunc() {
    Serial.println("DTINTER");
    if (!lastDTorCLK){
    lastDTorCLK = true;
    currCLK = digitalRead(_CLK_PIN);
    //CW->CWW
    if ((
        currCLK == LOW && 
        lastCLK == LOW &&
        currDT == HIGH)
        ||
        (
        currCLK == HIGH &&
        lastCLK == HIGH &&
        currDT == LOW
    )){
        counter = counterWrap(counter-1,minCounter,maxCounter);
    };

    lastCLK = currCLK;
    };
};
void RotaryEncoder::CLKInterruptFunc() {
    Serial.println("CLKINTER");

    if (lastDTorCLK){
    lastDTorCLK = false;
    currDT = digitalRead(_DT_PIN);
    //CW
    if ((
        currCLK == LOW && 
        lastDT == LOW &&
        currDT == HIGH)
        ||
        (
        currCLK == HIGH &&
        lastDT == HIGH &&
        currDT == LOW
    )){
        counter = counterWrap(counter+1,minCounter,maxCounter);

    };
    //CCW
    if ((
        currCLK == HIGH && 
        lastDT == LOW &&
        currDT == HIGH)
        ||
        (
        currCLK == LOW &&
        lastDT == HIGH &&
        currDT == LOW
    )){
        counter = counterWrap(counter-1,minCounter,maxCounter);

    };
    //CCW -> CW
    if ((
        currCLK == HIGH && 
        lastDT == LOW &&
        currDT == LOW)
        ||
        (
        currCLK == LOW &&
        lastDT == HIGH &&
        currDT == HIGH
    )){
        counter = counterWrap(counter+1,minCounter,maxCounter);
        
    };
    lastDT = currDT;
    };
  };
RotaryEncoder::RotaryEncoder() {
    counter = 0;
    lastCLK = true;
    lastDT = true;
    lastDTorCLK = false; //arbitrary

    minCounter = DEFAULT_MIN_COUNTER;
    maxCounter = DEFAULT_MAX_COUNTER;

}

RotaryEncoder::~RotaryEncoder() {}

void RotaryEncoder::attach(pin_size_t DT_PIN, pin_size_t CLK_PIN, pin_size_t SW_PIN) {
    _CLK_PIN = CLK_PIN;
    _DT_PIN = DT_PIN;
    _SW_PIN = SW_PIN;
    
    CLKpins[encoderCount] = CLK_PIN;
    DTpins[encoderCount] = _DT_PIN;
    instances[encoderCount] = this;
    encoderCount++;
    
    pinMode(_SW_PIN, INPUT);

    interruptSetup(_DT_PIN);
    interruptSetup(_CLK_PIN);
    
}
int RotaryEncoder::getCounter(){
    return counter;
}
void RotaryEncoder::resetCounter(){
    counter = 0;
}
bool RotaryEncoder::getButton(){
    return !digitalRead(_SW_PIN);
}