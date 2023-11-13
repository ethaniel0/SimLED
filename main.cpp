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

    objectSystem->strip->addStrip(30);
    objectSystem->strip->addStrip(30);

    strip1 = new StripElement(objectSystem->strip->getSegment(0), 30);
    strip1->setParameters(100, 460,  -M_PI/3, 15, 15);
    strip2 = new StripElement(objectSystem->strip->getSegment(1), 30);
    strip2->setParameters(550, 460, -2*M_PI/3, 15, 15);

//    auto* lightobj = sc.parseObject("l 0 0 c 1 ff0000 1 " "b -1 0 r 0 0 0 1 s 1");
    auto* gen = sc.parseObject("g0 8 " "l 0 0 c 1 ff0000 1 " "b -1 1 r 0 0 0 1 s 1");
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