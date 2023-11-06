
#ifndef ANIMATIONFUNCTION_H
#define ANIMATIONFUNCTION_H

class AnimationFunction{
    public:
        virtual ~AnimationFunction() = default;
        virtual int getValue(int time, int duration) = 0;
        virtual AnimationFunction* clone() = 0;
};

#endif