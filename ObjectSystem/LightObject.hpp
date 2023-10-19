#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include <vector>
#include "../FastLED/src/FastLED.h"
#include "animations/Animation.hpp"
#include "LightStrip.hpp"

class Animation;

enum EditableProperties {
    POSITION,
    RELATIVE_POSITION,
    COLORS,
    OPACITY,
    BRIGHTNESS
};

class LightObject {
public:
    int pos;
    int wrapMode;
    bool persistent;
    fract8 opacity;
    std::vector<CRGB> colors;
    std::vector<Animation*> animations;

    explicit LightObject(int length);
    LightObject(CRGB* colors, int length);
    ~LightObject();

    void update();
    void addAnimation(Animation* animation);
    void setState(int state);
    void applyToStrip(LightStrip* strip);
};

#endif