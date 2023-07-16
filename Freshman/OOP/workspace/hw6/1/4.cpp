#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

void func1(int n) {
    cout << "func1" << " " << n;
}


class func2 {
public: 
    void operator()(int n) const {	// (6)
        cout << "func2" << " " << n;
    }
};

template<class T>
void func3(int n, T f) { 
    f(n);
}

int main() {
    void (*F1) (int);   // (1)
    F1 = func1;         // (2)
    auto F2 = func2();  // (3)
    F2(4);              // (4)
    func3(5, F2);       // (5)
    
    return 0;
}
