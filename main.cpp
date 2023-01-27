#include "List.h"
#include <iostream>

using namespace std;
using namespace sablin;

int main(){
    List<int> list_one{1,2,3,4,5};
    for(List<int>::iterator iter = list_one.Begin();iter != list_one.End(); ++iter)
        cout << *iter << " ";
    cout << endl;
    return 0;
}
