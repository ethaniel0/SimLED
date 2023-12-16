//
// Created by Ethan Horowitz on 12/15/23.
//

#ifndef SIMLED_OBJECTGROUP_H
#define SIMLED_OBJECTGROUP_H

#include "./PlaceableObject.h"
#include "./ObjectManager.h"

class ObjectGroup: public PlaceableObject {
public:
    ObjectGroup();
    void update(ObjectSystem* system, ObjectManager* manager) override;
    void applyToStrip(LightStrip* strip) override;
    void setState(int state) override;
    PlaceableObject* clone() override;
    void addObject(PlaceableObject* object);
private:
    ObjectManager objects;
};


#endif //SIMLED_OBJECTGROUP_H
