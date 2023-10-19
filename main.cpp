//#include <iostream>
#include <cstdio>
//#include "FastLED/src/FastLED.h"
#include "ObjectSystem/ObjectSystem.hpp"
//#include <xd/xd.hpp>


int main() {
    CRGB led1[60];
    CRGB led2[60];
    LightStrip strip(2, new CRGB*[2]{led1, led2}, new int[2]{30, 30});

    ObjectSystem objsystem(&strip);

    LightObject obj(10);
    BaseAnimation anim(20, false, EditableProperties::POSITION);
    LinearTransform ltransform(0, 40);
    anim.addFunction(&ltransform);
    obj.addAnimation(&anim);

//    LightObject obj2(60);
//    obj2.pos = 0;
//    BaseAnimation anim2(255*20, false, EditableProperties::COLORS);
//    LinearTransform ltransform2(0, 255*20);
//    anim2.addFunction(&ltransform2);
//    obj2.addAnimation(&anim2);

    objsystem.add_object(&obj);
//    objsystem.add_object(&obj2);

    for (int i = 0; i < 30; i++){
        objsystem.update();
        printf("obj pos: %d\n", obj.pos);
    }

    return 0;
}


//using namespace xd;
//
//void setup() {
//    size(640, 480);
//}
//
//glm::vec4 color(int r, int g, int b) {
//    return {r/255.0, g/255.0, b/255.0, 1.0};
//}
//
//void draw() {
//    background(color(200, 200, 230));
//    // fill(255, 0, 0);
//
//    fill(color(255, 0, 0));
//
//    ellipse(100, 100, 50, 50);
//
//    // rect(50, 50, 100, 100);
//
//    fill(color(0, 255, 0));
//    rect(250, 250, 150, 20);
//
//}
//
//void destroy() {
//
//}