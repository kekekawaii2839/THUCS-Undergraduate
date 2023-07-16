#pragma once
#include <iostream>
#include "Animal.h"

class Fish : public Animal {
public:
    Fish(int color) : Animal(color) {}
    ~Fish() {
        std::string c;
        if(m_color == 0) c = "Red";
        else if(m_color == 1) c = "Blue";
        std::cout << c << " fish is gone." << std::endl;
    }
    void sing() {
        std::cout << "Fish can not sing." << std::endl;
    }
    void swim() {
        std::string c;
        if(m_color == 0) c = "Red";
        else if(m_color == 1) c = "Blue";
        std::cout << c << " fish is swimming." << std::endl;
    }
};