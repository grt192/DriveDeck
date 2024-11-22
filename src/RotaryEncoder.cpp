#include <Arduino.h>
#include <RotaryEncoder.h>
#include <hardware/clocks.h>
#include <hardware/pio.h>

//-------------------------------------------------------------------
// Servo class methods
RotaryEncoder* RotaryEncoder::instance = nullptr;
RotaryEncoder* RotaryEncoder::instance2 = nullptr;
RotaryEncoder* RotaryEncoder::instance3= nullptr;
RotaryEncoder* RotaryEncoder::instance4 = nullptr;

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
    Serial.print(gpio);
    Serial.print("  ");
    if (instance){
        Serial.println("instance1");
    }
    if (instance2){ 
        Serial.println("instance2");
    }
    /*
    if (instance) {
        instance -> InterruptHandler1(gpio,events);
    };
        if (instance2) {
        instance2 -> InterruptHandler1(gpio,events);
    };
        if (instance3) {
        instance3 -> InterruptHandler1(gpio,events);
    };
        if (instance4) {
        instance4 -> InterruptHandler1(gpio,events);
    };*/
};
void RotaryEncoder::InterruptHandler1(uint gpio, uint32_t events){
    if (gpio == _DT_PIN){
        DTInterruptFunc(gpio,events);
    }
    else{
        CLKInterruptFunc(gpio,events);
    }
    
};
void RotaryEncoder::DTInterruptFunc(uint gpio, uint32_t events) {
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
void RotaryEncoder::CLKInterruptFunc(uint gpio, uint32_t events) {
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
    instance = this;
    
    if (!(instance == nullptr)){
        instance = this;
    }
    else if (!(instance2 == nullptr)){
        instance2 = this;
    }
    else if (!(instance3 == nullptr)){
        instance3 = this;
    }
    else if (!(instance4 == nullptr)){
        instance4 = this;
    }

    minCounter = DEFAULT_MIN_COUNTER;
    maxCounter = DEFAULT_MAX_COUNTER;

}

RotaryEncoder::~RotaryEncoder() {
    detach();
}

void RotaryEncoder::attach(pin_size_t DT_PIN, pin_size_t CLK_PIN, pin_size_t SW_PIN) {
    _CLK_PIN = CLK_PIN;
    _DT_PIN = DT_PIN;
    _SW_PIN = SW_PIN;

    gpio_init(_DT_PIN);
    gpio_set_dir(_DT_PIN, GPIO_IN);

    gpio_set_irq_enabled_with_callback(
        _DT_PIN,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        &RotaryEncoder::InterruptHandler
    );

    gpio_init(_CLK_PIN);
    gpio_set_dir(_CLK_PIN, GPIO_IN);

    gpio_set_irq_enabled_with_callback(
        _CLK_PIN,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        &RotaryEncoder::InterruptHandler
    );
    
}