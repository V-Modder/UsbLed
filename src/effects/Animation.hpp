#ifndef Annimation_h
#define Annimation_h
#include <FastLED.h>

class Animation
{
public:
    Animation(CRGB *leds, byte count);
    virtual void start();
    virtual void runStep();

protected:
    CRGB *leds;
    byte ledCount;
};

Animation::Animation(CRGB *leds, byte ledCount)
{
    this->leds = leds;
    this->ledCount = ledCount;
}

#endif