#pragma once
#include "vehicle.h"

class Motor : public Vehicle {
public:
    Motor(int num, string nam) : Vehicle(num, nam, true) {
        cout << "Finish building a motor with " << get_num() << " wheels and a " << get_name() << " engine." << endl;
    }
    ~Motor();
    void describe();
    void sell() {
        cout << "A motor is sold!" << endl;
    }
};
