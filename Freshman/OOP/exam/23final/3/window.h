#pragma once
#include <memory>
#include <list>
#include <vector>
#include <map>
#include "event.h"

using namespace std;

class Window;

class Widget {
    string _name;
    Window* _parent;
public:
    Widget(string name) :_name(name), _parent(nullptr) {}
    string getName() const { return _name; }
    Window* getParent() const { return _parent; }
    void setParent(Window * parent) {_parent = parent;}
    virtual ~Widget() {}
};

class Button :public Widget, public Click, public DoubleClick {
public:
    Button(string name) :Widget(name) {}
};

class Checkbox :public Widget, public Click {
    bool _checked = false;
public:
    Checkbox(string name): Widget(name), Click() {}
    void click() {
        if(_checked) _checked = false;
        else _checked = true;
    }
    void clear_check() { _checked = false; }
    void set_check() { _checked = true; }
    bool checked() { return _checked; }
    void assign_checked(bool i) { _checked = i; }
};

class Window {

private:
    list<shared_ptr<Widget>> Widgets;
    //TODO
public:
    shared_ptr<Widget> getPointerByName(string name) {
        for(auto i : Widgets){
            if(i.get()->getName() == name) return i;
        }
    }
    Widget& getElementByName(string name) {
        for(auto i : Widgets){
            if(i.get()->getName() == name) return *(i.get());
        }
    }
    bool addElement(shared_ptr<Widget> w) {
        for(auto i : Widgets){
            if(i.get()->getName() == w.get()->getName()) return false;
        }
        Widgets.push_back(w);
        w.get()->setParent(this);
        return true;
    }
    bool undo() {
        return false;
    }
};
