#include "compare.h"

AbstractCompare<int>* get_compare_int(int type) {
    if(type == 1) {
        return new OneCompare();
    }
    if(type == 2) {
        return new TwoCompare();
    }
    return nullptr;
}

AbstractCompare<Point>* get_compare_point(int type) {
    if(type == 3) {
        return new ThreeCompare();
    }
    if(type == 4) {
        return new FourCompare();
    }
    return nullptr;
}

bool operator < (const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}