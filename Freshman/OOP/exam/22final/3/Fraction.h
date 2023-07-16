#pragma once
#include <iostream>

class Fraction
{
private:
    long long numerator, denominator;
public:
    Fraction(): numerator(0), denominator(1){}
    Fraction(int num): numerator(num), denominator(1){}
    long long gcd(long long a, long long b){
        return b ? gcd(b, a % b) : a;
    }
    void simple() {
        long long g = gcd(abs(numerator), abs(denominator));
        numerator /= g;
        denominator /= g;
        if(denominator < 0){
            denominator = -denominator;
            numerator = -numerator;
        }
    }
    Fraction operator+ (const Fraction& f){
        Fraction result;
        result.numerator = numerator * f.denominator + f.numerator * denominator;
        result.denominator = denominator * f.denominator;
        result.simple();
        return result;
    }
    Fraction operator+ (const int& f){
        Fraction result;
        result.numerator = numerator + f * denominator;
        result.denominator = denominator;
        result.simple();
        return result;
    }
    Fraction operator- (const Fraction& f){
        Fraction result;
        result.numerator = numerator * f.denominator - f.numerator * denominator;
        result.denominator = denominator * f.denominator;
        result.simple();
        return result;
    }
    Fraction operator- (const int& f){
        Fraction result;
        result.numerator = numerator - f * denominator;
        result.denominator = denominator;
        result.simple();
        return result;
    }
    Fraction operator* (const Fraction& f){
        Fraction result;
        result.numerator = numerator * f.numerator;
        result.denominator = denominator * f.denominator;
        result.simple();
        return result;
    }
    Fraction operator/ (const Fraction& f){
        Fraction result;
        result.numerator = numerator * f.denominator;
        result.denominator = denominator * f.numerator;
        result.simple();
        return result;
    }
     friend std::ostream& operator<<(std::ostream& os, const Fraction& c);
};