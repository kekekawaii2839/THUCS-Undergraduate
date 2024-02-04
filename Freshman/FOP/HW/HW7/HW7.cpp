#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

int **a, **b;
int N = 4;
float R = 0;

void show() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int t = a[i][j], c = 0;
			while (t >= 10) {
				++c;
				t /= 10;
			}
			for (int q = 0; q < N - 2 - c; ++q) cout << ' ';
			if (0 != j && a[i][j] != -1) cout << ' ' << a[i][j];
			else if (0 != j && -1 == a[i][j]) cout << " *";
			else if (-1 != a[i][j]) cout << a[i][j];
			else cout << '*';
		}
		cout << endl;
	}
}

bool isSame() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) if (b[i][j] != a[i][j]) return false;
	}
	return true;
}

bool read() {
	ifstream config("./config.txt");
	if (!config) {
		cout << "配置文件格式不对" << endl;
		a = new int*[4];
		b = new int*[4];
		for (int i = 0; i < 4; ++i) {
			a[i] = new int[4];
			b[i] = new int[4];
		}
		return false;
	}
	else {
		bool flag[4] = { 0 };
		string line;
		while (getline(config, line)) {
			if ('#' == line[0]) continue;
			istringstream temp(line);
			while (temp) {
				string buffer;
				temp >> buffer;
				//cout << "buffer= " << buffer << endl;
				if (flag[0] && flag[1]) {
					istringstream temp(buffer);
					float tempN = 0;
					temp >> tempN;
					if (tempN <= 0 || tempN != int(tempN)) N = 4;
					else N = tempN;
					cout << "N=" << N << endl;
					flag[0] = flag[1] = false;
				}
				if ("SIZE" == buffer) flag[0] = true;
				if (flag[0] && "=" == buffer) flag[1] = true;
				if (flag[2] && flag[3]) {
					istringstream temp(buffer);
					temp >> R;
					if (R < 0) R = 0;
					cout << "R=" << R << endl;
					flag[2] = flag[3] = false;
				}
				if ("RAND" == buffer) flag[2] = true;
				if (flag[2] && "=" == buffer) flag[3] = true;
			}
		}
		a = new int* [N];
		b = new int* [N];
		for (int i = 0; i < N; ++i) {
			a[i] = new int[N];
			b[i] = new int[N];
		}
		config.close();
	}
}

void compress(int direction) {
	if (direction < 0 || direction > 4) {
		cout << "wrong command!" << endl;
		return;
	}

	if (1 == direction) {
		for (int j = 0; j < N; ++j) {
			for (int i = 1; i < N; ++i) {
				a[0][j] += a[i][j];
				a[i][j] = 0;
			}
		}
	}
	else if (2 == direction) {
		for (int j = 0; j < N; ++j) {
			for (int i = 0; i < N - 1; ++i) {
				a[N - 1][j] += a[i][j];
				a[i][j] = 0;
			}
		}
	}
	else if (3 == direction) {
		for (int i = 0; i < N; ++i) {
			for (int j = 1; j < N; ++j) {
				a[i][0] += a[i][j];
				a[i][j] = 0;
			}
		}
	}
	else if (4 == direction) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N - 1; ++j) {
				a[i][N - 1] += a[i][j];
				a[i][j] = 0;
			}
		}
	}
}

void rotate() {
	int* temp = new int[N]();//带括号将调用构造函数以初始化new数组
	for (int k = N - 1; k >= 0; --k) {
		for (int i = 0; i < N; ++i) {
			b[k][N - 1 - i] = a[i][k];
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) a[i][j] = b[i][j];
	}
	delete []temp;
}

void merge(int direction) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) b[i][j] = a[i][j];
	}
	do {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) a[i][j] = b[i][j];
		}
		for (int j = 0; j < N; ++j) {
			int* temp = new int[N]();
			int counter = N - 1;
			for (int i = N - 1; i >= 0; --i) {
				if (b[i][j] != 0) temp[counter--] = b[i][j];
			}
			for (int i = 0; i < N - 1; ++i) {
				if (temp[i] == temp[i + 1]) {
					temp[i] = 0;
					temp[i + 1] *= 2;
				}
			}
			for (int i = 0; i < N; ++i) b[i][j] = temp[i];
			delete[]temp;
		}
	} while (!isSame());
}

int main() {
	read();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) a[i][j] = b[i][j] = 0;
	}
	srand(time(0));

	int counter = 0;
	while (counter < int(N * N * R / 100)) {
		int pos = rand() % (N * N);
		if (0 == a[pos / N][pos % N]) {
			a[pos / N][pos % N] = rand() % 20;
			++counter;
		}
	}
	if (0 == R) {
		int pos = rand() % (N * N);
		a[pos / N][pos % N] = rand() % 2 * 2 + 2;
	}

	cout << "原矩阵：" << endl;
	show();
	cout << endl;

	ifstream cmd("./cmd.txt");
	if (!cmd) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) a[i][j] = b[i][j] = 0;
		}
		int counter = 0;
		while (counter<int(N * N * R / 100)) {
			int pos = rand() % (N * N);
			if (0 == a[pos / N][pos % N]) {
				a[pos / N][pos % N] = -1;
				++counter;
			}
		}
		for (int i = 1; i < N - 1; ++i) {//先不计算四周的格子
			for (int j = 1; j < N - 1; ++j) {
				if (0 == a[i][j]) {
					a[i][j] = (-1 == a[i - 1][j - 1]) + (-1 == a[i][j - 1]) + (-1 == a[i - 1][j]) +
						(-1 == a[i + 1][j + 1]) + (-1 == a[i][j + 1]) + (-1 == a[i + 1][j]) +
						(-1 == a[i - 1][j + 1]) + (-1 == a[i + 1][j - 1]);//计算周围八格的*数
				}
			}
		}
		//现在计算四周的格子
		for (int i = 1; i < N - 1; ++i) {
			if (0 == a[i][0]) a[i][0] = (-1 == a[i - 1][0]) + (-1 == a[i + 1][0]) + (-1 == a[i - 1][1]) + (-1 == a[i][1]) + (-1 == a[i + 1][1]);
			if (0 == a[i][N - 1]) a[i][N - 1] = (-1 == a[i - 1][N - 1]) + (-1 == a[i + 1][N - 1]) + (-1 == a[i - 1][N - 2]) + (-1 == a[i][N - 2]) + (-1 == a[i + 1][N - 2]);
		}
		for (int j = 1; j < N - 1; ++j) {
			if (0 == a[0][j]) a[0][j] = (-1 == a[0][j - 1]) + (-1 == a[0][j + 1]) + (-1 == a[1][j - 1]) + (-1 == a[1][j]) + (-1 == a[1][j + 1]);
			if (0 == a[N - 1][j]) a[N - 1][j] = (-1 == a[N - 1][j - 1]) + (-1 == a[N - 1][j + 1]) + (-1 == a[N - 2][j - 1]) + (-1 == a[N - 2][j]) + (-1 == a[N - 2][j + 1]);
		}
		if (0 == a[0][0]) a[0][0] = (-1 == a[1][0]) + (-1 == a[1][1]) + (-1 == a[0][1]);
		if (0 == a[N - 1][0]) a[N - 1][0] = (-1 == a[N - 2][0]) + (-1 == a[N - 2][1]) + (-1 == a[N - 1][1]);
		if (0 == a[0][N - 1]) a[0][N - 1] = (-1 == a[0][N - 2]) + (-1 == a[1][N - 2]) + (-1 == a[1][N - 1]);
		if (0 == a[N - 1][N - 1]) a[N - 1][N - 1] = (-1 == a[N - 2][N - 2]) + (-1 == a[N - 2][N - 1]) + (-1 == a[N - 1][N - 2]);
		cout << "填入*后计算的结果：" << endl;
		show();
		return 0;
	}

	string line;
	char key = 0;
	while (getline(cmd, line)) {
		//cout << "line=" << line << endl;
		if ("Q" == line) break;
		istringstream temp(line);
		int command = 0, arg = 0;
		temp >> command;
		if (1 == command) {
			temp >> arg;
			compress(arg);
			cout << "压缩" << endl;
		}
		else if (2 == command) {
			rotate();
			cout << "旋转" << endl;
		}
		else if (3 == command) {
			temp >> arg;
			merge(arg);
			cout << "消融" << endl;
		}
		show();
	}
	cmd.close();
	cout << endl;
	if ("" == line) {//表示文件为空
		cout << "cmd.txt为空！" << endl;
		show();
		return 0;
	}
	cout << "最终结果：" << endl;
	show();
	return 0;
}