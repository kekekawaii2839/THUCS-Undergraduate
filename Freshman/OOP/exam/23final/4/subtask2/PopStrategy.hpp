#pragma once
#include <list>
#include <algorithm>

using namespace std;

template<typename T>
class PopStrategy{
public:
    list<T> li;
    virtual void visit(T key){
        auto it = std::find(li.begin(), li.end(), key);
        if(it == li.end()){
            li.push_back(key);
        }
    }
    virtual T pop() = 0;
};

template<typename T>
class FIFOStrategy:public PopStrategy<T>{
    using PopStrategy<T>::li;
public:
    T pop() override{
        T t = li.front();
        li.pop_front();
        return t;
    }
};

template<typename T>
class LRUStrategy:public PopStrategy<T>{
    using PopStrategy<T>::li;
public:
    virtual void visit(T key){
        auto it = std::find(li.begin(), li.end(), key);
        if(it == li.end()){
            li.push_front(key);
        }
        else{
            T t = *it;
            li.erase(it);
            li.push_front(t);
        }
    }
    T pop() override{
        T t = li.back();
        li.pop_back();
        return t;
    }
};