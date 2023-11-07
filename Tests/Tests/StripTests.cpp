//
// Created by Ethan Horowitz on 11/6/23.
//
#include <src/strips/LightStrip.h>
#include "StripTests.h"

void STests(){
    RUN_TEST_GROUP("Strip");
}

TEST(Strip, AddStrip){
    LightStrip strip;
    strip.addStrip(10);
    EXPECT_EQ(strip.size(), 10, %d)
    strip.addStrip(20);
    EXPECT_EQ(strip.size(), 30, %d)

    EXPECT_EQ(strip.getSegment(0), strip.getSegment(0), %p)
    EXPECT_NE(strip.getSegment(0), strip.getSegment(1), %p)

    EXPECT_TRUE(strip.getSegment(0)[0] == CRGB::Black)
    EXPECT_TRUE(strip.getSegment(0)[9] == CRGB::Black)
    EXPECT_TRUE(strip.getSegment(1)[0] == CRGB::Black)
    EXPECT_TRUE(strip.getSegment(1)[19] == CRGB::Black)
}

TEST(Strip, SetAndClear) {
    LightStrip strip;
    strip.addStrip(10);
    ASSERT_EQ(strip.size(), 10, %d);
    for (int i = 0; i < 10; i++) {
        strip.set(i, CRGB(i*20, i*10, i), 255);
    }
    CRGB* arr = strip.getSegment(0);
    for (int i = 0; i < 10; i++) {
        ASSERT_TRUE(strip.get(i) == CRGB(i*20, i*10, i))
        ASSERT_TRUE(arr[i] == CRGB(i*20, i*10, i))
    }

    strip.addStrip(10);
    for (int i = 0; i < 10; i++) {
        strip.set(i+10, CRGB(i, i*10, i*20), 255);
    }
    CRGB* arr2 = strip.getSegment(1);
    for (int i = 0; i < 10; i++) {
        CRGB c = strip.get(i+10);
        ASSERT_TRUE(strip.get(i+10) == CRGB(i, i*10, i*20))
        ASSERT_TRUE(arr[i] == CRGB(i, i*10, i*20))
    }

    strip.clear();
    for (int i = 0; i < 20; i++){
        ASSERT_TRUE(strip.get(i) == CRGB::Black)
        if (i < 10){
            ASSERT_TRUE(arr[i] == CRGB::Black)
        }
        else {
            ASSERT_TRUE(arr2[i-10] == CRGB::Black)
        }
    }
}

TEST(Strip, SetOpacity){
    LightStrip strip;
    strip.addStrip(10);
    strip.set(0, CRGB(255, 0, 0), 128);
    ASSERT_TRUE(strip.get(0) == CRGB(128, 0, 0))

    strip.set(0, CRGB(255, 255, 255), 230);
    ASSERT_TRUE(strip.get(0) == CRGB(230, 230, 230))
}

