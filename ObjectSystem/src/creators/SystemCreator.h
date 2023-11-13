//
// Created by Ethan Horowitz on 10/31/23.
//

#ifndef SIMLED_SYSTEMCREATOR_H
#define SIMLED_SYSTEMCREATOR_H

#include "../animations/AnimationFunction.h"
#include "../animations/Animation.h"
#include "../objects/PlaceableObject.h"
#include "../ObjectSystem.h"


class SystemCreator {

public:
    void addAnimationFunction(char specifier, AnimationFunction*(*func)(const char* string, int* pos, SystemCreator* system));
    void addAnimation(char specifier, Animation*(*func)(const char* string, int* pos, SystemCreator* system));
    void addPlaceableObject(char specifier, PlaceableObject*(*func)(const char* string, int* pos, SystemCreator* system));

    SystemCreator();

    Animation* parseAnimation(const char* string, int* pos = 0);
    AnimationFunction* parseAnimationFunction(const char* string, int* pos = 0);
    PlaceableObject* parseObject(const char* string, int* pos = 0);
    ObjectSystem* parseSystem(const char* string, int* pos = 0);

private:
    Animation* createAnimation(const char* string, int* pos);
    Animation* createAnimationFunction(const char* string, int* pos);
    PlaceableObject* createObject(const char* string, int* pos);

    AnimationFunction*(*animFunctions[26])(const char*, int*, SystemCreator*);
    Animation*(*anims[26])(const char*, int*, SystemCreator*);
    PlaceableObject*(*objs[26])(const char*, int*, SystemCreator*);
};


#endif //SIMLED_SYSTEMCREATOR_H
