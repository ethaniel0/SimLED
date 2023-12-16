//
// Created by Ethan Horowitz on 12/15/23.
//

#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

/*
previously:

    int slipx = 0;
    int whitebkg = 0;
    void slip(){
      if (wifiData != -1){
        whitebkg = wifiData;
        wifiData = -1;
      }
      if (slipx % 9 == 0 || slipx % 4 == 0){
        strip1.shift(CHSV(180, 255, 255));
        strip2.shift(CHSV(180, 255, 255));
      }
      else {
        strip1.shift(CHSV(0, 0, map(whitebkg, 0, 10, 0, 255)));
        strip2.shift(CHSV(0, 0, map(whitebkg, 0, 10, 0, 255)));
      }

      if (whitebkg > 0){
        for (int i = 0; i < NUM_LEDS; i++){
          CRGB c = strip1.get(i) ;
          if (c.r == c.g && c.g == c.b){
            strip1.set(i, CHSV(0, 0, map(whitebkg - 1, 0, 10, 0, 255)));
            strip2.set(i, CHSV(0, 0, map(whitebkg - 1, 0, 10, 0, 255)));
          }
        }
        whitebkg -= 1;
      }
      slipx++;
      delay(114);
    }

*/

void pg_setup(ObjectSystem* sys, SystemCreator* sc){
    // dots flowing down the sides, with a dot emerging every 4 or 9 beats

    int leds = sys->strip.size();
    int stripLen = leds/2;

    CRGB colors[] = {CHSV(180, 255, 255)};

    // set path for right leg
    int* pathRight = new int[]{stripLen+1, leds};

    // all objects will go from top to bottom of their path (move -1)
    auto* anim = new BaseAnimation(-1, true, RELATIVE_POSITION);
    anim->addFunction(new StaticTransform(-1));

    // reference objects - left will be normal, right side needs modified path - add animations
    auto* objLeft = new LightObject(colors, 1);
    objLeft->addAnimation(anim);

    auto* objRight = new LightObject(colors, 1);
    objRight->addAnimation(anim);
    objRight->path = new StripPath(1, pathRight);

    // two generators for each side - one for 4 beats, one for 9 beats
    auto* gen11 = new Generator(stripLen-1, objLeft);
    auto* gen12 = new Generator(stripLen-1, objLeft);
    gen11->spacing = 9;
    gen12->spacing = 4;

    auto* gen21 = new Generator(stripLen-1, objRight);
    auto* gen22 = new Generator(stripLen-1, objRight);
    gen21->spacing = 9;
    gen22->spacing = 4;

    // make a group so the hit renders above all the dots
    auto* group = new ObjectGroup();

    group->addObject(gen11);
    group->addObject(gen12);
    group->addObject(gen21);
    group->addObject(gen22);

    sys->addObject(group);

    // add the hit
    auto* obj = new LightObject(leds);
    obj->persistent = true;

    auto* whiteAnim = new BaseAnimation(-1, true, COLORS);
    whiteAnim->addFunction(new StaticTransform(255));
    whiteAnim->addFunction(new StaticTransform(0));
    obj->addAnimation(whiteAnim);

    auto* hitAnim = new BaseAnimation(5, false, OPACITY);
    hitAnim->addFunction(new LinearTransform(255, 0));
    hitAnim->frames = 5;
    hitAnim->addAbsoluteStateTrigger(0, 0);

    obj->addAnimation(hitAnim);
    sys->addObject(obj);
}
