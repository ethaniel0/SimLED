//
// Created by Ethan Horowitz on 11/2/23.
//

#include "Generator.h"

Generator::Generator(int pos, PlaceableObject* referenceObject) {
    this->pos = pos;
    object = referenceObject->clone();
    length = 0;
    persistent = true;
    spacing = 2;
}

void Generator::update(ObjectSystem* system) {
    if (frames % spacing == 0 && active) {
        system->addObject(object->clone());
    }
    frames++;
}

// generators are invisible
void Generator::applyToStrip(LightStrip *strip) {}

void Generator::setState(int state) {
    if (active){
        stopStates.moveToStart();
        int len = stopStates.getLength();
        for (int i = 0; i < len; i++){
            if (stopStates.current() == state){
                active = false;
                return;
            }
        }
    }
    else {
        startStates.moveToStart();
        int len = startStates.getLength();
        for (int i = 0; i < len; i++){
            if (startStates.current() == state){
                active = true;
                return;
            }
        }
    }
}

void Generator::addStopState(int state) {
    stopStates.append(state);
}

void Generator::addStartState(int state) {
    startStates.append(state);
}

Generator* Generator::clone() {
    auto* gen = new Generator(pos, object);
    delete object;
    gen->length = length;
    gen->persistent = persistent;
    gen->active = active;
    stopStates.moveToStart();
    int len = stopStates.getLength();
    for (int i = 0; i < len; i++){
        gen->stopStates.append(stopStates.current());
        stopStates.next();
    }
    startStates.moveToStart();
    len = startStates.getLength();
    for (int i = 0; i < len; i++){
        gen->startStates.append(startStates.current());
        startStates.next();
    }
    return gen;
}