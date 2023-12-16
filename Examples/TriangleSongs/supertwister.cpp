//
// Created by Ethan Horowitz on 12/16/23.
//

#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

/*
previously:

    void supertwister(){
      if (startup){
        for (int i = 0; i < 2*NUM_LEDS; i++){
          if (i >= NUM_LEDS){
            strip2.set(i - NUM_LEDS, CHSV((i * 10) % 256, 255, 255));
          }
          else strip1.set(i, CHSV((i * 10) % 256, 255, 255));
        }
        startup = false;
      }

      CRGB c = strip2.get(NUM_LEDS - 1);
      strip2.shift(strip1.unshift(c));
    }

*/

void pg_setup(ObjectSystem* sys, SystemCreator* sc){
    // off at state 0, twinkle at state 1
    int leds = sys->strip.size();

    int* path = new int[]{0, leds/2, leds-1, leds/2-1};

    // make object move along triangle, loop the path so it goes around and around
    auto* obj = new LightObject(leds);
    obj->path = new StripPath(2, path);
    obj->loopPath = true;

    // object moves forwards one, and is colored with the gradient (with bindToLength)
    auto* moveAnim = new BaseAnimation(20, true, POSITION);
    moveAnim->addFunction(new LinearTransform(0, leds));

    auto* colorAnim = new BaseAnimation(leds, true, COLORS);
    colorAnim->bindToLength = true;
    colorAnim->updateFrames = false; // don't update frames here -> so the colors will rotate
    colorAnim->addFunction(new LinearTransform(0, 255));

    obj->addAnimation(moveAnim);
    obj->addAnimation(colorAnim);

    sys->addObject(obj);
}