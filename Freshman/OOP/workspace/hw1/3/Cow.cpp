#include"Cow.h"

void Cow::eat(int food){
	eatenFood += food;
	//std::cout<<"eatenFood="<<eatenFood<<std::endl;
	return;
}

float Cow::Milk(){
	if(eatenFood==0){
		//std::cout<<"eatenFood==0"<<std::endl;
		return 0;
	}
	if(eatenFood<_min){
		eatenFood = 0;
		//std::cout<<"eatenFood<_min"<<std::endl;
		return _milk*1.0/2;
	}
	eatenFood = 0;
	//std::cout<<"return _milk"<<std::endl;
	return _milk;
}
