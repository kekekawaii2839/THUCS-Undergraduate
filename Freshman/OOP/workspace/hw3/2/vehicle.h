#pragma once
#include "wheel.h"
#include "engine.h"

class Vehicle {
    Engine engine;
    Wheel wheels;
public:
    Vehicle(int, string);
    Vehicle(int num, string name, bool f): engine(name), wheels(num){};
    int get_num() {
        return wheels.get_num();
    }
    string get_name() {
        return engine.get_name();
    }
    void describe();
};