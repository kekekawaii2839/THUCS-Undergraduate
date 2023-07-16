#include <iostream>
#include <list>
#include <vector>
#include "compare.h"
#include "sortlevel.h"
using namespace std;

Compare<vector<int>> make_comp(list<sort_level> sortlevels)
{
    vector<function<bool(vector<int>, vector<int>)>> il;
    for(auto level: sortlevels){
        if(level.order == ASCEND){
            il.push_back([level](vector<int> l, vector<int> r){return l[level.column - 1] < r[level.column - 1];});
        }
        else{
            il.push_back([level](vector<int> l, vector<int> r){return l[level.column - 1] > r[level.column - 1];});
        }
    }
    return Compare<vector<int>>(il);
}
