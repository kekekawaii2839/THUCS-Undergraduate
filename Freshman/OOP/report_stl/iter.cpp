#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

template <typename T>
class list_item
{
private:
    T _value;
    list_item<T> *_next;
public:
    list_item(T value) : _value(value), _next(nullptr) {}
    T value() const { return _value; }
    list_item<T>*& next() { return _next; }
    bool operator==(const list_item<T>& item) const { return _value == item._value; }
    bool operator!=(const list_item<T>& item) const { return _value != item._value; }
    bool operator==(const T& value) const { return _value == value; }
};

template <typename T>
class myList
{
private:
    size_t _size;
    list_item<T> *_head;
    list_item<T> *_tail;
public:
    myList() { _size = 0; _head = nullptr; _tail = nullptr; };
    void push_back(T data){
        list_item<T> *new_item = new list_item<T>(data);
        if(_head == nullptr){
            _head = new_item;
            _tail = new_item;
            ++_size;
            return;
        }
        _tail->next() = new_item;
        _tail = new_item;
        ++_size;
    }
    void print(){
        list_item<T> *current = _head;
        while(current != nullptr){
            cout << current->value() << endl;
            current = current->next();
        }
    }
    list_item<T>* head() const { return _head; }
    ~myList() {}
};

template <class Item>
struct myIter : public std::iterator<std::forward_iterator_tag, Item>
{
    Item *ptr;
    myIter(Item *p = 0) : ptr(p) {}
    Item& operator*() const { return *ptr; }
    Item* operator->() const { return ptr; }
    myIter& operator++() { ++ptr; return *this; }
    myIter operator++(int) { myIter tmp = *this; ++ptr; return tmp; }
    bool operator==(const myIter& i) const { return ptr == i.ptr; }
    bool operator!=(const myIter& i) const { return ptr != i.ptr; }
};

int main(){
    myList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.print();

    myIter<list_item<int>> begin(list.head());
    myIter<list_item<int>> end;
    myIter<list_item<int>> it = std::find(begin, end, 2);
    if(it != end)
        cout << "Found: " << it->value() << endl;
    else
        cout << "Not found" << endl;
    return 0;
}