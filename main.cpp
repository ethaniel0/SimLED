#include "src/ObjectSystem.h"
#include <xd/xd.hpp>
#include "Graphics.h"
#include "src/creators/SystemCreator.h"
#include <cmath>
#include <chrono>
#include <thread>

using namespace xd;

StripElement* strip1;
StripElement* strip2;
ObjectSystem* objectSystem;

Button* state1;

void action1(int _){
    objectSystem->setState(0);
}

void setup() {
    size(640, 480);

    trackMouse();

    objectSystem = new ObjectSystem();

    SystemCreator sc;

    objectSystem->strip.addStrip(30);
    objectSystem->strip.addStrip(30);

    strip1 = new StripElement(objectSystem->strip.getSegment(0), 30);
    strip1->setParameters(100, 460,  -M_PI/3, 15, 15);
    strip2 = new StripElement(objectSystem->strip.getSegment(1), 30);
    strip2->setParameters(550, 460, -2*M_PI/3, 15, 15);

    auto* smallObj = new LightObject(1);
    auto* smallAnim = new BaseAnimation(-1, true, EditableProperties::COLORS);
    smallAnim->addFunction(new StaticTransform(0));
    smallAnim->addFunction(new StaticTransform(255));

    printf("%d\n", smallObj->colors.getLength());

    auto* moveAnim = new BaseAnimation(80, false, EditableProperties::RELATIVE_POSITION);
    moveAnim->addFunction(new StaticTransform(1));

    smallObj->addAnimation(smallAnim);
    smallObj->addAnimation(moveAnim);


    auto* gen = new Generator(0, smallObj);
    gen->spacing = 10;


//    auto* entireObject = sc.parseObject(
//            "l0 1 l 10 2 "
//            "b80 1 c 1 0 2 l0 255 s255 0 0 "
//            "b60 1 p 0 0 2 l0 80 s255 1 0 0 0"
//    );
//
//    auto* movingobject = sc.parseObject(
//            "l0 1 c 7 ff0000 ffff00 00ff00 00ffff 0000ff ff00ff ffffff 1"
//            "b80 1 p 0 0 1 l0 80"
//    );

//    // LightObject pos 0, persistent. Create with length of 10. No animations.
//    auto* obj = (LightObject*) sc.parseObject("l0 1 l 10 0");
//
//    // baseAnimation dur 80, loop, bind color, bind to length, 0 offset. functions: linear 0 255, static 255. No absolute or relative state transitions
//    auto* gradient = sc.parseAnimation("b80 1 c 1 0 2 l0 255 s255 0 0");
//    obj->addAnimation(gradient);
//
//    // baseAnimation dur 16, loop, bind position, bind to length, 0 offset. functions: linear 0 80, static 255. One absolute state transition: 1 0, no relative state positions
//    auto* anim = (BaseAnimation*) sc.parseAnimation("b60 1 p 0 0 2 l0 80 s255 1 0 0 0");
//    obj->addAnimation(anim);

    auto obj2 = new LightObject(60);
    auto anim2 = new BaseAnimation(255*20, false, EditableProperties::COLORS);
    anim2->addFunction(new LinearTransform(0, 255*20));
    obj2->addAnimation(anim2);

//    objectSystem->addObject(obj2);
//    objectSystem->addObject(entireObject);
//    objectSystem->addObject(movingobject);
    objectSystem->addObject(gen);

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

    objectSystem->update();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void destroy() {
    delete objectSystem;
    delete strip1;
    delete strip2;
    delete state1;
}