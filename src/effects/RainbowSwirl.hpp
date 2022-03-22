#include "effects/Animation.hpp"

class RainbowSwirl : public Animation {
public:
    RainbowSwirl(CRGB* leds, byte count, bool forward);
    void start();
    void runStep();
private:
    bool forward;
    byte initialHue;
};

RainbowSwirl::RainbowSwirl(CRGB* leds, byte count, bool forward) : Animation(leds, count) {
    this->forward = forward;
    this->initialHue = 0;
}

void RainbowSwirl::start() {
    fill_rainbow(leds, ledCount, 0, 255 / ledCount);
    FastLED.show();
}

void RainbowSwirl::runStep() {
    if(forward) {
        if(initialHue == 254) {
            initialHue = 0;    
        }
        else {
            initialHue++;
        }
    }
    else {
        if(initialHue == 0) {
            initialHue = 254;    
        }
        else {
            initialHue--;
        }
    }

    fill_rainbow(leds, ledCount, initialHue, 255 / ledCount);
    FastLED.show();
}
