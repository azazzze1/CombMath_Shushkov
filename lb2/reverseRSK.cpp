#include "reverseRSK.hpp"

ReverseRSK::ReverseRSK(const std::string& fileNameP, const std::string& fileNameQ){
    tableCell maxQCell;
    this->tableP = loadTableFromFile(fileNameP, false);
    this->tableQ = loadTableFromFile(fileNameQ, true);
}


std::vector<std::vector<int>> ReverseRSK::loadTableFromFile(const std::string& fileName, bool loadQPositions){
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


std::vector<int> ReverseRSK::algReverseRSK(){
    int permutationSize = this->qPos.size();

    this->permutation.resize(permutationSize); 

    std::vector<std::vector<int>> P = this->tableP;

    for(int i = permutationSize; i >= 1; --i){
        std::pair<int, int> pos = qPos.at(i);
        int row = pos.first;
        int col = pos.second;

        int x = P[row][col];
        P[row][col] = -1;

        while(row > 0){
            int prewRow = row - 1;
            int bestCol = -1;

            for(int j = 0; j < P[prewRow].size(); ++j){
                if(P[prewRow][j] != -1 && P[prewRow][j] < x){
                    if(bestCol == -1 || P[prewRow][j] > P[prewRow][bestCol]){
                        bestCol = j; 
                    }
                }
            }
            if(bestCol == -1){
                std::cerr<<"Некорректная таблица Юнга!"<<std::endl;
                std::exit(1); 
            }

            int temp = P[prewRow][bestCol];
            P[prewRow][bestCol] = x;
            x = temp;
            row = prewRow;
            col = bestCol;
        }

        this->permutation[i-1] = x;
        
    }

    return permutation; 
}
