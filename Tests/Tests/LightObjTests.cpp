//
// Created by Ethan Horowitz on 10/20/23.
//
#include <cassert>
#include <cstdio>
#include "src/ObjectSystem.h"
#include <vector>
#include "../Framework/TestFramework.h"

TEST(LightObjects, LightObjectCreation){
    LightObject obj(30);
    ASSERT_EQ(obj.colors.getLength(), 30, %d)
    CRGB colors[] = {
        CRGB(255, 0, 0),
        CRGB(0, 255, 0),
        CRGB(0, 0, 255),
        CRGB(142, 213, 23),
        CRGB(42, 0, 69)
    };

    LightObject obj2(colors, 5);

    ASSERT_EQ(obj2.colors.getLength(), 5, %d)
    obj2.colors.moveToStart();
    for (auto color : colors){
        ASSERT_TRUE(obj2.colors.current() == color)
        obj2.colors.next();
    }
}

TEST(LightObjects, ApplyToStrip){
    LightObject obj = LightObject(new CRGB[]{
        CRGB(255, 0, 0),
        CRGB(0, 255, 0),
        CRGB(0, 0, 255),
        CRGB(142, 213, 23),
        CRGB(42, 0, 69)}, 5);

    LightStrip strip = LightStrip();
    strip.addStrip(30);

    obj.applyToStrip(&strip);

    assert(strip.get(0) == CRGB(255, 0, 0));
    assert(strip.get(1) == CRGB(0, 255, 0));
    assert(strip.get(2) == CRGB(0, 0, 255));
    assert(strip.get(3) == CRGB(142, 213, 23));
    assert(strip.get(4) == CRGB(42, 0, 69));

    strip.clear();

    obj.pos = 5;
    obj.applyToStrip(&strip);

    assert(strip.get(5) == CRGB(255, 0, 0));
    assert(strip.get(6) == CRGB(0, 255, 0));
    assert(strip.get(7) == CRGB(0, 0, 255));
    assert(strip.get(8) == CRGB(142, 213, 23));
    assert(strip.get(9) == CRGB(42, 0, 69));

    strip.clear();

    obj.pos = 28;
    obj.applyToStrip(&strip);

    assert(strip.get(28) == CRGB(255, 0, 0));
    assert(strip.get(29) == CRGB(0, 255, 0));
}

TEST(LightObjects, AddAnimation){
    LightObject obj(10);
    auto* anim = new BaseAnimation(10, true, EditableProperties::POSITION);
    obj.addAnimation(anim);
    ASSERT_EQ(obj.animations.getLength(), 1, %d)
    auto* anim2 = new BaseAnimation(10, true, EditableProperties::POSITION);
    obj.addAnimation(anim2);
    ASSERT_EQ(obj.animations.getLength(), 2, %d)
}

TEST(LightObjects, SetStateAndUpdate){
    LightObject obj(10);
    obj.pos = 10;
    auto* anim = new BaseAnimation(10, true, EditableProperties::POSITION);
    auto* func = new LinearTransform(0, 10);
    anim->addFunction(func);
    obj.addAnimation(anim);
    for (int i = 0; i < 11; i++) {
        obj.update(nullptr);
    }
    EXPECT_EQ(obj.pos, 10, %d);


}

void LOTests(){
    RUN_TEST_GROUP("LightObjects");
}
