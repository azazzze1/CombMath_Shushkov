#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


struct tableCell{
    int x;
    int y;
    int value;
};


class ReverseRSK {
public:
    ReverseRSK(const std::string& fileNameP, const std::string& fileNameQ); 

private:
    std::vector<std::vector<int>> loadTableFromFile(const std::string& fileName);

    std::vector<std::vector<int>> tableP;
    std::vector<std::vector<int>> tableQ;
    


};