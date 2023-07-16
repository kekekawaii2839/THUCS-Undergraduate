#include "car.h"

Car::~Car()
{
}

void Car::describe() {
    cout << "A car with " << get_num() << " wheels and a " << get_name() << " engine." << endl;
}