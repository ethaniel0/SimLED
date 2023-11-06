#include "LightStrip.h"

__attribute__((unused)) uint16_t XY(uint8_t x, uint8_t y){
    return x + y;
}

LightStrip::LightStrip(){
    numStrips = 0;
    totalLEDs = 0;
}

LightStrip::~LightStrip(){
    strips.moveToStart();
    for (int i = 0; i < numStrips; i++) {
        delete[] strips.current();
        strips.next();
    }
    strips.clear();
}

void LightStrip::addStrip(int length) {
    CRGB* strip = new CRGB[length];
    strips.append(strip);
    lengths.append(length);
    totalLEDs += length;
    numStrips++;
}

int LightStrip::size() const{
    return totalLEDs;
}

struct Position LightStrip::getStripAndPos(int led){
    struct Position pos{};

    lengths.moveToStart();

    for (int i = 0; i < numStrips; i++) {
        if (led < lengths.current()) {
            pos.strip = i;
            pos.pos = led;
            return pos;
        }
        led -= lengths.current();
        lengths.next();
    }

    pos.strip = numStrips - 1;
    pos.pos = lengths.current() - 1;

    return pos;
}

void LightStrip::set(int led, CRGB color, fract8 alpha){
    if (led >= totalLEDs || led < 0) return;
    Position p = getStripAndPos(led);

    CRGB oldColor = strips.get(p.strip)[p.pos];
    CRGB newColor = blend(oldColor, color, alpha);
    strips.get(p.strip)[p.pos] = newColor;
}

CRGB LightStrip::get(int led){
    if (led >= totalLEDs || led < 0) return CRGB::Black;
    Position p = getStripAndPos(led);
    return strips.get(p.strip)[p.pos];
}

void LightStrip::clear(){
    strips.moveToStart();
    lengths.moveToStart();
    for (int i = 0; i < numStrips; i++){
        int len = lengths.current();
        for (int j = 0; j < len; j++)
            strips.current()[j] = CRGB::Black;
        strips.next();
        lengths.next();
    }
}
