#pragma once
#include <iostream>
#include "Animal.h"

class Bird : public Animal {
public:
    Bird(int color) : Animal(color) {}
    ~Bird() {
        std::string c;
        if(m_color == 0) c = "Red";
        else if(m_color == 1) c = "Blue";
        std::cout << c << " bird is gone." << std::endl;
    }
    void sing() {
        std::string c;
        if(m_color == 0) c = "Red";
        else if(m_color == 1) c = "Blue";
        std::cout << c << " bird is singing." << std::endl;
    }
    void swim() {
        std::cout << "Bird can not swim." << std::endl;
    }
};