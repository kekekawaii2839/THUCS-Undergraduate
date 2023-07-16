#include <iostream>
#include "PopStrategy.hpp"

int main(){
    FIFOStrategy<char> fifo;
fifo.visit('a');
fifo.visit('b');
fifo.visit('a');
fifo.visit('c');
std::cout << fifo.pop() << std::endl; // 输出为 a，因为 a 是最早被插入的元素
fifo.visit('a');
std::cout << fifo.pop() << std::endl; // 输出为 b，因为弹出 a 后再访问视作重新插入，因此 b 是此时最早被插入的元素

LRUStrategy<char> lru;
lru.visit('a');
lru.visit('b');
lru.visit('a');
lru.visit('c');
std::cout << lru.pop() << std::endl; // 输出为 b，因为 b 是最长时间未被访问的元素
lru.visit('a');
std::cout << lru.pop() << std::endl; // 输出为 c，因为此时 c 是最长时间未被访问的元素

}