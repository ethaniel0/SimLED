//
// Created by Ethan Horowitz on 11/6/23.
//

#include "AnimationFunctionTests.h"
#include <src/animations/AnimationFunctions.h>

void AnimationFunctionTests(){
    RUN_TEST_GROUP("AnimationFunctions");
}

TEST(AnimationFunctions, Ease){
    EaseTransform ease(0, 100);
    ASSERT_EQ(ease.getValue(0, 100), 0, %d)
    ASSERT_EQ(ease.getValue(50, 100), 50, %d)
    ASSERT_EQ(ease.getValue(100, 100), 100, %d)
    // (int)12.5 = 12
    ASSERT_EQ(ease.getValue(25, 100), 12, %d)
    ASSERT_EQ(ease.getValue(75, 100), 87, %d)
}

TEST(AnimationFunctions, EaseClone){
    EaseTransform ease(20, 40);
    EaseTransform* ease2 = ease.clone();

    ASSERT_EQ(ease.start, ease2->start, %d);
    ASSERT_EQ(ease.end, ease2->end, %d);

    ASSERT_EQ(ease.getValue(0, 100), ease2->getValue(0, 100), %d)
    ASSERT_EQ(ease.getValue(25, 100), ease2->getValue(25, 100), %d)
    ASSERT_EQ(ease.getValue(50, 100), ease2->getValue(50, 100), %d)
    ASSERT_EQ(ease.getValue(75, 100), ease2->getValue(75, 100), %d)
    ASSERT_EQ(ease.getValue(100, 100), ease2->getValue(100, 100), %d)
}

TEST(AnimationFunctions, Linear){
    LinearTransform linear(0, 100);
    ASSERT_EQ(linear.getValue(0, 100), 0, %d)
    ASSERT_EQ(linear.getValue(25, 100), 25, %d)
    ASSERT_EQ(linear.getValue(50, 100), 50, %d)
    ASSERT_EQ(linear.getValue(75, 100), 75, %d)
    ASSERT_EQ(linear.getValue(100, 100), 100, %d)
}

TEST(AnimationFunctions, LinearClone){
    LinearTransform linear(20, 40);
    LinearTransform* linear2 = linear.clone();

    ASSERT_EQ(linear.start, linear2->start, %d);
    ASSERT_EQ(linear.end, linear2->end, %d);

    ASSERT_EQ(linear.getValue(0, 100), linear2->getValue(0, 100), %d)
    ASSERT_EQ(linear.getValue(25, 100), linear2->getValue(25, 100), %d)
    ASSERT_EQ(linear.getValue(50, 100), linear2->getValue(50, 100), %d)
    ASSERT_EQ(linear.getValue(75, 100), linear2->getValue(75, 100), %d)
    ASSERT_EQ(linear.getValue(100, 100), linear2->getValue(100, 100), %d)
}

TEST(AnimationFunctions, Static){
    StaticTransform staticTransform(100);
    ASSERT_EQ(staticTransform.getValue(0, 100), 100, %d)
    ASSERT_EQ(staticTransform.getValue(50, 100), 100, %d)
    ASSERT_EQ(staticTransform.getValue(100, 100), 100, %d)
}

TEST(AnimationFunctions, StaticClone){
    StaticTransform staticTransform(100);
    StaticTransform* staticTransform2 = staticTransform.clone();

    ASSERT_EQ(staticTransform.val, staticTransform2->val, %d);

    ASSERT_EQ(staticTransform.getValue(0, 100), staticTransform2->getValue(0, 100), %d)
    ASSERT_EQ(staticTransform.getValue(50, 100), staticTransform2->getValue(50, 100), %d)
    ASSERT_EQ(staticTransform.getValue(100, 100), staticTransform2->getValue(100, 100), %d)
}
