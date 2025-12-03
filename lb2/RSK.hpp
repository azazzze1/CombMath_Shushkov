#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>


class RSK {
public:
    std::vector<std::vector<int>> P; 
    std::vector<std::vector<int>> Q;
    std::vector<int> permutation; 

    RSK(const std::string& fileName);

    void algRSK(); 
    void saveTableToFile(const std::string& filename, const std::vector<std::vector<int>>& table);

    std::vector<int> getShape();

private:
    std::vector<int> shape;
};
