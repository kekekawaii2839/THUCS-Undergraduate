#include <iostream>
#include "Example.h"

using namespace std;

int Example::count = 0;

Example::Example(int data) {
	_data = data;
	id = ++count;
	cout<<"Example #"<<id<<" is created"<<endl;
}

void Example::getData() {
	cout<<"The data of Example #"<<id<<" is "<<_data<<endl;
}

Example::~Example() {
	cout<<"Example #"<<id<<" is destroyed"<<endl;
}
