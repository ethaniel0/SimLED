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
    auto* anim = new BaseAnimation(10, false, EditableProperties::POSITION);
    auto* func = new LinearTransform(0, 10);
    anim->addFunction(func);
    obj.addAnimation(anim);
    for (int i = 0; i <= 10; i++) {
        obj.update(nullptr);
    }
    EXPECT_EQ(obj.pos, 10, %d);


}

TEST(LightObjects, VariedLengths){
    LightObject obj(1);
    LightObject obj2(5);
    LightObject obj3(10);
    LightObject obj4(50);
    LightObject obj5(100);

    EXPECT_EQ(obj.length, 1, %d)
    EXPECT_EQ(obj.colors.getLength(), 1, %d)
    obj.colors.moveToStart();
    obj.colors.next();

    EXPECT_EQ(obj2.length, 5, %d)
    EXPECT_EQ(obj2.colors.getLength(), 5, %d)
    obj2.colors.moveToStart();
    for (int i = 0; i < 5; i++) obj2.colors.next();

    EXPECT_EQ(obj3.length, 10, %d)
    EXPECT_EQ(obj3.colors.getLength(), 10, %d)
    obj3.colors.moveToStart();
    for (int i = 0; i < 10; i++) obj3.colors.next();

    EXPECT_EQ(obj4.length, 50, %d)
    EXPECT_EQ(obj4.colors.getLength(), 50, %d)
    obj4.colors.moveToStart();
    for (int i = 0; i < 50; i++) obj4.colors.next();

    EXPECT_EQ(obj5.length, 100, %d)
    EXPECT_EQ(obj5.colors.getLength(), 100, %d)
    obj5.colors.moveToStart();
    for (int i = 0; i < 100; i++) obj5.colors.next();
}

TEST(LightObjects, Cloning){
    LightObject obj(1);
    LightObject* obj2 = obj.clone();

    EXPECT_EQ(obj.length, obj2->length, %d)
    EXPECT_EQ(obj.wrapMode, obj2->wrapMode, %d)
    EXPECT_EQ(obj.opacity, obj2->opacity, %d)
    EXPECT_EQ(obj.persistent, obj2->persistent, %d)
    EXPECT_EQ(obj.pos, obj2->pos, %d)
    EXPECT_EQ(obj.colors.getLength(), obj2->colors.getLength(), %d)
    obj.colors.moveToStart();
    obj2->colors.moveToStart();
    for (int i = 0; i < obj.length; i++){
        EXPECT_TRUE(obj.colors.current() == obj2->colors.current())
        obj.colors.next();
        obj2->colors.next();
    }
    EXPECT_EQ(obj.animations.getLength(), obj2->animations.getLength(), %d)

    delete obj2;

    CRGB colors[] = {
            CRGB(255, 0, 0), CRGB(255, 255, 0),
            CRGB(0, 255, 0), CRGB(0, 255, 255),
            CRGB(0, 0, 255), CRGB(255, 0, 255)
    };

    LightObject coloredObj(colors, 6);
    coloredObj.opacity = 128;
    coloredObj.wrapMode = 1;
    coloredObj.pos = 21;
    coloredObj.persistent = true;
    LightObject* coloredObj2 = coloredObj.clone();

    EXPECT_EQ(coloredObj.length, coloredObj2->length, %d)
    EXPECT_EQ(coloredObj.wrapMode, coloredObj2->wrapMode, %d)
    EXPECT_EQ(coloredObj.opacity, coloredObj2->opacity, %d)
    EXPECT_EQ(coloredObj.colors.getLength(), coloredObj2->colors.getLength(), %d)
    EXPECT_EQ(coloredObj.persistent, coloredObj2->persistent, %d)
    EXPECT_EQ(coloredObj.pos, coloredObj2->pos, %d)
    coloredObj.colors.moveToStart();
    coloredObj2->colors.moveToStart();
    for (int i = 0; i < coloredObj.length; i++){
        EXPECT_TRUE(coloredObj.colors.current() == coloredObj2->colors.current())
        coloredObj.colors.next();
        coloredObj2->colors.next();
    }
    EXPECT_EQ(coloredObj.animations.getLength(), coloredObj2->animations.getLength(), %d)
}

void LOTests(){
    RUN_TEST_GROUP("LightObjects");
}
