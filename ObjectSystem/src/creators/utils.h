//
// Created by Ethan Horowitz on 10/31/23.
//

#ifndef SIMLED_UTILS_H
#define SIMLED_UTILS_H

#include "../../../FastLED/src/FastLED.h"

void incPtr(int* pos);
void skipWhitespace(const char* string, int* pos);
int extractNumber(const char* string, int* pos);
CRGB extractColor(const char* string, int* pos);

#endif //SIMLED_UTILS_H
