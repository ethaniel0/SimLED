//
// Created by Ethan Horowitz on 10/18/23.
//

#include "ObjectSystem.hpp"

bool inView(LightObject* obj, int numLEDs){
    return obj->pos + obj->colors.size() > 0 && obj->pos < numLEDs;
}

ObjectSystem::ObjectSystem(LightStrip* strip){
    this->strip = strip;
    objects = std::vector<LightObject*>();
}

void ObjectSystem::update(){
    strip->clear();

    int numObjects = (int) objects.size();

    for (int i = numObjects - 1; i >= 0; i--) {

        LightObject *obj = objects[i];
        obj->update();

        if (!obj->persistent && !inView(obj, strip->totalLEDs)) {
            objects.erase(objects.begin() + i);
            numObjects--;
        } else {
            obj->applyToStrip(strip);
        }
    }

    for (auto obj : this->objects){
        if (inView(obj, this->strip->totalLEDs)){
            for (int j = 0; j < obj->colors.size(); j++)
                this->strip->set(obj->pos + j, obj->colors[j]);
        }
    }
}

void ObjectSystem::add_object(LightObject* object){
    this->objects.push_back(object);
}

void ObjectSystem::setState(int val){
    for (auto obj : this->objects){
        obj->setState(val);
    }
}