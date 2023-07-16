#include <iostream>

using namespace std;

class Instrument{
public:
    void play() { cout << "Instrument::play()" << endl; }
};

class StringInstrument : public Instrument{
public:
    void play() { cout << "StringInstrument::play()" << endl; }
    virtual void tune(string component) { cout << "StringInstrument::tune(string)" << endl; }
};

class Violin{
public:
    void tune() { cout << "Violin::tune()" << endl; }
};


int main(){
    Instrument * p = new StringInstrument();
    StringInstrument* a = dynamic_cast<StringInstrument*>(p);
    return 0;
}