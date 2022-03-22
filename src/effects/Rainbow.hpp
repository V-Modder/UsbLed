#include "effects/Animation.h"

class Rainbow : public Animation {
public:
    Rainbow(CRGB* leds, byte count) : Animation(leds, count){};
    void start();
    void runStep();
};

void Rainbow::start() {
    fill_rainbow(leds, ledCount, 0, 255 / ledCount);
    FastLED.show();
}

void Rainbow::runStep() {
}
