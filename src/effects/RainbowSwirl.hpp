#include "effects/Animation.hpp"

class RainbowSwirl : public Animation
{
public:
    RainbowSwirl(CRGB *leds, byte count, bool forward);
    void start();
    void runStep();

private:
    bool forward;
    byte initialHue;
    byte iteration;
    void fillRainbow(byte initialHue);
};

RainbowSwirl::RainbowSwirl(CRGB *leds, byte count, bool forward) : Animation(leds, count)
{
    this->forward = forward;
    this->initialHue = 0;
    this->iteration = 0;
}

void RainbowSwirl::start()
{
    fillRainbow(0);
}

void RainbowSwirl::runStep()
{
    iteration += 1;
    if (iteration % 2 != 0)
    {
        return;
    }

    if (forward)
    {
        if (initialHue == 254)
        {
            initialHue = 0;
        }
        else
        {
            initialHue++;
        }
    }
    else
    {
        if (initialHue == 0)
        {
            initialHue = 254;
        }
        else
        {
            initialHue--;
        }
    }

    fillRainbow(initialHue);
}

void RainbowSwirl::fillRainbow(byte initialHue)
{
    byte deltaHue = 255 / ledCount;
    CHSV hsv;
    hsv.hue = initialHue;
    hsv.val = 128;
    hsv.sat = 240;

    for (int i = 0; i < ledCount; ++i)
    {
        leds[i] = hsv;
        hsv.hue += deltaHue;
    }

    FastLED.show();
}