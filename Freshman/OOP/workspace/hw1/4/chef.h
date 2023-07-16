#pragma once
#include <string>

class Chef {
private:
    std::string name, signatureDish;
public:
    Chef(std::string _name, std::string _signatureDish); // Construct a `Chef` object.
    bool isSignatureDish(std::string dish); // Check whether `dish` is a signature dish.
    void cook(std::string dish); // Cook and print.
};