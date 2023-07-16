#include "editor.h"

#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    TextEditor t;
    string opr;
    int opr_num, screenshot_cnt = 0;
    cin >> opr_num;
    while (opr_num--)
    {
        cin >> opr;
        if (opr == "MOVE")
        {
            int row, col;
            cin >> row >> col;
            t.moveCursor({row, col});
        }
        else if (opr == "SELECT")
        {
            int row1, col1, row2, col2;
            cin >> row1 >> col1 >> row2 >> col2;
            t.select({row1, col1}, {row2, col2});
        }
        else if (opr == "WRITE")
        {
            std::string data;
            cin >> data;
            t.write(data);
        }
        else if (opr == "NEWLINE")
        {
            t.newline();
        }
        else if (opr == "DELETE")
        {
            t.del();
        }
        else if (opr == "COPY")
        {
            t.copy();
        }
        else if (opr == "PASTE")
        {
            t.paste();
        }
        else if (opr == "SCREEN")
        {
            cout << '#' << ++screenshot_cnt << ':' << endl;
            t.screenShot();
            cout << endl;
        }
        else if (opr == "QUIT")
        {
            break;
        }
        else
            cout << "Invalid operation" << endl;
    }
    return 0;
}