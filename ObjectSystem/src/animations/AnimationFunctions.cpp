#include "AnimationFunctions.h"

#if defined(ARDUINO)
    #include "FastLED.h"
#else
    #include "../../../FastLED/src/FastLED.h"
#endif



EaseTransform::EaseTransform(int start, int end) {
    this->start = start;
    this->end = end;
}
int EaseTransform::getValue(int time, int duration) {
    double t = time / (double) duration;
    double val = t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
    val = (end - start) * val + start;
    return (int) val;
}
EaseTransform* EaseTransform::clone() {
    return new EaseTransform(start, end);
}

LinearTransform::LinearTransform(int start, int end) {
    this->start = start;
    this->end = end;
}
int LinearTransform::getValue(int time, int duration) {
    return (int) (start + (end - start) * (time / (double) duration));
}
LinearTransform* LinearTransform::clone() {
    return new LinearTransform(start, end);
}

PerlinTransform::PerlinTransform(int speed, int min, int max) {
    this->speed = speed;
    this->min = min;
    this->max = max;
}
int PerlinTransform::getValue(int time, int duration) {
    uint16_t val = inoise16(time*speed);
    return (int) (this->min + (this->max - this->min) * (val / (double) 65536));
}
PerlinTransform* PerlinTransform::clone() {
    return new PerlinTransform(speed, min, max);
}

RandomTransform::RandomTransform(int min, int max) {
    this->min = min;
    this->max = max;
}
int RandomTransform::getValue(int time, int duration) {
    return (int) random(min, max);
}
RandomTransform* RandomTransform::clone() {
    return new RandomTransform(min, max);
}

StaticTransform::StaticTransform(int val) {
    this->val = val;
}
int StaticTransform::getValue(int time, int duration) {
    return this->val;
}
StaticTransform* StaticTransform::clone() {
    return new StaticTransform(val);
}
