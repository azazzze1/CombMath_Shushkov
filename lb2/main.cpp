#include <iostream>
#include "reverseRSK.hpp"
#include "RSK.hpp"


int main(){

    RSK("permutation.txt");

    ReverseRSK a("pTable.txt", "qTable.txt");

    std::vector<int> result = a.algReverseRSK();
    
    for(auto i : result) std::cout<<i<<" ";
    std::cout<<std::endl; 
}