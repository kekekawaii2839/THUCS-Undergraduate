#include "vehicle.h"

Vehicle::Vehicle(int num, string nam): engine(nam), wheels(num) {
    cout << "Finish building a vehicle with " << wheels.get_num() << " wheels and a " << engine.get_name() << " engine." << endl;
}

void Vehicle::describe() {
    cout << "A vehicle with " << wheels.get_num() << " wheels and a " << engine.get_name() << " engine." << endl;
}