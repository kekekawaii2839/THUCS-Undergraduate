#pragma once
#include <iostream>
#include "Object.h"

using namespace std;

class Splash {
private:
	int size;
	int score;
	Object*** map;
public:
	Splash(int _size): size(_size), score(0) {
		map = new Object**[size];
		for (int i = 0; i < size; i++) {
			map[i] = new Object*[size];
		}
	}
	~Splash() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				delete map[i][j];
			}
			delete[] map[i];
		}
		delete map;
	}
	void buildMap();
	void actAt(int x, int y);
	int getScore() {return score;}
	friend class Object;
};