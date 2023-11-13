#ifndef LIGHTSTRIP_H
#define LIGHTSTRIP_H

#if defined(ARDUINO) && ARDUINO >= 100
    #include "FastLED.h"
#else
    #include "../../../FastLED/src/FastLED.h"
#endif
#include "../linkedlist/LinkedList.h"

struct Position {
    int strip;
    int pos;
};

class LightStrip {
public:
    LightStrip();
    ~LightStrip();

    void addStrip(int length);

    int size() const;

    void set(int led, CRGB color, fract8 alpha);
    CRGB get(int led);
    void clear();

    CRGB* getSegment(int stripNum) {
        return strips.get(stripNum);
    }

    int numSegments(){
        return numStrips;
    }

private:
    LinkedList<CRGB*> strips;
    LinkedList<int> lengths;
    int totalLEDs;
    int numStrips;

    struct Position getStripAndPos(int led);
};

#endif
