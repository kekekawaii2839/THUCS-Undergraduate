#include"Farm.h"

Farm::Farm(int n){
	tins = new int[n];
	for(int i=0;i<n;++i){
		tins[i]=0;
	}
}

void Farm::addCow(Cow& cow){
	cows.push_back(cow);
	return;
}

void Farm::supply(std::string name,int food){
	for(auto i=0;i<cows.size();++i){
		if(cows[i].get_name()==name){
			tins[i]+=food;
		}
	}
	return;
}

void Farm::startMeal(){
	for(auto i=0;i<cows.size();++i){
		int ff=std::min(tins[i],cows[i].get_max());
		cows[i].eat(ff);
		tins[i] -= ff;
	}
	return;
}

void Farm::produceMilk(){
	for(auto i=0;i<cows.size();++i){
		MilkProduction += cows[i].Milk();
	}
	return;
}
