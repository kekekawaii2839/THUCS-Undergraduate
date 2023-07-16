#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Line
{
private:
    T k, b;
public:
    Line(T k, T b): k(k), b(b) {}
    Line(T k): k(k), b(0) {}
    T get_k() const { return k; }
    T get_b() const { return b; }
    bool operator< (const Line& other){
        return this->k < other.k;
    }
    bool intersect(const Line& other) {
        if(k != other.k) return true;
        if(b == other.b) return true;
        return false;
    }
    void show() {
        cout << k << "," << b << endl;
    }
};