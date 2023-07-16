#include <cassert>

class Test{};

int main(){
Test* p = new Test();
delete p;
assert(p == nullptr);
return 0;
}
