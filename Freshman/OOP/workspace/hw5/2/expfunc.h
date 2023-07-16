#pragma once

#include "func.h"

class ExpFunc : public Func{
private:
    double _base;
public:
    ExpFunc(double base) : _base(base) {}
    double getPoint(double point){
        return powl(_base, point);
    }
};