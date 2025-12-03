#include "reverseRSK.hpp"


ReverseRSK::ReverseRSK(const std::string& fileNameP, const std::string& fileNameQ){
    tableCell maxQCell;
    this->tableP = loadTableFromFile(fileNameP, maxQCell, false);
    this->tableQ = loadTableFromFile(fileNameQ, maxQCell, true);
}


std::vector<std::vector<int>> ReverseRSK::loadTableFromFile(const std::string& fileName, tableCell& maxQCell, bool loadQPositions){
    std::ifstream file(fileName);

    if (!file.is_open()){
        std::cerr<<"Ошибка: файл "<<fileName<<" не удалось открыть!"<<std::endl;
        std::exit(1);
    }

    std::vector<std::vector<int>> grid;
    std::vector<tableCell> cellsList;
    int maxCellValue = 0;
    int maxRow = 0;

    std::string line;
    while(std::getline(file,line)){
        std::istringstream ss(line);
        tableCell newCell;
        
        ss >> newCell.x >> newCell.y >> newCell.value;
        cellsList.push_back(newCell);

        if(newCell.value > maxCellValue) maxCellValue = newCell.value; 

        if(newCell.x > maxRow){
            maxRow = newCell.x;
            maxQCell = newCell; 
        };
    }

    file.close();

    grid.resize(maxRow + 1);
    std::vector<int> rowWidths(maxRow + 1, 0);

    for(const tableCell& cell : cellsList){
        if(cell.y + 1 > rowWidths[cell.x]) rowWidths[cell.x] = cell.y + 1;
    }

    for(int i = 0; i <= maxRow; ++i){
        grid[i].assign(rowWidths[i], -1);
    }

    if (loadQPositions){
        for(const tableCell& cell : cellsList){
            grid[cell.x][cell.y] = cell.value;
            this->qPos[cell.value] = std::make_pair(cell.x, cell.y);
        }

        return grid;
    }
    
    for(const tableCell& cell : cellsList){
        grid[cell.x][cell.y] = cell.value;
    }

    return grid;
}