//
// Created by Ethan Horowitz on 10/20/23.
//

#include "Button.h"
#include <xd/xd.hpp>
#include "GraphicsUtils.h"


Button::Button() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    fontsize = 0;
    text = nullptr;
    action = nullptr;
}

Button::Button(char *innerText) {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    fontsize = 0;
    text = innerText;
    action = nullptr;
}

Button::Button(char *innerText, int b_x, int b_y, int b_width, int b_height, int b_fontsize) {
    x = b_x;
    y = b_y;
    width = b_width;
    height = b_height;
    fontsize = b_fontsize;
    text = innerText;
    action = nullptr;
}

void Button::draw() const {
    xd::rect((float)x, (float)y, (float)width, (float)height);
    xd::stroke(color(0, 0, 0));
    if (text != nullptr){
        xd::textSize((float)fontsize);
        xd::text(text, (float)(x + width/2.), (float)(y + height/2.) + (float)fontsize/3.f);
    }
    if (action != nullptr){
        struct Point mouse = mousePos();
        if (mouse.x >= x && mouse.x <= x + width && mouse.y >= y && mouse.y <= y + height && mouseIsPressed()) {
            action();
        }
    }
}
