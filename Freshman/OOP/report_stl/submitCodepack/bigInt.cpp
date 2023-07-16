#include <iostream>
#include <chrono>
#include "SGI-STL/type_traits.h"
#include "SGI-STL/stl_iterator_base.h"
#include "SGI-STL/stl_construct.h"
#include "SGI-STL/stl_uninitialized.h"

using std::cout;
using std::endl;

using namespace sgi_std;

class bigInt
{
private:
    size_t _value, _dummy;
public:
    bigInt(): _value(0) { _dummy = -1; }
    bigInt(int value): _value(value), _dummy(-1) {}
    ~bigInt() {}
};

namespace sgi_std{
    template<> struct __type_traits<bigInt> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
        //typedef __false_type is_POD_type;
    };
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    bigInt* a = new bigInt[int(10e4)];
    for(size_t i = 0; i < 10e3; ++i)
        sgi_std::uninitialized_fill_n(a, 10e4, bigInt(-10));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    cout << "time=" << duration.count() << endl;
    return 0;
}