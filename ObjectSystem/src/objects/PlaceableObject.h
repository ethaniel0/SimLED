//
// Created by Ethan Horowitz on 10/22/23.
//

#ifndef SIMLED_PLACEABLEOBJECT_H
#define SIMLED_PLACEABLEOBJECT_H

class ObjectSystem;

class PlaceableObject {
public:
    int pos = 0;
    bool persistent = false;
    int length = 0;

    virtual void update(ObjectSystem*) = 0;
    virtual void applyToStrip(LightStrip* strip) = 0;
    virtual void setState(int state) = 0;
};

#endif //SIMLED_PLACEABLEOBJECT_H
