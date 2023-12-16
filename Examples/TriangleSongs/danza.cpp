//
// Created by Ethan Horowitz on 12/16/23.
//

#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

/*
previously:

    int danzax = 0;
    void danza(){
      strip1.fill(CHSV(map(inoise8(danzax), 0, 255, 100, 190), 255, 100));
      strip2.fill(CHSV(map(inoise8(danzax), 0, 255, 100, 190), 255, 100));
      danzax++;
    }

*/


void pg_setup(ObjectSystem* sys, SystemCreator* sc){
    int leds = sys->strip.size();

    // one object the length of the triangle
    auto* obj = new LightObject(leds);
    obj->persistent = true;

    // color the whole object with solid color, update with perlin noise
    auto* colorAnim = new BaseAnimation(-1, true, COLORS);
    colorAnim->addFunction(new PerlinTransform(800, 100, 190));
    colorAnim->addFunction(new StaticTransform(255));
    colorAnim->addFunction(new StaticTransform(200));

    obj->addAnimation(colorAnim);
    sys->addObject(obj);
}