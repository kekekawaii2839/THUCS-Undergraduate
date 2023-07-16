#include <iostream>

using namespace std;

class Instrument{
public:
    void play() { cout << "Instrument::play()" << endl; }
    virtual void tune() { cout << "Instrument::tune()" << endl; }
    virtual void tune(string component) { cout << "Instrument::tune(string)" << endl; }
};

class StringInstrument : public Instrument{
public:
    void play() { cout << "StringInstrument::play()" << endl; }
    void tune(string component) { cout << "StringInstrument::tune(string)" << endl; }
};

class Violin : public StringInstrument{
public:
    void tune() { cout << "Violin::tune()" << endl; }
};

int main(){
    StringInstrument * obj = new Violin();
    //obj->tune();
    return 0;
}