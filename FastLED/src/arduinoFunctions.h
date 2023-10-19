//
// Created by Ethan Horowitz on 10/17/23.
//
#include <chrono>
#include <thread>

#ifndef SIMLED_ARDUINOFUNCTIONS_H
#define SIMLED_ARDUINOFUNCTIONS_H


void delay(int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// now
auto arduino_start_millis = std::chrono::system_clock::now();

long long millis(){
    auto now = std::chrono::system_clock::now();
    auto duration = now - arduino_start_millis;
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

long long micros(){
    auto now = std::chrono::system_clock::now();
    auto duration = now - arduino_start_millis;
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

void yield(){
    std::this_thread::yield();
}

#endif //SIMLED_ARDUINOFUNCTIONS_H
