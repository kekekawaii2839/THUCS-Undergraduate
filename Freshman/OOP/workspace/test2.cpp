#include <iostream>

using namespace std;

class base{
public:
    base(){
        cout << "base" << endl;
    }
    ~base(){
        cout << "~base" << endl;
    }
};

class member{
public:
    member(){
        cout << "member" << endl;
    }
    ~member(){
        cout << "~member" << endl;
    }
};

class derived: public base{
    member m;
public:
    derived(){
        cout << "derived" << endl;
    }
    ~derived(){
        cout << "~derived" << endl;
    }
};

int main(){
    derived d;
    int a = 0;
    int &&x = 1;
    cout << x << endl;
    x = a;
    cout << x << endl;
    a = 1;
    cout << x << a << endl;
    return 0;
}