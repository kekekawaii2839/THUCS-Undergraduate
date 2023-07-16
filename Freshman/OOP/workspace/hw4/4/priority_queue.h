#pragma once
#include "abstract_compare.h"
#include <algorithm>

template<class T> class PriorityQueue {
private:
    AbstractCompare<T> *cmp;
    int _size;
    T *data;
public:
    PriorityQueue(AbstractCompare<T> *_cmp);
    ~PriorityQueue();
    bool empty();
    int size();
    void push(T element);
    void pop();
    T top();
};

template<class T> PriorityQueue<T>::PriorityQueue(AbstractCompare<T> *_cmp) {
    cmp = _cmp;
    _size = 0;
    data = new T[101];
}

template<class T> PriorityQueue<T>::~PriorityQueue() {
    delete[] data;
}

template<class T> bool PriorityQueue<T>::empty() {
    return _size == 0;
}

template<class T> int PriorityQueue<T>::size() {
    return _size;
}

template<class T> void PriorityQueue<T>::push(T element) {
    data[_size++] = element;
    for(int i = 0; i < _size; ++i){
        for(int j = i + 1; j < _size; ++j){
            if(cmp->compare(data[i], data[j])){
                std::swap(data[i], data[j]);
            }
        }
    }
}

template<class T> void PriorityQueue<T>::pop() {
    if(_size == 0) {
        return;
    }
    --_size;
}

template<class T> T PriorityQueue<T>::top() {
    return data[_size - 1];
}