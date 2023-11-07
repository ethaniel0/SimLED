#include "BaseAnimation.h"

BaseAnimation::BaseAnimation(int duration, bool loop, EditableProperties bind) {
    this->duration = duration;
    this->loop = loop;
    this->bind = bind;
    this->done = false;
    this->frames = 0;
    this->offset = 1;
    this->bindToLength = false;
    this->obj = nullptr;
    for (int i = 0; i < 16; i++){
        absoluteStateTriggers[i] = -1;
        relativeStateTriggers[i] = -1;
    }
}

BaseAnimation::~BaseAnimation() {
    funcs.moveToStart();
    int len = funcs.getLength();
    for (int i = 0; i < len; i++) {
        delete funcs.current();
        funcs.next();
    }
}

CHSV makeColor(int* numbers, int position, int numFunctions) {
    if (numFunctions == 0) return {0, 0, 0};
    if (numFunctions == 1) {
        return CHSV(numbers[position], 255, 255);
    }
    if (numFunctions == 2)
        return CHSV(numbers[position], numbers[position + 1], 255);

    return CHSV(numbers[position], numbers[position + 1], numbers[position + 2]);
}

void BaseAnimation::update() {
    if (done) return;

    int numFuncs = (int) funcs.getLength();

    int gen = numFuncs;
    int outerSize = bindToLength ? (int)obj->colors.getLength() : 1;

    int numbers[outerSize * numFuncs];

    for (int i = 0; i < outerSize; i++) {
        int count = 0;
        funcs.moveToStart();
        int len = funcs.getLength();
        for (int j = 0; j < len; j++) {
            numbers[i * gen + count] = funcs.current()->getValue(frames + offset*i, duration);
            funcs.next();
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
                obj->colors.moveToStart();
                int len = obj->colors.getLength();
                for (int i = 0; i < len; i++) {
                    CRGB c = makeColor(numbers, i * gen, numFuncs);
                    obj->colors.update(c);
                    obj->colors.next();
                }
            }
            else {
                CHSV color = makeColor(numbers, 0, numFuncs);
                obj->colors.moveToStart();
                int len = obj->colors.getLength();

                for (int i = 0; i < len; i++) {
                    obj->colors.update(color);
                    obj->colors.next();
                }
            }
            break;
        case EditableProperties::BRIGHTNESS:
            if (bindToLength) {
                obj->colors.moveToStart();
                int len = obj->colors.getLength();
                for (int i = 0; i < len; i++) {
                    obj->colors.update(obj->colors.current() % numbers[i * gen]);
                    obj->colors.next();
                }
            }
            else {
                int b = numbers[0];
                obj->colors.moveToStart();
                int len = obj->colors.getLength();
                for (int i = 0; i < len; i++) {
                    obj->colors.update(obj->colors.current() % b);
                    obj->colors.next();
                }
            }
            break;
        case EditableProperties::NONE:
            break;
    }

    frames++;
    if (duration != -1 && frames > duration && loop){
        reset();
    }
    else if (duration != -1 && frames > duration){
        done = true;
    }
}

bool BaseAnimation::isFinished() {
    return false;
}

void BaseAnimation::reset() {
    frames = 0;
    done = false;
}

void BaseAnimation::setState(int state) {
    if (state < 0 || state > 15) return;
    if (absoluteStateTriggers[state] != -1) {
        frames = absoluteStateTriggers[state];
    }
    else if (relativeStateTriggers[state] != -1) {
        frames += relativeStateTriggers[state];
    }
}

BaseAnimation* BaseAnimation::clone() {
    auto* anim = new BaseAnimation(duration, loop, bind);
    anim->bindToLength = bindToLength;
    anim->offset = offset;
    funcs.moveToStart();
    int len = funcs.getLength();
    for (int i = 0; i < len; i++) {
        anim->funcs.append(funcs.current()->clone());
        funcs.next();
    }
    for (int i = 0; i < 16; i++){
        anim->absoluteStateTriggers[i] = absoluteStateTriggers[i];
        anim->relativeStateTriggers[i] = relativeStateTriggers[i];
    }
    return anim;
}

void BaseAnimation::addFunction(AnimationFunction *func) {
    funcs.append(func);
}

void BaseAnimation::addAbsoluteStateTrigger(int state, int frame) {
    if (state >= 0 && state < 16)
        absoluteStateTriggers[state] = frame;
}

void BaseAnimation::addRelativeStateTrigger(int state, int frame) {
    if (state >= 0 && state < 16)
        relativeStateTriggers[state] = frame;
}
