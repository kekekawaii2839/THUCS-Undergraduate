#include <iostream>
#include <vector>

using namespace std;

int main(){
    string str1("abc");
    string str2 = str1;
    char str3[] = "abc";
    cout << str3 << endl;
    char* str4 = str3;
    cout << str4 << endl;
    return 0;
}