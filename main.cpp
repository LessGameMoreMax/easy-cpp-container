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

        map_one.Erase(12);
        map_one.Erase(17);
        map_one.Erase(9);
        map_one.Erase(2);
        map_one.Erase(7);
        map_one.PrintAll();
    return 0;
}
