//
// Created by Ethan Horowitz on 10/20/23.
//

#ifndef SIMLED_BUTTON_H
#define SIMLED_BUTTON_H


class Button {
public:
    char* text;
    void (*action)(); // void action()
    int x;
    int y;
    int width;
    int height;
    int fontsize;

    Button();
    Button(char* text);
    Button(char* text, int x, int y, int width, int height, int fontsize=12);
    void draw() const;
};


#endif //SIMLED_BUTTON_H
