#include "knuthEquivalence.hpp"

KnuthEquivalence::KnuthEquivalence(const std::string& fileName){
    RSK rsk (fileName); 
    this->colHeights = rsk.getShape();
    this->POrig = rsk.P;
    this->QOrig = rsk.Q;
    this->originalPermutation = rsk.permutation;
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

    for (int i = 0; i < rowSeq.size(); ++i) {
        int row = rowSeq[i];
        int step = i + 1; 
        table[row].push_back(step);
    }

    return table;
}

void KnuthEquivalence::algKnuthEquilvalence(){
    std::ifstream solFile("youngTables.txt");

    if (!solFile.is_open()) {
        std::cerr<<"Ошибка: файл youngTables.txt не удалось открыть!"<<std::endl;
        std::exit(1);
    }

    std::vector<std::vector<int>> allRowSeqs;
    std::string line;
    while (std::getline(solFile, line)) {
        std::istringstream ss(line);
        std::vector<int> rowSeq;
        int r;
        while (ss >> r) {
            rowSeq.push_back(r);
        }
        if (!rowSeq.empty()) {
            allRowSeqs.push_back(rowSeq);
        }
    }
    solFile.close();

    int n = this->originalPermutation.size();

    std::set<std::vector<int>> knuthClass; 

    auto saveTableToFile = [](const std::string& fname, const std::vector<std::vector<int>>& T) {
        std::ofstream f(fname);
        if (!f.is_open()) {
            std::cerr<<"Ошибка: файл " << fname << " не удалось открыть!"<<std::endl;
            std::exit(1);
        }
        for (int x = 0; x < T.size(); ++x) {
            for (int y = 0; y < T[x].size(); ++y) {
                f << x << " " << y << " " << T[x][y] << std::endl;
            }
        }
        f.close();
    };

    for (const std::vector<int>& rowSeq : allRowSeqs) {
        auto QNew = this->convertRowSequenceToCells(rowSeq); 

        saveTableToFile("PTmp.txt", this->POrig);
        saveTableToFile("QTmp.txt", QNew);

        ReverseRSK rev("PTmp.txt", "QTmp.txt");
        auto perm = rev.algReverseRSK();
        
        knuthClass.insert(perm);
    }

    std::ofstream knuthFile("knuth.txt");

    for (const auto& p : knuthClass) {
        for (int i = 0; i < p.size(); ++i) {
            if (i > 0) knuthFile << " ";
            knuthFile << p[i];
        }
        knuthFile << std::endl;
    }
    knuthFile.close();
}