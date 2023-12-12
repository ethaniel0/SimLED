//
// Created by Ethan Horowitz on 12/12/23.
//

#ifndef SIMLED_GENERATOR_EXAMPLE_H
#define SIMLED_GENERATOR_EXAMPLE_H

#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

void gen_setup(ObjectSystem* sys, SystemCreator* sc) {
    auto* gen = sc->parseObject("g0 8 " "l 0 0 c 1 ff0000 1 " "b -1 1 r 0 0 0 0 0 1 s 1");
    sys->addObject(gen);

    /*
    equivalent to:

    auto* obj = new LightObject(new CRGB[]{CRGB::Red}, 1);

    auto* anim = new BaseAnimation(-1, true, RELATIVE_POSITION);
    anim->addFunction(new StaticTransform(1));
    obj->addAnimation(anim);

    auto* gen = new Generator(0, obj);
    gen->spacing = 8;

    objectSystem->addObject(gen);
     */
}

#endif //SIMLED_GENERATOR_EXAMPLE_H
