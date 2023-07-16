#pragma once
#include <iostream>
#include "Line.h"

using namespace std;

template<typename T>
class Point
{
private:
    T x, y;
public:
    Point(T x, T y): x(x), y(y) {}
    void move(T dx, T dy) {
        x += dx;
        y += dy;
    }
    void show() {
        cout << "(" << x << "," << y << ")" << endl;
    }
    bool check(Line<T> const& l){
        return (l.get_k() * x + l.get_b()) == y;
    }
};