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
    else return EditableProperties::NONE;
}

Animation* createBaseAnimation(const char* string, int* pos, SystemCreator* sc){
    // syntax: <duration> <loop> <bind> <bind to length> <offset> <# of functions> <functions> <# absolute state transitions> <state> <frame> ... <# relative state transitions> <state> <frame> ...
    int duration = extractNumber(string, pos);
    bool loop = extractNumber(string, pos);
    // bind: position(p), relative position(r), colors(c), opacity(o), brightness(b)
    skipWhitespace(string, pos);
    char bindChar = string[*pos];
    EditableProperties bind = getEditableProperty(bindChar);
    if (bind == EditableProperties::NONE) return nullptr;
    incPtr(pos);

    bool bindToLength = extractNumber(string, pos);
    int offset = extractNumber(string, pos);

    int numFuncs = extractNumber(string, pos);
    auto* base = new BaseAnimation(duration, loop, bind);
    base->bindToLength = bindToLength;
    base->offset = offset;
    for (int i = 0; i < numFuncs; i++){
        AnimationFunction* func = sc->parseAnimationFunction(string, pos);
        if (func == nullptr) return nullptr;
        base->addFunction(func);
    }

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

    return base;
}

Animation* createAnimationSequence(const char* string, int* pos, SystemCreator* sc){
    // syntax: <loops> <# of animations> <animations> ... <# next triggers> <state1> <state2>... <# prev triggers> <state1>... <# reset triggers> <state1>...
    int loops = extractNumber(string, pos);
    int numAnimations = extractNumber(string, pos);
    auto* seq = new AnimationSequence(loops);
    for (int i = 0; i < numAnimations; i++){
        Animation* a = sc->parseAnimation(string, pos);
        if (a == nullptr) return nullptr;
        seq->addAnimation(a);
    }

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

    return seq;
}

Animation* createAnimationStateMap(const char* string, int* pos, SystemCreator* sc){
    // syntax: <# of states> <state1> <animation1> <state2> <animation2> ...
    skipWhitespace(string, pos);
    int numStates = extractNumber(string, pos);
    auto* map = new AnimationStateMap();
    for (int i = 0; i < numStates; i++){
        skipWhitespace(string, pos);
        int state = extractNumber(string, pos);
        skipWhitespace(string, pos);
        Animation* a = sc->parseAnimation(string, pos);
        if (a == nullptr) return nullptr;
        map->addState(state, a);
    }
    return map;
}


