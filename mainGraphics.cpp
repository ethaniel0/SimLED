#include "src/ObjectSystem.h"
#include <xd/xd.hpp>
#include "Graphics/Graphics.h"
#include <cmath>

using namespace xd;

StripElement* strip1;
StripElement* strip2;
ObjectSystem* objsystem;

Button* state1;

void action1(int _){
    objsystem->setState(0);
}

void setup() {
    size(640, 480);

    trackMouse();

    objsystem = new ObjectSystem();

    objsystem->strip.addStrip(30);
    objsystem->strip.addStrip(30);

    strip1 = new StripElement(objsystem->strip.getSegment(0), 30);
    strip1->setParameters(100, 460,  -M_PI/3, 15, 15);
    strip2 = new StripElement(objsystem->strip.getSegment(1), 30);
    strip2->setParameters(550, 460, -2*M_PI/3, 15, 15);

    auto* obj = new LightObject(10);
    obj->persistent = true;
    auto* gradient = new BaseAnimation(80, true, EditableProperties::COLORS);
    gradient->bindToLength = true;
    gradient->addFunction(new LinearTransform(0, 255));
    gradient->addFunction(new StaticTransform(255));
    obj->addAnimation(gradient);

    auto* anim = new BaseAnimation(60, true, EditableProperties::POSITION);
//    auto* ltransform = ;
    anim->addFunction(new LinearTransform(0, 80));
    anim->addAbsoluteStateTrigger(0, 0);
    obj->addAnimation(anim);


    auto obj2 = new LightObject(60);
    auto anim2 = new BaseAnimation(255*20, false, EditableProperties::COLORS);
    anim2->addFunction(new LinearTransform(0, 255*20));
    obj2->addAnimation(anim2);


    objsystem->addObject(obj2);
    objsystem->addObject(obj);

    state1 = new Button(new char[]{'1'}, 10, 10, 80, 25);
    state1->fontsize = 30;
    state1->action = action1;
}



void draw() {
    background(color(0, 0, 0));
    strip1->draw();
    strip2->draw();

    fill(color(255, 255, 255));
    state1->draw();

    objsystem->update();
}

void destroy() {
    delete objsystem;
    delete strip1;
    delete strip2;
    delete state1;
}