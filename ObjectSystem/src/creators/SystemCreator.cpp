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

    addAnimationFunction('e', createEaseTransform);
    addAnimationFunction('l', createLinearTransform);
    addAnimationFunction('p', createPerlinTransform);
    addAnimationFunction('r', createRandomTransform);
    addAnimationFunction('s', createStaticTransform);

    addAnimation('b', createBaseAnimation);
    addAnimation('s', createAnimationSequence);
    addAnimation('m', createAnimationStateMap);
    addAnimation('d', createDataReactor);

    addPlaceableObject('l', createLightObject);
    addPlaceableObject('g', createGenerator);
    addPlaceableObject('o', createObjectGroup);
    addPlaceableObject('m', createObjectStateMap);
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

ObjectSystem *SystemCreator::parseSystem(const char *string, int *pos) {
    // <# of strips> <strip lengths> <# of objects> <objects>
    int start = 0;
    if (pos == nullptr) pos = &start;
    skipWhitespace(string, pos);
    int numStrips = extractNumber(string, pos);
    ObjectSystem* system = new ObjectSystem();
    for (int i = 0; i < numStrips; i++){
        int len = extractNumber(string, pos);
        system->strip.addStrip(len);
    }
    int numObjects = extractNumber(string, pos);

    for (int i = 0; i < numObjects; i++){
        PlaceableObject* obj = parseObject(string, pos);
        if (obj == nullptr) return nullptr;
        system->addObject(obj);
    }

    return system;
}
