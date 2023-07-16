#pragma once

class Animal{
protected:
    int m_color;
public:
    Animal(int color) : m_color(color) {}
    virtual ~Animal() {}
    virtual void sing() = 0;
    virtual void swim() = 0;
};