#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "../../../FastLED/src/FastLED.h"
#include "../animations/Animation.h"
#include "../strips/LightStrip.h"
#include "PlaceableObject.h"
#include "src/linkedlist/LinkedList.h"

class Animation;

enum EditableProperties {
    POSITION,
    RELATIVE_POSITION,
    COLORS,
    OPACITY,
    BRIGHTNESS
};

class LightObject: public PlaceableObject {
public:
    int pos;
    int wrapMode;
    bool persistent;
    fract8 opacity;
    LinkedList<CRGB> colors;
    LinkedList<Animation*> animations;

    explicit LightObject(int length);
    LightObject(CRGB* colors, int length);
    ~LightObject();

    void update(ObjectSystem* system) override;
    void applyToStrip(LightStrip* strip) override;
    void setState(int state) override;
    void addAnimation(Animation* animation);
    LightObject* clone();
};

#endif