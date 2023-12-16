//
// Created by Ethan Horowitz on 10/17/23.
//

#ifndef SIMLED_OBJECTSYSTEM_H
#define SIMLED_OBJECTSYSTEM_H

#include "strips/LightStrip.h"
#include "strips/StripPath.h"
#include "objects/PlaceableObject.h"
#include "objects/Generator.h"
#include "animations/BaseAnimation.h"
#include "animations/AnimationGroups.h"
#include "animations/DataReactor.h"
#include "animations/AnimationFunctions.h"
#include "linkedlist/LinkedList.h"
#include "creators/SystemCreator.h"
#include "objects/ObjectManager.h"
#include "objects/ObjectGroup.h"
#include "objects/ObjectStateMap.h"

class PlaceableObject;

class ObjectSystem {
public:
    LightStrip strip;
    int32_t data[16];
    bool dataReset[16];
    ObjectSystem();
    ~ObjectSystem();

    void update();
    void setState(int val);
    void addObject(PlaceableObject* object);

private:
    ObjectManager objects;

};

#endif //SIMLED_OBJECTSYSTEM_H
