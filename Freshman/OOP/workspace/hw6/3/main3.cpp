#include<iostream>
#include<vector>
#include"myqueriable.h"

using namespace std;

int op1(int x) {return x - 1;}

int main(){
    vector<int> vec = {1, 2, 3, 4, 5};
    auto arr = from(vec).apply(op1);
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << endl;
    }
    cout << "sum = " << arr.sum() << endl;
    return 0;
}

// Output
/*
0
1
2
3
4
sum = 10

*/