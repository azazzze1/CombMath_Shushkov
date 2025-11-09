#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>

class Solution{
    public:

    Solution(const std::string& fileName);
    ~Solution();

    void generateYoungTables(std::vector<int> filled, std::vector<int> current);

    void setDiagYoungForm(std::vector<int> newForm);

    private:
    std::vector<int> diagYoungForm;
    std::ofstream solutionFile;
    int totalCells; 

};

#endif