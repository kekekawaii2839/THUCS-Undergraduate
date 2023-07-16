#pragma once
#include <vector>
#include <functional>

template<typename T>
class Compare {
    std::vector<std::function<bool(T, T)>> comp;
public:
    Compare(const std::initializer_list<std::function<bool(T, T)>> &il) {
        for (auto f : il) {
            comp.push_back(f);
        }
    }
    Compare(const std::vector<std::function<bool(T, T)>> &v) {
        for (auto f : v) {
            comp.push_back(f);
        }
    }
    bool operator()(T l, T r) {
        for (auto f : comp) {
            if (f(l, r)) return true;
            else if (f(r, l)) return false;
        }
        return false;
    }
};