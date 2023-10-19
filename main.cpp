#include "ObjectSystem/ObjectSystem.hpp"
#include <xd/xd.hpp>
#include "Graphics/StripElement.h"
#include <cmath>

using namespace xd;

StripElement* strip1;
StripElement* strip2;
ObjectSystem* objsystem;

CRGB* strip1Arr;
CRGB* strip2Arr;

void setup() {
    size(640, 480);

    strip1Arr = new CRGB[30];
    strip2Arr = new CRGB[30];
    auto* strip = new LightStrip(2, new CRGB*[2]{strip1Arr, strip2Arr}, new int[2]{30, 30});

    strip1 = new StripElement(strip1Arr, 30);
    strip1->setParameters(100, 460,  -M_PI/3, 15, 15);
    strip2 = new StripElement(strip2Arr, 30);
    strip2->setParameters(550, 460, -2*M_PI/3, 15, 15);

    objsystem = new ObjectSystem(strip);

    auto* obj = new LightObject(10);
    obj->persistent = true;
    auto* gradient = new BaseAnimation(80, true, EditableProperties::COLORS);
    gradient->bindToLength = true;
    gradient->addFunction(new LinearTransform(0, 255));
    gradient->addFunction(new StaticTransform(255));
    gradient->bindToLength = true;
    obj->addAnimation(gradient);

    auto* anim = new BaseAnimation(60, true, EditableProperties::POSITION);
//    auto* ltransform = ;
    anim->addFunction(new LinearTransform(0, 80));
    obj->addAnimation(anim);

    //    LightObject obj2(60);
    //    obj2.pos = 0;
    //    BaseAnimation anim2(255*20, false, EditableProperties::COLORS);
    //    LinearTransform ltransform2(0, 255*20);
    //    anim2.addFunction(&ltransform2);
    //    obj2.addAnimation(&anim2);

    objsystem->add_object(obj);
    //    objsystem.add_object(&obj2);
}

void draw() {
    background(color(0, 0, 0));
    strip1->draw();
    strip2->draw();
//    testCircle(640, 480);
//    printf("led 1 color: %d, %d, %d\n", strip1Arr[0].r, strip1Arr[0].g, strip1Arr[0].b);


    objsystem->update();
}

void destroy() {

}