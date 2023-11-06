//
// Created by Ethan Horowitz on 10/31/23.
//

#include "SystemCreator.h"
#include "AnimationCreators.h"
#include "utils.h"
#include "FunctionCreators.h"
#include "ObjectCreators.h"

SystemCreator::SystemCreator() {
    // add default animations and animationfunctions

    for (int i = 0; i < 26; i++){
        animFunctions[i] = nullptr;
        anims[i] = nullptr;
        objs[i] = nullptr;
    }

    animFunctions['e'-'a'] = createEaseTransform;
    animFunctions['l'-'a'] = createLinearTransform;
    animFunctions['p'-'a'] = createPerlinTransform;
    animFunctions['r'-'a'] = createRandomTransform;
    animFunctions['s'-'a'] = createStaticTransform;

    anims['b'-'a'] = createBaseAnimation;
    anims['s'-'a'] = createAnimationSequence;
    anims['m'-'a'] = createAnimationStateMap;

    objs['l'-'a'] = createLightObject;
}

void SystemCreator::addAnimationFunction(char specifier, AnimationFunction* (*func)(const char*, int*, SystemCreator*)) {
    animFunctions[specifier-'a'] = func;
}
void SystemCreator::addAnimation(char specifier, Animation* (*func)(const char *, int *, SystemCreator*)) {
    anims[specifier-'a'] = func;
}
void SystemCreator::addPlaceableObject(char specifier, PlaceableObject* (*func)(const char *, int *, SystemCreator*)) {
    objs[specifier-'a'] = func;
}

AnimationFunction* SystemCreator::parseAnimationFunction(const char *string, int* pos) {
    int start = 0;
    if (pos == nullptr) pos = &start;
    skipWhitespace(string, pos);
    char specifier = string[*pos]-'a';
    incPtr(pos);
    if (animFunctions[specifier] == 0) return 0;
    return animFunctions[specifier](string, pos, this);
}

Animation* SystemCreator::parseAnimation(const char *string, int* pos) {
    int start = 0;
    if (pos == nullptr) pos = &start;
    skipWhitespace(string, pos);
    char specifier = string[*pos]-'a';
    incPtr(pos);
    if (anims[specifier] == nullptr) return nullptr;
    Animation* a = anims[specifier](string, pos, this);
    return a;
}

PlaceableObject* SystemCreator::parseObject(const char *string, int* pos) {
    int start = 0;
    if (pos == nullptr) pos = &start;
    skipWhitespace(string, pos);
    char specifier = string[*pos]-'a';
    incPtr(pos);
    if (objs[specifier] == nullptr) return nullptr;
    PlaceableObject* o = objs[specifier](string, pos, this);
    return o;
}
