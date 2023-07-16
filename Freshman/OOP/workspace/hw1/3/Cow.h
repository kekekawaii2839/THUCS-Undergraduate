#ifndef COW_H
#define COW_H

#include<string>
#include<iostream>

class Cow{
	private:
		std::string name;
		int _min,_max,_milk;
		int eatenFood;
	public:
		Cow(std::string NAME,int minn,int maxx,int milk):name(NAME),_min(minn),_max(maxx),_milk(milk){eatenFood=0;};
		std::string get_name(){return name;};
		int get_min(){return _min;};
		int get_max(){return _max;};
		void eat(int food);
		float Milk();
};

#endif
