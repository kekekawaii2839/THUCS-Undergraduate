#include "Splash.h"
#include "Object.h"

int Object::act_water(Direction fromwhere, Actor fromwho) {
	int res = 0;
	if(fromwho == PLAYER or fromwho == WATER){
		++size;
		if(size > 3){
			++res;
			this->set2void(x,y,splash);
			if(x > 0) res += splash->map[x-1][y]->act(LEFT,WATER);
			if(x < splash->size - 1) res += splash->map[x+1][y]->act(RIGHT,WATER);
			if(y > 0) res += splash->map[x][y-1]->act(UP,WATER);
			if(y < splash->size - 1) res += splash->map[x][y+1]->act(DOWN,WATER);
		}
	}
	else{
		--size;
		if(size == 0) this->set2void(x,y,splash);
	}
	return res;
}

int Object::act_void(Direction fromwhere, Actor fromwho) {
	int res = 0;
	if(fromwho == PLAYER){
		cout<<"Error: Cannot act a Void."<<endl;
	}
	else{
		if(fromwhere == NONE){
			if(x > 0) res += splash->map[x-1][y]->act(fromwhere,fromwho);
			if(x < splash->size - 1) res += splash->map[x+1][y]->act(fromwhere,fromwho);
			if(y > 0) res += splash->map[x][y-1]->act(fromwhere,fromwho);
			if(y < splash->size - 1) res += splash->map[x][y+1]->act(fromwhere,fromwho);
		}
		else if(fromwhere == LEFT){
			if(x > 0) res += splash->map[x-1][y]->act(fromwhere,fromwho);
		}
		else if(fromwhere == RIGHT){
			if(x < splash->size - 1) res += splash->map[x+1][y]->act(fromwhere,fromwho);
		}
		else if(fromwhere == UP){
			if(y > 0) res += splash->map[x][y-1]->act(fromwhere,fromwho);
		}
		else if(fromwhere == DOWN){
			if(y < splash->size - 1) res += splash->map[x][y+1]->act(fromwhere,fromwho);
		}
		
	}
	return res;
}

int Object::act_barrier(Direction fromwhere, Actor fromwho) {
	if(fromwho == PLAYER){
		cout<<"Error: Cannot act a Barrier."<<endl;
	}
	return 0;
}

int Object::act_toxic(Direction fromwhere, Actor fromwho) {
	int res = 0;
	if(fromwho == PLAYER or fromwho == TOXIC){
		++size;
		if(size > 3){
			--res;
			this->set2void(x,y,splash);
			if(x > 0) res += splash->map[x-1][y]->act(LEFT,TOXIC);
			if(x < splash->size - 1) res += splash->map[x+1][y]->act(RIGHT,TOXIC);
			if(y > 0) res += splash->map[x][y-1]->act(UP,TOXIC);
			if(y < splash->size - 1) res += splash->map[x][y+1]->act(DOWN,TOXIC);
		}
	}
	else{
		--size;
		if(size == 0) this->set2void(x,y,splash);
	}
	return res;
}
