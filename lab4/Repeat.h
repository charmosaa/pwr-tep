#pragma once
#include <vector>
#include <string>

#include <iostream>



template <typename T, unsigned N>
class Repeat
{
    public:
    using ValueType = T
    T operator()(const T& value) const {
        T result = value;
        for (int i = 1; i < N; ++i) {
            result = result + value;
        }
        return result;
    }
};

template <typename Funct>
class Mapper {
    public:
    using ValueType = typename Funct::ValueType;

    std::vector<ValueType>& operator()(std::vector<ValueType>& vec) const {
        Funct funct; 
        for (int i=0;i<vec.size();i++) 
        {
            vec[i] = funct(vec[i]);   
        }
        return vec;

    }

};

