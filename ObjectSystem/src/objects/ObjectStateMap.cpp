//
// Created by Ethan Horowitz on 12/15/23.
//

#include "ObjectStateMap.h"

ObjectStateMap::ObjectStateMap() {
    persistent = true;
    for (int i = 0; i < 16; i++) {
        stateMap[i] = nullptr;
    }
}

void ObjectStateMap::addState(int state, PlaceableObject* obj) {
    stateMap[state] = obj;
}

void ObjectStateMap::update(ObjectSystem *system, ObjectManager *manager) {
    if (currentGroup == nullptr) return;
    currentGroup->update(system, manager);
}

void ObjectStateMap::applyToStrip(LightStrip *strip) {
    if (currentGroup == nullptr) return;
    currentGroup->applyToStrip(strip);
}

void ObjectStateMap::setState(int state) {
    if (state < 0 || state > 15) return;
    auto s = stateMap[state];
    if (s != nullptr) {
        currentGroup = s;
    }
}

PlaceableObject *ObjectStateMap::clone() {
    auto map = new ObjectStateMap();
    for (int i = 0; i < 16; i++) {
        if (stateMap[i] != nullptr)
            map->addState(i, stateMap[i]->clone());
    }
    return map;
}