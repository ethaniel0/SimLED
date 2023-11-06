//
// Created by Ethan Horowitz on 11/5/23.
//
#include "TestFramework.h"
#include <vector>
#include <map>
#include <string>

typedef struct Test{
    void (*test)();
    const char* name;
} Test;

std::map<std::string, std::vector<Test>*>* testGroups;
bool errorFlag = false;

void __addTest(void (*test)(), const char* group, const char* name){
    if (!testGroups){
        testGroups = new std::map<std::string, std::vector<Test>*>();
    }
    if(testGroups->find(group) == testGroups->end()){
        auto* tests = new std::vector<Test>();
        std::string s(group);
        (*testGroups)[s] = tests;
    }
    (*testGroups)[group]->push_back({test, name});

}


void __setErrorFlag(){
    errorFlag = true;
}

void RUN_TESTS(){
    for(auto& group : *testGroups){
        printf("Running tests in group %s\n", group.first.c_str());
        for(auto& test : *group.second){
            errorFlag = false;
            test.test();
            if (errorFlag)
                printf("\tx  ");
            else
                printf("\t✓  ");
            printf("%s\n", test.name);

        }
    }
}

void RUN_TEST_GROUP(std::string group){
    for(auto& test : *((*testGroups)[group])){
        errorFlag = false;
        test.test();
        if (errorFlag)
            printf("\tx  ");
        else
            printf("\t✓  ");
        printf("%s\n", test.name);

    }
}

__TFTest::__TFTest(void (*test)(), const char* group, const char* name){
    __addTest(test, group, name);
}