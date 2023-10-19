#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "AnimationFunction.hpp"

class EaseTransform: public AnimationFunction {
    public:
        int start;
        int end;
        EaseTransform(int start, int end);
        int getValue(int time, int duration) override;
};

class LinearTransform: public AnimationFunction {
    public:
        int start;
        int end;
        LinearTransform(int start, int end);
        int getValue(int time, int duration) override;
};

class PerlinTransform: public AnimationFunction {
    public:
        int min;
        int max;
        int speed;
        PerlinTransform(int speed, int min, int max);
        int getValue(int time, int duration) override;
};

class RandomTransform: public AnimationFunction {
    public:
        int min;
        int max;
        RandomTransform(int min, int max);
        int getValue(int time, int duration) override;
};

class StaticTransform: public AnimationFunction {
    public:
        int val;
        explicit StaticTransform(int val);
        int getValue(int time, int duration) override;
};

#endif