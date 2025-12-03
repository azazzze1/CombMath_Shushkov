#include "RSK.hpp"

RSK::RSK(const std::string& fileName){
    std::ifstream file(fileName);

    if (!file.is_open()){
        std::cerr<<"Ошибка: файл "<<fileName<<" не удалось открыть!"<<std::endl;
        std::exit(1);
    }

    std::string line;
    std::getline(file, line); 
    file.close();

    std::istringstream ss(line);
    
    int n;
    while(ss >> n){
        this->permutation.push_back(n); 
    }

    this->algRSK();

    this->saveTableToFile("pTable.txt", this->P);
    this->saveTableToFile("qTable.txt", this->Q);
}


void RSK::algRSK(){
    this->P.clear();
    this->Q.clear();
    this->shape.clear();

    if (this->permutation.empty()) return;

    int n = permutation.size();

    for (int i = 0; i < n; ++i) {
        int value = permutation[i];
        int step = i + 1;

        int bumped = value;
        int row = 0;

        while (bumped != -1) {
            if (row >= P.size()) {
                P.push_back({});
                Q.push_back({});
            }

            std::vector<int>& pRow = P[row];
            std::vector<int>& qRow = Q[row];

            auto it = std::lower_bound(pRow.begin(), pRow.end(), bumped);
            int pos = static_cast<int>(it - pRow.begin());

            if (pos == static_cast<int>(pRow.size())) {
                pRow.push_back(bumped);
                qRow.push_back(step);
                bumped = -1;
            } else {
                int temp = pRow[pos];
                pRow[pos] = bumped;
                bumped = temp;
                row++;
            }
        }
    }

    for (std::vector<std::vector<int>>::const_iterator rit = P.begin(); rit != P.end(); ++rit) {
        shape.push_back(static_cast<int>(rit->size()));
    }
}


void RSK::saveTableToFile(const std::string& fileName, const std::vector<std::vector<int>>& table){
    std::ofstream file(fileName);
    if (!file) {
        std::cerr<<"Ошибка: файл "<<fileName<<" не удалось открыть!"<<std::endl;
        std::exit(1); 
    }

    for (int y = 0; y < table.size(); ++y) {
        for (int x = 0; x < table[y].size(); ++x) {
            file << y << " " << x << " " << table[y][x] << "\n";
        }
    }
    file.close();
}
