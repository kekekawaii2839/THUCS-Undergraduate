#include <iostream>
#include <vector>
#include "multidimarray.hpp"

int main(){
    std::vector<int> init_1 = {2, 3, 4};
    MultiDimArray<int, 3> arr_1(init_1);   // int 型的三维数组，大小为 2*3*4
    std::vector<int> init_2 = {7};
    MultiDimArray<float, 1> arr_2(init_2); // float 型的一维数组，大小为 7

    std::cout << arr_1[1][0][0] << std::endl; // 输出 0
    return 0;
}