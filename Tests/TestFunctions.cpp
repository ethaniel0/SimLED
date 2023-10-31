//
// Created by Ethan Horowitz on 10/24/23.
//

#include "TestFunctions.h"
#include <stdio.h>

void runTest(char* name, void (*test)()){
    printf("  Running test %s: ", name);
    try{
        test();
        printf("✓\n");
    } catch (const char* msg){
        printf("✗\n");
        printf("    %s\n", msg);
        return;
    }
    test();
}