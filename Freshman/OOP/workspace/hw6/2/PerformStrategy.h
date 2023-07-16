#pragma once

class PerformStrategy
{
private:
    double _gpa;
public:
    PerformStrategy(double gpa): _gpa(gpa) {}
    double get_gpa() {
        return _gpa;
    }
    virtual double get_bonus(int) = 0;
};

class sPerformStrategy: public PerformStrategy{
public:
    sPerformStrategy(double gpa): PerformStrategy(gpa) {}
    double get_bonus(int) {
        return 1000;
    }
};

class mPerformStrategy: public PerformStrategy{
public:
    mPerformStrategy(double gpa): PerformStrategy(gpa) {}
    double get_bonus(int base) {
        return get_gpa() * base;
    }
};

class lPerformStrategy: public PerformStrategy{
public:
    lPerformStrategy(double gpa): PerformStrategy(gpa) {}
    double get_bonus(int base) {
        return 2 * get_gpa() * base;
    }
};