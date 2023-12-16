#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#if defined(ARDUINO) && ARDUINO >= 100
    #include "FastLED.h"
#else
    #include "../../../FastLED/src/FastLED.h"
#endif

#include "../animations/Animation.h"
#include "../strips/LightStrip.h"
#include "../strips/StripPath.h"
#include "PlaceableObject.h"
#include "../linkedlist/LinkedList.h"

class Animation;

enum EditableProperties {
    POSITION,
    RELATIVE_POSITION,
    COLORS,
    OPACITY,
    BRIGHTNESS,
    LENGTH,
    NONE
};

class LightObject: public PlaceableObject {
public:
    fract8 opacity;
    LinkedList<CRGB> colors;
    LinkedList<Animation*> animations;
    StripPath* path;
    bool loopPath;

    explicit LightObject(int length);
    LightObject(CRGB* colors, int length);
    ~LightObject() override;

    void update(ObjectSystem* system, ObjectManager* manager) override;
    void applyToStrip(LightStrip* strip) override;
    void setState(int state) override;
    void addAnimation(Animation* animation);
    LightObject* clone() override;

private:
    int lightPos;
    int checkPos;
    void adjustLength();
};

#endif