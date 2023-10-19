#include "LightStrip.hpp"

__attribute__((unused)) uint16_t XY(uint8_t x, uint8_t y){
    return x + y;
}

LightStrip::LightStrip(int numStrips, CRGB** strips, int* lengths){
    this->strips = strips;
    this->lengths = lengths;
    this->numStrips = numStrips;
    starts = new int[numStrips];
    int prev = 0;
    for (int i = 0; i < numStrips; i++) {
        starts[i] = prev;
        int len = lengths[i];
        prev += len;
    }
    totalLEDs = prev;
}

LightStrip::~LightStrip(){
    delete[] starts;
}

struct Position LightStrip::getStripAndPos(int led){
    struct Position pos{};

    for (int i = 0; i < numStrips; i++) {
        if (led < starts[i]) {
            pos.strip = i - 1;
            pos.pos = led - starts[i-1];
            return pos;
        }
    }
    pos.strip = numStrips - 1;
    pos.pos = led - starts[numStrips - 1];

    return pos;
}

void LightStrip::set(int led, CRGB color){
    Position p = getStripAndPos(led);
    strips[p.strip][p.pos] = color;
}

void LightStrip::set(int led, CRGB color, fract8 alpha){
    if (led > totalLEDs) return;
    Position p = getStripAndPos(led);
    CRGB oldColor = strips[p.strip][p.pos];
    CRGB newColor = blend(oldColor, color, alpha);
    strips[p.strip][p.pos] = newColor;
}

CRGB LightStrip::get(int led){
    Position p = getStripAndPos(led);
    return strips[p.strip][p.pos];
}

void LightStrip::clear(){
    for (int i = 0; i < numStrips; i++) {
        int len = lengths[i];
        for (int j = 0; j < len; j++)
            strips[i][j] = CRGB::Black;
    }
}


