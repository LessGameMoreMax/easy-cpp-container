#include <iostream>
#include "Map.h"

using namespace std;
using namespace sablin;

int main(){
    Map<int,string> map_one;
    map_one.Insert(MakePair<int,string>(1,"1"));
    map_one.PrintAll();
    return 0;
}
