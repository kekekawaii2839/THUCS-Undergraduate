#pragma once

#include "func.h"

class CompFunc : public Func{
private:
    // Todo
    // 声明成员变量
    Func* f, *g;
public:
    CompFunc(Func *outer, Func* inner): f(outer), g(inner) {}
    // compute f(g(x))
    // Todo
    // 请参照指数函数类(ExpFunc)实现一个复合函数类
    // 并且要求，传入的参数的析构在该类被析构时同时析构
    double getPoint(double point){
        return f->getPoint(g->getPoint(point));
    }
    ~CompFunc() {
        delete f;
        delete g;
    }
};