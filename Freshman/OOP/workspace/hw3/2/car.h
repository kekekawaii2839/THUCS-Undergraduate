#pragma once
#include "vehicle.h"

class Car : public Vehicle {
public:
    Car(int num, string nam) : Vehicle(num, nam, true) {
        cout << "Finish building a car with " << get_num() << " wheels and a " << get_name() << " engine." << endl;
    }
    ~Car();
    void describe();
};