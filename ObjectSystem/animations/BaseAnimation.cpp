#include "BaseAnimation.hpp"

BaseAnimation::BaseAnimation(int duration, bool loop, EditableProperties bind)
{
    this->duration = duration;
    this->loop = loop;
    this->bind = bind;
    this->done = false;
    this->frames = 0;
    this->offset = 0;
    this->bindToLength = false;
    this->funcs = std::vector<AnimationFunction*>();
    this->obj = nullptr;
}

CHSV makeColor(int* numbers, int position, int numFunctions) {
    if (numFunctions == 0) return {0, 0, 0};
    if (numFunctions == 1) {
        return CHSV(numbers[position], numbers[position], numbers[position]);
    }
    if (numFunctions == 2)
        return CHSV(numbers[position], numbers[position + 1], 255);

    return CHSV(numbers[position], numbers[position + 1], numbers[position + 2]);
}

void BaseAnimation::update()
{
    if (this->done) return;

    int numFuncs = (int) this->funcs.size();

    int gen = numFuncs;
    int outerSize = this->bindToLength ? (int)this->obj->colors.size() : 1;

    int numbers[outerSize * numFuncs];

    for (int i = 0; i < outerSize; i++) {
        int count = 0;
        for (auto func : this->funcs){
            numbers[i * gen + count] = func->getValue(frames + offset*i, duration);
            count++;
        }
    }

    switch(this->bind){
        case EditableProperties::POSITION:
            this->obj->pos = numbers[0];
            break;
        case EditableProperties::RELATIVE_POSITION:
            this->obj->pos += numbers[0];
            break;
        case EditableProperties::OPACITY:
            this->obj->opacity = numbers[0];
            break;
        case EditableProperties::COLORS:
            if (this->bindToLength){
                for (int i = 0; i < this->obj->colors.size(); i++) {
                    this->obj->colors[i] = makeColor(numbers, i * gen, numFuncs);
                }
            }
            else {
                CHSV color = makeColor(numbers, 0, numFuncs);
                for (auto & i : this->obj->colors) {
                    i = color;
                }
            }
            break;
        case EditableProperties::BRIGHTNESS:
            if (this->bindToLength) {
                for (int i = 0; i < this->obj->colors.size(); i++) {
                    this->obj->colors[i] = obj->colors[i] % numbers[i * gen];
                }
            }
            else {
                int b = numbers[0];
                for (int i = 0; i < this->obj->colors.size(); i++) {
                    this->obj->colors[i] = obj->colors[i] % b;
                }
            }
            break;
    }

    this->frames++;
    if (duration != -1 && frames >= duration && loop){
        reset();
    }
    else if (frames > duration){
        this->done = true;
    }
}

bool BaseAnimation::isFinished()
{
    return false;
}

void BaseAnimation::reset()
{
    this->frames = 0;
    this->done = false;
}

void BaseAnimation::setState(int state)
{
    if (this->absoluteStateTriggers.find(state) != this->absoluteStateTriggers.end()) {
        this->offset = this->absoluteStateTriggers[state];
    }
    else if (this->relativeStateTriggers.find(state) != this->relativeStateTriggers.end()) {
        this->offset += this->relativeStateTriggers[state];
    }
}

void BaseAnimation::addFunction(AnimationFunction *func)
{
    this->funcs.push_back(func);
}

void BaseAnimation::addAbsoluteStateTrigger(int state, int frame)
{
    this->absoluteStateTriggers[state] = frame;
}

void BaseAnimation::addRelativeStateTrigger(int state, int frame)
{
    this->relativeStateTriggers[state] = frame;
}
