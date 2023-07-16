#include <iostream>
using namespace std;

class Test{
public:
    int data;
    Test(int d):data(d){}
};

Test operator +(const Test& a, const int& b){
    return Test(a.data + b);
}

Test operator +(const int& b, const Test& a){
    return Test(- a.data - b);
}

int main(){
Test obj(1);
int data = 2;
cout << (obj + data).data << endl;
cout << (data + obj).data << endl;
return 0;
}
