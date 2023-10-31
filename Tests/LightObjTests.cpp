//
// Created by Ethan Horowitz on 10/20/23.
//
#include <assert.h>
#include <stdio.h>
#include "src/ObjectSystem.h"
#include "TestFunctions.h"

void lightObjectCreation(){
    LightObject obj(30);
    assert(obj.colors.size() == 30);

    LightObject obj2(new CRGB[]{
        CRGB(255, 0, 0),
        CRGB(0, 255, 0),
        CRGB(0, 0, 255),
        CRGB(142, 213, 23),
        CRGB(42, 0, 69)}, 5);

    assert(obj2.colors.size() == 5);
    assert(obj2.colors[0] == CRGB(255, 0, 0));
    assert(obj2.colors[1] == CRGB(0, 255, 0));
    assert(obj2.colors[2] == CRGB(0, 0, 255));
    assert(obj2.colors[3] == CRGB(142, 213, 23));
    assert(obj2.colors[4] == CRGB(42, 0, 69));
}

void applyToStrip(){
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

void LOTests(){
    printf("LightObjectTests:\n");
    runTest("lightObjectCreation", lightObjectCreation);
    runTest("applyToStrip", applyToStrip);
}
