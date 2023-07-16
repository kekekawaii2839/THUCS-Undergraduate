#include<iostream>
using namespace std;
class P
{
public:
    P(){cout << "调用构造函数" << endl;}
    ~P(){cout << "析构函数的调用" << endl;}
};
void test(){P p;}
int main()
{
    test();
    P p1;
    return 0;
}
