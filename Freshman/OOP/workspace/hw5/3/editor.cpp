#include "editor.h"
#include <iostream>

TextEditor::TextEditor(){
    selected = false;
    cursor = {0, 0};
    data.push_back("");
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
    data[cursor.first].insert(cursor.second, str);
    cursor.second += str.size();
}

void TextEditor::newline(){
    if(selected) del();
    std::string tmp = data[cursor.first];
    data[cursor.first] = tmp.substr(0, cursor.second) + "\n";
    data.insert(data.begin() + cursor.first + 1, tmp.substr(cursor.second));
    moveCursor({cursor.first + 1, 0});
    selected = false;
}

void TextEditor::del(){
    if(!selected){
        if(cursor.second < data[cursor.first].size()){
            data[cursor.first].erase(cursor.second, 1);
            if(cursor.second == data[cursor.first].size() && cursor.first < data.size() - 1){//刚才的的erase已经将本行文本的换行符删除了
                data[cursor.first] += data[cursor.first + 1];
                data.erase(data.begin() + cursor.first + 1);
            }
        }
    }
    else{
        if(cursor_beg.first < cursor_end.first){
            data[cursor_beg.first].erase(cursor_beg.second, data[cursor_beg.first].size() - cursor_beg.second);
            data[cursor_end.first].erase(0, cursor_end.second);
            //删除中间行的内容, 会导致迭代器失效
            data.erase(data.begin() + cursor_beg.first + 1, data.begin() + cursor_end.first);
            //将原本选中区域的最后一行与选中区域的第一行合并
            data[cursor_beg.first] += data[cursor_beg.first + 1];
            data.erase(data.begin() + cursor_beg.first + 1);
        }
        else if(cursor_beg.first == cursor_end.first){
            data[cursor_beg.first].erase(cursor_beg.second, cursor_end.second - cursor_beg.second);
        }
        moveCursor(cursor_beg);
    }
}

void TextEditor::copy(){
    if(selected){
        clipboard.clear();
        if(cursor_beg.first < cursor_end.first){
            clipboard.push_back(data[cursor_beg.first].substr(cursor_beg.second));
            for(int i = 1; i < cursor_end.first - cursor_beg.first; i++){
                clipboard.push_back(data[cursor_beg.first + i]);
            }
            clipboard.push_back(data[cursor_end.first].substr(0, cursor_end.second));
        }
        else if(cursor_beg.first == cursor_end.first){
            clipboard.push_back(data[cursor_beg.first].substr(cursor_beg.second, cursor_end.second - cursor_beg.second));
        }
    }
    /*std::cout << "clipboard: " << std::endl;
    for(auto& str : clipboard){
        std::cout << str;
    }
    std::cout << "||\n";*/
}

void TextEditor::paste(){
    if(selected) del();
    if(clipboard.empty()) return;
    newline();
    moveCursor({cursor.first - 1, 0});
    data[cursor.first].erase(data[cursor.first].size() - 1, 1);//删除刚才的换行符
    for(int i = 0; i < clipboard.size(); i++){
        data.insert(data.begin() + cursor.first + i + 1, clipboard[i]);
    }
    if(data[cursor.first + clipboard.size()].end()[-1] != '\n'){
        data[cursor.first + clipboard.size()] += data[cursor.first + clipboard.size() + 1];
        data.erase(data.begin() + cursor.first + clipboard.size() + 1);
    }
    if(data[cursor.first].end()[-1] != '\n'){
        data[cursor.first] += data[cursor.first + 1];
        data.erase(data.begin() + cursor.first + 1);
    }
    moveCursor({cursor.first + clipboard.size() - 1, clipboard.back().size()});
}

void TextEditor::screenShot(){
    std::string out;
    if(!selected){
        for(int i = 0; i < data.size(); i++){
            if(i == cursor.first)
                out += data[i].substr(0, cursor.second) + "*" + data[i].substr(cursor.second);
            else
                out += data[i];
        }
    }
    else{
        for(int i = 0; i < data.size(); i++){
            if(i == cursor_beg.first && i == cursor_end.first)
                out += data[i].substr(0, cursor_beg.second) + "*" + data[i].substr(cursor_beg.second, cursor_end.second) + "*" + data[i].substr(cursor_end.second);
            else{
                if(i == cursor_beg.first)
                    out += data[i].substr(0, cursor_beg.second) + "*" + data[i].substr(cursor_beg.second);
                else if(i == cursor_end.first)
                    out += data[i].substr(0, cursor_end.second) + "*" + data[i].substr(cursor_end.second);
                else
                    out += data[i];
            }
        }
    }
    std::cout << out;
}