#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <type_traits>
#include "multidimarray.hpp"
#include "capsule.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

#define DIM_3

#ifdef DIM_3
    #define DIM 3
#endif

using DataType = int;
using CapsuleType = Capsule<DataType>;
using ArrayType = MultiDimArray<CapsuleType, DIM>;

vector<int> getPos()
{
    vector<int> pos(DIM);
    for (int i = 0; i < DIM; ++i)
    {
        cin >> pos[i];
    }
    return pos;
}

CapsuleType& getElem(ArrayType& arr, const vector<int>& pos)
{
#ifdef DIM_3
    return arr[pos[0]][pos[1]][pos[2]]; // DIM = 3
#endif
}

int main()
{
    int n;
    cin >> n;
    vector<ArrayType*> arrays;
    for (int i = 0; i < n; ++i)
    {
        vector<int> init(DIM);
        for (int j = 0; j < DIM; ++j)
        {
            cin >> init[j];
        }
        arrays.push_back(new ArrayType(std::move(init)));
    }

    int cmd_num;
    cin >> cmd_num;
    string cmd;
    while (cmd_num--)
    {
        cin >> cmd;
        if (cmd == "assign")
        {
            int i;
            cin >> i;
            vector<int> pos = getPos();
            cin >> getElem(*arrays[i - 1], pos);
        }
        else if (cmd == "get")
        {
            int i;
            cin >> i;
            vector<int> pos = getPos();
            if (std::is_same<double, DataType>::value)
                cout << std::fixed << std::setprecision(6);
            cout << getElem(*arrays[i - 1], pos) << endl;
        }
        else if (cmd == "copy")
        {
            int i, j;
            cin >> i >> j;
            *arrays[j - 1] = *arrays[i - 1];
        }
        else if (cmd == "move")
        {
            int i, j;
            cin >> i >> j;
            *arrays[j - 1] = std::move(*arrays[i - 1]);
        }
        else
            cout << "invalid operation" << endl;
    }

    for (auto* p : arrays)
    {
        delete p;
    }

    cout << "sanity check: " << (Capsule<DataType>::is_ok() ? "ok" : "fail") << endl;
    return 0;
}