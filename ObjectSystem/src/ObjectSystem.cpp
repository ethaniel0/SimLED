//
// Created by Ethan Horowitz on 10/18/23.
//

#include "ObjectSystem.h"

bool inView(PlaceableObject* obj, int numLEDs){
    return obj->pos + obj->length > 0 && obj->pos < numLEDs;
}

ObjectSystem::ObjectSystem(){
    this->strip = LightStrip();
}

ObjectSystem::~ObjectSystem(){
    objects.moveToStart();
    int len = objects.getLength();
    for (int i = 0; i < len; i++) {
        delete objects.current();
        objects.next();
    }
}

void ObjectSystem::update(){
    strip.clear();

    int numObjects = (int) objects.getLength();

    objects.moveToStart();
    for (int i = 0; i < numObjects; i++){
        PlaceableObject *obj = objects.current();
        obj->update(this);

        if (!obj->persistent && !inView(obj, strip.size())) {
            objects.deleteCurrent();
            numObjects--;
        } else {
            obj->applyToStrip(&strip);
        }
        objects.next();
    }

}

void ObjectSystem::addObject(PlaceableObject* object){
    this->objects.append(object);
}

void ObjectSystem::setState(int val){
    objects.moveToStart();
    int len = objects.getLength();
    for (int i = 0; i < len; i++) {
        objects.current()->setState(val);
        objects.next();
    }
}