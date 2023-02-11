#ifndef PAIR_H
#define PAIR_H
#include <iostream>
namespace sablin{
 
template <typename TONE,typename TTWO>
class Pair{
public:
    TONE first;
    TTWO second;
    typedef TONE first_type;
    typedef TTWO second_type;
    Pair():first(),second(){}
    Pair(const TONE&,const TTWO&);
    Pair(const Pair&);
    Pair(Pair&&);
    Pair& operator=(const Pair&);
    Pair& operator=(Pair&&);
    ~Pair() = default;
};

template <typename TONE,typename TTWO>
Pair<TONE,TTWO>::Pair(const TONE &first_element,const TTWO &second_element):
    first(first_element),second(second_element){}

template <typename TONE,typename TTWO>
Pair<TONE,TTWO>::Pair(const Pair &another):
    first(another.first),second(another.second){}

template <typename TONE,typename TTWO>
Pair<TONE,TTWO>::Pair(Pair &&another):
    first(std::move(another.first)),second(std::move(another.second)){}

template <typename TONE,typename TTWO>
Pair<TONE,TTWO>& Pair<TONE,TTWO>::operator=(const Pair &another){
    first = another.first;
    second = another.second;
    return *this;
}

template <typename TONE,typename TTWO>
Pair<TONE,TTWO>& Pair<TONE,TTWO>::operator=(Pair &&another){
    first = std::move(another.first);
    second = std::move(another.second);
    return *this;
}

template <typename TONE,typename TTWO>
Pair<TONE,TTWO> MakePair(TONE &&first_element,TTWO &&second_element){
    return Pair<TONE,TTWO>(std::forward<TONE>(first_element),std::forward<TTWO>(second_element));
}

}
#endif
