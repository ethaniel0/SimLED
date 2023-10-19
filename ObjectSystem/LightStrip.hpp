#ifndef LIGHTSTRIP_H
#define LIGHTSTRIP_H

#include <vector>
#include <tuple>
#include "../FastLED/src/FastLED.h"
#include "../FastLED/src/colorutils.h"



struct Position {
    int strip;
    int pos;
};

class LightStrip {
public:
    int totalLEDs;

    LightStrip(int numStrips, CRGB** strips, int* lengths);
    ~LightStrip();

    void set(int led, CRGB color);
    void set(int led, CRGB color, fract8 alpha);
    CRGB get(int led);
    void clear();

private:
    int numStrips;
    CRGB** strips;
    int* lengths;
    int* starts;

    struct Position getStripAndPos(int led);
};

#endif
