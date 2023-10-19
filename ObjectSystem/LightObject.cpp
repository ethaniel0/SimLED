#include "LightObject.hpp"
#include "animations/Animation.hpp"

LightObject::LightObject(int length) {
    this->pos = 0;
    this->wrapMode = 0;
    this->persistent = false;
    this->opacity = 255;
    this->colors = std::vector<CRGB>(length);

    for (int i = 0; i < length; i++) {
        this->colors[i] = CRGB::Black;
    }
}

LightObject::LightObject(CRGB* colors, int length) {
    this->pos = 0;
    this->wrapMode = 0;
    this->persistent = false;
    this->opacity = 255;
    this->colors = std::vector<CRGB>(length);
    this->animations = std::vector<Animation*>();

    for (int i = 0; i < length; i++) {
        this->colors[i] = colors[i];
    }
}

LightObject::~LightObject() = default;

void LightObject::update() {
    for (auto & animation : this->animations)
    {
        animation->update();
    }
}

void LightObject::addAnimation(Animation* animation) {
    animation->linkObject(this);
    this->animations.push_back(animation);
}

void LightObject::setState(int state){
    for (auto & animation : this->animations)
    {
        animation->setState(state);
    }
}

void LightObject::applyToStrip(LightStrip* strip) {
    for (int i = 0; i < this->colors.size(); i++) {
        strip->set(this->pos + i, this->colors[i]);
    }
}