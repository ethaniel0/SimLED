//
// Created by Ethan Horowitz on 11/6/23.
//
#include "FunctionCreators.h"

AnimationFunction* createEaseTransform(const char* string, int* pos, SystemCreator* _){
    // 2 numbers: start, end
    int start = extractNumber(string, pos);
    int end = extractNumber(string, pos);
    return new EaseTransform(start, end);
}

AnimationFunction* createLinearTransform(const char* string, int* pos, SystemCreator* _){
    // 2 numbers: start, end
    int start = extractNumber(string, pos);
    int end = extractNumber(string, pos);
    return new LinearTransform(start, end);
}

AnimationFunction* createPerlinTransform(const char* string, int* pos, SystemCreator* _){
    // 3 numbers:speed, min, max
    int speed = extractNumber(string, pos);
    int min = extractNumber(string, pos);
    int max = extractNumber(string, pos);
    return new PerlinTransform(speed, min, max);
}

AnimationFunction* createRandomTransform(const char* string, int* pos, SystemCreator* _){
    // 2 numbers: min, max
    int min = extractNumber(string, pos);
    int max = extractNumber(string, pos);
    return new RandomTransform(min, max);
}

AnimationFunction* createStaticTransform(const char* string, int* pos, SystemCreator* _){
    // 1 number: val
    int val = extractNumber(string, pos);
    return new StaticTransform(val);
}