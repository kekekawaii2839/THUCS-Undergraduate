#include <vector>

template <typename T, int dim>
struct MultiDimArray
{
private:
    std::vector<MultiDimArray<T, dim-1>> data;
public:
    MultiDimArray() {}
    MultiDimArray(std::vector<int> init): data(init[0]){
        for (int i = 0; i < init[0]; i++){
            data[i] = MultiDimArray<T, dim-1>(std::vector<int>(init.begin()+1, init.end()));
        }
    }
    MultiDimArray(const MultiDimArray<T, dim>& ori){
        data = std::vector<MultiDimArray<T, dim-1>>(ori.data.size());
        for (int i = 0; i < ori.data.size(); i++){
            data[i] = ori.data[i];
        }
    }

    MultiDimArray& operator = (const MultiDimArray& ori){
        data = std::vector<MultiDimArray<T, dim-1>>(ori.data.size());
        for (int i = 0; i < ori.data.size(); i++){
            data[i] = ori.data[i];
        }
        return *this;
    }

    MultiDimArray& operator = (MultiDimArray&& ori){
        data = std::move(ori.data);
        return *this;
    }

    MultiDimArray<T, dim-1>& operator[](int i){
        return data[i];
    }
};

template <typename T>
struct MultiDimArray<T, 1>
{
private:
    std::vector<T> data;
public:
    MultiDimArray() {}
    MultiDimArray(std::vector<int> init) : data(init[0]) {}

    MultiDimArray& operator = (const MultiDimArray& ori){
        data = ori.data;
        return *this;
    }

    MultiDimArray& operator = (MultiDimArray&& ori){
        data = std::move(ori.data);
        return *this;
    }

    T& operator[](int i){
        return data[i];
    }
};