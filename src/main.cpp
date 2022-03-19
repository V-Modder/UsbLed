#include <Arduino.h>
#include <FastLED.h>
#include <EEPROM.h>

#define MODE_STATIC_FILL 1
#define MODE_STATIC_PATTERN 2
#define MODE_DYNAMIC_PATTERN 3

#define VIN_INPUT_PIN A7

#define LED_PIN 3
#define NUM_LEDS 144
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
//#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];
byte mode;
byte effect;

bool isVinConnected()
{
    return analogRead(VIN_INPUT_PIN) > 1000;
}

void runEffect(byte effect)
{
}

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600);

    FastLED.setBrightness(EEPROM.read(0));

    Serial.println("Clear");
    FastLED.clear();
    FastLED.show();

    while(true){
    }


    Serial.println("Starting init sequence");

    switch (EEPROM.read(1))
    {
    case MODE_STATIC_FILL:
        CRGB color = CRGB();
        color.red = EEPROM.read(2);
        color.green = EEPROM.read(3);
        color.blue = EEPROM.read(4);
        fill_solid(leds, NUM_LEDS, color);
        mode = MODE_STATIC_FILL;
        break;
    case MODE_STATIC_PATTERN:
        runEffect(EEPROM.read(2));
        mode = MODE_STATIC_PATTERN;
        break;
    case MODE_DYNAMIC_PATTERN:
        effect = EEPROM.read(2);
        mode = MODE_DYNAMIC_PATTERN;
        break;
    default:
        Serial.println("No value present...using default");
        fill_solid(leds, NUM_LEDS, CRGB::Blue);
        mode = MODE_STATIC_FILL;
    }

    Serial.println("Starup done");
}

void loop()
{
    if (mode == MODE_DYNAMIC_PATTERN)
    {
        runEffect(effect);
    }
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