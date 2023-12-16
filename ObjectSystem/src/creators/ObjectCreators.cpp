//
// Created by Ethan Horowitz on 11/2/23.
//

#include "ObjectCreators.h"
#include "../objects/ObjectGroup.h"
#include "../objects/ObjectStateMap.h"

PlaceableObject* createLightObject(const char* string, int* pos, SystemCreator* sc){
    // define by either segments or colors
    // define PlaceableObject parameters first:
    // <pos> <persistent>
    // define by segments:
    //    l <length>
    // define by colors:
    //    c <# colors> <color1 hex> <color2 hex> ...
    // after defining segments or colors:
    // ... <# animations> <animation1> <animation2> ...
    int strip_pos = extractNumber(string, pos);
    bool persistent = extractNumber(string, pos);

    skipWhitespace(string, pos);
    char specifier = string[*pos];
    incPtr(pos);

    LightObject* obj;

    if (specifier == 'l'){
        int length = extractNumber(string, pos);
        obj = new LightObject(length);
    } else if (specifier == 'c'){
        incPtr(pos);
        int numColors = extractNumber(string, pos);
        CRGB colors[numColors];
        for (int i = 0; i < numColors; i++){
            colors[i] = extractColor(string, pos);
        }
        obj = new LightObject(colors, numColors);
    }
    else return nullptr;

    obj->pos = strip_pos;
    obj->persistent = persistent;

    // add animations
    int numAnimations = extractNumber(string, pos);

    for (int i = 0; i < numAnimations; i++){
        Animation* a = sc->parseAnimation(string, pos);
        if (a == nullptr) return nullptr;
        obj->addAnimation(a);
    }
    return obj;
}

PlaceableObject* createGenerator(const char* string, int* pos, SystemCreator* sc){
    // syntax: <pos> <spacing> <... object to copy>
    int strip_pos = extractNumber(string, pos);
    int spacing = extractNumber(string, pos);
    PlaceableObject* obj = sc->parseObject(string, pos);
    if (obj == nullptr) return nullptr;
    auto* gen = new Generator(strip_pos, obj);
    gen->spacing = spacing;
    return gen;
}

PlaceableObject* createObjectGroup(const char* string, int* pos, SystemCreator* sc){
    // syntax: <# objects> <... objects to group>
    auto* group = new ObjectGroup();
    int numObjects = extractNumber(string, pos);
    for (int i = 0; i < numObjects; i++){
        PlaceableObject* obj = sc->parseObject(string, pos);
        if (obj == nullptr) return nullptr;
        group->addObject(obj);
    }
    return group;
}

PlaceableObject* createObjectStateMap(const char* string, int* pos, SystemCreator* sc){
    // syntax: <# states> ...<state> <object>...
    auto* map = new ObjectStateMap();
    int numStates = extractNumber(string, pos);
    for (int i = 0; i < numStates; i++){
        int state = extractNumber(string, pos);
        PlaceableObject* obj = sc->parseObject(string, pos);
        if (obj == nullptr) return nullptr;
        map->addState(state, obj);
    }
    return map;
}
