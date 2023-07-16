#include"manager.h"

void Manager::newChef(Chef chef){
	chefs.push_back(chef);
}

void Manager::order(std::string dish){
	for(int i=0;i<chefs.size();++i){
		if(chefs[i].isSignatureDish(dish)){
			chefs[i].cook(dish);
			return;
		}
	}
	for(int i=0;i<chefs.size();++i){
		chefs[i].cook(dish);
		return;
	}
}

void Manager::order(std::string dish,int chefId){
	chefs[chefId].cook(dish);
}
