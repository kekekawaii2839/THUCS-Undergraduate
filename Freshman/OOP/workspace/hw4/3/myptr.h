#include <iostream>

using std::cout;
using std::endl;

template <typename T> class my_ptr {
    private:
        T* ptr;
        static T* null_ptr;
    public:
        my_ptr(T* _ptr = nullptr): ptr(_ptr) { cout<<"my_ptr constructed."<<endl; }
        ~my_ptr() {
            if(ptr != nullptr) delete ptr;
            cout<<"my_ptr destructed."<<endl;
        }

        my_ptr(const my_ptr& other) {
            cout<<"Copying of my_ptr is forbidden!"<<endl;
            cout<<"my_ptr constructed."<<endl;
            ptr = nullptr;
        }

        my_ptr& operator = (const my_ptr& other) {
            cout<<"Copying of my_ptr is forbidden!"<<endl;
            cout<<"my_ptr updated."<<endl;
            //ptr = nullptr;
            return *this;
        }

        my_ptr(my_ptr&& other) {
            cout<<"my_ptr constructed."<<endl;
            if(ptr != nullptr) delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        my_ptr& operator = (my_ptr&& other) {
            cout<<"my_ptr updated."<<endl;
            if(ptr != nullptr) delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
            return *this;
        }

        T& operator * () {
            if (ptr == nullptr) {
                cout<<"Do not attempt to read a nullptr!"<<endl;
                return *null_ptr;
            }
            return *ptr;
        }

        T* operator -> () {
            if (ptr == nullptr) {
                cout<<"Do not attempt to read a nullptr!"<<endl;
                return null_ptr;
            }
            return ptr;
        }
};

template <typename T> T* my_ptr<T>::null_ptr = new T();