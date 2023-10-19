#include "LightObject.hpp"
#include "animations/Animation.hpp"

LightObject::LightObject(int length) {
    pos = 0;
    wrapMode = 0;
    persistent = false;
    opacity = 255;
    colors = std::vector<CRGB>(length);

    for (int i = 0; i < length; i++) {
        colors[i] = CRGB::Black;
    }
}

LightObject::LightObject(CRGB* colors, int length) {
    pos = 0;
    wrapMode = 0;
    persistent = false;
    opacity = 255;
    animations = std::vector<Animation*>();
    this->colors = std::vector<CRGB>(length);

    for (int i = 0; i < length; i++) {
        this->colors[i] = colors[i];
    }
}

LightObject::~LightObject() = default;

void LightObject::update() {
    if (animations.empty()) return;
    for (auto animation : animations)
        animation->update();
}

void LightObject::addAnimation(Animation* animation) {
    animation->linkObject(this);
    animations.push_back(animation);
}

void LightObject::setState(int state){
    for (auto & animation : animations)
    {
        animation->setState(state);
    }
}

void LightObject::applyToStrip(LightStrip* strip) {
    for (int i = 0; i < this->colors.size(); i++) {
        strip->set(pos + i, colors[i]);
    }
}