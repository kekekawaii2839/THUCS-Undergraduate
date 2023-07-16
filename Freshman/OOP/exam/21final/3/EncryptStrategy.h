#pragma once
#include <string>

class EncryptStrategy{
public:
	virtual std::string encode(std::string mes) = 0;
};

class InsertStrategy: public EncryptStrategy{
public:
	std::string encode(std::string mes) {
		std::string res = "";
		for (int i = 0; i < mes.length(); ++i) {
			res += mes[i];
			res += "#";
		}
		return res;
	}
};

class InvertStrategy: public EncryptStrategy{
public:
	std::string encode(std::string mes){
		std::string res = "";
		for (int i = mes.length() - 1; i >= 0; --i)
			res += mes[i];
		return res;
	}
};