#include <iostream>
using namespace std;

class Identity {
    int number = 1;
    int type = 0;
public:
    Identity(){cout << "Identity::Identity()" << endl;}
    Identity(int _t):type(_t){cout << "Identity::Identity(" << type << ")" << endl;}
    Identity(const Identity &other) {
        number = other.number + 1;
        type = other.type;
    }
    int getNumber() const {return number;}
    int getType() const {return type;}
};

class Appearance {
    double weight = 0;
public:
    Appearance(){cout << "Appearance::Appearance()" << endl;}
    Appearance(double _w):weight(_w){cout << "Appearance::Appearance(" << weight << ")" << endl;}
};

class Animal {
    Identity I;
    Appearance A;
public:
    Animal(int _t, double _w){
        I = Identity(_t);
        A = Appearance(_w);
    }
    int getNumber() const {return I.getNumber();}
    int getType() const {return I.getType();}
};

int main(){
    Animal a1(2, 7.5);
    cout<<a1.getNumber()<<endl;
    Animal a2(a1);
    cout<<a2.getNumber()<<endl;
    cout<<a2.getType()<<endl;
    return 0;
}
