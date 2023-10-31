//
// Created by Ethan Horowitz on 10/30/23.
//
#include <random>
#include <chrono>
#include <thread>

// now
auto arduino_start_millis = std::chrono::system_clock::now();

unsigned long millis(void){
    auto now = std::chrono::system_clock::now();
    auto duration = now - arduino_start_millis;
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
unsigned long micros(void){
    auto now = std::chrono::system_clock::now();
    auto duration = now - arduino_start_millis;
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}
void delay(unsigned long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void delayMicroseconds(unsigned int us){
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}


void yield(){
    std::this_thread::yield();
}

void randomSeed(unsigned long seed)
{
    if (seed != 0) {
        srandom(seed);
    }
}

long random(long howbig)
{
    if (howbig == 0) {
        return 0;
    }
    return random() % howbig;
}

long random(long howsmall, long howbig)
{
    if (howsmall >= howbig) {
        return howsmall;
    }
    long diff = howbig - howsmall;
    return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned int makeWord(unsigned int w) { return w; }
unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }