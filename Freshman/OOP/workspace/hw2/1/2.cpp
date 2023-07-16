#include <iostream>

class Member{
public:
    Member(){std::cout<<"Constructing member.";}
    ~Member(){std::cout<<"Destructing member.";}
};

class Group{
public:
    Member member;
    Group(){std::cout<<"Constructing group.";}
    ~Group(){std::cout<<"Destructing group.";}
};

int main(){
    Group group;
    return 0;
}
