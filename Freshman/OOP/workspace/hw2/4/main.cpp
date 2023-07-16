#include "Splash.h"
#include <iostream>

using namespace std;

int main()
{
	int _size, x, y;
	cin >> _size;
	Splash splash(_size);
	splash.buildMap();
	int op;
	cin >> op;
	while(op--) {
		cin >> x >> y;
		splash.actAt(x, y);
	}
	cout << splash.getScore() << endl;
	return 0;
}