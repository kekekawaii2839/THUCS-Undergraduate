#include "Splash.h"

void Splash::buildMap() {
	char tmp;
	tmp = getchar();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp = getchar();
			if (tmp == '1' || tmp == '2' || tmp == '3') {
				this->map[i][j] = new Object();
				this->map[i][j]->set2water(tmp - '0', i, j, this);
			}
			else if (tmp == '#') {
				this->map[i][j] = new Object();
				this->map[i][j]->set2void(i, j, this);
			}
			else if (tmp == '*') {
				this->map[i][j] = new Object();
				this->map[i][j]->set2barrier(i, j, this);
			}
			else if (tmp == '-') {
				tmp = getchar();
				this->map[i][j] = new Object();
				this->map[i][j]->set2toxic(tmp - '0', i, j, this);
			}
			getchar();
		}
	}
}

void Splash::actAt(int x, int y) {
	Object *obj = map[x][y];
	score += obj->act(NONE, PLAYER);
	if(obj != map[x][y]) delete obj;
	return;
}