#pragma once
#include "window.h"
#include <iostream>
#include <memory>
#include <list>
using namespace std;

class ClearAll {
    list<shared_ptr<Checkbox>> li;
public:
    ClearAll(list<shared_ptr<Checkbox>> checkbox): li(checkbox) {}
    void operator()() {
        for(auto &i : li){
            i.get()->clear_check();
        }
    }
};

class SelectAll {
    list<shared_ptr<Checkbox>> li;
public:
    SelectAll(list<shared_ptr<Checkbox>> checkbox): li(checkbox) {}
    void operator()(){
        for(auto &i : li){
            i.get()->set_check();
        }
    }
};

class Submit {
    list<shared_ptr<Checkbox>> li;
public:
    Submit(list<shared_ptr<Checkbox>> checkbox): li(checkbox) {}
    void operator()(){
        for(auto &i : li){
            if(i.get()->checked()) cout << i.get()->getName() << " is selected" << endl;
            else cout << i.get()->getName() << " is not selected" << endl;
        }
    }
};