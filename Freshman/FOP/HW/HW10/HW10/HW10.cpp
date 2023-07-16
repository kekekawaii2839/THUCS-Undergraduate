#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <Windows.h>

using namespace std;

int** a, ** b;//-1表示*
int **mask;//用于上机实验十的新增功能 mask作为遮罩记录矩阵的哪些元素可以显示
           //0表示不显示 1表示正常显示 -1表示以'-'显示 2表示'#'标记
int N = 9;
float R = 30;//缺省配置参数
string filePath;
ofstream output;
bool box = false;

void show() {//正常显示矩阵
	int maxx = 0, c = 0;//c表示最大值是几位数
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (a[i][j] > maxx) maxx = a[i][j];
		}
	}
	while (maxx >= 10) {
		++c;
		maxx /= 10;
	}
	++c;
	for (int i = 0; i < N; ++i) {
		cout << '+';
		if (output) output << '+';
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < c; ++k) {
				cout << '-';
				if (output) output << '-';
			}
			cout << '+';
			if (output) output << '+';
		}
		cout << endl << '|';
		if (output) output << endl << '|';
		for (int j = 0; j < N; ++j) {
			int t = a[i][j], ct = 0;
			while (t >= 10) {
				++ct;
				t /= 10;
			}
			for (int q = 0; q < c - ct - 1; ++q) {
				cout << ' ';
				if (output) output << ' ';
			}
			if (a[i][j] != -1) {
				cout << a[i][j] << '|';
				if (output) output << a[i][j] << '|';
			}
			else if (0 != j && -1 == a[i][j]) {
				cout << "*|";
				if (output) output << "*|";
			}
			else {
				cout << "*|";
				if (output) output << "*|";
			}
		}
		cout << endl;
		if (output) output << endl;
	}
	cout << '+';
	if (output) output << '+';
	for (int j = 0; j < N; ++j) {
		for (int k = 0; k < c; ++k) {
			cout << '-';
			if (output) output << '-';
		}
		cout << '+';
		if (output) output << '+';
	}
	cout << endl;
	if (output) output << endl;
}

void showByMask() {//遮罩后显示矩阵
	int maxx = 0, c = 0;//c表示最大值是几位数
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (a[i][j] > maxx) maxx = a[i][j];
		}
	}
	while (maxx >= 10) {
		++c;
		maxx /= 10;
	}
	++c;
	for (int i = 0; i < N; ++i) {
		cout << '+';
		if (output) output << '+';
		for (int j = 0; j < N; ++j) {//先打印上边框
			for (int k = 0; k < c; ++k) {
				cout << '-';
				if (output) output << '-';
			}
			cout << '+';
			if (output) output << '+';
		}
		cout << endl << '|';
		if (output) output << endl << '|';
		for (int j = 0; j < N; ++j) {
			int t = a[i][j], ct = 0;
			while (t >= 10) {//计算打印此元素前要补多少个空格来对齐边框
				++ct;
				t /= 10;
			}
			for (int q = 0; q < c - ct - 1; ++q) {//补空格ing
				cout << ' ';
				if (output) output << ' ';
			}
			if (a[i][j] != -1 && 0 != a[i][j]) {//元素是数字的情况
				if (mask[i][j] == 1) {
					cout << a[i][j] << '|';
					if (output) output << a[i][j] << '|';
				}
				else if (2 == mask[i][j]) {
					for (int u = 0; u < ct; ++u) cout << ' ';
					cout << "#|";
					if (output) output << "#|";
				}
				else {
					for (int u = 0; u <= ct; ++u) cout << ' ';
					cout << "|";
					if (output) output << "|";
				}
			}
			else if (0 == a[i][j]) {//元素是空位(0)的情况
				if (mask[i][j] == 1) {
					cout << a[i][j] << '|';
					if (output) output << a[i][j] << '|';
				}
				else if (2 == mask[i][j]) {
					for (int u = 0; u < ct; ++u) cout << ' ';
					cout << "#|";
					if (output) output << "#|";
				}
				else if (mask[i][j] == -1) {
					for (int u = 0; u < ct; ++u) cout << ' ';
					cout << "-|";
					if (output) output << "|";
				}
				else {
					for (int u = 0; u <= ct; ++u) cout << ' ';
					cout << "|";
					if (output) output << "|";
				}
			}
			else {//元素是地雷(*)的情况
				if (mask[i][j] == 1) {
					cout << "*|";
					if (output) output << "*|";
				}
				else if (2 == mask[i][j]) {
					for (int u = 0; u < ct; ++u) cout << ' ';
					cout << "#|";
					if (output) output << "#|";
				}
				else {
					cout << " |";
					if (output) output << " |";
				}
			}
		}
		cout << endl;
		if (output) output << endl;
	}
	cout << '+';
	if (output) output << '+';
	for (int j = 0; j < N; ++j) {//补充下边框
		for (int k = 0; k < c; ++k) {
			cout << '-';
			if (output) output << '-';
		}
		cout << '+';
		if (output) output << '+';
	}
	cout << endl;
	if (output) output << endl;
}

void unveal(int x, int y) {//显示相连区域
	if (x < 0 || x >= N || y < 0 || y >= N) return;
	if (-1 == mask[x][y] || 1 == mask[x][y]) return;//防止无限递归
	if (0 == a[x][y]) {
		mask[x][y] = -1;
		//周围8格的递归
		if (x > 0 && y > 0) unveal(x - 1, y - 1);
		if (y > 0) unveal(x, y - 1);
		if (x > 0) unveal(x - 1, y);
		if (y + 1 < N) unveal(x, y + 1);
		if (x + 1 < N) unveal(x + 1, y);
		if (x + 1 < N && y + 1 < N) unveal(x + 1, y + 1);
		if (x > 0 && y + 1 < N) unveal(x - 1, y + 1);
		if (x + 1 < N && y > 0) unveal(x + 1, y - 1);
	}
	else if (-1 != a[x][y]) mask[x][y] = 1;
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
		cout << "缺少config.txt!" << endl;
		a = new int* [N];
		b = new int* [N];
		mask = new int* [N];
		for (int i = 0; i < N; ++i) {
			a[i] = new int[N];
			b[i] = new int[N];
			mask[i] = new int[N];
		}
		return false;
	}
	else {
		bool flag[6] = { 0 };
		string line;
		while (getline(config, line)) {
			if ('#' == line[0]) continue;
			istringstream temp(line);
			while (temp) {
				string buffer;
				if ("BOX = TRUE" == buffer) {
					box = true;
					continue;
				}
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
				if (flag[4] && flag[5]) {
					filePath = buffer;
					cout << "filePath=" << filePath << endl;
					flag[4] = flag[5] = false;
				}
				if ("LOG" == buffer) flag[4] = true;
				if (flag[4] && "=" == buffer) flag[5] = true;
			}
		}
		a = new int* [N];
		b = new int* [N];
		mask = new int* [N];
		for (int i = 0; i < N; ++i) {
			a[i] = new int[N];
			b[i] = new int[N];
			mask[i] = new int[N];
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
	delete[]temp;
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

bool isGameOver() {//检查矩阵是否有空位
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (0 != a[i][j]) return false;
		}
	}
	return true;
}

bool isWin() {//循环判断游戏胜利的函数 for扫雷
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (a[i][j] >= 0) {
				if (mask[i][j] != -1 && mask[i][j] != 1) return false;
			}
		}
	}
	return true;
}

int main() {
	read();
	output.open(filePath);
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

	ifstream cmd("./cmd.txt");
	if (!cmd) {//当前路径找不到cmd.txt文件的情况
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) mask[i][j] = 0;//默认矩阵元素均不显示
		}

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

		while (!isWin()) {
			cout << "请输入要查看的元素行下标和列下标，或者使用'#'来标记：";
			int x = -1, y = -1;
			string temp;
			getline(cin, temp);
			if (temp[0] != '#') {
				istringstream convert(temp);
				convert >> x >> y;
				while (x < 0 || x >= N || y < 0 || y >= N) {
					cout << "非法输入！请重新输入：";
					cin >> x >> y;
				}
				system("cls");
				if (-1 == a[x][y]) {
					mask[x][y] = 1;
					//show();
					showByMask();
					cout << "GAME OVER";
					return 0;
				}
				else if (0 == a[x][y]) {
					unveal(x, y);
				}
				else {
					mask[x][y] = 1;
				}
				//show();
				showByMask();
			}
			else {//#标记
				istringstream convert(temp);
				char trash;
				convert >> trash >> x >> y;
				mask[x][y] = 2;
				system("cls");
				//show();
				showByMask();
			}
		}
		cout << "YOU WIN!" << endl;
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
			if (output) output << "压缩" << endl;
		}
		else if (2 == command) {
			rotate();
			cout << "旋转" << endl;
			if (output) output << "旋转" << endl;
		}
		else if (3 == command) {
			temp >> arg;
			merge(arg);
			cout << "消融" << endl;
			if (output) output << "消融" << endl;
		}
		show();
	}
	cmd.close();
	cout << endl;
	if ("" == line) {//表示文件为空
		cout << "cmd.txt为空！" << endl;
		if (output) output << "cmd.txt为空！" << endl;
		cout << "现在请用键盘输入指令：（1——压缩 2——旋转 3——消融）" << endl;
		cout << "i表示矩阵向上进行消融，k表示向下进行消融，j表示向左进行消融，l（字母L的小写字符）表示向右消融，以及q表示程序退出" << endl;
		bool flag = true;
		while (flag) {
			char ch = _getch();
			switch (ch) {
				cout << endl;
			case '1': {
				cout << "压缩！" << endl;
				cout << "敲击数字键输入指令方向：（1234表示上下左右）" << endl;
				int arg = _getch() - 48;
				compress(arg);
				show();
				break;
			}
			case '2':
				cout << "旋转！" << endl;
				rotate();
				show();
				break;
			case '3': {
				cout << "消融！" << endl;
				cout << "敲击数字键输入指令方向：（1234表示上下左右）" << endl;
				int arg = _getch() - 48;
				merge(arg);
				show();
				break;
			}
			case 'i':
				cout << "向上压缩！" << endl;
				compress(1);
				show();
				break;
			case 'k':
				cout << "向下压缩！" << endl;
				compress(2);
				show();
				break;
			case 'j':
				cout << "向左压缩！" << endl;
				compress(3);
				show();
				break;
			case 'l':
				cout << "向右压缩！" << endl;
				compress(4);
				show();
				break;
			case 'q':
				cout << "程序退出！" << endl;
				flag = false;
				break;
			default:
				break;
			}
			if (isGameOver()) {
				cout << "GAME OVER" << endl;
				break;
			}
		}
		return 0;
	}
	cout << "最终结果：" << endl;
	if (output) output << "最终结果：" << endl;
	show();
	return 0;
}