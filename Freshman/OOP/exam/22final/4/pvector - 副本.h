#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>

template<class T>
class Data
{
protected:
    int _length;
public:
    Data(int _length) : _length(_length) {}
    virtual const T& get(int index) = 0;
    int length() {
        return _length;
    }
    void set_length(int _length) {
        this->_length = _length;
    }
    virtual ~Data() {}
};

template<class T>
class DataEmpty : public Data<T>
{
public:
    DataEmpty<T>(): Data<T>(0) {};
    const T& get(int index) {
        assert(0); // No data in DataEmpty
    }
};

template<class T>
class DataPushBackDecorator : public Data<T>
{
    // Implement a Decorator for push_back operation
    Data<T>* data;
    T* value;
public:
    DataPushBackDecorator(Data<T>* _data, const T& _value): Data<T>(_data->length() + 1), data(_data) {value = new T(_value);}
    const T& get(int index) {
        if (index == data->length()) {
            return *value;
        } else {
            return data->get(index);
        }
    }
    Data<T>* get_data() { return data; }
    ~DataPushBackDecorator() {
        if(value != nullptr) delete value;
        if(data != nullptr) delete data;
    }
};

template<class T>
class DataSetDecorator : public Data<T>
{
    // Implement a Decorator for set operation
    Data<T>* data;
    int index;
    T value;
public:
    DataSetDecorator(Data<T>* _data, int _index, const T& _value): Data<T>(_data->length()), data(_data), index(_index), value(_value) {}
    const T& get(int _index) {
        if (_index == index) {
            return value;
        } else {
            return data->get(_index);
        }
    }
    Data<T>* get_data() { return data; }
    ~DataSetDecorator() {
        if(data != nullptr) delete data;
    }
};

template<class T>
class PVector
{
public:
    Data<T>* data;
    PVector<T>() {
        data = new DataEmpty<T>();
        // when to delete??
    }
    PVector<T>(Data<T>* _data): data(_data) {}
    PVector<T> push_back(const T &value) const{
        return PVector<T>(new DataPushBackDecorator<T>(data, value));
    }
    PVector<T> set(int index, const T &value) const{
        return PVector<T>(new DataSetDecorator<T>(data, index, value));
    }
    PVector<T> undo() const{
        if(data->length() == 0) {
            std::cout << "cannot undo" << std::endl;
            return *this;
        }
        else{
            DataPushBackDecorator<T>* a = dynamic_cast<DataPushBackDecorator<T>*>(data);
            if(a != nullptr){
                return PVector<T>(a->get_data());
            }
            else{
                DataSetDecorator<T>* b = dynamic_cast<DataSetDecorator<T>*>(data);
                if(b != nullptr){
                    return PVector<T>(b->get_data());
                }
            }
        }
    }
    const T& operator[](int index){
        return data->get(index);
    }
    friend std::ostream& operator<< (std::ostream& out, const PVector<T>& v) {
        out << "[";
        for (int i = 0; i < v.data->length(); i++) {
            out << v.data->get(i);
            if (i != v.data->length() - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }
    ~PVector<T>() {
        delete data;
    }
};
