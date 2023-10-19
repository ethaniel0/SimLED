//
// Created by Ethan Horowitz on 10/19/23.
//
#include "GraphicsUtils.h"

glm::vec4 color(int r, int g, int b) {
    return {r/255.0, g/255.0, b/255.0, 1.0};
}

void testCircle(int width, int height){
    int x = width/2;
    int y = height/2;
    int radius = 100;
    xd::fill(color(255, 0, 0));
    xd::ellipse(x, y, x, y);

}