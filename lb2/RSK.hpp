#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>


class RSK {
public:
    RSK(const std::string& fileName);

    void algRSK(); 
    void saveTableToFile(const std::string& filename, const std::vector<std::vector<int>>& table);

    std::vector<int> getShape() const;

private:
    std::vector<int> permutation; 
    std::vector<std::vector<int>> P; 
    std::vector<std::vector<int>> Q;
    std::vector<int> shape;
};
