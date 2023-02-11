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
};
