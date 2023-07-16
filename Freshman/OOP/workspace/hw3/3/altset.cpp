#include "altset.h"

Altset::Altset()
{
    //data = new bool[2000];
    //len = 0;
}

Altset::~Altset()
{
    //delete [] data;
}

Altset::Altset(const char *data, int len)
{
    //this->data = new bool[20000];
    for(int i = 0; i < len; i++)
        this->data.push_back(data[len - i - 1] - '0');
    //this->len = len;
}

Altset& Altset::operator = (const Altset &altset)
{
    if(this == &altset)
        return *this;
    //delete [] this->data;
    //this->data = new bool[20000];
    //for(int i = 0; i < altset.len; i++)
    //    this->data[i] = altset.data[i];
    //this->len = altset.len;
    this->data = altset.data;
    return *this;
}

Altset& Altset::operator = (Altset &&altset)
{
    this->data = std::move(altset.data);
    //altset.data = nullptr;
    altset.data.clear();
    //this->len = altset.len;
    //altset.len = 0;
    return *this;
}

void Altset::inverse(int index)
{
    data[index] = !data[index];
}

void Altset::append(int value)
{
    //data[len++] = value;
    data.push_back(value);
}

bool Altset::get(int index) const
{
    return data[index];
}

bool Altset::empty() const
{
    //return len == 0;
    return data.empty();
}

int Altset::count() const
{
    int count = 0;
    for(int i = 0; i < data.size(); i++)
        if(data[i])
            count++;
    return count;
}