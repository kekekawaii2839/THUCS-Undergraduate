#pragma once
#include <string>

class VerificationStrategy{
public:
	virtual std::string verify(std::string mes) = 0;
};

class PrefixStrategy: public VerificationStrategy{
public:
	std::string verify(std::string mes){
		std::string res = "";
		for (int i = 0; i < 3; ++i) {
			res += mes[i];
		}
		return res;
	}
};

class IntervalStrategy: public VerificationStrategy{
public:
	std::string verify(std::string mes){
		std::string res = "";
		for (int i = 0; i < mes.length(); i += 2) {
			res += mes[i];
		}
		return res;
	}
};