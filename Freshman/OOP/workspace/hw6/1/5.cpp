#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IntNum {
public:
    int value;
    IntNum(int _value) : value(_value) {}
    bool operator<(const IntNum& b) const { 
        return value > b.value;
    };
};

void my_sort(vector<int>& arr) {
    vector<IntNum> nums;
    for (int i : arr) nums.push_back(IntNum(i));
    sort(nums.begin(), nums.end());
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = nums[i].value;
    }
}

int main(){
    vector<int> arr = {1, 2, 3, 4, 5};
    my_sort(arr);
    for (auto i : arr) cout << i << " ";
    return 0;
}