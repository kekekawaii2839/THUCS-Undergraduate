#pragma once
#include <vector>
#include <iostream>

class Instruction
{
public:
    virtual void apply(std::vector<int> &vec) = 0;
    virtual void apply(std::vector<double> &vec) = 0;
    virtual void output() = 0;
};

class Add : public Instruction{
private:
    int _index;
    double _num;
public:
    Add(int index, double num): _index(index), _num(num) {}
    void apply(std::vector<int> &vec){
        vec[_index] += _num;
    }
    void apply(std::vector<double> &vec){
        vec[_index] += _num;
    }
    void output(){
        std::cout << "arr[" << _index << "] += " << _num << std::endl;
    }
};

class AddLink : public Instruction{
private:
    int _index1;
    int _index2;
public:
    AddLink(int index1, int index2): _index1(index1), _index2(index2) {}
    void apply(std::vector<int> &vec){
        vec[_index1] += vec[_index2];
    }
    void apply(std::vector<double> &vec){
        vec[_index1] += vec[_index2];
    }
    void output(){
        std::cout << "arr[" << _index1 << "] +=arr[" << _index2 << "]" << std::endl;
    }
};

class Assign : public Instruction{
private:
    int _index1;
    int _index2;
public:
    Assign(int index1, int index2): _index1(index1), _index2(index2) {}
    void apply(std::vector<int> &vec){
        vec[_index1] = vec[_index2];
    }
    void apply(std::vector<double> &vec){
        vec[_index1] = vec[_index2];
    }
    void output(){
        std::cout << "arr[" << _index1 << "] = arr[" << _index2 << "]" << std::endl;
    }
};

class Out : public Instruction{
private:
    int _index;
    std::ostream& _os;
public:
    Out(int index, std::ostream& os): _index(index), _os(os) {}
    void apply(std::vector<int> &vec){
        _os << vec[_index];
    }
    void apply(std::vector<double> &vec){
        _os << vec[_index];
    }
    void output(){
        std::cout << "cout << arr[" << _index << "]" << std::endl;
    }
};

class Endl : public Instruction{
public:
    void apply(std::vector<int> &vec){
        std::cout << std::endl;
    }
    void apply(std::vector<double> &vec){
        std::cout << std::endl;
    }
    void output(){
        std::cout << "cout << endl" << std::endl;
    }
};