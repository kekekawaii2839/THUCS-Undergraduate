#include <iostream>
using namespace std;

class A {
public:
    const char* s;
    A(const char* str) : s(str) { }
    ~A() { }
};

class B {
public:
    static A a1;
    const A a2;
    B(const char* str) : a2(str) { }
    ~B() {  }
};

void foo() {
    static A obj("static obj");
}

A B::a1("static B::a1");  // (1)

int main() {
    // (2)
    cout << "main starts" << endl;
    static B b("static b");
    for (int i = 0; i < 4; i++) {
        foo();
    }
    cout << B::a1.s << endl; // (3)
    cout << "main ends" << endl;
    return 0; // (4)
}
