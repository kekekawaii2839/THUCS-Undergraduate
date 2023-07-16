#include "Matrix.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int matNum;
	cin >> matNum;
	Matrix* matrices = new Matrix[matNum];
	for (int i = 0; i < matNum; i++) {
		cin >> matrices[i];
	}

	int opNum;
	cin >> opNum;
	int opnd1, opnd2, opnd3;
	string op;
	for (int i = 0; i < opNum; i++) {
		cin >> op;
		if (op == "+") {
			cin >> opnd1 >> opnd2;
			cout << matrices[opnd1] + matrices[opnd2];
		}
		else if (op == "-") {
			cin >> opnd1 >> opnd2;
			cout << matrices[opnd1] - matrices[opnd2];
		}
		else if (op == "*") {
			cin >> opnd1 >> opnd2;
			cout << matrices[opnd1] * matrices[opnd2];
		}
		else if (op == ".*") {
			cin >> opnd1 >> opnd2;
			cout << matrices[opnd1] * opnd2;
		}
		else if (op == "t") {
			cin >> opnd1;
			cout << transpose(matrices[opnd1]);
		}
		else if (op == "[]") {
			cin >> opnd1 >> opnd2 >> opnd3;
			cout << matrices[opnd1][opnd2][opnd3] << endl;
		}
		else if (op == "?") {
			cin >> opnd1;
			cout << matrices[opnd1];
		}
	}

	delete[] matrices;
	return 0;
}