//
// Created by Ethan Horowitz on 11/1/23.
//
#include "AnimationCreators.h"

EditableProperties getEditableProperty(char c){
    if (c == 'p') return EditableProperties::POSITION;
    else if (c == 'r') return EditableProperties::RELATIVE_POSITION;
    else if (c == 'c') return EditableProperties::COLORS;
    else if (c == 'o') return EditableProperties::OPACITY;
    else if (c == 'b') return EditableProperties::BRIGHTNESS;
    else if (c == 'l') return EditableProperties::LENGTH;
    else return EditableProperties::NONE;
}

Animation* createBaseAnimation(const char* string, int* pos, SystemCreator* sc){
    // syntax: <duration> <loop> <bind> <bind to length> <frameOffset> <lightOffset> <# absolute state transitions> <state> <frame> ... <# relative state transitions> <state> <frame> ... <# of functions> <functions>
    int duration = extractNumber(string, pos);
    bool loop = extractNumber(string, pos);
    // bind: position(p), relative position(r), colors(c), opacity(o), brightness(b)
    skipWhitespace(string, pos);
    char bindChar = string[*pos];
    EditableProperties bind = getEditableProperty(bindChar);
    if (bind == EditableProperties::NONE) return nullptr;
    incPtr(pos);

    bool bindToLength = extractNumber(string, pos);
    int frameOffset = extractNumber(string, pos);
    int lightOffset = extractNumber(string, pos);

    auto* base = new BaseAnimation(duration, loop, bind);
    base->bindToLength = bindToLength;
    base->frameOffset = frameOffset;
    base->lightOffset = lightOffset;

    int numAbs = extractNumber(string, pos);
    for (int i = 0; i < numAbs; i++){
        int state = extractNumber(string, pos);
        int frame = extractNumber(string, pos);
        base->addAbsoluteStateTrigger(state, frame);
    }

    int numRel = extractNumber(string, pos);
    for (int i = 0; i < numRel; i++){
        int state = extractNumber(string, pos);
        int frame = extractNumber(string, pos);
        base->addRelativeStateTrigger(state, frame);
    }


    int numFuncs = extractNumber(string, pos);
    for (int i = 0; i < numFuncs; i++){
        AnimationFunction* func = sc->parseAnimationFunction(string, pos);
        if (func == nullptr) return nullptr;
        base->addFunction(func);
    }


    return base;
}

Animation* createAnimationSequence(const char* string, int* pos, SystemCreator* sc){
    // syntax: <loops> <# next triggers> <state1> <state2>... <# prev triggers> <state1>... <# reset triggers> <state1>... <# of animations> <animations> ...
    int loops = extractNumber(string, pos);

    auto* seq = new AnimationSequence(loops);

    // all AnimationSequence-specific variables first
    int i;
    int num = extractNumber(string, pos);
    for (i = 0; i < num; i++){
        seq->addNextTrigger(extractNumber(string, pos));
    }

    num = extractNumber(string, pos);
    for (i = 0; i < num; i++){
        seq->addPrevTrigger(extractNumber(string, pos));
    }

    num = extractNumber(string, pos);
    for (i = 0; i < num; i++){
        seq->addResetTrigger(extractNumber(string, pos));
    }

    // then the animations

    int numAnimations = extractNumber(string, pos);
    for (int i = 0; i < numAnimations; i++){
        Animation* a = sc->parseAnimation(string, pos);
        if (a == nullptr) return nullptr;
        seq->addAnimation(a);
    }

    return seq;
}

Animation* createAnimationStateMap(const char* string, int* pos, SystemCreator* sc){
    // syntax: <# of states> <state1> <state2> ... <animation1> <animation2> ...
    int numStates = extractNumber(string, pos);
    auto* map = new AnimationStateMap();
    for (int i = 0; i < numStates; i++){
        int state = extractNumber(string, pos);
        Animation* a = sc->parseAnimation(string, pos);
        if (a == nullptr) return nullptr;
        map->addState(state, a);
    }
    return map;
}

Animation* createDataReactor(const char* string, int* pos, SystemCreator* sc){
    int dataNum = extractNumber(string, pos);
    dataNum = dataNum < 0 ? 0 : dataNum > 15 ? 15 : dataNum;

    Animation* a = sc->parseAnimation(string, pos);
    if (a == nullptr) return nullptr;
    return new DataReactor(a, dataNum);
}
