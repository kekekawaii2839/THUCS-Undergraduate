#include <iostream>

using namespace std;

class haha
{
public:
    static int count;
    haha() { count++; }
    ~haha() { count--; }
};

int haha::count = 0;

class Animal{
public:
    haha* a;
    Animal() {}
};

int main(){
    Animal* animal = new Animal();
    animal->a = new haha[10];
    cout << haha::count << endl;
    delete animal;
    cout << haha::count << endl;
    return 0;
}