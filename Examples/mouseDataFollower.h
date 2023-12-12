//
// Created by Ethan Horowitz on 12/12/23.
//

#ifndef SIMLED_MOUSEDATAFOLLOWER_EXAMPLE_H
#define SIMLED_MOUSEDATAFOLLOWER_EXAMPLE_H

#include "src/ObjectSystem.h"
#include "Graphics.h"
#include "src/creators/SystemCreator.h"

void mdf_setup(ObjectSystem* sys, SystemCreator* sc){
    auto* bar = sc->parseObject("l 0 0 l 2 1 d 0 b 1120 1 c 0 0 0 0 0 1 l 0 255");
    sys->addObject(bar);

    /*
    equivalent to:
    auto* bar = new LightObject(2);
    // 640 + 480 = 1120
    auto* color = new BaseAnimation(1120, true, EditableProperties::COLORS);
    auto* colorFunc = new LinearTransform(0, 255);
    color->addFunction(colorFunc);
    auto* dataFollower = new DataReactor(color, 0);
    bar->addAnimation(dataFollower);
    sys->addObject(bar);
    */
}
void mdf_update(ObjectSystem* sys){
    Point pos = mousePos();
    sys->data[0] = pos.x + pos.y;
}



#endif //SIMLED_MOUSEDATAFOLLOWER_EXAMPLE_H
