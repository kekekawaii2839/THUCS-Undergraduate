#pragma once

#include <string>

class TextEditor {
private:
    using Position = std::pair<int, int>;
    std::string data; // 数据区，亦可采用其他数据结构
    std::string clipboard; // 剪贴板，亦可采用其他数据结构
    bool selected; // 是否有选中区域
    Position cursor; // 光标位置
    Position cursor_beg, cursor_end; // 选中区域的起始和终止位置
public:
    TextEditor();
    int calcIndex(Position pos);
    std::pair<int, int> calcPosition(int index);
    void moveCursor(Position dest);
    void select(Position beg, Position end);
    void write(const std::string& str);
    void newline();
    void del();
    void copy();
    void paste();
    void screenShot();
};