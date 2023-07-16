#include<iostream>
#include<vector>
#include"myqueriable.h"

using namespace std;

bool op1(int x) {return x > 3;}

int main(){
    vector<int> vec = {1, 2, 3, 4, 5};
    auto arr = from(vec).where(op1);
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << endl;
    }
    cout << "sum = " << arr.sum() << endl;
    return 0;
}

// Output
/*
4
5
sum = 9

*/