//
// Created by Ethan Horowitz on 10/31/23.
//

#ifndef SIMLED_FUNCTIONCREATOR_H
#define SIMLED_FUNCTIONCREATOR_H

#include "../animations/AnimationFunction.h"
#include "../animations/AnimationFunctions.h"
#include "utils.h"

class SystemCreator;

AnimationFunction* createEaseTransform(const char* string, int* pos, SystemCreator* _);

AnimationFunction* createLinearTransform(const char* string, int* pos, SystemCreator* _);

AnimationFunction* createPerlinTransform(const char* string, int* pos, SystemCreator* _);

AnimationFunction* createRandomTransform(const char* string, int* pos, SystemCreator* _);

AnimationFunction* createStaticTransform(const char* string, int* pos, SystemCreator* _);

#endif //SIMLED_FUNCTIONCREATOR_H
