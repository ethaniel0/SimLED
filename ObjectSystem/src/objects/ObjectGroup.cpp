//
// Created by Ethan Horowitz on 12/15/23.
//

#include "ObjectGroup.h"

ObjectGroup::ObjectGroup(){
    persistent = true;
}

void ObjectGroup::update(ObjectSystem* system, ObjectManager* _){
    objects.update(system);
}

void ObjectGroup::applyToStrip(LightStrip* strip){
    objects.applyToStrip(strip);
}

void ObjectGroup::setState(int state){
    objects.setState(state);
}

PlaceableObject* ObjectGroup::clone(){
    return new ObjectGroup();
}

void ObjectGroup::addObject(PlaceableObject* object){
    objects.addObject(object);
}
