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

class DataColorAnimation : public Animation {
public:
    DataColorAnimation() = default;

    void update(int32_t *data) override{
        obj->colors.moveToStart();
        for (int i = 0; i < obj->length; i++) {
            obj->colors.current() = CHSV(data[0], 255, 255);
            obj->colors.next();
        }
        data[0] = (data[0] + 20) % 255;
    };

    bool isFinished() override{
        return false;
    };
    void reset() override {}
    void setState(int state) override {};
    Animation* clone() override {
        return new DataColorAnimation();
    };


};


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

    LightObject* obj = new LightObject(1);
    obj->colors.update(CRGB::Red);
    obj->path = new StripPath(2, new int[]{0, 30, 59, 29});
    obj->addAnimation(new DataColorAnimation());
    obj->addAnimation(sc.parseAnimation("b -1 0 r 0 0 0 1 s 1"));


//    auto* lightobj = (LightObject*) sc.parseObject("l 0 0 c 1 ff0000 1 " "b -1 0 r 0 0 0 1 s 1");
//    lightobj->path = new StripPath(6, new int[]{0, 5, 10, 5, 11, 20, 25, 20, 25, 30, 59, 30});
    auto* gen = new Generator(0, obj);
    gen->spacing = 5;
//    auto* gen = sc.parseObject("g0 8 " "l 0 0 c 1 ff0000 1 " "b -1 1 r 0 0 0 1 s 1");
    objectSystem->addObject(gen);
    objectSystem->dataReset[0] = true;

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
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void destroy() {
    delete objectSystem;
    delete strip1;
    delete strip2;
    delete state1;
}