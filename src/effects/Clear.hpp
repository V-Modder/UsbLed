#include "effects/Animation.hpp"

class Clear : public Animation
{
public:
    Clear() : Animation(NULL, 0){};
    void start();
    void runStep();
};

void Clear::start()
{
    FastLED.clear();
}

void Clear::runStep()
{
}