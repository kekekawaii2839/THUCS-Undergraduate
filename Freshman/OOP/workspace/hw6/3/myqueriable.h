#pragma once
#include <vector>

template<typename T>
class MyQueriable{
private:
    std::vector<T> _arr;
public:
    MyQueriable(std::vector<T> arr): _arr(arr) {}
    T& operator[](int index) { return _arr[index]; }
    int size() { return _arr.size(); }

    template<typename FUNC>
    MyQueriable where(FUNC f) {
        std::vector<T> res;
        for(int i = 0; i < _arr.size(); i++) {
            if(f(_arr[i])) {
                res.push_back(_arr[i]);
            }
        }
        return MyQueriable(res);
    }

    template<typename FUNC>
    MyQueriable apply(FUNC f) {
        std::vector<T> res;
        for(int i = 0; i < _arr.size(); i++) {
            res.push_back(f(_arr[i]));
        }
        return MyQueriable(res);
    }

    T sum() {
        T res(0);
        for(int i = 0; i < _arr.size(); i++) {
            res += _arr[i];
        }
        return res;
    }
};

template<typename T>
MyQueriable<T> from(std::vector<T> arr) {
    return MyQueriable<T>(arr);
}