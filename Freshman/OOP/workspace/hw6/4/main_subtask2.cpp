#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include "sortlevel.h"
#include "compare.h"
using namespace std;

Compare<vector<int>> make_comp(list<sort_level>);

int main()
{
    int m, n, d;
    cin >> m >> n >> d;

    vector<vector<int>> v(m, vector<int>(n));  // 生成m行n列的vector，默认值初始化

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> v[i][j];

    list<sort_level> sortlevels;
    while (d--) 
    {
        int i; char c;
        cin >> i >> c;
        order_type t;
        switch (c)
        {
            case 'a': t = ASCEND; break;
            case 'd': t = DESCEND; break;
        }
        sortlevels.push_back({ i,t });
    }

    sort(v.begin(), v.end(), make_comp(sortlevels));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cout << v[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}