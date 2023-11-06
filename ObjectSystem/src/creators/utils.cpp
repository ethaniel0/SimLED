//
// Created by Ethan Horowitz on 11/1/23.
//

#include "utils.h"

void incPtr(int* pos){
    *pos = (*pos) + 1;
}

void skipWhitespace(const char* string, int* pos){
    while(string[*pos] != 0 && string[*pos] == ' ' || string[*pos] == '\t' || string[*pos] == '\n'){
        incPtr(pos);
    }
}

int extractNumber(const char* string, int* pos){
    skipWhitespace(string, pos);
    int num = 0;
    while(string[*pos] >= '0' && string[*pos] <= '9'){
        num *= 10;
        num += string[*pos] - '0';
        incPtr(pos);
    }
    return num;
}

int extractHex(const char* string, int* pos, int digits){
    skipWhitespace(string, pos);
    int num = 0;
    for (int i = 0; i < digits; i++){
        num *= 16;
        if (string[*pos] >= '0' && string[*pos] <= '9'){
            num += string[*pos] - '0';
        } else if (string[*pos] >= 'a' && string[*pos] <= 'f'){
            num += string[*pos] - 'a' + 10;
        } else if (string[*pos] >= 'A' && string[*pos] <= 'F'){
            num += string[*pos] - 'A' + 10;
        }
        incPtr(pos);
    }
    return num;
}

CRGB extractColor(const char* string, int* pos){
    // extracts color from hex
    skipWhitespace(string, pos);
    int color = extractHex(string, pos, 6);
    return CRGB(color);
}