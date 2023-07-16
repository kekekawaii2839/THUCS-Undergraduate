#pragma once
#include <functional>
using namespace std;

class Click {
private:
    std::function<void()> click_react;
    bool isSet = false;
public:
    Click() {}
    void setClickCommand(std::function<void()> f) {
        click_react = f;
        isSet = true;
    }
    virtual void click() {
        if(!isSet) return;
        click_react();
    }
};
class DoubleClick {
private:
    std::function<void()> dbclick_react;
    bool isSet = false;
public:
    DoubleClick() {}
    void setDoubleClickCommand(std::function<void()> f) {
        dbclick_react = f;
        isSet = true;
    }
    virtual void doubleClick() {
        if(!isSet) return;
        dbclick_react();
    }
};