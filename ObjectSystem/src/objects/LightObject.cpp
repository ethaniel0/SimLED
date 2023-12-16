#include "LightObject.h"
#include "../ObjectSystem.h"

LightObject::LightObject(int length) {
    pos = 0;
    lightPos = 0;
    checkPos = 0;
    persistent = false;
    loopPath = false;
    opacity = 255;
    this->length = length;
    path = nullptr;
    for (int i = 0; i < length; i++) {
        this->colors.append(CRGB::Black);
    }
}

LightObject::LightObject(CRGB* colors, int length) {
    pos = 0;
    lightPos = 0;
    checkPos = 0;
    persistent = false;
    loopPath = false;
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

void LightObject::adjustLength() {
    if (length == colors.getLength()) return;
    if (length > colors.getLength()) {
        for (int i = 0; i < length - colors.getLength(); i++) {
            colors.append(CRGB::Black);
        }
    }
    else {
        int clen = colors.getLength();
        colors.get(clen - 1);
        int times = clen - length;
        for (int i = 0; i < times; i++) {
            colors.deleteCurrent();
        }
    }
}

void LightObject::update(ObjectSystem* system, ObjectManager* manager) {
    if (animations.getLength() == 0) return;
    // to keep consistency between animations and where we are on the StripPath, keep animation position in lightPos
    // and update pos to be the StripPath position once animations are done
    if (checkPos == pos) pos = lightPos;

    adjustLength();
    animations.moveToStart();
    int len = animations.getLength();
    for (int i = 0; i < len; i++) {
        animations.current()->update(system->data);
        animations.next();
    }
    lightPos = pos;
    if (path != nullptr) pos = path->get(pos, loopPath);
    checkPos = pos;
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
    if (path == nullptr) {
        for (int i = 0; i < len; i++) {
            CRGB color = colors.current();

            color = blend(strip->get(pos + i), color, opacity);
            strip->set(pos + i, color, opacity);
            colors.next();
        }
    }
    else {
        for (int i = 0; i < len; i++) {
            CRGB color = colors.current();
            int index = path->get(lightPos + i, loopPath);
            color = blend(strip->get(index), color, opacity);
            strip->set(index, color, opacity);
            colors.next();
        }
    }
}

LightObject* LightObject::clone() {
    auto* obj = new LightObject(length);
    obj->pos = pos;
    obj->persistent = persistent;
    obj->opacity = opacity;
    obj->path = path;
    obj->loopPath = loopPath;

    colors.moveToStart();
    obj->colors.moveToStart();
    for (int i = 0; i < length; i++) {
        obj->colors.update(colors.current());
        colors.next();
        obj->colors.next();
    }

    animations.moveToStart();
    int len = animations.getLength();
    for (int i = 0; i < len; i++) {
        obj->addAnimation(animations.current()->clone());
        animations.next();
    }

    return obj;
}
