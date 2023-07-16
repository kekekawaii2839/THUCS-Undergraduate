#ifndef FARM_H
#define FARM_H

#include<vector>
#include"Cow.h"

class Farm{
	private:
		std::vector<Cow> cows;
		int* tins;
		float MilkProduction;
	public:
		Farm(int n);
		void addCow(Cow& cow);
		void supply(std::string name,int food);
		void startMeal();
		void produceMilk();
		float getMilkProduction(){return MilkProduction;};
		
		~Farm(){delete []tins;}
};

#endif
