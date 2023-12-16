//
// Created by Ethan Horowitz on 12/15/23.
//

#ifndef SIMLED_OBJECTMANAGER_H
#define SIMLED_OBJECTMANAGER_H

#include "../strips/LightStrip.h"
#include "./PlaceableObject.h"

class ObjectSystem;

class ObjectManager {
public:
    ObjectManager();
    void updateAndApply(ObjectSystem* system);
    void update(ObjectSystem* system);
    void applyToStrip(LightStrip* strip);
    void addObject(PlaceableObject* object);
    void setState(int val);
    void clear();

private:
    LinkedList<PlaceableObject*> objects;
};


#endif //SIMLED_OBJECTMANAGER_H
