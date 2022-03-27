#include <Arduino.h>

struct __attribute__ ((packed)) Color {
    int RED;
    int GREEN;
    int BLUE;
};

struct __attribute__ ((packed)) Status
{
    //int EEPROM_BRIGHTNESS;
    //int EEPROM_MODE;
    Color EEPROM_COLOR;
    int BRIGHTNESS;
    int MODE;
    //Color COLOR;
};

void writeInt(int value)
{
    Serial.write((byte)value >> 24);
    Serial.write((byte)value >> 16);
    Serial.write((byte)value >> 8);
    Serial.write((byte)value);
}

void writeStatus(Status status) {
    uint8_t* ptr = (uint8_t*) &status;
    for(int i = 0; i < sizeof(Status); i++) {
        Serial.print(*ptr++, HEX);
    }
}