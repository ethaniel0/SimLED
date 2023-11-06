//
// Created by Ethan Horowitz on 11/6/23.
//
#include "AnimationTests.h"
#include <src/animations/BaseAnimation.h>
#include <src/animations/AnimationFunctions.h>

void AnimationTests(){
    RUN_TEST_GROUP("Animations");
}

TEST(Animations, BasePos){
    auto* anim = new BaseAnimation(10, false, EditableProperties::POSITION);
    AnimationFunction* func = new LinearTransform(0, 100);
    anim->addFunction(func);

    LightObject obj(10);
    obj.pos = 0;

    obj.addAnimation(anim);

    for(int i = 0; i < 10; i++){
        obj.update(nullptr);
        ASSERT_EQ(anim->frames, i+1, %d)
        EXPECT_EQ(obj.pos, i*10, %d)
    }
}

TEST(Animations, BaseRelPos){
    auto* anim = new BaseAnimation(10, false, EditableProperties::RELATIVE_POSITION);
    AnimationFunction* func = new LinearTransform(0, 10);
    anim->addFunction(func);

    LightObject obj(10);
    obj.pos = 0;

    obj.addAnimation(anim);

    int exp_pos = 0;
    for(int i = 0; i < 10; i++){
        exp_pos += i;
        obj.update(nullptr);
        ASSERT_EQ(anim->frames, i+1, %d)
        EXPECT_EQ(obj.pos, exp_pos, %d)

    }
}

TEST(Animations, BaseOpacity){
    auto* anim = new BaseAnimation(10, false, EditableProperties::OPACITY);
    AnimationFunction* func = new LinearTransform(0, 100);
    anim->addFunction(func);

    LightObject obj(10);
    obj.opacity = 0;

    obj.addAnimation(anim);

    for(int i = 0; i < 10; i++){
        obj.update(nullptr);
        ASSERT_EQ(anim->frames, i+1, %d)
        EXPECT_EQ(obj.opacity, i*10, %d)
    }
}

TEST(Animations, BaseColorsSingleVarFunctions){
    auto* anim = new BaseAnimation(10, false, EditableProperties::COLORS);
    // one function -> applies hue, saturation and value are 255
    anim->addFunction(new LinearTransform(0, 100));

    // just hue
    auto* obj1 = new LightObject(10);
    obj1->addAnimation(anim);
    for(int i = 0; i < 10; i++){
        obj1->update(nullptr);
        CRGB exp = CHSV(i*10, 255, 255);
        EXPECT_TRUE(obj1->colors.current() == exp)
        EXPECT_TRUE(obj1->colors.first() == exp)
        EXPECT_TRUE(obj1->colors.last() == exp)
    }

    // hue and saturation
    anim->reset();
    anim->addFunction(new LinearTransform(20, 120));
    for(int i = 0; i < 10; i++){
        obj1->update(nullptr);
        CRGB exp = CHSV(i*10, i*10 + 20, 255);
        EXPECT_TRUE(obj1->colors.current() == exp)
        EXPECT_TRUE(obj1->colors.first() == exp)
        EXPECT_TRUE(obj1->colors.last() == exp)
    }

    // hue, saturation, and value
    anim->frames = 0;
    anim->addFunction(new LinearTransform(40, 140));
    for (int i = 0; i < 10; i++){
        obj1->update(nullptr);
        CRGB exp = CHSV(i*10, i*10 + 20, i*10 + 40);
        EXPECT_TRUE(obj1->colors.current() == exp)
        EXPECT_TRUE(obj1->colors.first() == exp)
        EXPECT_TRUE(obj1->colors.last() == exp)
    }
}

TEST(Animations, BaseColorsSingle){
    // test changing just hue
    auto* anim = new BaseAnimation(100, false, EditableProperties::COLORS);
    AnimationFunction* func = new LinearTransform(0, 100);
    anim->addFunction(func);

    LightObject obj(10);
    obj.addAnimation(anim);

    for(int i = 0; i < 100; i++){
        obj.update(nullptr);
        ASSERT_EQ(anim->frames, i+1, %d)
        CRGB exp = CHSV(i, 255, 255);
        EXPECT_TRUE(obj.colors.current() == exp)
        EXPECT_TRUE(obj.colors.first() == exp)
        EXPECT_TRUE(obj.colors.last() == exp)
    }

    // test changing hue, saturation, and value
    anim->reset();
    anim->addFunction(new LinearTransform(0, 100));
    anim->addFunction(new LinearTransform(0, 100));
    anim->addFunction(new LinearTransform(0, 100));

    for(int i = 0; i < 100; i++){
        obj.update(nullptr);
        ASSERT_EQ(anim->frames, i+1, %d)
        CRGB exp = CHSV(i, i, i);
        EXPECT_TRUE(obj.colors.current() == exp)
        EXPECT_TRUE(obj.colors.first() == exp)
        EXPECT_TRUE(obj.colors.last() == exp)
    }
}

TEST(Animations, BaseColorsLengthVarFuncs){

    // hue only
    auto* anim = new BaseAnimation(10, false, EditableProperties::COLORS);
    anim->offset = 17;
    anim->bindToLength = true;
    anim->addFunction(new LinearTransform(0, 100));

    LightObject obj(10);
    obj.addAnimation(anim);

    for(int i = 0; i < 10; i++){
        obj.update(nullptr);
        obj.colors.moveToStart();
        for (int c = 0; c < 10; c++){
            CRGB exp = CHSV(i*10 + c*17, 255, 255);
            EXPECT_TRUE(obj.colors.current() == exp)
            obj.colors.next();
        }
    }

    anim->reset();

    // hue, saturation, and value
    anim->addFunction(new LinearTransform(20, 120));
    anim->addFunction(new LinearTransform(40, 140));
    for(int i = 0; i < 10; i++){
        obj.update(nullptr);
        obj.colors.moveToStart();
        for (int c = 0; c < 10; c++){
            CRGB exp = CHSV(i*10 + c*17, i*10 + 20 + c*17, i*10 + 20 + c*17);
            EXPECT_TRUE(obj.colors.current() == exp)
            obj.colors.next();
        }
    }


}

TEST(Animations, BaseBrightness){
    auto* anim = new BaseAnimation(255, false, EditableProperties::BRIGHTNESS);
    anim->addFunction(new LinearTransform(0, 255));

    auto* colorAnim = new BaseAnimation(-1, false, EditableProperties::COLORS);
    colorAnim->addFunction(new StaticTransform(0));

    LightObject obj(10);
    obj.addAnimation(colorAnim);
    obj.addAnimation(anim);

    for (int i = 0; i < 255; i++){
        obj.update(nullptr);
        CRGB exp = CHSV(0, 255, i);
        EXPECT_TRUE(obj.colors.current() == exp)
    }
}


