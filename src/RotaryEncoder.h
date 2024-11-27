#include <Arduino.h>
#include <hardware/pio.h>
#include <array>

#define DEFAULT_MIN_COUNTER -100;
#define DEFAULT_MAX_COUNTER 100;
#define MAX_ENCODERS 10;

class RotaryEncoder {
public:
    static constexpr size_t maxEncoders = MAX_ENCODERS;
    static std::array<int, maxEncoders> CLKpins;
    static std::array<int, maxEncoders> DTpins;
    static std::array<RotaryEncoder*, maxEncoders> instances;
    static size_t encoderCount;

    RotaryEncoder();//constructor
    ~RotaryEncoder();//destructor
    //attaches a rotary encoder interrupt to a DT_PIN and CLK_PIN
    void attach(pin_size_t DT_PIN, pin_size_t CLK_PIN, pin_size_t SW_PIN);
    int getCounter();
    void resetCounter();
    bool getButton();
    int minCounter;
    int maxCounter;

    static void InterruptHandler(uint gpio, uint32_t events); 
private:
    int counter;
    bool lastDT;
    bool lastCLK;
    bool currDT;
    bool currCLK;
    pin_size_t  _DT_PIN;
    pin_size_t _CLK_PIN;
    pin_size_t _SW_PIN;

    bool lastDTorCLK;//flag
    bool Button;
    
    void DTInterruptFunc();
    void CLKInterruptFunc();
};
