#include "LightObject.h"
#include "../animations/Animation.h"

LightObject::LightObject(int length) {
    pos = 0;
    wrapMode = 0;
    persistent = false;
    opacity = 255;
    this->length = length;
    for (int i = 0; i < length; i++) {
        this->colors.append(CRGB::Black);
    }
}

LightObject::LightObject(CRGB* colors, int length) {
    pos = 0;
    wrapMode = 0;
    persistent = false;
    opacity = 255;
    this->length = length;

    for (int i = 0; i < length; i++) {
        this->colors.append(colors[i]);
    }
}

LightObject::~LightObject(){
    animations.moveToStart();
    for (int i = 0; i < animations.getLength(); i++) {
        delete animations.current();
        animations.next();
    }
    animations.clear();
};

void LightObject::update(ObjectSystem* system) {
    if (animations.getLength() == 0) return;
    animations.moveToStart();
    int len = animations.getLength();
    for (int i = 0; i < len; i++) {
        animations.current()->update();
        animations.next();
    }
}

void LightObject::addAnimation(Animation* animation) {
    animation->linkObject(this);
    animations.append(animation);
}

void LightObject::setState(int state){
    animations.moveToStart();
    int len = animations.getLength();
    for (int i = 0; i < len; i++) {
        animations.current()->setState(state);
        animations.next();
    }
}

void LightObject::applyToStrip(LightStrip* strip) {
    colors.moveToStart();
    int len = colors.getLength();
    for (int i = 0; i < len; i++) {
        CRGB color = colors.current();

        color = blend(strip->get(pos + i), color, opacity);
        strip->set(pos + i, color);
        colors.next();
    }
}

LightObject* LightObject::clone() {
    auto* obj = new LightObject(this->length);
    obj->pos = this->pos;
    obj->wrapMode = this->wrapMode;
    obj->persistent = this->persistent;
    obj->opacity = this->opacity;

    colors.moveToStart();
    int len = colors.getLength();
    for (int i = 0; i < len; i++) {
        obj->colors.append(colors.current());
        colors.next();
    }

    animations.moveToStart();
    len = animations.getLength();
    for (int i = 0; i < len; i++) {
        obj->addAnimation(animations.current()->clone());
        animations.next();
    }

    return obj;
}
