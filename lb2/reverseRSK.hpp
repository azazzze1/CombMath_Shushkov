#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>


struct tableCell{
 /* 
    x - столбец,
    y - строка,
    value - значение

    В стандартной таблице Юнга прямой формы. 
 */

    int x;
    int y;
    int value;
};

class ReverseRSK {
public:
    ReverseRSK(const std::string& fileNameP, const std::string& fileNameQ); 
    std::vector<int> algReverseRSK();

private:
    std::vector<std::vector<int>> loadTableFromFile(const std::string& fileName, bool loadQPositions);

    std::vector<std::vector<int>> tableP;
    std::vector<std::vector<int>> tableQ;
    std::map<int, std::pair<int, int>> qPos;

    std::vector<int> permutation;
    
};
