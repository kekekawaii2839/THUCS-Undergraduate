#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int mul = 1;
	for (int n = 1; n <= 100; n++) {
		mul *= n;
		cout << "n=" << n << "	mul=" << mul << "	" << bitset<sizeof(int) * 8>(mul) << endl;
	}
	cout << "1*2*...*100=" << mul << endl;
	return 0;
}