#pragma once

#include"chef.h"
#include<vector>

class Manager{
	private:
		std::vector<Chef> chefs;
	public:
		Manager(){};
		void newChef(Chef chef);
		void order(std::string dish);
		void order(std::string dish,int chefId);
};
