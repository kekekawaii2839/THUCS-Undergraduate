#pragma once

class Splash;

#include <iostream>

using namespace std;

enum Direction {NONE, LEFT, RIGHT, UP, DOWN};
enum Actor {PLAYER, WATER, TOXIC};
enum Type {T_WATER, T_TOXIC, T_BARRIER, T_VOID};

class Object {
private:
	Splash* splash;
	int type, x, y, size;
	int act_water(Direction fromwhere, Actor fromwho);
	int act_toxic(Direction fromwhere, Actor fromwho);
	int act_barrier(Direction fromwhere, Actor fromwho);
	int act_void(Direction fromwhere, Actor fromwho);
public:
	Object() {}
	~Object() {}
	void set2water(int _size, int _x, int _y, Splash* _splash) {
		type = T_WATER;
		x = _x; 
		y = _y; 
		splash = _splash;
		size = _size;
	}
	void set2toxic(int _size, int _x, int _y, Splash* _splash) {
		type = T_TOXIC;
		x = _x; 
		y = _y; 
		splash = _splash;
		size = _size;
	}
	void set2barrier(int _x, int _y, Splash* _splash) {
		type = T_BARRIER;
		x = _x; 
		y = _y; 
		splash = _splash;
	}
	void set2void(int _x, int _y, Splash* _splash) {
		type = T_VOID;
		x = _x; 
		y = _y; 
		splash = _splash;
	}
	int act(Direction fromwhere, Actor fromwho) {
		switch(type) {
			case T_WATER:
				return act_water(fromwhere, fromwho);
			case T_TOXIC:
				return act_toxic(fromwhere, fromwho);
			case T_BARRIER:
				return act_barrier(fromwhere, fromwho);
			case T_VOID:
				return act_void(fromwhere, fromwho);
			default:
				cout << "Error! Object-type is wrong.";
				return -1;
		}
	}
};