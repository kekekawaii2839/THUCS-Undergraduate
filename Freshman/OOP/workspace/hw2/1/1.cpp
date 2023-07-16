#include <iostream>

class Test {
public:
    int data = -1;
    Test() = default; // (A)
    Test(int dat){ // (B)
        this->data = dat; // (C)
    }
    ~Test(){ // (D)
        std::cout<<data;
    }
};

int main() {
    Test* t = new Test();
    delete t;
    return 0;
}
