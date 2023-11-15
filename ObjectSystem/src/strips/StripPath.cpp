//
// Created by Ethan Horowitz on 11/13/23.
//

#include "StripPath.h"
#include <Arduino.h>

StripPath::StripPath(int segments, int *path) {
    this->segments = segments;
    this->path = path;
    length = 0;
    for (int i = 0; i < segments; i++){
        length += abs(path[i * 2] - path[i * 2 + 1]);
    }
}

int StripPath::get(int index, bool loop) {
    if (loop) {
        index %= length;
        if (index < 0) index += length;
    }
    if (index < 0 || index >= length) return -1;

    for (int i = 0; i < segments * 2; i+=2) {
        int dist = abs(path[i] - path[i+1]);
        if (dist <= index){
            index -= dist;
            continue;
        }
        if (path[i] < path[i+1]) return path[i] + index;
        else return path[i] - index;
    }
    return path[segments - 1];
}