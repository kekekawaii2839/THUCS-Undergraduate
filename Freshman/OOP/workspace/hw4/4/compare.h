#pragma once

#include "abstract_compare.h"
#include "point.h"

AbstractCompare<int>* get_compare_int(int type);
AbstractCompare<Point>* get_compare_point(int type);

bool operator < (const Point &a, const Point &b);

class OneCompare : public AbstractCompare<int> {
public:
    bool compare(int a, int b) override {
        return a < b;
    }
};

class TwoCompare : public AbstractCompare<int> {
public:
    bool compare(int a, int b) override {
        int t1 = 0, t2 = 0;
        int a1 = a, b1 = b;
        while (a1) {
            t1 += a1 % 10;
            a1 /= 10;
        }
        while (b1) {
            t2 += b1 % 10;
            b1 /= 10;
        }
        if(t1 == t2) {
            return a < b;
        }
        return t1 < t2;
    }
};

class ThreeCompare : public AbstractCompare<Point> {
public:
    bool compare(Point a, Point b) override {
        return a < b;
    }
};

class FourCompare : public AbstractCompare<Point> {
public:
    bool compare(Point a, Point b) override {
        float t1 = a.x * a.x + a.y * a.y;
        float t2 = b.x * b.x + b.y * b.y;
        if(t1 == t2) {
            return a < b;
        }
        return t1 < t2;
    }
};