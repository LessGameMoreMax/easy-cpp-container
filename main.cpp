#include <iostream>
#include "Map.h"

using namespace std;
using namespace sablin;

int main(){
    try{
        Map<int,string> map_one;
        map_one.Insert(MakePair<int,string>(1,"1"));
        map_one.PrintAll();
    }catch(exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}
