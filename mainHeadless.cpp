//
// Created by Ethan Horowitz on 10/22/23.
//
#include "src/ObjectSystem.h"
#include <cmath>

ObjectSystem* objsystem;

int main() {
    objsystem = new ObjectSystem();

    objsystem->strip.addStrip(30);
    objsystem->strip.addStrip(30);

    auto* obj = new LightObject(10);
    obj->persistent = true;
    auto* gradient = new BaseAnimation(80, true, EditableProperties::COLORS);
    gradient->bindToLength = true;
    gradient->addFunction(new LinearTransform(0, 255));
    gradient->addFunction(new StaticTransform(255));
    obj->addAnimation(gradient);

    auto* anim = new BaseAnimation(60, true, EditableProperties::POSITION);
    anim->addFunction(new LinearTransform(0, 80));
    anim->addAbsoluteStateTrigger(0, 0);
    obj->addAnimation(anim);


    auto obj2 = new LightObject(60);
    auto anim2 = new BaseAnimation(255*20, false, EditableProperties::COLORS);
    anim2->addFunction(new LinearTransform(0, 255*20));
    obj2->addAnimation(anim2);


    objsystem->addObject(obj2);
    objsystem->addObject(obj);


    for (int i = 0; i < 500; i++){
        objsystem->update();
    }
}
