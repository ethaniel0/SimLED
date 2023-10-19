//
// Created by Ethan Horowitz on 10/19/23.
//

#include "StripElement.h"
#include <cmath>


StripElement::StripElement(CRGB* leds, int length) {
    this->leds = leds;
    this->length = length;
    this->x = 0;
    this->y = 0;
    this->angle = M_PI;
    this->ledSize = 10;
    this->ledSpacing = 15;
}

void StripElement::setParameters(int x, int y, double angle, int ledSize, int ledSpacing) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->ledSize = ledSize;
    this->ledSpacing = ledSpacing;
}

void StripElement::draw(){
    double x_step = cos(this->angle) * this->ledSpacing;
    double y_step = sin(this->angle) * this->ledSpacing;
    for (int i = 0; i < this->length; i++) {
        int lx = (int)(this->x + i * x_step);
        int ly = (int)(this->y + i * y_step);

        xd::stroke(color(255, 255, 255));
        xd::fill(color(leds[i].r, leds[i].g, leds[i].b));
        xd::ellipse((float)lx, (float)ly, (float)this->ledSize, (float)this->ledSize);
//        printf("     led %d color: (%d, %d, %d)\n", i, leds[i].r, leds[i].g, leds[i].b);
    }
}