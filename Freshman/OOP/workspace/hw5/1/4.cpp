#include <iostream>
#include <map>
using namespace std;

void choiceA(map<string, int, greater<string>> age)
{
    age["Dave"] = age["Carol"] + 1;
    cout << age.size() << endl; // (1)
}

void choiceB(map<string, int, greater<string>> age)
{
    age.insert(make_pair("Alex", 5));
    cout << age["Alex"] << endl; // (2)
}

void choiceC(map<string, int, greater<string>> age)
{
    age["Alex"] = 5;
    cout << age["Alex"] << endl; // (3)
}

void choiceD(map<string, int, greater<string>> age)
{
    for (auto it = age.begin(); it != age.end(); it++)
    {
        cout << it->second << ' '; // (4a)
    }
    cout << endl; // (4b)
}

void choiceE(map<string, int, greater<string>> age)
{
    age.insert(make_pair("Carol", 5));
    age.erase(age.begin(), --age.end());
    cout << age.size() << endl;
}

int main()
{
    map<string, int, greater<string>> age;

    age["Alex"] = 2;
    age["Bob"] = 1;

    choiceA(age);
    choiceB(age);
    choiceC(age);
    choiceD(age);
    choiceE(age);
}
