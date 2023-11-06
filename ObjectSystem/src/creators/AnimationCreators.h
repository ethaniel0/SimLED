//
// Created by Ethan Horowitz on 10/31/23.
//

#ifndef SIMLED_ANIMATIONCREATORS_H
#define SIMLED_ANIMATIONCREATORS_H

#include "../animations/Animation.h"
#include "../animations/BaseAnimation.h"
#include "../animations/AnimationGroups.h"
#include "SystemCreator.h"
#include "utils.h"

class SystemCreator;

Animation* createBaseAnimation(const char* string, int* pos, SystemCreator* sc);

Animation* createAnimationSequence(const char* string, int* pos, SystemCreator* sc);

Animation* createAnimationStateMap(const char* string, int* pos, SystemCreator* sc);

#endif //SIMLED_ANIMATIONCREATORS_H
