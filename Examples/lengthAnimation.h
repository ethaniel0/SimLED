//
// Created by Ethan Horowitz on 12/12/23.
//

#ifndef SIMLED_LENGTHANIMATION_EXAMPLE_H
#define SIMLED_LENGTHANIMATION_EXAMPLE_H

#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

void l_setup(ObjectSystem* sys, SystemCreator* sc){
    auto* obj = sc->parseObject("l 0 0 l 1 2 b 30 1 l 0 0 0 0 0 1 l 1 30 b -1 1 c 0 0 0 0 0 1 s 255");
    sys->addObject(obj);

    /*
    equivalent to:

    auto* obj = new LightObject(1);

    auto* lengthAnim = new BaseAnimation(30, true, LENGTH);
    lengthAnim->addFunction(new LinearTransform(1, 30));
    obj->addAnimation(lengthAnim);

    auto* colorAnim = new BaseAnimation(-1, true, COLORS);
    colorAnim->addFunction(new StaticTransform(255));

    obj->addAnimation(colorAnim);
    */
}

#endif //SIMLED_LENGTHANIMATION_EXAMPLE_H
