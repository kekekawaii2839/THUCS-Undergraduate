 #include<iostream>
 using namespace std;

 class Base {
 public:
     virtual void f1(float x) {
         cout << "Base::f1 " << x << endl;
     }
     void f2(float x) {
         cout << "Base::f2 " << x << endl;
     }
 };

 class Derived : public Base {
 public:
     virtual void f1(float x) {
         cout << "Derived::f1 " << x << endl;
     }
     void f2(int x) {									// (1)
         cout << "Derived::f2 " << x << endl;
     }
 };

 int main(void) {
     Base x;
     Derived y;        
     Base* pb1 = &x; 
     Base* pb2 = &y;
     Derived* pd = &y; 

     pd->f2(3.14f);			// (2)

     return 0;
 }
