#pragma once
#include <iostream>

using namespace std;

class Vehicle{
    int wheel_num, wing_num;
    int max_wheel_num, max_wing_num;
public:
    Vehicle() : wheel_num(0), wing_num(0), max_wheel_num(0), max_wing_num(0) {}
    void set_max_wheel_num(int n) { max_wheel_num = n; }
    void set_max_wing_num(int n) { max_wing_num = n; }
    void add_wheel() { wheel_num++; }
    void add_wing() { wing_num++; }
    bool finished() { return wheel_num >= max_wheel_num && wing_num >= max_wing_num; }
    void run() {
        if(max_wing_num == 0) cout << "I am running" << endl;
        else cout << "I am running and flying" << endl;
    }
};