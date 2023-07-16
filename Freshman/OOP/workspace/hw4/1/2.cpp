#include <iostream>
using namespace std;

class Base{
public:
    virtual void func() { cout << "Base::func" << endl; }
    virtual ~Base() {
        func(); // (*)
    }
};
class Derived: public Base{
public:
    virtual void func() { cout << "Derived::func" << endl; }
    virtual ~Derived() { func(); }
};

int main(){
    Base * p = new Derived();
    delete p;
    return 0;
}
