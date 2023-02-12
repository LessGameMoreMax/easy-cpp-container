#include <iostream>
#include "Map.h"

using namespace std;
using namespace sablin;

int main(){
        Map<int,string> map_one;
        map_one.Insert(MakePair<int,string>(12,"12"));
        map_one.Insert(MakePair<int,string>(11,"11"));
        map_one.Insert(MakePair<int,string>(18,"18"));
        map_one.Insert(MakePair<int,string>(2,"2"));
        map_one.Insert(MakePair<int,string>(7,"7"));
        map_one.Insert(MakePair<int,string>(3,"3"));
        map_one.Insert(MakePair<int,string>(4,"4"));
        map_one.Insert(MakePair<int,string>(22,"22"));
        map_one.Insert(MakePair<int,string>(6,"6"));
        map_one.Insert(MakePair<int,string>(17,"17"));
        map_one.Insert(MakePair<int,string>(9,"9"));
        map_one.Insert(MakePair<int,string>(14,"14"));
        map_one.Insert(MakePair<int,string>(19,"19"));
        map_one.Insert(MakePair<int,string>(20,"20"));

        auto iter_forward = map_one.Begin();
        ++iter_forward;
        ++iter_forward;
        auto iter_back = map_one.End();
        --iter_back;
        --iter_back;
        auto iter_one = map_one.Erase(iter_forward,iter_back);
        cout << iter_one->first << endl;
        map_one.PrintAll();
    return 0;
}
