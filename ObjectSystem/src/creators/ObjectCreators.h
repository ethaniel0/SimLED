//
// Created by Ethan Horowitz on 11/2/23.
//

#ifndef SIMLED_OBJECTCREATORS_H
#define SIMLED_OBJECTCREATORS_H

#include "../objects/PlaceableObject.h"
#include "../objects/LightObject.h"
#include "SystemCreator.h"
#include "utils.h"

PlaceableObject* createLightObject(const char* string, int* pos, SystemCreator* _);

PlaceableObject* createGenerator(const char* string, int* pos, SystemCreator* _);

#endif //SIMLED_OBJECTCREATORS_H
