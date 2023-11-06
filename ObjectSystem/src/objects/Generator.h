//
// Created by Ethan Horowitz on 11/2/23.
//

#ifndef SIMLED_GENERATOR_H
#define SIMLED_GENERATOR_H

#include "PlaceableObject.h"
#include "../ObjectSystem.h"
#include "../linkedlist/LinkedList.h"

class Generator: public PlaceableObject {
public:
    int frames = 0;
    int spacing = 2;
    Generator(int pos, PlaceableObject* referenceObject);

    void update(ObjectSystem*) override;
    void applyToStrip(LightStrip* strip) override;
    void setState(int state) override;
    void addStopState(int state);
    void addStartState(int state);

    Generator* clone() override;

private:
    bool active = true;
    PlaceableObject* object;
    LinkedList<int> stopStates;
    LinkedList<int> startStates;
};


#endif //SIMLED_GENERATOR_H
