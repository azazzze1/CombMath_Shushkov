#include "knuthEquivalence.hpp"

KnuthEquivalence::KnuthEquivalence(const std::string& fileName){
    RSK rsk (fileName); 
    this->colHeights = rsk.getShape();
    this->writeColHeightsToFile();

    Solution youngTableGenerator ("shape.txt");
    youngTableGenerator.writeSolutionToFile(); 

    ReverseRSK revRSK ("pTable.txt", "qTable.txt");

    this->algKnuthEquilvalence(); 
}

void KnuthEquivalence::writeColHeightsToFile(){
    std::ofstream file("shape.txt");
    if (!file.is_open()) {
        std::cerr<<"Ошибка: файл shape.txt не удалось открыть!"<<std::endl;
        std::exit(1);
    }

    for (int i = 0; i < this->colHeights.size(); ++i) {
        if (i > 0) file << " ";
        file << this->colHeights[i];
    }

    file << std::endl;
    file.close();
}

std::vector<std::vector<int>> KnuthEquivalence::convertRowSequenceToCells(const std::vector<int>& rowSeq){
    if (rowSeq.empty()) {
        return {};
    }

    int maxRow = *std::max_element(rowSeq.begin(), rowSeq.end());
    std::vector<std::vector<int>> table(maxRow + 1);

    for (int i = 0; i < static_cast<int>(rowSeq.size()); ++i) {
        int row = rowSeq[i];
        int step = i + 1; 
        table[row].push_back(step);
    }

    return table;
}