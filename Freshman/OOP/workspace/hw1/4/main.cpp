#include <iostream>
#include <string>
#include "chef.h"
#include "manager.h"

int main() {
    int C, N;
    Manager manager;

    std::cin >> C;
    for (int i = 0; i < C; ++i) {
        std::string name, signatureDish;
        std::cin >> name >> signatureDish;
        manager.newChef(Chef(name, signatureDish));
    }

    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int t, chefId;
        std::string dish;
        std::cin >> t >> dish;
        if (t == 0) {
            manager.order(dish);
        }
        else {
            std::cin >> chefId;
            manager.order(dish, chefId);
        }
    }

    return 0;
}