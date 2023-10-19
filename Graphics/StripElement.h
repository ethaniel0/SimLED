//
// Created by Ethan Horowitz on 10/19/23.
//

#ifndef SIMLED_STRIPELEMENT_H
#define SIMLED_STRIPELEMENT_H

#include "../FastLED/src/FastLED.h"
#include "GraphicsUtils.h"
#include <cmath>

class StripElement {

public:
    StripElement(CRGB* leds, int length);
    void setParameters(int x, int y, double angle=M_PI, int ledSize=10, int ledSpacing=15);
    int x{};
    int y{};
    double angle{};
    int ledSize{};
    int ledSpacing{};

    void draw();

private:
    CRGB* leds;
    int length;

};


#endif //SIMLED_STRIPELEMENT_H
