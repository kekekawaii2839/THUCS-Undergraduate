#pragma once

#include "func.h"

class LinearFunc : public Func{
private:
    double _a, _b;
public:
    LinearFunc(double a, double b): _a(a), _b(b) {}
    // Todo
    // 请参照指数函数类(ExpFunc)实现一个一次函数类
    // f(x) = ax + b;
    double getPoint(double point){
        return _a * point + _b;
    }
    ~LinearFunc() {}
};