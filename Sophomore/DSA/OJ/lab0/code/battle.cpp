#include <cstdio>
#include <cstdlib> 
#include <chrono>
int main(){
    system("g++ rand_input.cpp -o rand_input");
    system("g++ check_input.cpp -o check_input");
    system("g++ solution_1.cpp -o solution_1");
    system("g++ solution_2.cpp -o solution_2");
    system("g++ solution_3.cpp -o solution_3");
    int counter = 0;
    int all_time[3] = {0};
    while(counter < 100){
        ++counter;
        system("./rand_input > rand.in");
        if(system("./check_input < rand.in")!=0){
            printf("invalid input!\n");
            break;
        }
        // 参考了 https://blog.csdn.net/hsy12342611/article/details/127964500
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        system("./solution_1 < rand.in > 1.out");
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        all_time[0] += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        begin = std::chrono::steady_clock::now();
        system("./solution_2 < rand.in > 2.out");
        end = std::chrono::steady_clock::now();
        all_time[1] += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        begin = std::chrono::steady_clock::now();
        system("./solution_3 < rand.in > 3.out");
        end = std::chrono::steady_clock::now();
        all_time[2] += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        if(system("diff 1.out 3.out")!=0 or system("diff 1.out 2.out")!=0){
            printf("different output!\n");
            break;
        }
    }
    printf("solution_1: %dms\n",all_time[0]);
    printf("solution_2: %dms\n",all_time[1]);
    printf("solution_3: %dms\n",all_time[2]);
    return 0;
}