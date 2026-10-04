#include <iostream>
#include"DSA_Upgrade/vec.h"
#include"funcs.h"
#include<vector>



int main(){

     Vec<int> arr(5);

     arr.add_all(1, 2, 3, 4, 5);

     arr.add(89);

     arr.add_all(99, 134, 1765, 87, 975, 31, 43, 16);

     print(arr.getCapasity());
     print(arr.getSize());

     print("###################");



    return 0;
}