#pragma once
#include <map>
#include "HitStatsResult.hpp"
#include "PopStrategy.hpp"

using namespace std;

template<class Key, class Value>
class MyDict{
    map<Key, Value> m;
    int hit = 0, miss = 0;
    int _capacity = 0;
    PopStrategy<Key>* p;
public:
    MyDict() {}
    MyDict(int capacity, PopStrategy<Key>* popStrategyPtr): _capacity(capacity), p(popStrategyPtr) {}
    Value& operator[] (Key key){
        if(m.find(key) != m.end()){
            hit++;
            return m[key];
        }
        else{
            miss++;
            m[key] = Value();
            return m[key];
        }
    }
    HitStatsResult hitStats() const{
        return HitStatsResult(hit, miss);
    }
    int size() const{
        return m.size();
    }
    void clear(){
        m.clear();
        hit = 0;
        miss = 0;
    }
};