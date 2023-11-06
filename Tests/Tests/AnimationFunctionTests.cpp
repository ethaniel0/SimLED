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

TEST(AnimationFunctions, Linear){
    LinearTransform linear(0, 100);
    ASSERT_EQ(linear.getValue(0, 100), 0, %d)
    ASSERT_EQ(linear.getValue(25, 100), 25, %d)
    ASSERT_EQ(linear.getValue(50, 100), 50, %d)
    ASSERT_EQ(linear.getValue(75, 100), 75, %d)
    ASSERT_EQ(linear.getValue(100, 100), 100, %d)
}

TEST(AnimationFunctions, Static){
    StaticTransform staticTransform(100);
    ASSERT_EQ(staticTransform.getValue(0, 100), 100, %d)
    ASSERT_EQ(staticTransform.getValue(50, 100), 100, %d)
    ASSERT_EQ(staticTransform.getValue(100, 100), 100, %d)
}