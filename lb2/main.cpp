#include "knuthEquivalence.hpp"


int main(){
    KnuthEquivalence ke ("permutation.txt");

    std::vector<std::vector<int>> form = ke.convertRowSequenceToCells({0, 0, 1, 1, 0, 2});

    for(auto i : form){
        for(auto j : i){
            std::cout << j << " "; 
        }
        std::cout<<std::endl; 
    }
}