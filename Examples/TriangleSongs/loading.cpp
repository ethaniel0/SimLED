//
// Created by Ethan Horowitz on 12/15/23.
//
#include "src/ObjectSystem.h"
#include "src/creators/SystemCreator.h"

/*
Previously:

    int32_t loadingx = random(0, 1000);
    int32_t loadingy = random(0, 1000);

    // lights that follow each other randomly across the triangle
    void loading(){
      strip1.blank();
      strip2.blank();
      for (int i = 0; i < 5; i++){
        int pos = (int) map(inoise8(loadingx + i*800), 0, 255, 0, NUM_LEDS*2 - 1);
        int c = (230/5)*i;
        if (pos < NUM_LEDS) strip1.set(pos, CHSV(c, 255, 255));
        else strip2.set(2*NUM_LEDS - pos-1, CHSV(c, 255, 255));
      }
      loadingx += 1;
    }
*/

void pg_setup(ObjectSystem* sys, SystemCreator* sc){
    // 5 leds randomly (perlin noise) move and follow each other

    int leds = sys->strip.size();
    int stripLen = leds/2;

    int* path = new int[]{0, stripLen+1, leds-1, stripLen};

    for (int i = 0; i < 5; i++){
        int c = (230/5)*i;
        CRGB colors[] = {CHSV(c, 255, 255)};
        auto* obj = new LightObject(colors, 1);
        obj->path = new StripPath(2, path);
        auto* anim = new BaseAnimation(-1, true, POSITION);
        anim->frameOffset = 800*i;
        anim->addFunction(new PerlinTransform(1000, 0, leds));
        obj->addAnimation(anim);
        sys->addObject(obj);
    }
}
