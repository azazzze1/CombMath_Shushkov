#include "knuthEquivalence.hpp"


int main(){
    ReverseRSK r ("pTest.txt", "qTest.txt");
    std::vector<int> s = r.algReverseRSK();

    std::cout<<"Работа обратного алгоритма RSK:"<<std::endl;
    for(int i : s){
        std::cout<<i<<' '; 
    }
    std::cout<<std::endl;

    KnuthEquivalence ke ("permutation.txt");
}