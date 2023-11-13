//
// Created by Ethan Horowitz on 10/18/23.
//

#include "ObjectSystem.h"

bool inView(PlaceableObject* obj, int numLEDs){
    return obj->pos + obj->length > 0 && obj->pos < numLEDs;
}

ObjectSystem::ObjectSystem(){
    this->strip = new LightStrip();
}

ObjectSystem::~ObjectSystem(){
    delete strip;
    objects.moveToStart();
    int len = objects.getLength();
    for (int i = 0; i < len; i++) {
        delete objects.current();
        objects.next();
    }
}

void ObjectSystem::update(){
    strip->clear();

    objects.moveToStart();
    while(true){
        if (objects.getLength() == 0) break;
        PlaceableObject *obj = objects.current();
        obj->update(this);

        if (!obj->persistent && !inView(obj, strip->size())) {
            objects.deleteCurrent();
        } else {
            obj->applyToStrip(strip);
        }
        bool hasNext = objects.next();
        if (!hasNext) break;
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