#include <vector>
#include <string>
#include <cassert>
#include <iostream>

template <typename T, unsigned N>
class Repeat
{
    public:
    typedef T ValueType;

    T operator()(const T& value) const {
        T result = value;
        for (int i = 1; i < N; i++)
            result = result + value;
        
        return result;
    }
};

template <typename Funct>
class Mapper {
    public:
    typedef typename Funct::ValueType ValueType;

    std::vector<ValueType>& operator()(std::vector<ValueType>& vec) const {
        Funct funct; 
        for (int i=0;i<vec.size();i++) 
            vec[i] = funct(vec[i]);   
        
        return vec;
    }

};

int main()
{
    std::cout<<"Test started"<<std::endl;
    Mapper< Repeat<int, 3> > map_int;
    Mapper< Repeat<std::string, 2> > map_str;
    std::vector<int> vec_int;
    for(int i = 1; i <= 5; ++i){ vec_int.push_back(i); };
    map_int(vec_int);
    // test dla int
    {
        static const int res[] = {3,6,9,12,15};
        std::vector<int> test(res, res + 5);
        assert(test == vec_int);
    }

    std::vector<std::string> vec_str;
    vec_str.push_back("foo"); vec_str.push_back("bar");
    map_str(vec_str);
    // test dla str
    {
        static const char* res[] = {"foofoo", "barbar"};
        std::vector<std::string> test(res, res + 2);
        assert(test == vec_str);
    }

    std::cout<<"Test ended"<<std::endl;

    return 0;
}

