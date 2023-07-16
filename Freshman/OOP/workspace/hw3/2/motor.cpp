#include "motor.h"

Motor::~Motor()
{
}

void Motor::describe() {
    cout << "A motor with " << get_num() << " wheels and a " << get_name() << " engine." << endl;
}