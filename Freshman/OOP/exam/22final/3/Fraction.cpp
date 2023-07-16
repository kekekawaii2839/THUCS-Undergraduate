#include "Fraction.h"

std::ostream& operator<<(std::ostream& os, const Fraction& c){
    if(c.denominator == 1){
        os << c.numerator;
    }
    else{
        os << c.numerator << "/" << c.denominator;
    }
    return os;
}