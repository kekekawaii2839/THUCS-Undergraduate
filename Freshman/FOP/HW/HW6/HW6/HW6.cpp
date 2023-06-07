#include <iostream>
#include <cmath>

using namespace std;

int a[4][4], b[4][4];

void show() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int t = a[i][j],c=0;
			while (t >= 10) {
				++c;
				t /= 10;
			}
			for (int q = 0; q < 2 - c; ++q) cout << ' ';
			if (0 != j) cout << ' ' << a[i][j];
			else cout << a[i][j];
		}
		cout << endl;
	}
}

bool isSame() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) if (b[i][j] != a[i][j]) return false;
	}
	return true;
}

int main() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			a[i][j] = 0;
		}
	}
	float pr = 0;
	cout << "请输入比例值：";
	cin >> pr;
	srand(time(0));
	int counter = 0;
	while (counter < int(16 * pr)) {
		int pos = rand() % 16;
		if (0 == a[pos / 4][pos % 4]) {
			a[pos / 4][pos % 4] = pow(2, rand() % 5);//防止元素过大
			++counter;
		}
	}
	
	show();
	cout << endl << "1——压缩 2——旋转 3——消融" << endl;
	char command;
	rewind(stdin);
	while (command = getchar()) {
		rewind(stdin);
		if ('1' == command) {
			int arg = 0;
			cout << "1234表示上下左右" << endl;
			cin >> arg;
			if (arg < 0 || arg > 4) {
				cout << "wrong command!" << endl;
				return 1;
			}

			if (1 == arg) {
				for (int j = 0; j < 4; ++j) {
					for (int i = 1; i < 4; ++i) {
						a[0][j] += a[i][j];
						a[i][j] = 0;
					}
				}
			}
			else if (2 == arg) {
				for (int j = 0; j < 4; ++j) {
					for (int i = 0; i < 3; ++i) {
						a[3][j] += a[i][j];
						a[i][j] = 0;
					}
				}
			}
			else if (3 == arg) {
				for (int i = 0; i < 4; ++i) {
					for (int j = 1; j < 4; ++j) {
						a[i][0] += a[i][j];
						a[i][j] = 0;
					}
				}
			}
			else if (4 == arg) {
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 3; ++j) {
						a[i][3] += a[i][j];
						a[i][j] = 0;
					}
				}
			}
			show();
		}
		else if ('2' == command) {
			int b[4][4] = { 0 };
			int temp[4] = { 0 };
			for (int k = 3; k >= 0; --k) {
				for (int i = 0; i < 4; ++i) {
					b[k][3 - i] = a[i][k];
				}
			}
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) a[i][j] = b[i][j];
			}
			show();
		}
		else if ('3' == command) {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) b[i][j] = a[i][j];
			}
			do {
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) a[i][j] = b[i][j];
				}
				for (int j = 0; j < 4; ++j) {
					int temp[4] = { 0 };
					int counter = 3;
					for (int i = 3; i >= 0; --i) {
						if (b[i][j] != 0) temp[counter--] = b[i][j];
					}
					for (int i = 0; i < 3; ++i) {
						if (temp[i] == temp[i + 1]) {
							temp[i] = 0;
							temp[i + 1] *= 2;
						}
					}
					for (int i = 0; i < 4; ++i) b[i][j] = temp[i];
				}
			} while (!isSame());
			show();
		}
		else if ('Q' == command) {
			cout << "exit!" << endl;
			return 0;
		}
		else {
			cout << "wrong command!" << endl;
			return 1;
		}
	}
	return 0;
}