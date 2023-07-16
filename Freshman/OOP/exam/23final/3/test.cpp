#include <iostream>
#include <list>
#include <functional>
#include <memory>
#include "window.h"
using namespace std;

int main(){
    Button b("btn1");
    b.setClickCommand([]{ cout << "btn1 was clicked!"; }); // 此处展示的 `[]{ cout << "btn1 was clicked!"; }` 是lambda表达式，是一个void()的可调用对象的示例，实际并不需要大家编写lambda表达式
    b.setDoubleClickCommand([]{ cout << "btn1 was double-clicked!"; });
    b.click();  // 输出 btn1 was clicked!
    b.doubleClick();  // 输出 btn1 was double-clicked!
}