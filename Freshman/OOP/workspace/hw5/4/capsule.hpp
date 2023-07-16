#pragma once

template <typename T>
class Capsule {
private:
    T data;
    static unsigned long long create_cnt, copy_cnt, move_cnt, delete_cnt;
public:
    Capsule() : data(0) { ++create_cnt; }
    Capsule(T n) : data(n) { ++create_cnt; }
    Capsule(const Capsule& other) : data(other.data) { ++copy_cnt; }
    Capsule(Capsule&& other) : data(other.data) { other.data = 0; ++move_cnt; }
    ~Capsule() { ++delete_cnt; }

    Capsule& operator=(const Capsule& other) {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }
    Capsule& operator=(Capsule&& other) {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }

    friend std::istream& operator>>(std::istream& in, Capsule& t) {
        in >> t.data;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Capsule& t) {
        out << t.data;
        return out;
    }

    static bool is_ok()
    {
        return create_cnt + copy_cnt + move_cnt == delete_cnt;
    }
};

template <typename T>
unsigned long long Capsule<T>::create_cnt = 0;
template <typename T>
unsigned long long Capsule<T>::copy_cnt = 0;
template <typename T>
unsigned long long Capsule<T>::move_cnt = 0;
template <typename T>
unsigned long long Capsule<T>::delete_cnt = 0;