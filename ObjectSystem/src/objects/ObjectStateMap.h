//
// Created by Ethan Horowitz on 12/15/23.
//

#ifndef SIMLED_OBJECTSTATEMAP_H
#define SIMLED_OBJECTSTATEMAP_H

#include "./PlaceableObject.h"
#include "./ObjectGroup.h"

class ObjectStateMap: public PlaceableObject {
public:
    ObjectStateMap();

    void addState(int state, PlaceableObject* group);
    void update(ObjectSystem*, ObjectManager*) override;
    void applyToStrip(LightStrip* strip) override;
    void setState(int state) override;
    PlaceableObject* clone() override;
private:
    PlaceableObject* stateMap[16]{};
    PlaceableObject* currentGroup;
};


#endif //SIMLED_OBJECTSTATEMAP_H
