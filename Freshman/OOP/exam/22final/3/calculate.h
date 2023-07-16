#pragma once
#include <iostream>

template <typename T>
class calculate
{
private:
    char expressionType;
    T x, y, z;
public:
    calculate(char expressionType, int x, int y, int z): expressionType(expressionType), x(x), y(y), z(z){}
    ~calculate() {}
    T operator() () {
        if (expressionType == 'A'){
            return (x*x)+(y*y)+(z*z);
        }
        else if (expressionType == 'B'){
            return (x*y)+(y/z)-(x*z);
        }
        else if (expressionType == 'C'){
            return (y*3*z)-(x*z/(y-2))-(x*y/(z+1));
        }
        else return 0;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, calculate<T> c){
    os << c();
    return os;
}