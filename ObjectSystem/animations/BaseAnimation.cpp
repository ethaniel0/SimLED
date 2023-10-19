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
    if (done) return;

    int numFuncs = (int) funcs.size();

    int gen = numFuncs;
    int outerSize = bindToLength ? (int)obj->colors.size() : 1;

    int numbers[outerSize * numFuncs];

    for (int i = 0; i < outerSize; i++) {
        int count = 0;
        for (auto func : funcs){
            numbers[i * gen + count] = func->getValue(frames + offset*i, duration);
            count++;
        }
    }

    switch(bind){
        case EditableProperties::POSITION:
            obj->pos = numbers[0];
            break;
        case EditableProperties::RELATIVE_POSITION:
            obj->pos += numbers[0];
            break;
        case EditableProperties::OPACITY:
            obj->opacity = numbers[0];
            break;
        case EditableProperties::COLORS:
            if (bindToLength){
                for (int i = 0; i < this->obj->colors.size(); i++) {
                    this->obj->colors[i] = makeColor(numbers, i * gen, numFuncs);
                }
            }
            else {
                CHSV color = makeColor(numbers, 0, numFuncs);
                for (auto & i : obj->colors) {
                    i = color;
                }
            }
            break;
        case EditableProperties::BRIGHTNESS:
            if (bindToLength) {
                for (int i = 0; i < obj->colors.size(); i++) {
                    obj->colors[i] = obj->colors[i] % numbers[i * gen];
                }
            }
            else {
                int b = numbers[0];
                for (auto & color : obj->colors) {
                    color = color % b;
                }
            }
            break;
    }

    frames++;
    if (duration != -1 && frames >= duration && loop){
        reset();
    }
    else if (frames > duration){
        done = true;
    }
}

bool BaseAnimation::isFinished()
{
    return false;
}

void BaseAnimation::reset()
{
    frames = 0;
    done = false;
}

void BaseAnimation::setState(int state)
{
    if (absoluteStateTriggers.find(state) != absoluteStateTriggers.end()) {
        offset = absoluteStateTriggers[state];
    }
    else if (relativeStateTriggers.find(state) != relativeStateTriggers.end()) {
        offset += relativeStateTriggers[state];
    }
}

void BaseAnimation::addFunction(AnimationFunction *func)
{
    funcs.push_back(func);
}

void BaseAnimation::addAbsoluteStateTrigger(int state, int frame)
{
    absoluteStateTriggers[state] = frame;
}

void BaseAnimation::addRelativeStateTrigger(int state, int frame)
{
    relativeStateTriggers[state] = frame;
}
