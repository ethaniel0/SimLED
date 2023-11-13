//
// Created by Ethan Horowitz on 11/6/23.
//
#include "AnimationTests.h"
#include <src/animations/BaseAnimation.h>
#include <src/animations/AnimationFunctions.h>
#include <src/animations/AnimationGroups.h>

void AnimationTests(){
    RUN_TEST_GROUP("Animations");
}

 /*  BaseAnimation Tests */
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

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
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

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
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

    EXPECT_EQ(obj.pos, 0, %d)
    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
}

TEST(Animations, BaseColorsSingleVarFunctions){
    auto* anim = new BaseAnimation(10, false, EditableProperties::COLORS);
    // one function -> applies hue, saturation and value are 255
    anim->addFunction(new LinearTransform(0, 100));

    // just hue
    LightObject obj(10);
    obj.addAnimation(anim);
    for(int i = 0; i < 10; i++){
        obj.update(nullptr);
        CRGB exp = CHSV(i*10, 255, 255);
        EXPECT_TRUE(obj.colors.current() == exp)
        EXPECT_TRUE(obj.colors.first() == exp)
        EXPECT_TRUE(obj.colors.last() == exp)
    }

    // hue and saturation
    anim->reset();
    anim->addFunction(new LinearTransform(20, 120));
    for(int i = 0; i < 10; i++){
        obj.update(nullptr);
        CRGB exp = CHSV(i*10, i*10 + 20, 255);
        EXPECT_TRUE(obj.colors.current() == exp)
        EXPECT_TRUE(obj.colors.first() == exp)
        EXPECT_TRUE(obj.colors.last() == exp)
    }

    // hue, saturation, and value
    anim->frames = 0;
    anim->addFunction(new LinearTransform(40, 140));
    for (int i = 0; i < 10; i++){
        obj.update(nullptr);
        CRGB exp = CHSV(i*10, i*10 + 20, i*10 + 40);
        EXPECT_TRUE(obj.colors.current() == exp)
        EXPECT_TRUE(obj.colors.first() == exp)
        EXPECT_TRUE(obj.colors.last() == exp)
    }

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
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

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
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

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
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

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
}

TEST(Animations, BaseSetState){
    auto* anim = new BaseAnimation(10, false, EditableProperties::POSITION);
    auto* func = new LinearTransform(0, 100);
    anim->addFunction(func);
    // two absolute state triggers
    anim->addAbsoluteStateTrigger(0, 2);
    anim->addAbsoluteStateTrigger(1, 0);
    // one relative state trigger
    anim->addRelativeStateTrigger(2, 3);

    LightObject obj(10);
    obj.pos = 0;
    obj.addAnimation(anim);

    for(int i = 0; i <= 5; i++){
        obj.update(nullptr);
    }

    EXPECT_EQ(obj.pos, 50, %d)

    // make sure unset triggers don't do anything
    obj.setState(9);
    EXPECT_EQ(obj.pos, 50, %d)

    // test 1st absolute state trigger (bring to frame 2)
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_EQ(obj.pos, 20, %d)

    // test 2nd absolute state trigger (bring to frame 0)
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_EQ(obj.pos, 0, %d)

    anim->reset();
    // test relative state trigger (+3 frames)
    obj.setState(2);
    obj.update(nullptr);
    ASSERT_EQ(obj.pos, 30, %d)
    // test relative state trigger again (+3 frames)
    obj.setState(2);
    obj.update(nullptr);
    EXPECT_EQ(obj.pos, 70, %d)

    EXPECT_EQ(obj.colors.getLength(), 10, %d)
    EXPECT_EQ(obj.length, 10, %d)
    EXPECT_FALSE(obj.persistent)
    
    EXPECT_EQ(obj.opacity, 255, %d)
}

TEST(Animations, BaseClone){
    auto* anim = new BaseAnimation(10, true, EditableProperties::POSITION);
    anim->offset = 17;
    anim->frames = 12;
    anim->bindToLength = true;

    AnimationFunction* func = new LinearTransform(0, 100);
    anim->addFunction(func);

    BaseAnimation* anim2 = anim->clone();

    EXPECT_EQ(anim->offset, anim2->offset, %d)
    EXPECT_EQ(anim->loop, anim2->loop, %d)
    EXPECT_EQ(anim2->frames, 0, %d)
    EXPECT_EQ(anim->offset, anim2->offset, %d)
    EXPECT_EQ(anim->duration, anim2->duration, %d)
    EXPECT_EQ(anim->bindToLength, anim2->bindToLength, %b)
}

/* AnimationSequence Tests */

TEST(Animations, SequenceFunctionality){
    auto* stack = new AnimationSequence(false);
    stack->addNextTrigger(0);
    stack->addPrevTrigger(1);

    auto* subAnim1 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim1->addFunction(new StaticTransform(0));

    auto* subAnim2 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim2->addFunction(new StaticTransform(60));

    auto* subAnim3 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim3->addFunction(new StaticTransform(120));

    stack->addAnimation(subAnim1);
    stack->addAnimation(subAnim2);
    stack->addAnimation(subAnim3);

    LightObject obj(1);
    obj.addAnimation(stack);

    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to next state
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))

    // go to next state
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))


    // go to previous state
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))

    // go to previous state
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    EXPECT_EQ(obj.colors.getLength(), 1, %d)
    EXPECT_EQ(obj.length, 1, %d)
}

TEST(Animations, SequenceClone){
    auto* seq = new AnimationSequence(false);
    seq->addNextTrigger(0);
    seq->addPrevTrigger(1);

    auto* subAnim1 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim1->addFunction(new StaticTransform(0));

    auto* subAnim2 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim2->addFunction(new StaticTransform(60));

    auto* subAnim3 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim3->addFunction(new StaticTransform(120));

    seq->addAnimation(subAnim1);
    seq->addAnimation(subAnim2);
    seq->addAnimation(subAnim3);

    AnimationSequence* seq2 = seq->clone();

    delete seq;

    LightObject obj(1);
    obj.addAnimation(seq2);

    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to next state
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))

    // go to next state
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))

    // go to previous state
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))

    // go to previous state
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    EXPECT_EQ(obj.colors.getLength(), 1, %d)
    EXPECT_EQ(obj.length, 1, %d)
}

/* AnimationMap Tests */

TEST(Animations, MapFunctionality){
    auto* map = new AnimationStateMap();

    auto* subAnim1 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim1->addFunction(new StaticTransform(0));

    auto* subAnim2 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim2->addFunction(new StaticTransform(60));

    auto* subAnim3 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim3->addFunction(new StaticTransform(120));

    map->addState(0, subAnim1);
    map->addState(1, subAnim2);
    map->addState(2, subAnim3);

    LightObject obj(1);
    obj.addAnimation(map);

    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to state 0 (animation 0)
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to state 1 (animation 1)
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))

    // go back to state 0
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to state 2
    obj.setState(2);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))

    EXPECT_EQ(obj.colors.getLength(), 1, %d)
    EXPECT_EQ(obj.length, 1, %d)
}

TEST(Animations, MapClone){
    auto* map = new AnimationStateMap();

    auto* subAnim1 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim1->addFunction(new StaticTransform(0));

    auto* subAnim2 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim2->addFunction(new StaticTransform(60));

    auto* subAnim3 = new BaseAnimation(-1, false, EditableProperties::COLORS);
    subAnim3->addFunction(new StaticTransform(120));

    map->addState(0, subAnim1);
    map->addState(1, subAnim2);
    map->addState(2, subAnim3);

    AnimationStateMap* map2 = map->clone();

    delete map;

    LightObject obj(1);
    obj.addAnimation(map2);

    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to state 0 (animation 0)
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to state 1 (animation 1)
    obj.setState(1);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(60, 255, 255))

    // go back to state 0
    obj.setState(0);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(0, 255, 255))

    // go to state 2
    obj.setState(2);
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))
    obj.update(nullptr);
    EXPECT_TRUE(obj.colors.current() == CHSV(120, 255, 255))

    EXPECT_EQ(obj.colors.getLength(), 1, %d)
    EXPECT_EQ(obj.length, 1, %d)
}
