#include <iostream>
using namespace std;

class Animal {
public:
    void move(){cout << "Animal::move()" << endl;} // (1)
    void move(int i){cout << "Animal::move(" << i << ")" << endl;} // (2)
    void move(double i){cout << "Animal::move(" << i << ")" << endl;} // (3)
};
 
class Rabbit : public Animal {
    void move(){cout << "Rabbit::move()" << endl;} // (4)
public:
    void move(int i){cout << "Rabbit::move(" << i << ")" << endl;} // (5)
    using Animal::move;
};

int main(){
    Rabbit r;
    r.move(1);
    Animal &a = r;
    a.move(1);
    return 0;
}
