#ifndef ANIMATION_FUNCTIONS_H
#define ANIMATION_FUNCTIONS_H

#include "AnimationFunction.h"

#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include "../Arduino/Arduino.h"
#endif



class EaseTransform: public AnimationFunction {
    public:
        int start;
        int end;
        EaseTransform(int start, int end);
        int getValue(int time, int duration) override;
        EaseTransform* clone() override;
};

class LinearTransform: public AnimationFunction {
    public:
        int start;
        int end;
        LinearTransform(int start, int end);
        int getValue(int time, int duration) override;
        LinearTransform* clone() override;
};

class PerlinTransform: public AnimationFunction {
    public:
        int min;
        int max;
        int speed;
        PerlinTransform(int speed, int min, int max);
        int getValue(int time, int duration) override;
        PerlinTransform* clone() override;
};

class RandomTransform: public AnimationFunction {
    public:
        int min;
        int max;
        RandomTransform(int min, int max);
        int getValue(int time, int duration) override;
        RandomTransform* clone() override;
};

class StaticTransform: public AnimationFunction {
    public:
        int val;
        explicit StaticTransform(int val);
        int getValue(int time, int duration) override;
        StaticTransform* clone() override;
};

#endif