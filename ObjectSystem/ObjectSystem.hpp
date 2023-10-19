//
// Created by Ethan Horowitz on 10/17/23.
//

#ifndef SIMLED_OBJECTSYSTEM_HPP
#define SIMLED_OBJECTSYSTEM_HPP

#include "LightStrip.hpp"
#include "LightObject.hpp"
#include "animations/Animation.hpp"
#include "animations/BaseAnimation.hpp"
#include "animations/animations.hpp"
#include <vector>

class ObjectSystem {
public:
    std::vector<LightObject*> objects;
    explicit ObjectSystem(LightStrip* strip);

    void update();
    void add_object(LightObject* object);
    void setState(int val);

private:
    LightStrip* strip;

};

#endif //SIMLED_OBJECTSYSTEM_HPP
