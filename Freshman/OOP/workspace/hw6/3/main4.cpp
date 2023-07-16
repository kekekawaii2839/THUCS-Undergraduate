#include<iostream>
#include<vector>
#include"myqueriable.h"

using namespace std;

bool op1(int x) {return x % 2 == 0;}
class Op2{
public:
	int operator()(int x) {return x * 2;}
} op2;

int main(){
    vector<int> vec = {1, 2, 3, 4, 5};
    auto arr = from(vec)
        .where(op1)
        .apply(op2);
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << endl;
    }
    cout << "sum = " << arr.sum() << endl;
}

// Output
/*
4
8
sum = 12

*/