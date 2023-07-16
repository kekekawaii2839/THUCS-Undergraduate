#pragma once
#include "Instruction.h"
#include <iostream>

class temp;
class temp2;

class MagicArray{
private:
    int _length;
    std::vector<Instruction*> instructions;
public:
    MagicArray(int length): _length(length) {}
    temp operator[] (int index);
    temp2 endl();
    void add_ins(Instruction* ins){
        instructions.push_back(ins);
    }
    void apply(std::vector<int> &vec){
        for(auto i: instructions){
            i->apply(vec);
        }
    }
    void apply(std::vector<double> &vec){
        for(auto i: instructions){
            i->apply(vec);
        }
    }
    std::vector<Instruction*>& getInstructions(){
        return instructions;
    }
};

class temp{
private:
    MagicArray* _array;
    int _index;
public:
    temp(MagicArray* array, int index): _array(array), _index(index) {}
    MagicArray* get_array(){ return _array; }
    int get_index(){ return _index; }
    void operator+= (int num){
        Instruction* ins = new Add(_index, num);
        _array->add_ins(ins);
    }
    void operator+= (temp t){
        Instruction* ins = new AddLink(_index, t.get_index());
        _array->add_ins(ins);
    }
    void operator= (temp t){
        Instruction* ins = new Assign(_index, t.get_index());
        _array->add_ins(ins);
    }
};

class temp2{
private:
    MagicArray* _array;
public:
    temp2(MagicArray* array): _array(array) {}
    MagicArray* get_array(){ return _array; }
};

std::ostream& operator<< (std::ostream& os, temp t){
    Instruction* ins = new Out(t.get_index(), os);
    t.get_array()->add_ins(ins);
    return os;
}

temp MagicArray::operator[] (int index){
    return temp(this, index);
}

temp2 MagicArray::endl(){
    return temp2(this);
}

std::ostream& operator<< (std::ostream& os, temp2 t){
    Instruction* ins = new Endl();
    t.get_array()->add_ins(ins);
    return os;
}