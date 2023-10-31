//
// Created by Ethan Horowitz on 10/19/23.
//

#ifndef SIMLED_GRAPHICSUTILS_H
#define SIMLED_GRAPHICSUTILS_H

#include <xd/xd.hpp>

struct Point{
    int x;
    int y;
};

struct Point mousePos();

bool mouseIsPressed();

void trackMouse();

glm::vec4 color(int r, int g, int b);

void testCircle(int width, int height);

#endif //SIMLED_GRAPHICSUTILS_H
