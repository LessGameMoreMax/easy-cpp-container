#include <iostream>
#include "UnorderedMap.h"

using namespace std;
using namespace sablin;

int main(){
    UnorderedMap<int,std::string> my_map;
    my_map.Insert(Pair<int,string>(1,"1"));
    my_map.Insert(Pair<int,string>(2,"2"));
    my_map.Insert(Pair<int,string>(3,"3"));
    my_map.Insert(Pair<int,string>(4,"4"));
    my_map.Insert(Pair<int,string>(5,"5"));
    my_map.Insert(Pair<int,string>(6,"6"));
    my_map.Insert(Pair<int,string>(3,"100"));
    
    auto iter = my_map.Erase(my_map.Begin(2));
    cout << iter->first << iter->second << endl;
    my_map.PrintAll();
    return 0;
}
