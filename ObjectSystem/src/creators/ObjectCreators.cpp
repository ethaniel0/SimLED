//
// Created by Ethan Horowitz on 11/2/23.
//

#include "ObjectCreators.h"

PlaceableObject* createLightObject(const char* string, int* pos, SystemCreator* sc){
    // define by either length or colors
    // define PlaceableObject parameters first:
    // <pos> <persistent>
    // define by length:
    //    l <length>
    // define by colors:
    //    c <# colors> <color1 hex> <color2 hex> ...
    // after defining length or colors:
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
