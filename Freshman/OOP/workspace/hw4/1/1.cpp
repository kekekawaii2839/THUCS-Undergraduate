#include <iostream>
using namespace std;

class Instrument{
public:
    int price;
    void tune() { cout << "Instrument::tune()" << endl; }
    virtual void play() { cout << "Instrument::play()" << endl; }
};

class Violin : public Instrument{
public:
    void tune() { cout << "Violin::tune()" << endl; } // (1)
};

void tune(Instrument* p){
    p->tune();
}

int main(){
    Violin obj;
    tune(&obj); // (2)
    return 0;
}
