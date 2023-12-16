#include "src/ObjectSystem.h"
#include <xd/xd.hpp>
#include "Graphics.h"
#include "src/creators/SystemCreator.h"
#include <cmath>
#include <chrono>
#include <thread>

//#include "Examples/generator.h"
#include "Examples/TriangleSongs/slip.cpp"

using namespace xd;

StripElement* strip1;
StripElement* strip2;
ObjectSystem* objectSystem;

Button* state1;
Button* state2;

void action1(){
    objectSystem->setState(0);
}
void action2(){
    objectSystem->setState(1);
}

void setup() {
    const int NUM_LEDS = 91;
    size(640, 480);

    trackMouse();

    objectSystem = new ObjectSystem();

    SystemCreator sc;

    objectSystem->strip.addStrip(NUM_LEDS);
    objectSystem->strip.addStrip(NUM_LEDS);

    strip1 = new StripElement(objectSystem->strip.getSegment(0), NUM_LEDS);
    strip1->setParameters(100, 460,  -M_PI/3, 5, 5);
    strip2 = new StripElement(objectSystem->strip.getSegment(1), NUM_LEDS);
    strip2->setParameters(550, 460, -2*M_PI/3, 5, 5);

    pg_setup(objectSystem, &sc);

    state1 = new Button(new char[]{'0'}, 10, 10, 80, 25);
    state1->fontsize = 30;
    state1->action = action1;

    state2 = new Button(new char[]{'1'}, 10, 40, 80, 25);
    state2->fontsize = 30;
    state2->action = action2;
}

void draw() {
    background(color(0, 0, 0));
    strip1->draw();
    strip2->draw();

    fill(color(255, 255, 255));
    state1->draw();
    state2->draw();

    objectSystem->update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void destroy() {
    delete objectSystem;
    delete strip1;
    delete strip2;
    delete state1;
}