#include<iostream>
 using namespace std;

 void f(int& x) {
     x += 1;
 }

 void f(int&& x) {
     int& y = x;             // (1)
     const int& z = y + 1;   // (2)
     f(y);                   // (3)
 }

 int main() {
     int a = 1;
     f(a);       // (4)
     f(1);       // (5)
     cout << a << endl;
     return 0;}
