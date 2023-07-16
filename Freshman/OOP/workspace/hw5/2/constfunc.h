#pragma once

#include <iostream>
#include "func.h"

class ConstFunc : public Func{
private:
    static int obj_num;
    double _c;
public:
    ConstFunc(double n) : _c(n) { obj_num++; }
    ~ConstFunc() { obj_num--; }
    double getPoint(double point) { return _c; };
    static void checkMemoryLeak(){
        if(obj_num == 0){
            std::cout << "YES" << std::endl;
        }else{
            std::cout << "NO" << std::endl;
        }
    }
};

int ConstFunc::obj_num = 0;