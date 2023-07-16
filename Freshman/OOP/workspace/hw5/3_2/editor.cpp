#include "editor.h"
#include <iostream>

TextEditor::TextEditor(){
    selected = false;
    cursor = {0, 0};
}

int TextEditor::calcIndex(Position pos){
    int index = 0, i = 0;
    while(i < pos.first){
        if(data[index] == '\n') ++i;
        ++index;
    }
    index += pos.second;
    return index;
}

std::pair<int, int> TextEditor::calcPosition(int index){
    int first = 0, i = 0, sum = -1;
    while(i < index){
        if(data[i] == '\n'){
            ++first;
            sum = i;
        }
        ++i;
    }
    return {first, index - sum - 1};
}

void TextEditor::moveCursor(Position dest){
    selected = false;
    cursor = dest;
}

void TextEditor::select(Position beg, Position end){
    cursor_beg = beg;
    cursor_end = end;
    selected = true;
    cursor = beg;
}

void TextEditor::write(const std::string& str){
    if(selected) del();
    data.insert(calcIndex(cursor), str);
    cursor.second += str.size();
}

void TextEditor::newline(){
    if(selected) del();
    data.insert(calcIndex(cursor), "\n");
    moveCursor({cursor.first + 1, 0});
    selected = false;
}

void TextEditor::del(){
    if(!selected){
        data.erase(calcIndex(cursor), 1);
    }
    else{
        data.erase(calcIndex(cursor_beg), calcIndex(cursor_end) - calcIndex(cursor_beg));
        selected = false;
        cursor = cursor_beg;
    }
}

void TextEditor::copy(){
    if(selected){
        clipboard = data.substr(calcIndex(cursor_beg), calcIndex(cursor_end) - calcIndex(cursor_beg));
    }
}

void TextEditor::paste(){
    if(selected) del();
    data.insert(calcIndex(cursor), clipboard);
    //std::cout<<calcIndex(cursor) + clipboard.size()<<std::endl;
    moveCursor(calcPosition(calcIndex(cursor) + clipboard.size()));
}

void TextEditor::screenShot(){
    std::string out = data;
    if(!selected){
        out.insert(calcIndex(cursor), "*");
    }
    else{
        out.insert(calcIndex(cursor_beg), "*");
        out.insert(calcIndex(cursor_end) + 1, "*");
    }
    //std::cout<<"cursor:"<<cursor.first<<","<<cursor.second<<std::endl;
    std::cout << out;
}