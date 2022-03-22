#include <Arduino.h>
#include <FastLED.h>
#include <EEPROM.h>

#include "effects/Animation.hpp"
#include "effects/Clear.hpp"
#include "effects/Rainbow.hpp"
#include "effects/RainbowSwirl.hpp"

#define REQUEST_BRIGHTNESS 1
#define REQUEST_MODE 2

#define MODE_STATIC_FILL 1
#define MODE_DYNAMIC_PATTERN 3

#define EFFECT_CLEAR 1
#define EFFECT_RAINBOW 2
#define EFFECT_RAINBOW_SWIRL 3
#define EFFECT_RAINBOW_SWIRL_BACKWARDS 4

#define EEPROM_BRIGHTNESS 0
#define EEPROM_MODE 1
#define EEPROM_DATA_1 2
#define EEPROM_DATA_2 3
#define EEPROM_DATA_3 4

#define VIN_INPUT_PIN A7

#define LED_PIN 3
#define NUM_LEDS 144
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
//#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];
byte mode;
Animation *effect;

bool isVinConnected()
{
    return analogRead(VIN_INPUT_PIN) > 1000;
}

void setEffect(byte id)
{
    switch (id)
    {
    case EFFECT_CLEAR:
        effect = new Clear();
        break;
    case EFFECT_RAINBOW:
        effect = new Rainbow(leds, NUM_LEDS);
        break;
    case EFFECT_RAINBOW_SWIRL:
        effect = new RainbowSwirl(leds, NUM_LEDS, true);
        break;
    case EFFECT_RAINBOW_SWIRL_BACKWARDS:
        effect = new RainbowSwirl(leds, NUM_LEDS, false);
        break;
    }
}

void runEffect()
{
    effect->runStep();
}

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600);

    byte initBrightness = EEPROM.read(EEPROM_BRIGHTNESS);
    if (initBrightness != 0)
    {
        FastLED.setBrightness(initBrightness);
    }
    else
    {
        FastLED.setBrightness(128);
    }

    Serial.println("Clear");
    FastLED.clear();

    //for (unsigned int i = 0; i < EEPROM.length(); i++)
    //{
    //    EEPROM.write(i, 0);
    //}

    //Serial.println("EEPROM cleared");
    //while (true)
    //{
    //}

    RainbowSwirl swirl = RainbowSwirl(leds, NUM_LEDS, true);
    swirl.start();
    for (int i = 0; i < 500; i++)
    {
        delay(10);
        swirl.runStep();
    }

    Serial.println("Starting init sequence");

    switch (EEPROM.read(EEPROM_MODE))
    {
    case MODE_STATIC_FILL:
        CRGB color;
        color.red = EEPROM.read(EEPROM_DATA_1);
        color.green = EEPROM.read(EEPROM_DATA_2);
        color.blue = EEPROM.read(EEPROM_DATA_3);
        fill_solid(leds, NUM_LEDS, color);
        mode = MODE_STATIC_FILL;
        effect = NULL;
        break;
    case MODE_DYNAMIC_PATTERN:
        setEffect(EEPROM.read(EEPROM_DATA_1));
        effect->start();
        mode = MODE_DYNAMIC_PATTERN;
        break;
    default:
        Serial.println("No value present...using default");
        fill_solid(leds, NUM_LEDS, CRGB::Blue);
        FastLED.show();
        mode = MODE_STATIC_FILL;
    }

    Serial.println("Starup done");
}

void readCommand()
{
    byte request = Serial.read();
    if (request == REQUEST_BRIGHTNESS)
    {
        byte brightness = Serial.read();
        FastLED.setBrightness(brightness);
        EEPROM.write(EEPROM_BRIGHTNESS, brightness);
    }
    else if (request == REQUEST_MODE)
    {
        switch (Serial.read())
        {
        case MODE_STATIC_FILL:
            CRGB color;
            color.red = Serial.read();
            color.green = Serial.read();
            color.blue = Serial.read();
            fill_solid(leds, NUM_LEDS, color);
            mode = MODE_STATIC_FILL;
            EEPROM.write(EEPROM_MODE, mode);
            EEPROM.write(EEPROM_DATA_1, color.red);
            EEPROM.write(EEPROM_DATA_2, color.green);
            EEPROM.write(EEPROM_DATA_3, color.blue);
            break;
        case MODE_DYNAMIC_PATTERN:
            byte effectId = Serial.read();
            setEffect(effectId);
            effect->start();
            mode = MODE_DYNAMIC_PATTERN;
            EEPROM.write(EEPROM_MODE, mode);
            EEPROM.write(EEPROM_DATA_1, effectId);
            break;
            // default:
            //  Serial.println("No value present...using default");
            //  fill_solid(leds, NUM_LEDS, CRGB::Blue);
            //  mode = MODE_STATIC_FILL;
        }
    }
}

void loop()
{
    if (Serial.available())
    {
        readCommand();
    }

    if (mode == MODE_DYNAMIC_PATTERN)
    {
        runEffect();
    }

    delay(10);

    // put your main code here, to run repeatedly:
    /*
    Serial.println("Green");
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(3000);

    Serial.println("Blue");
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    delay(3000);

    Serial.println("Megenta-Yellow");
    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Magenta, CRGB::Yellow);
    FastLED.show();
    delay(3000);

    Serial.println("Yellow-Green-Blue");
    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Red, CRGB::Yellow, CRGB::Green, CRGB::Blue);
    FastLED.show();
    delay(3000);

    Serial.println("Rainbow");
    fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
    FastLED.show();
    delay(3000);

    Serial.println("Clear");
    digitalWrite(LED_BUILTIN, LOW);
    FastLED.clear();
    FastLED.show();
    delay(3000);
    */
}