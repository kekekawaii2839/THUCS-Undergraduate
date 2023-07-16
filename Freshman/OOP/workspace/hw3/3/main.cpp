#include <iostream>
#include <utility>
#include "altset.h"

int main() {
    int n, m, k;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;
    Altset *altset = new Altset[n];
    char *str = new char[k + 1];
    std::cin >> str;
    altset[0] = Altset(str, k);

    std::cin >> m;
    for (int op, i, j; m --;) {
        std::cin >> op >> i >> j;
        if (op == 0) {
            altset[i].inverse(j);
        } else if (op == 1) {
            altset[i].append(j);
        } else if (op == 2) {
            altset[j] = altset[i];
        } else if (op == 3) {
            altset[j] = std::move(altset[i]);
        } else if (op == 4) {
            std::cout << int(altset[i].get(j)) << '\n';
        }
    }

    for (int i = 0; i < n; i ++) {
        if (altset[i].empty()) {
            std::cout << -1 << '\n';
        }
        else {
            std::cout << altset[i].count() << '\n';
        }
    }

    delete [] str;
    delete [] altset;
	return 0;
}
