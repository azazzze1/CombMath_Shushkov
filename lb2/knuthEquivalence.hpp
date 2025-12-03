#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

#include "reverseRSK.hpp"
#include "RSK.hpp"
#include "../lb1/solution.hpp"  

class KnuthEquivalence{
public:
    KnuthEquivalence(const std::string& fileName);

    void writeColHeightsToFile();

    void algKnuthEquilvalence();

    std::vector<std::vector<int>> convertRowSequenceToCells(const std::vector<int>& rowSeq);

private:  
    
    std::vector<int> colHeights; 
};

