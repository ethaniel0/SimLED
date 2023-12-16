//
// Created by Ethan Horowitz on 10/22/23.
//

#ifndef SIMLED_PLACEABLEOBJECT_H
#define SIMLED_PLACEABLEOBJECT_H

#include "../strips/LightStrip.h"

class ObjectSystem;
class ObjectManager;

class PlaceableObject {
public:
    int pos = 0;
    bool persistent = false;
    int length = 0;

    virtual ~PlaceableObject() = default;
    virtual void update(ObjectSystem*, ObjectManager*) = 0;
    virtual void applyToStrip(LightStrip* strip) = 0;
    virtual void setState(int state) = 0;
    virtual PlaceableObject* clone() = 0;
};

#endif //SIMLED_PLACEABLEOBJECT_H
