//
// Created by Ethan Horowitz on 12/15/23.
//

#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

/*
previously:

    int ctlState = 0;
    void ctl(){
      if (wifiData != -1){
        ctlState = wifiData;
        wifiData = -1;
      }
      if (ctlState == 0){
        strip1.blank();
        strip2.blank();
      }
      else {
        strip1.fill(CRGB(255, 255, 255));
        strip2.fill(CRGB(255, 255, 255));
        strip1.fillBrightRand(100, 255);
        strip2.fillBrightRand(100, 255);
        delay(50);
      }
    }

*/


void pg_setup(ObjectSystem* sys, SystemCreator* sc){
    // off at state 0, twinkle at state 1
    int leds = sys->strip.size();

    // make two groups - blank and the blinking one
    ObjectGroup* blank = new ObjectGroup();
    ObjectGroup* blink = new ObjectGroup();

    // the blinking object, with animations to set color (white) and random brightness
    auto* obj = new LightObject(leds);
    obj->persistent = true;

    auto* colorAnim = new BaseAnimation(-1, true, COLORS);
    colorAnim->addFunction(new StaticTransform(0));
    colorAnim->addFunction(new StaticTransform(0));
    obj->addAnimation(colorAnim);

    auto* animation = new BaseAnimation(-1, true, BRIGHTNESS);
    animation->bindToLength = true;
    animation->addFunction(new RandomTransform(100, 255));
    obj->addAnimation(animation);

    blink->addObject(obj);

    // make state map - start at 0 (blank), then blink at 1
    ObjectStateMap* map = new ObjectStateMap();
    map->addState(0, blank);
    map->addState(1, blink);
    sys->addObject(map);
}