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

    void writeSolutionToFile(); 

    private:
    std::vector<int> diagYoungForm;
    std::vector<std::vector<int>> solutionTables; 
    std::ofstream solutionFile;
    int totalCells; 

};

#endif