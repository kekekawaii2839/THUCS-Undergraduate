#include"chef.h"
#include<iostream>

Chef::Chef(std::string _name,std::string _signatureDish){
	name = _name;
	signatureDish = _signatureDish;
}

bool Chef::isSignatureDish(std::string dish){
	return (dish==signatureDish);
}

void Chef::cook(std::string dish){
	if(isSignatureDish(dish)){
		std::cout<<name<<" made an awesome "<<dish<<std::endl;
	}
	else std::cout<<name<<" made a plain "<<dish<<std::endl;
}
