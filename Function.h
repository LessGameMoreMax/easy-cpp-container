#ifndef FUNCTION_H
#define FUNCTION_H
namespace sablin{

template <typename T>
struct Less{
    typedef T first_element_type;
    typedef T second_element_type;
    typedef bool result_type;
    bool operator()(const T &first,const T &second) const{
        return first < second;
    }
};

template <typename T>
struct EqualTo{
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
    bool operator()(const T &first,const T &second) const{
        return first == second;
    }
};

};
#endif
