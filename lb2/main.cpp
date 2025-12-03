#include <iostream>
#include "reverseRSK.hpp"


int main(){
    ReverseRSK a("testP.txt", "testQ.txt");

    std::vector<int> result = a.algReverseRSK();
    
    for(auto i : result) std::cout<<i<<" ";
    std::cout<<std::endl; 
}