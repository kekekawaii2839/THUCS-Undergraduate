#include <iostream>

template<typename T>
struct Iter{
    typedef T value_type;  //内嵌类型声明
    T* ptr;
    Iter(T* p=0): ptr(p){}
    T& operator*() const { return *ptr; }
    // ...
};

template<typename I>
typename I::value_type func(I iter){return *iter;}

template<typename I>
struct iterator_traits{
    typedef typename I::value_type value_type;
};

template<typename T>
struct iterator_traits<T*>{
    typedef T value_type;
};

template<typename T>
struct iterator_traits<const T*>{
    typedef T value_type;
};

int main(){
    int a[5] = {1,2,3,4,5};
    Iter<int> iter(a);
    std::cout << func(iter) << std::endl;
    return 0;
}