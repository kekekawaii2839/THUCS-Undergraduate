#include "Rack.h"
#include <algorithm>

Rack& Rack::operator += (const int& value)
{
    data.push_back(value);
    return *this;
}

Rack& Rack::operator += (const Rack rhs)//不引用 防止A+=A时死循环
{
    for (int i = 0; i < rhs.data.size(); i++)
    {
        data.push_back(rhs.data[i]);
    }
    return *this;
}

std::ostream& operator << (std::ostream& out, const Rack& rhs)
{
    for (int i = 0; i < rhs.data.size(); i++)
    {
        out << " " << rhs.data[i];
    }
    return out;
}

Rack Rack::operator , (const Rack& rhs)
{
    Rack temp;
    temp += *this;
    temp += rhs;
    return temp;
}

Rack Rack::operator , (const int& value)
{
    Rack temp;
    temp += *this;
    temp += value;
    return temp;
}

Rack operator , (const int& value, const Rack& rhs)
{
    Rack temp;
    temp += value;
    temp += rhs;
    return temp;
}

bool Rack::operator == (const Rack& rhs)
{
    return data.size() == rhs.data.size();
}

bool Rack::operator < (const Rack& rhs)
{
    return data.size() < rhs.data.size();
}

bool Rack::operator > (const Rack& rhs)
{
    return data.size() > rhs.data.size();
}

Rack Rack::operator & (const Rack& rhs)
{
    Rack temp;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < rhs.data.size(); j++)
        {
            if (data[i] == rhs.data[j])
            {
                temp.data.push_back(data[i]);
                break;
            }
        }
    }
    return temp;
}

int Rack::operator () (const int& index)
{
    return std::count(data.begin(), data.end(), index);
}

Rack& Rack::operator ~ ()
{
    std::reverse(data.begin(), data.end());
    return *this;
}

Rack& Rack::operator -- ()
{
    data.erase(data.begin());
    return *this;
}

Rack& Rack::operator -- (int dummy)
{
    data.pop_back();
    return *this;
}