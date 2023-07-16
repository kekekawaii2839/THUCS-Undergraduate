#include <iostream>

template <int k>
struct Factorial {
    static const int value = k * Factorial<k-1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

int main()
{
    std::cout << Factorial<10>::value << std::endl; 
    return 0;
}