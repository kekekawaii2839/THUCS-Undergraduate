#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

template<class T>
class Data
{
protected:
    std::shared_ptr<Data<T>> data;
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
    std::shared_ptr<Data<T>> get_data() {
        return data;
    }
    virtual ~Data() {}
};

template<class T>
class DataEmpty : public Data<T>
{
    // Implement a Null Object for Data
    using Data<T>::data;
public:
    DataEmpty<T>(): Data<T>(0) { this->data = nullptr; }
    const T& get(int index) {
        assert(0); // No data in DataEmpty
    }
};

template<class T>
class DataPushBackDecorator : public Data<T>
{
    // Implement a Decorator for push_back operation
    using Data<T>::data;
    std::shared_ptr<T> value;
public:
    int index;
    DataPushBackDecorator(std::shared_ptr<Data<T>> _data, const T& _value): Data<T>(_data->length() + 1), value(std::make_shared<T>(_value)) {
        this->data = _data;
        index = _data->length();
    }
    const T& get(int index) {
        if (index == data->length()) {
            return *value;
        } else {
            return data->get(index);
        }
    }
};

template<class T>
class DataSetDecorator : public Data<T>
{
    // Implement a Decorator for set operation
    using Data<T>::data;
    T value;
public:
    int index;
    DataSetDecorator(std::shared_ptr<Data<T>> _data, int _index, const T& _value): Data<T>(_data->length()), index(_index), value(_value) {
        this->data = _data;
    }
    const T& get(int _index) {
        if (_index == index) {
            return value;
        } else {
            return data->get(_index);
        }
    }
};

template<class T>
class DataUpdateDecorator : public Data<T>
{
    // Implement a Decorator for merge operation
    std::shared_ptr<Data<T>> merge_data;
public:
    std::vector<int> index;
    DataUpdateDecorator(std::shared_ptr<Data<T>> _data, std::shared_ptr<Data<T>> _merge_data, std::vector<int> _index): Data<T>(std::max(_data->length(), _merge_data->length())), merge_data(_merge_data), index(_index) {
        this->data = _data;
    }
    const T& get(int _index) {
        if(std::find(index.begin(), index.end(), _index) != index.end()) {
            return merge_data->get(_index);
        } else {
            return this->data->get(_index);
        }
    }
};

template<class T>
class PVector
{
public:
    std::shared_ptr<Data<T>> data;
    PVector<T>() {
        data = std::make_shared<DataEmpty<T>>();
    }
    PVector<T>(std::shared_ptr<Data<T>> _data): data(_data) {}
    PVector<T> push_back(const T &value) const{
        return PVector<T>(std::make_shared<DataPushBackDecorator<T>>(data, value));
    }
    PVector<T> set(int index, const T &value) const{
        return PVector<T>(std::make_shared<DataSetDecorator<T>>(data, index, value));
    }
    PVector<T> undo() const{
        if(data->length() == 0) {
            std::cout << "cannot undo" << std::endl;
            return *this;
        }
        else{
            return PVector<T>(data->get_data());
        }
    }
    PVector<T> update(const PVector<T>& res) const{
        std::vector<std::shared_ptr<Data<T>>> v1, v2;
        std::vector<int> s1, s2;
        for(auto i = data; i != nullptr; i = i->get_data()){
            v1.push_back(i);
        }
        for(auto i = res.data; i != nullptr; i = i->get_data()){
            v2.push_back(i);
        }
        if(*(v1.end()-1) != *(v2.end()-1)){
            std::cout << "cannot update: no origin found" << std::endl;
            return *this;
        }
        while(v1.size() > 0 && v2.size() > 0 && v1.back() == v2.back()){
            v1.pop_back();
            v2.pop_back();
        }
        for(auto i = v1.rbegin(); i != v1.rend(); i++){
            auto a = std::dynamic_pointer_cast<DataPushBackDecorator<T>>(*i);
            if(a) s1.push_back((*a).index);
            else{
                auto b = std::dynamic_pointer_cast<DataSetDecorator<T>>(*i);
                if(b) s1.push_back((*b).index);
                else{
                    auto c = std::dynamic_pointer_cast<DataUpdateDecorator<T>>(*i);
                    if(c) s1.insert(s1.end(), (*c).index.begin(), (*c).index.end());
                }
            }
        }
        for(auto i = v2.rbegin(); i != v2.rend(); i++){
            auto a = std::dynamic_pointer_cast<DataPushBackDecorator<T>>(*i);
            if(a) s2.push_back((*a).index);
            else{
                auto b = std::dynamic_pointer_cast<DataSetDecorator<T>>(*i);
                if(b) s2.push_back((*b).index);
                else{
                    auto c = std::dynamic_pointer_cast<DataUpdateDecorator<T>>(*i);
                    if(c) s2.insert(s2.end(), (*c).index.begin(), (*c).index.end());
                }
            }
        }
        std::sort(s1.begin(), s1.end());
        std::sort(s2.begin(), s2.end());
        std::vector<int> s3;
        std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(s3));
        if(s3.size() > 0){
            std::cout << "cannot update: conflicts found" << std::endl;
            return *this;
        }
        return PVector<T>(std::make_shared<DataUpdateDecorator<T>>(data, res.data, s2));
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
};