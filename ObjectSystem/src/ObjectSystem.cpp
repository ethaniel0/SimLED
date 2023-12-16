//
// Created by Ethan Horowitz on 10/18/23.
//

#include "ObjectSystem.h"

ObjectSystem::ObjectSystem(){
    for (int i = 0; i < 16; i++) data[i] = 0;
    for (bool & b : dataReset) b = false;
}

ObjectSystem::~ObjectSystem(){
    objects.clear();
}

void ObjectSystem::update(){
    strip.clear();

    objects.updateAndApply(this);

    for (int i = 0; i < 16; i++){
        if (dataReset[i]) data[i] = 0;
    }
}

void ObjectSystem::setState(int val){
    objects.setState(val);
}

void ObjectSystem::addObject(PlaceableObject* object){
    objects.addObject(object);
}
