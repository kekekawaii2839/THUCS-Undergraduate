#pragma once
#include <iostream>
#include <vector>

class Rack{
    std::vector<int> data;
public:
    Rack(){}
    ~Rack(){}

    Rack& operator += (const int&);
    Rack& operator += (const Rack);

    Rack operator , (const Rack&);
    Rack operator , (const int&);
    friend Rack operator , (const int&, const Rack&);

    bool operator == (const Rack&);
    bool operator < (const Rack&);
    bool operator > (const Rack&);
    Rack operator & (const Rack&);

    int operator () (const int&);
    Rack& operator ~ ();
    Rack& operator -- ();
    Rack& operator -- (int);

    friend std::ostream& operator << (std::ostream&, const Rack&);
};