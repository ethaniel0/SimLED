//
// Created by Ethan Horowitz on 12/15/23.
//

#include "ObjectManager.h"
#include "../ObjectSystem.h"

bool inView(PlaceableObject* obj, int numLEDs){
    return obj->pos + obj->length > 0 && obj->pos < numLEDs;
}

ObjectManager::ObjectManager() = default;

void ObjectManager::updateAndApply(ObjectSystem* system){
    objects.moveToStart();
    while(true){
        if (objects.getLength() == 0) break;
        PlaceableObject *obj = objects.current();
        obj->update(system, this);

        if (!obj->persistent && !inView(obj, system->strip.size())) {
            objects.deleteCurrent();
        } else {
            obj->applyToStrip(&system->strip);
        }

        bool hasNext = objects.next();
        if (!hasNext) break;
    }
}

void ObjectManager::update(ObjectSystem* system){
    objects.moveToStart();
    while(true){
        if (objects.getLength() == 0) break;
        PlaceableObject *obj = objects.current();
        obj->update(system, this);

        if (!obj->persistent && !inView(obj, system->strip.size())) {
            objects.deleteCurrent();
        }

        bool hasNext = objects.next();
        if (!hasNext) break;
    }
}

void ObjectManager::applyToStrip(LightStrip* strip){
    objects.moveToStart();
    while(true){
        if (objects.getLength() == 0) break;
        objects.current()->applyToStrip(strip);
        bool hasNext = objects.next();
        if (!hasNext) break;
    }
}

void ObjectManager::addObject(PlaceableObject* object){
    objects.append(object);
}

void ObjectManager::setState(int val){
    objects.moveToStart();
    int length = objects.getLength();
    for (int i = 0; i < length; i++) {
        objects.current()->setState(val);
        objects.next();
    }
}

void ObjectManager::clear(){
    objects.moveToStart();
    int length = objects.getLength();
    for (int i = 0; i < length; i++) {
        delete objects.current();
        objects.next();
    }
    objects.clear();
}

