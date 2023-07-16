#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "compare.h"
using namespace std;

struct Point {
    int x = 0, y = 0, z = 0;
    Point() {}
    Point(int x_, int y_, int z_) :x(x_), y(y_), z(z_) {}
};

istream& operator>> (istream& in, Point& p) {
    int x, y, z;
    in >> x >> y >> z;
    p.x = x, p.y = y; p.z = z;
    return in;
}

ostream& operator<< (ostream& out, const Point& p) {
    out << p.x << " " << p.y << " " << p.z;
    return out;
}

int main()
{
    int n;
    cin >> n;
    vector<Point> v;
    while (n--)
    {
        Point p;
        cin >> p;
        v.push_back(p);
    }

    auto xcomp = [](Point l, Point r) { return l.x < r.x; };
    auto ycomp = [](Point l, Point r) { return l.y < r.y; };
    auto zcomp = [](Point l, Point r) { return l.z < r.z; };
    Compare<Point> comp = { xcomp,ycomp,zcomp };
    sort(v.begin(), v.end(), comp);

    for (auto p : v) cout << p << endl;
    return 0;
}